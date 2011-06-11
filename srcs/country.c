//-----------------------------------------------------------------------------
// MEKA - country.c
// Country / Nationalization - Code
//-----------------------------------------------------------------------------

#include "shared.h"
#include "app_filebrowser.h"
#include "app_game.h"

//-----------------------------------------------------------------------------

// Also see stuff in CONFIG.C
// Note that country handling is quite weird because:

// If you have country in EUR/US mode, for example, and start
// Meka with /JAP it will run in JAP mode, but will keep your
// configuration in EUR/US unless you manually click on JAP.
// This is very useful, user wise.
// And that's the reason for _CL (CommandLine) stuff, too.

//-----------------------------------------------------------------------------

void    Set_Country_European_US (void)
{
    Msg (MSGT_USER, Msg_Get (MSG_Country_European_US));
    if (g_machine_flags & MACHINE_POWER_ON)
        Msg (MSGT_USER_BOX, Msg_Get (MSG_Must_Reset));
    g_Configuration.country = g_Configuration.country_cfg = COUNTRY_EXPORT;
    gui_menu_un_check (menus_ID.country);
    gui_menu_check (menus_ID.country, 0);

    // Set emulation country
    sms.Country = g_Configuration.country;

    // Update game boxes name and file browser
    gamebox_rename_all ();
    FB_Reload_Names ();
}

void    Set_Country_JP (void)
{
    Msg (MSGT_USER, Msg_Get (MSG_Country_JAP));
    if (g_machine_flags & MACHINE_POWER_ON)
        Msg (MSGT_USER_BOX, Msg_Get (MSG_Must_Reset));
    g_Configuration.country = g_Configuration.country_cfg = COUNTRY_JAPAN;
    gui_menu_un_check (menus_ID.country);
    gui_menu_check (menus_ID.country, 1);

    // Set emulation country
    sms.Country = g_Configuration.country;

    // Update game boxes name and file browser
    gamebox_rename_all ();
    FB_Reload_Names ();
}

void    Nationalize (byte *v)
{
    if (sms.Country == COUNTRY_EXPORT)
        if ((tsms.Periph_Nat & 0xF) == 0x5)
        {
            if ((tsms.Periph_Nat & 0xF0) == 0xF0)
            {
                *v |= 0xC0; // set bits 6 and 7
            }
            else
            {
                *v &= 0x3F; // clear bits 6 and 7
            }
        }
}

// INITIALIZE COUNTRY ---------------------------------------------------------
void    Country_Init (void)
{
    if (g_Configuration.country_cl != COUNTRY_AUTO)
        g_Configuration.country = g_Configuration.country_cl;
    else
        g_Configuration.country = g_Configuration.country_cfg;
}

//-----------------------------------------------------------------------------

