//-----------------------------------------------------------------------------
// MEKA - bios.h
// Interface with the Master System BIOS ROMs - Headers
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

byte *  BIOS_ROM;
byte *  BIOS_ROM_Jap;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void    BIOS_Load (void);
void    BIOS_Unload (void);
void    BIOS_Switch_to_Game (void);
void    BIOS_Free_Roms (void);

//-----------------------------------------------------------------------------

