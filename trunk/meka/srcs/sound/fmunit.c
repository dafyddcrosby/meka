//
// Meka - FMUNIT.C
// FM Unit - Miscellaneous & wrapper to emulators
//

#include "shared.h"

//-----------------------------------------------------------------------------

// Registers (pointer to current FM emulator register)
byte *                  FM_Regs = NULL;

// Flag telling weither seems to be used or not
int                     FM_Used = FALSE;

// Interface
void                    FM_Null_Interface_Function(void) { }
t_fm_unit_interface     FM_Null_Interface =
{
  "FM Null Interface",
  "<none>",
  FM_Null_Interface_Function,
  (void (*)(int, int))FM_Null_Interface_Function,
  FM_Null_Interface_Function,
  FM_Null_Interface_Function,
  FM_Null_Interface_Function
};

t_fm_unit_interface *   FM_Unit_Current = &FM_Null_Interface;

//-----------------------------------------------------------------------------

// Instruments Name (strings)
const char *FM_Instruments_Name[YM2413_INSTRUMENTS] =
{
  "User Voice",
  "Violin",
  "Guitar",
  "Piano",
  "Flute",
  "Clarinet",
  "Oboe",
  "Trumpet",
  "Organ",
  "Horn",
  "Synthesizer",
  "Harpsichord",
  "Vibraphone",
  "Synthetizer bass",
  "Acoustic bass",
  "Electric bass",
};

//-----------------------------------------------------------------------------

// Mask of Registers data to save for a state save
const byte      FM_Regs_SavingFlags [YM2413_REGISTERS] =
{
  // Registers
  // 00-07: user-definable tone channel - left at 0xff for now
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  // 0E:    rhythm mode control - only bit 5 since rest are unused/keys
  0,    0,    0,    0,    0,    0,    0x20, 0,
  // 10-18: tone F-number low bits - want all bits
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  // 19-1F: not needed
  0,    0,    0,    0,    0,    0,    0,
  // 20-28: tone F-number high bit, octave set, "key" & sustain
  //      0x3f = all
  //      0x2f = all but key
  //      0x1f = all but sustain
  //      0x0f = all but key and sustain
  0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
  // 29-2F: not needed
  0,    0,    0,    0,    0,    0,    0,
  // 30-38: instrument number/volume - want all bits
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  // 39: not needed
  0
};

//-----------------------------------------------------------------------------
// FM_Set_Interface()
// Active given interface
//-----------------------------------------------------------------------------
void    FM_Set_Interface (t_fm_unit_interface *intf, byte *new_fm_regs)
{
  if (FM_Unit_Current)
     FM_Mute ();

  if ((new_fm_regs != FM_Regs) && FM_Regs)
     {
     // Msg (MSGT_DEBUG, "%s: Copying FM registers...", __FUNCTION__);
     memcpy (new_fm_regs, FM_Regs, YM2413_REGISTERS);
     }

  FM_Unit_Current = intf;
  FM_Regs = new_fm_regs;
  FM_Regenerate ();
}

//-----------------------------------------------------------------------------
// FM_Null_Active()
// Active the fake/null FM interface
// FIXME: theorically this should never be called now. Need to assert there.
//-----------------------------------------------------------------------------
void    FM_Null_Active (void)
{
  // FIXME: currently using FM_OPL_Regs as a buffer to avoid crashing in
  // access to the registers (by applet, etc...).
  FM_Set_Interface (&FM_Null_Interface, FM_OPL_Regs);
}

//-----------------------------------------------------------------------------
// FM_Used_Check()
// Compute weither the FM Unit seems to be used or not
//-----------------------------------------------------------------------------
void    FM_Used_Check (void)
{
  int   i;

  if (FM_Regs)
     for (i = 0; i < YM2413_REGISTERS; i++)
        if (FM_Regs[i] != 0x00)
           {
           FM_Used = 60;
           return;
           }
  FM_Used = FALSE;
}

//-----------------------------------------------------------------------------
// FM_Save()
// Save FM register to given file pointer
//-----------------------------------------------------------------------------
void    FM_Save (FILE *f)
{
  fwrite (FM_Regs, YM2413_REGISTERS, 1, f);
}

//-----------------------------------------------------------------------------
// FM_Load()
// Load FM registers from given file pointer and call emulator Reload function
// Note: only the registers are saved/loaded currently
// If this has to change, please pay attention to the fact that MSD loading
// use this fonction to load old Massage save states.
//-----------------------------------------------------------------------------
void    FM_Load (FILE *f)
{
  fread (FM_Regs, YM2413_REGISTERS, 1, f);
  FM_Used_Check ();
  FM_Regenerate ();
}

//-----------------------------------------------------------------------------

