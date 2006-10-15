//-----------------------------------------------------------------------------
// MEKA - bios.c
// Interface with the Master System BIOS ROMs - Code
//-----------------------------------------------------------------------------

#include "shared.h"
#include "bios.h"

//-----------------------------------------------------------------------------
// BIOS_Switch_to_Game (void)
// Switch from loaded BIOS to ROM
//-----------------------------------------------------------------------------
void    BIOS_Switch_to_Game (void)
{
  BIOS_Unload ();
  Machine_Reset ();
}

//-----------------------------------------------------------------------------
// BIOS_Unload (void)
// Unload BIOS ROM and replace with Game ROM
//-----------------------------------------------------------------------------
void    BIOS_Unload (void)
{
  ROM = Game_ROM;
  machine |= MACHINE_NOT_IN_BIOS;
}

//-----------------------------------------------------------------------------
// BIOS_Load (void)
// Load BIOS ROM
//-----------------------------------------------------------------------------
void    BIOS_Load (void)
{
    if (sms.Country == COUNTRY_JAP)
    {
        ROM = BIOS_ROM_Jap;
    }
    else
    {
        ROM = BIOS_ROM;
    }
    cur_machine.driver_id = DRV_SMS;
    Machine_Reset ();
}

//-----------------------------------------------------------------------------
// BIOS_Free_Roms (void)
// Free memory used by BIOS ROMs
//-----------------------------------------------------------------------------
void    BIOS_Free_Roms (void)
{
  // FIXME: aren't the data released by Allegro datafile routines ?!
  // free (Bios_ROM);
  // free (Bios_ROM_Jap);
  // free (Bios_ROM_Coleco);
  // free (Bios_ROM_Sf7000);
}

//-----------------------------------------------------------------------------

