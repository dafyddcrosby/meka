//-----------------------------------------------------------------------------
// MEKA - vmachine.c
// Virtual Machine - Code
//-----------------------------------------------------------------------------

#include "shared.h"
#include "app_game.h"
#include "bios.h"
#include "db.h"
#include "file.h"
#include "games.h"
#include "effects.h"
#include "skin_bg.h"

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void    VMachine_Draw (void)
{
    int    x, y;

    #ifdef DEBUG_WHOLE
        Msg (MSGT_DEBUG, "VMachine_Draw ();");
    #endif

    x = gui.info.screen.x;
    y = 0;
    switch (cur_drv->id)
    {
    case DRV_COLECO: //-------------- Draw a Colecovision ---------------------
        x += VMACHINE_COLECO_POS_X;
        y += VMACHINE_COLECO_POS_Y;
        draw_sprite (gui_background, Graphics.Machines.ColecoVision, x, y);
        break;
    default: //---------------------- Draw a Master System --------------------
        x += VMACHINE_SMS_POS_X;
        y += VMACHINE_SMS_POS_Y;
        draw_sprite (gui_background, Graphics.Machines.MasterSystem, x, y);
        if (machine & MACHINE_POWER_ON)
        {
            draw_sprite (gui_background, Graphics.Machines.MasterSystem_Light, x + VMACHINE_SMS_LIGHT_POS_X, y + VMACHINE_SMS_LIGHT_POS_Y);
        }
        if (machine & MACHINE_CART_INSERTED)
        {
            draw_sprite (gui_background, Graphics.Machines.MasterSystem_Cart, x + VMACHINE_SMS_CART_POS_X, y + VMACHINE_SMS_CART_POS_Y);
        }
        break;
    }
}

void    Machine_Init (void)
{
    machine = 0;
}

void    Machine_ON (void)
{
 #ifdef DEBUG_WHOLE
   Msg (MSGT_DEBUG, "Machine_ON()");
 #endif
 if (!(machine & MACHINE_POWER_ON))
    {
    machine |= MACHINE_POWER_ON;
    CPU_Loop_Stop = TRUE;
    Machine_Reset ();
    if (!(machine & MACHINE_ROM_LOADED))
       {
       #ifdef DEBUG_WHOLE
          Msg (MSGT_DEBUG, "Machine_ON() : BIOS_Load()");
       #endif
       BIOS_Load ();
       Machine_Remove_Cartridge ();
       }
    Skins_Background_Redraw();
    }
}

void    Machine_OFF (void)
{
    if (machine & MACHINE_POWER_ON)
    {
        BMemory_Save ();                    // Write Backed Memory if necessary
        game_running = GAME_RUNNING_NONE;   // No internal game is playing
        machine &= ~MACHINE_POWER_ON;       // Switch power Off
        CPU_Loop_Stop = TRUE;                // Setup flag to stop Z80 emulation
        Machine_Reset ();                   // Reset machine
        Skins_Background_Redraw();
        //effects.TV_Start_Line = 0;
        Effects_TV_Reset();
    }
}

void    Machine_Insert_Cartridge (void)
{
    machine |= MACHINE_CART_INSERTED;
    Skins_Background_Redraw();
}

void    Machine_Remove_Cartridge (void)
{
    if (machine & MACHINE_CART_INSERTED)
    {
        memset (Game_ROM, 0, tsms.Size_ROM);
    }
    machine &= ~MACHINE_CART_INSERTED;
    Skins_Background_Redraw();
}

void    Free_ROM (void)
{
    // Call BMemory_Save() only if Machine_Off() won't call it
    // FIXME: this is some crap hack, the whole machine thing need to be rewritten
    if (!(machine & MACHINE_POWER_ON))
        BMemory_Save ();
    Machine_OFF ();
    Machine_Remove_Cartridge ();
    machine = 0;
    if (Game_ROM)
    {
        free (Game_ROM);
        Game_ROM = NULL;
        tsms.Size_ROM = 0;
        DB_CurrentEntry = NULL;
        BIOS_Load ();
    }
    if (cur_machine.driver_id != DRV_COLECO && cur_machine.driver_id != DRV_NES)
        cur_machine.driver_id = DRV_SMS;
    Machine_Reset ();
    gamebox_rename_all ();
    Change_System_Misc ();

	// Clear filename data
    strcpy(g_Env.Paths.MediaImageFile, "");
    Filenames_Init_ROM();
}

//-----------------------------------------------------------------------------
