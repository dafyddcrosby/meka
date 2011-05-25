//-----------------------------------------------------------------------------
// MEKA - techinfo.c
// Technical Information Applet - Code
//-----------------------------------------------------------------------------
// TO DO:
//  - re do.
//-----------------------------------------------------------------------------

#include "shared.h"
#include "app_techinfo.h"
#include "desktop.h"
#include "debugger.h"
#include "g_widget.h"
#include "vdp.h"

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

t_app_tech_info TechInfo;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

static void TechInfo_Layout(t_app_tech_info *app, bool setup)
{
    // Clear
	al_set_target_bitmap(app->box->gfx_buffer);
    al_clear_to_color(COLOR_SKIN_WINDOW_BACKGROUND);

    if (setup)
    {
        // Add closebox widget
        widget_closebox_add(app->box, (t_widget_callback)TechInfo_Switch);
    }
}

void        TechInfo_Init (void)
{
    int    i;
    t_frame frame;

    frame.pos.x = 150;
    frame.pos.y = 382;
    frame.size.x = TECHINFO_COLUMNS * Font_TextLength(F_MIDDLE, " ");
    frame.size.y = TECHINFO_LINES * Font_Height(F_MIDDLE);
    
    TechInfo.active = FALSE;

    TechInfo.box = gui_box_new(&frame, Msg_Get(MSG_TechInfo_BoxTitle));
    Desktop_Register_Box("TECHINFO", TechInfo.box, 0, &TechInfo.active);
    TechInfo.box->update = TechInfo_Update;

    // Layout
    TechInfo_Layout(&TechInfo, TRUE);

    // Clear lines
    for (i = 0; i != TECHINFO_LINES; i++)
    {
        strcpy(TechInfo.lines[i], "");
        TechInfo.lines_dirty[i] = TRUE;
    }
}

static void TechInfo_Redraw(t_app_tech_info *app)
{
    int i;
    bool dirty = FALSE;

    for (i = 0; i != TECHINFO_LINES; i++)
    {
        if (app->lines_dirty[i])
        {
            const int h = Font_Height (F_MIDDLE);
            const int y = (h * i);

			al_set_target_bitmap(app->box->gfx_buffer);
            al_draw_filled_rectangle(0, y, app->box->frame.size.x+1, y + h, COLOR_SKIN_WINDOW_BACKGROUND);
            Font_Print(F_MIDDLE, app->box->gfx_buffer, app->lines[i], 4, y, COLOR_SKIN_WINDOW_TEXT);

            app->lines_dirty[i] = FALSE;
            dirty = TRUE;
        }
    }

    if (dirty)
        app->box->flags |= GUI_BOX_FLAGS_DIRTY_REDRAW;
}

// UPDATE ONE LINE ------------------------------------------------------------
static void TechInfo_SetLine(t_app_tech_info *app, const char *line, int line_idx)
{
    // If line hasn't changed, ignore the update
    if (strcmp(TechInfo.lines[line_idx], line) == 0)
        return;

    // Copy new line, set dirty flag
    strncpy(TechInfo.lines[line_idx], line, sizeof(TechInfo.lines[line_idx])/sizeof(*TechInfo.lines[line_idx]));
    TechInfo.lines_dirty[line_idx] = TRUE;
}

// UPDATE TECHNICAL INFORMATIONS APPLET ---------------------------------------
void        TechInfo_Update(void)
{
    t_app_tech_info *app = &TechInfo;   // Global instance

    char    line[512];
    int     line_idx = 0;

    // Skip update if not active
    if (!app->active)
        return;

    // If skin has changed, redraw everything
    if (app->box->flags & GUI_BOX_FLAGS_DIRTY_REDRAW_ALL_LAYOUT)
    {
        int i;
        TechInfo_Layout(app, FALSE);
        app->box->flags &= ~GUI_BOX_FLAGS_DIRTY_REDRAW_ALL_LAYOUT;
        for (i = 0; i != TECHINFO_LINES; i++)
            TechInfo.lines_dirty[i] = TRUE;
    }

    sprintf (line, "   [MODE] %s (%s)", cur_drv->full_name, cur_drv->short_name);
    TechInfo_SetLine(app, line, line_idx++);

    // Sega 8-bit

    // - VDP
    {
        char model_str[9];
        switch (cur_machine.VDP.model)
        {
        case VDP_MODEL_315_5124: sprintf(model_str, "315-5124"); break;
        case VDP_MODEL_315_5226: sprintf(model_str, "315-5226"); break;
        case VDP_MODEL_315_5378: sprintf(model_str, "315-5378"); break;
        case VDP_MODEL_315_5313: sprintf(model_str, "315-5313"); break;
        default: assert(0); break;
        }
        sprintf (line, "    [VDP] Model:%s - Display Mode:%d",
            model_str, tsms.VDP_VideoMode);
        TechInfo_SetLine(app, line, line_idx++);
        sprintf (line, "    [VDP] Status:$%02X - Address:$%04X - Latch:$%02X - IE0:%d - IE1:%d - DIS:%d",
            sms.VDP_Status, sms.VDP_Address, sms.VDP_Access_First,
            (VBlank_ON?1:0), (HBlank_ON?1:0), (Display_ON?1:0));
        TechInfo_SetLine(app, line, line_idx++);
    }

    // - Scroll
    {
        sprintf (line, " [SCROLL] X:$%02X - Y:$%02X - LeftColumnBlank:%d - HSI:%d - VSI:%d",
            sms.VDP[8], sms.VDP[9], (Mask_Left_8?1:0), (Top_No_Scroll?1:0), (Right_No_Scroll?1:0));
        TechInfo_SetLine(app, line, line_idx++);
    }

    // - Sprites
    {
        sprintf (line, "[SPRITES] Size:%s - Double:%d - EarlyClock:%d - SAT:$%04X - SPG:$%04X",
            (Sprites_8x16?"8x16":"8x8"), (Sprites_Double?1:0), (Sprites_Left_8?1:0), (int)(sprite_attribute_table - VRAM), (int)(cur_machine.VDP.sprite_pattern_base_address - VRAM));
        TechInfo_SetLine(app, line, line_idx++);
    }

    // - Inputs
    {
        sprintf (line, " [INPUTS] PortDE:$%02X - Port3F:$%02X - Joy:$%04X - GG:$%02X - Paddle:$%02X,$%02X",
            (sms.Input_Mode), (tsms.Periph_Nat), tsms.Control[7], (tsms.Control_GG), (Inputs.Paddle_X [PLAYER_1]), (Inputs.Paddle_X [PLAYER_2]));
        TechInfo_SetLine(app, line, line_idx++);
    }

    // - Various
    {
#ifdef MEKA_Z80_DEBUGGER
        if (Debugger.enabled && Debugger.active)
            sprintf (line, "[VARIOUS] Country:%s - Border:%d - IPeriod:%d/%d - Lines:%d/%d",
            (sms.Country==COUNTRY_EXPORT)?"Export":"Japan", (sms.VDP[7] & 15), CPU_GetICount(), CPU_GetIPeriod(), tsms.VDP_Line, cur_machine.TV_lines);
        else
#endif
            sprintf (line, "[VARIOUS] Country:%s - Border:%d - IPeriod:%d - Lines:%d",
            (sms.Country==COUNTRY_EXPORT)?"Export":"Japan", (sms.VDP[7] & 15), CPU_GetIPeriod(), cur_machine.TV_lines);
        TechInfo_SetLine(app, line, line_idx++);
    }

    // - TMS9918
    {
        sprintf(line, "[TMS9918] Name:%04X - Color:%04X - Pattern:%04X - SPG:%04X", 
		    (int)(BACK_AREA - VRAM), (int)(SG_BACK_COLOR - VRAM), (int)(SG_BACK_TILE - VRAM), (int)(cur_machine.VDP.sprite_pattern_base_address - VRAM));
        TechInfo_SetLine(app, line, line_idx++);
    }

    // - PSG
    {
        t_psg *psg = &PSG;
        sprintf (line, "    [PSG] Tone 0: %03X,%01X  Tone 1: %03X,%01X  Tone 2: %03X,%01X  Noise:%02X,%01X (%s)",
            psg->Registers[0], psg->Registers[1], psg->Registers[2], psg->Registers[3],
            psg->Registers[4], psg->Registers[5], psg->Registers[6], psg->Registers[7],
            ((psg->Registers[6] & 0x04) ? "White" : "Periodic"));
        TechInfo_SetLine(app, line, line_idx++);
    }

    // - Memory
    {
        sprintf (line, " [MEMORY] Mapper:%d - Control:$%02X - F0:%02X - F1:%02X - F2:%02X - Pages:[%d/%d][%d/%d]",
            (cur_machine.mapper), (sms.Mapping_Register), (sms.Pages_Reg[0]), (sms.Pages_Reg[1]), (sms.Pages_Reg[2]), (tsms.Pages_Count_8k), (tsms.Pages_Mask_8k), (tsms.Pages_Count_16k), (tsms.Pages_Mask_16k));
        TechInfo_SetLine(app, line, line_idx++);
    }

    // Blank left lines
    while (line_idx < TECHINFO_LINES)
        TechInfo_SetLine(app, "", line_idx++);

    // Redraw
    TechInfo_Redraw(app);
}

void    TechInfo_Switch (void)
{
    if (TechInfo.active ^= 1)
        Msg (MSGT_USER, Msg_Get(MSG_TechInfo_Enabled));
    else
        Msg (MSGT_USER, Msg_Get(MSG_TechInfo_Disabled));
    gui_box_show(TechInfo.box, TechInfo.active, TRUE);
    gui_menu_inverse_check(menus_ID.tools, 5);
}

//-----------------------------------------------------------------------------

