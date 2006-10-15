//-----------------------------------------------------------------------------
// MEKA - vdp.c
// TMS9918/28 Accesses and Registers Handling - Code
//-----------------------------------------------------------------------------

#include "shared.h"
#include "vdp.h"
#include "debugger.h"
#include "palette.h"
#include "video_m2.h"

//#define DEBUG_VDP
//#define DEBUG_VDP_DATA

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

// VDP Models Differences Table -----------------------------------------------
// MODELS                               315-5124  315-5226  315-5378  315-5313
// Machines                             M3,SMS    SMS/SMS2  GG        MD
//-----------------------------------------------------------------------------
// TMS9918 video modes                  Yes       Yes       Yes       No
// 224-Lines Mode                       ??        ??        ??        ??
// 240-Lines Mode                       ??        ??        ??        ??
// Bits 0-4 of Status Register          ??        Garbage   ??        MD data
// Bit 0 of Register 2 apply a mask     Yes       ??        No        No
// Bit 7 of Register 1 (VRAM Size)      ??        ??        ??        ??
// Zoomed Sprites Bug (+4 per Lines)    Yes       No        No        ??
// Writing data port update read buf.   ??        Yes       ??        Yes
// Palette write if only bit 1 is set   ??        ??        ??        Yes
// First address byte is latched        ??        No        ??        Yes
// Writing to Register update address   ??        ??        ??        ??
//-----------------------------------------------------------------------------
// Note: not everything is implemented as on this table.
//-----------------------------------------------------------------------------

static u8   VDP_Mask [10] [2] =
{
  /* 0 */ { 0x00, /*0x3F*/ 0x07 },
  /* 1 */ { 0xFF, /*0x3F*/ 0x07 },
  /* 2 */ { 0x80, /*0x3C*/ 0x04 },
  /* 3 */ { 0x00, /*0x07*/ 0x3F },
  /* . */ { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }
};

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

int     VDP_Model_FindByName(const char *name)
{
    if (!strcmp(name, "315-5124"))
        return (VDP_MODEL_315_5124);
    else if (!strcmp(name, "315-5226"))
        return (VDP_MODEL_315_5226);
    else if (!strcmp(name, "315-5378"))
        return (VDP_MODEL_315_5378);
    else if (!strcmp(name, "315-5313"))
        return (VDP_MODEL_315_5313);
    return (-1);
}

void    VDP_VideoMode_Change (void)
{
    int   i;

    if (tsms.VDP_Video_Change & VDP_VIDEO_CHANGE_MODE)
    {
        //Msg (MSGT_DEBUG, "Line %d. Change video mode %d -> %d (bits = %d)",
        //     tsms.VDP_Line, tsms.VDP_VideoMode, tsms.VDP_New_VideoMode, ((sms.VDP[0] & 0x06) >> 1) | ((sms.VDP[1] & 0x18) >> 1));
        tsms.VDP_VideoMode = tsms.VDP_New_VideoMode;
        if (tsms.VDP_VideoMode <= 3)
        {
            if (cur_drv->id == DRV_SMS)
                drv_set (DRV_SG1000);
        }
        else
        {
            drv_set (cur_machine.driver_id); // Revert back to original driver
        }
        Update_Line_Start_End ();
        Machine_Set_Handler_Loop ();
        Palette_Emulation_Reload ();
        for (i = 0; i < 16; i ++)
            Tms_VDP_Out (i, sms.VDP [i]);
    }

    if (tsms.VDP_Video_Change & VDP_VIDEO_CHANGE_SIZE)
    {
        if (cur_drv->id == DRV_SMS)
        {
            cur_drv->y_res = ((Wide_Screen_28) ? 224 : 192);
            gamebox_resize_all ();
            Update_Line_Start_End ();
            Video_Mode_Update_Size ();
            if (Meka_State == MEKA_STATE_FULLSCREEN)
            {
                Video_Clear ();
            }
        }
        else
        {
            Update_Line_Start_End ();
        }
    }
    tsms.VDP_Video_Change = 0x00;
}

void    VDP_VideoMode_Update (void)
{
  switch (((sms.VDP[0] & 0x06) >> 1) | ((sms.VDP[1] & 0x18) >> 1))
     {
      // Bits 0, 1 are bits 1, 2 in VDP Register 0
      // Bits 3, 4 are bits 3, 4 in VDP Register 1
      case 0x08: /* 10.00 */ tsms.VDP_New_VideoMode = 0; break;
      case 0x00: /* 00.00 */ tsms.VDP_New_VideoMode = 1; break;
      case 0x01: /* 00.01 */ tsms.VDP_New_VideoMode = 2; break;
      case 0x04: /* 01.00 */ tsms.VDP_New_VideoMode = 3; break;
      case 0x02: /* 00.10 */ tsms.VDP_New_VideoMode = 4; break;
      case 0x03: /* 00.11 */ tsms.VDP_New_VideoMode = 5; break;
      case 0x0A: /* 10.10 */ tsms.VDP_New_VideoMode = 9; break; // ?
      // default: Msg (MSGT_DEBUG, "Error #42 - Unknown video mode %d - Please contact me", ((sms.VDP[0] & 0x06) >> 1) | ((sms.VDP[1] & 0x18) >> 1));
     }
  if (tsms.VDP_VideoMode != tsms.VDP_New_VideoMode)
     {
     tsms.VDP_Video_Change |= VDP_VIDEO_CHANGE_MODE;
     // Msg (MSGT_DEBUG, "Change video mode, %d -> %d", tsms.VDP_VideoMode, tsms.VDP_New_VideoMode);
     }
}

// WRITE A VALUE TO A VDP REGISTER --------------------------------------------
void    Tms_VDP_Out (int vdp_register, int value)
{
  #ifdef DEBUG_VDP
    Msg (MSGT_DEBUG, "At PC=%04X: VDP Reg[%d] = %02X", CPU_GetPC, vdp_register, value);
  #endif

  switch (vdp_register)
    {
     // VDP Configuration 0 ---------------------------------------------------
     case 0: if ((value & 0x20) != Mask_Left_8)
                {
                // FIXME
                if (Meka_State == MEKA_STATE_FULLSCREEN && LightGun.Enabled)
                   LightGun_Mouse_Range (value & 0x20);
                }
             /*
             if ((Value & 0x10) != HBlank_ON)
                {
                Msg (MSGT_DEBUG, "At PC=%04X, Line=%d, HBlank %s, IRequest = %02X", CPU_GetPC, tsms.VDP_Line, (Value & 0x10) ? "Enable" : "Disable", sms.R.IRequest);
                }
             */

             if ((sms.Need_HBlank) && ((HBlank_ON) != (value & 0x10)))
             {
                if (!(value & 0x10))
                   {
                   // Msg (MSGT_DEBUG, "At PC=%04X, Line=%d, disabling IE1 unasserted the Z80 IRQ Line", CPU_GetPC, tsms.VDP_Line);
                   sms.R.IRequest = INT_NONE;
                   }
                else
                   {
                   sms.R.IRequest = INT_IRQ;
                   }
             }

             sms.VDP [0] = value;
             cur_machine.VDP.sprite_shift_x = ((Sprites_Left_8) ? 8 : 0);
             VDP_VideoMode_Update ();
             // Msg (MSGT_DEBUG, "At PC=%04X, line=%d, VDP[0] = %02X", sms.R.PC.W, tsms.VDP_Line, value);
             return;

     // VDP Configuration 1 ---------------------------------------------------
     case 1: if ((value & 0x10) != Wide_Screen_28) // Wide just enabled/disabled
                tsms.VDP_Video_Change |= VDP_VIDEO_CHANGE_SIZE;
             /* if ((value & 0x40) != Display_ON)
                {
                Msg (MSGT_DEBUG, "At PC=%04X, Line=%d, Enable/Disable Display %02X", sms.R.PC.W, tsms.VDP_Line, value);
                sms.R.Trace = TRUE;
                } */
             sms.VDP [1] = value;
             // Sprite_Shift_Y = 0; // ((Wide_Screen_28) ? -16 : 0);
             // Sprite_Shift_Y = ((Wide_Screen_28 && cur_drv->id == DRV_GG) ? -16 : 0);
             VDP_VideoMode_Update ();
             // Msg (MSGT_DEBUG, "At PC=%04X, Line=%d, VDP[1] = %02X", sms.R.PC.W, tsms.VDP_Line, value);

             // Update tilemap/name table address accordingly
             if (cur_drv->vdp == VDP_SMSGG)
             {
                if (Wide_Screen_28)
                    BACK_AREA  = VRAM + 0x700 + (int)((sms.VDP[2] & 0xC) << 10); // 0x0700 -> 0x3700, 0x1000 increments
                else
                    BACK_AREA  = VRAM + (int)((sms.VDP[2] & 0xE) << 10); // 0x0000 -> 0x3800, 0x0800 increments
             }
             return;

     // Background/Foreground map address -------------------------------------
     case 2: switch (cur_drv->vdp)
                {
                case VDP_SMSGG:
                     if (Wide_Screen_28)
                         BACK_AREA  = VRAM + 0x700 + (int)((value & 0xC) << 10); // 0x0700 -> 0x3700, 0x1000 increments
                     else
                         BACK_AREA  = VRAM + (int)((value & 0xE) << 10); // 0x0000 -> 0x3800, 0x0800 increments
                     break;
                case VDP_TMS9918:
                     BACK_AREA = VRAM + (int)((value & /*0x7F*/ 0xF /*7*/) << 10);
                     break;
                }
             break;

     // TMS9918 register: contain bit 13 of the color table adress ------------
     case 3: SG_BACK_COLOR = VRAM + ((((int)(value & VDP_Mask[tsms.VDP_VideoMode][0]) << 6) + ((int)sms.VDP[10] << 14)) & 0x3FFF);
             break;

     // TMS9918 register: address of tile data --------------------------------
     case 4: SG_BACK_TILE = VRAM + ((int)(value & VDP_Mask[tsms.VDP_VideoMode][1]) << 11);
             break;

     // Sprite Attribute Table (SAT) address
     case 5: switch (cur_drv->vdp)
                {
                case VDP_SMSGG:
                     sprite_attribute_table = VRAM + (((int)value << 7) & 0x3F00);
                     break;
                case VDP_TMS9918:
                     sprite_attribute_table = VRAM + ((int)(value & 0x7F) << 7);
                     break;
                }
             break;

     // Sprite tile data address ----------------------------------------------
     case 6: 
         {
			 switch (cur_drv->vdp)
                {
                case VDP_SMSGG:
					cur_machine.VDP.sprite_pattern_base_index = (value & 4) ? 256 : 0;
					cur_machine.VDP.sprite_pattern_base_address = VRAM + ((value & 4) ? 0x2000 : 0x0000);
					break;
				case VDP_TMS9918:
		            cur_machine.VDP.sprite_pattern_base_address = VRAM + ((int)(value & 7) << 11);
                    break;
				}
             break;
         }

     // Border Color ----------------------------------------------------------
     case 7: if (cur_drv->vdp == VDP_TMS9918)
                Palette_Emulation_SetColor(0, TMS9918_Palette[value & 15]);
             break;

     // Horizontal Scrolling --------------------------------------------------
     case 8: if (CPU_GetICount() >= 8) 
                 cur_machine.VDP.scroll_x_latched = value;
             // Msg (MSGT_DEBUG, "%d @ ICount = % 3d, VDP[8] = %d", tsms.VDP_Line, CPU_GetICount(), value);
             break;

     // Vertical Scrolling ----------------------------------------------------
     //case 9: Msg (MSGT_DEBUG, "At PC=%04X, Line=%d: vscroll = %d", CPU_GetPC(), tsms.VDP_Line, value);
             // if ((Wide_Screen_28) && value > 224)
             //   {
             //   Msg (MSGT_DEBUG, "Error #9384: Please contact me if you see this message.");
             //   value = 224;
             //   }
     //        break;

     // TMS9918 register: contain bit 14-16 of the color table adress ---------
     // Else in video mode 5 contains number of line for H-Interrupt
     case 10: SG_BACK_COLOR = VRAM + ((((int)(sms.VDP[3] & VDP_Mask[tsms.VDP_VideoMode][0]) << 6) + ((int)(value & 0x07) << 14)) & 0x3FFF);
              // Msg (MSGT_DEBUG, "%d @ VDP[10] = %d", tsms.VDP_Line, value);
              break;
    }

    // Finally save to VDP Register state
    sms.VDP[vdp_register] = value;
}

void    Tms_VDP_Palette_Write(int addr, int value)
{
    RGB color;

    // Write to CRAM (currently named PRAM)
    PRAM [addr] = value;

    switch (cur_drv->id)
    {
    case DRV_GG:
        {
            // Sega Game Gear
            if (addr & 0x01) // Update only on second byte write
            {
                Palette_Compute_RGB_GG(&color, addr & 0xFE);
                Palette_Emulation_SetColor(addr >> 1, color);
            }
            return;
        }
    case DRV_SMS:
        {
            // Sega Master System
            Palette_Compute_RGB_SMS(&color, addr);
            Palette_Emulation_SetColor(addr, color);
            return;
        }
    }
}

void    Tms_VDP_Out_Data (int value)
{
    sms.VDP_Access_Mode = VDP_Access_Mode_1;
    if (sms.VDP_Pal == FALSE)
    {
        // VRAM write
        #ifdef DEBUG_VDP_DATA
            Msg (MSGT_DEBUG, "At PC=%04X: VDP[%04X] = %02X", CPU_GetPC, sms.VDP_Address, value);
        #endif
        VRAM [sms.VDP_Address] = sms.VDP_ReadLatch = value;

        // Debugger hook
        #ifdef MEKA_Z80_DEBUGGER
			if (Debugger.active)
				Debugger_WrVRAM_Hook(sms.VDP_Address, value);
		#endif

        // Mark corresponding tile as dirty
        tgfx.Tile_Dirty [sms.VDP_Address / 32] |= TILE_DIRTY_DECODE;

        // - Sylvantale patching: Catch writes to tile 265
        // if ((sms.VDP_Address / 32) == 265)
        //    Msg (MSG_USER, "%04X (%d): VDP[%04X] = %02X", CPU_GetPC, sms.Pages_Reg [0], sms.VDP_Address, value);
        // - Bart vs. the Space Mutants (GG)
        // if (sms.VDP_Address >= 0x3800 && sms.VDP_Address < 0x3F00)
        //    printf ("%04X: VDP[%04X] = %02X\n", CPU_GetPC, sms.VDP_Address, value);
        sms.VDP_Address = (sms.VDP_Address + 1) & 0x3FFF;
        return;
    }
    else
    {
        // Palette/CRAM write
        #ifdef DEBUG_VDP_DATA
            Msg (MSGT_DEBUG, "At PC=%04X: PRAM[%04X] = %02X", CPU_GetPC, sms.VDP_Address, value);
        #endif

        Tms_VDP_Palette_Write(sms.VDP_Address, value);

        // Debugger hook
        #ifdef MEKA_Z80_DEBUGGER
	        if (Debugger.active)
		        Debugger_WrPRAM_Hook(sms.VDP_Address, value);
		#endif

        // Increment VDP address
        switch (cur_drv->id)
        {
            case DRV_GG:    sms.VDP_Address = (sms.VDP_Address + 1) & 0x3F;    break;
            case DRV_SMS:   sms.VDP_Address = (sms.VDP_Address + 1) & 0x1F;    break;
            default:
                // Default is needed for F-16 Fighter / Fighting Falcon
                // (Maybe Back to the Future 2 ? I'm not sure)
                // Just increment CRAM address, but don't set the color entry now
                sms.VDP_Address = (sms.VDP_Address + 1) & 0x1F;
                break;
        }
    }
}

void    Tms_VDP_Out_Address (int value)
{
    // [DEBUG] Daffy Duck
    //if (CPU_GetPC == 0x7348)
    //{
    //   Msg (MSGT_DEBUG, "At PC=%04X: VDP Out: %02X", CPU_GetPC, Value);
    //   if (sms.VDP_Access_Mode != VDP_Access_Mode_1)
    //       if ((Value & 0xC0) == 0x80)
    //          Msg (MSGT_DEBUG, " -> (line %d) vreg[%d] = %02X ", tsms.VDP_Line, Value & 0x0F, sms.VDP_Access_First);
    //}

    if (sms.VDP_Access_Mode == VDP_Access_Mode_1)
    {
        #ifdef DEBUG_VDP
            Msg (MSGT_DEBUG, "At PC=%04X: VDP Address1: %02X", CPU_GetPC, value);
        #endif
        sms.VDP_Access_First = value;   // Latch
        sms.VDP_Access_Mode  = VDP_Access_Mode_2;
        // Fixes Cosmic Spacehead
        // FIXME: line above is not valid for 315-5124
        // We're keeping it as is now to speed up emulation a bit
        sms.VDP_Address = (sms.VDP_Address & 0xFF00) | value;
        // sms.VDP_Pal = FALSE;
        return;
    }

    // 00 : ?
    // 10 : VDP_Reg
    // 11 : Palette
    // 01 : Address
    // Msg (MSGT_DEBUG, "[%04X] VDP Set %02X,%02X", sms.R.PC.W,sms.VDP_Access_First, Value);

    #ifdef DEBUG_VDP
        Msg (MSGT_DEBUG, "At PC=%04X: VDP Address2: %02X", CPU_GetPC, value);
        // printf ("At PC=%04X: VDP Address2: %02X\n", CPU_GetPC, Value);
    #endif

    sms.VDP_Access_Mode = VDP_Access_Mode_1;
    if ((value & 0xC0) == 0xC0)
    {
        switch (cur_drv->id)
        {
        case DRV_GG:
            sms.VDP_Pal = TRUE;
            sms.VDP_Address = sms.VDP_Access_First & 0x3F;
            break;
        default: // needed for F-16 Fighters and Back to the Future 2
            sms.VDP_Pal = TRUE;
            sms.VDP_Address = sms.VDP_Access_First & 0x1F;
            break;
        }
    }
    //else
    //if ((Value & 0xF0) == 0x80)
    //      {
    //      Tms_VDP_Out (Value & 0x0F, sms.VDP_Access_First);
    //      }
    else
        // if ((Value & 0xC0) == 0x40)
    {
        if (value & 0x80)
            //((Value & 0xC0) == 0x80)
        {
            Tms_VDP_Out (value & 0x0F, sms.VDP_Access_First);
            // FIXME: clear last bit of value before setting address ?
        }
        sms.VDP_Pal = FALSE;
        sms.VDP_Address = (((word)value << 8) | sms.VDP_Access_First) & 0x3FFF;
        // if (sms.VDP_Address >= 0x8000)
        //    {
        //    Msg (MSGT_DEBUG, "[%04X] VDP Address %04X", sms.R.PC.W, sms.VDP_Address);
        //    }
        if ((value & 0xC0) == 0)
        { // Read Mode
            sms.VDP_ReadLatch = VRAM [sms.VDP_Address];
            sms.VDP_Address ++;
        }
    }
}

u8      Tms_VDP_In_Data (void)
{
    sms.VDP_Access_Mode = VDP_Access_Mode_1;
    // if (sms.VDP_Pal)
    //    {
    //    Msg (MSGT_DEBUG, "Error #7313 [Read from PRAM] - Please contact me.");
    //    return (0);
    //    }
    // else
    {
        u8 b = sms.VDP_ReadLatch;

        #ifdef DEBUG_VDP_DATA
            Msg (MSGT_DEBUG, "At PC=%04X: VDP Read, returning latched %02X", CPU_GetPC, b);
        #endif

        // Debugger hook
        #ifdef MEKA_Z80_DEBUGGER
	        if (Debugger.active)
		        Debugger_RdVRAM_Hook(sms.VDP_Address, b);
		#endif

        // Read next latch and increment address
        sms.VDP_ReadLatch = VRAM [sms.VDP_Address];
        sms.VDP_Address = (sms.VDP_Address + 1) & 0x3FFF;

        // Return latch
        return (b);
    }
}

u8          Tms_VDP_In_Status (void)
{
    u8      b;

    b = sms.VDP_Status;
    // Value &= 0xDF; // Disable sprite collisions
    sms.VDP_Status &= 0x1F; // Clear bits 5, 6, 7
    // sms.VDP_Status = 0x1F // FIXME: investigate on this!
    sms.VDP_Access_Mode = VDP_Access_Mode_1;
    sms.Need_HBlank = FALSE;
    #ifdef MARAT_Z80
        sms.R.IRequest = INT_NONE;
    #elif MAME_Z80
        z80_set_irq_line (0, CLEAR_LINE);
    #endif
    #ifdef DEBUG_VDP
        Msg (MSGT_DEBUG, "At PC=%04X: VDP Status Read, returning %02X", CPU_GetPC, b | 0x1F);
    #endif
    return (b | 0x1F);
    //return (b & 0xE0);
}

//-----------------------------------------------------------------------------

