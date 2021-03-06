//-----------------------------------------------------------------------------
// MEKA - specials.h
// Special effects - Headers
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

#define MAX_BLOOD_DROP          (300)
#define MAX_SNOW_FLAKES         (400)
#define MAX_HEARTS              (16)

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// OLD ------------------------------------------------------------------------
void gui_applet_blood_create  (int v, int x, int y);

// NEW ------------------------------------------------------------------------
void special_effects_init               (void);
void special_effects_update_after       (void);
void special_effects_update_before      (void);
void special_effects_snow_init          (int i);

//-----------------------------------------------------------------------------

