//-----------------------------------------------------------------------------
// MEKA - about.c
// About Box - Code
//-----------------------------------------------------------------------------

#include "shared.h"
#include "desktop.h"
#include "g_widget.h"
#include "inputs_t.h"
#include "app_about.h"

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

t_app_about_box     AboutBox;

//-----------------------------------------------------------------------------
// Forward Declaration
//-----------------------------------------------------------------------------

static void         AboutBox_Layout(bool setup);

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void    AboutBox_Switch (void)
{
#ifdef ARCH_DOS
    int menu_pos = 4;
#else
    int menu_pos = 5;
#endif

	AboutBox.active ^= 1;
	gui_box_show (AboutBox.box, AboutBox.active, TRUE);
    gui_menu_inverse_check (menus_ID.help, menu_pos);
}

static void     AboutBox_Layout(bool setup)
{
    t_app_about_box *app = &AboutBox;	// Global instance
	const int dragon_h = al_get_bitmap_height(Graphics.Misc.Dragon);

	al_set_target_bitmap(app->box->gfx_buffer);
    al_clear_to_color(COLOR_SKIN_WINDOW_BACKGROUND);

    if (setup)
    {
        // Add closebox widget
        widget_closebox_add(app->box, AboutBox_Switch);
    }

    // Draw MEKA dragon sprite
	al_draw_bitmap(Graphics.Misc.Dragon, 10, (app->box->frame.size.y - dragon_h) / 2, 0);

	// Print about information lines
	{
		int i;
		int y = 9;
		Font_SetCurrent(F_LARGE);
		for (i = 0; i < 4; i ++)
		{
			int x;
			char buffer[256];
			switch (i)
			{
			case 0: snprintf(buffer, countof(buffer), Msg_Get(MSG_About_Line_Meka_Date), MEKA_NAME_VERSION, MEKA_DATE); break;
			case 1: snprintf(buffer, countof(buffer), Msg_Get(MSG_About_Line_Authors), MEKA_AUTHORS_SHORT); break;
			case 2: snprintf(buffer, countof(buffer), Msg_Get(MSG_About_Line_Homepage), MEKA_HOMEPAGE); break;
			case 3: snprintf(buffer, countof(buffer), "Built %s, %s", MEKA_BUILD_DATE, MEKA_BUILD_TIME); break;
			}
			x = (( (app->box->frame.size.x - dragon_h - 18 - 6) - Font_TextLength (-1, buffer) ) / 2) + dragon_h + 8 + 6;
			Font_Print(-1, app->box->gfx_buffer, buffer, x, y, COLOR_SKIN_WINDOW_TEXT);
			y += Font_Height(-1) + 3;
		}
	}
}

void            AboutBox_Init (void)
{
    t_app_about_box *app = &AboutBox;	// Global instance

    t_frame frame;
	frame.pos.x = 285;
	frame.pos.y = 60;
	frame.size.x = 346;
	frame.size.y = 93;
    app->box = gui_box_new(&frame, Msg_Get(MSG_About_BoxTitle));
	Desktop_Register_Box("ABOUT", app->box, 0, &AboutBox.active);

    // Layout
    AboutBox_Layout(TRUE);
}

void        AboutBox_Update()
{
    // Skip update if not active
    if (!AboutBox.active)
        return;

    // If skin has changed, redraw everything
    if (AboutBox.box->flags & GUI_BOX_FLAGS_DIRTY_REDRAW_ALL_LAYOUT)
    {
        AboutBox_Layout(FALSE);
        AboutBox.box->flags &= ~GUI_BOX_FLAGS_DIRTY_REDRAW_ALL_LAYOUT;
    }
}

//-----------------------------------------------------------------------------

