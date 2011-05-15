//-----------------------------------------------------------------------------
// MEKA - S_MISC.C
// Sound Miscellaenous - Headers
//-----------------------------------------------------------------------------

#ifndef __S_MISC_H__
#define __S_MISC_H__

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

extern int		Sound_Rate_Default_Table[4];

extern int		sound_vcount;
extern int		sound_icount;
extern int		Sound_Update_Count;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

double  Sound_Calc_CPU_Time (void);

void    FM_Disable                      (void);
void    FM_Enable                       (void);
void    FM_Emulator_OPL                 (void);
void    FM_Emulator_Digital             (void);

void    Sound_Volume_Menu_Init          (int menu_id);

void    Sound_Rate_Set                  (int value, int reinit_hardware);
void    Sound_Rate_Menu_Init            (int menu_id);

void	Sound_Channels_Menu_Handler		(t_menu_event *event);

#endif /* __S_MISC_H__ */

