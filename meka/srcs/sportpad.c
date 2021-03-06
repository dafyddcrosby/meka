//-----------------------------------------------------------------------------
// MEKA - sportpad.c
// Sports Pad Emulation - Code
//-----------------------------------------------------------------------------
// TO DO:
//   Real Sports Pad should be carefully tested to see their reaction,
//   actual human-reachable speed, etc...
//-----------------------------------------------------------------------------

#include "shared.h"
#include "sportpad.h"

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void    SportsPad_Init (void)
{
    Inputs.SportsPad_XY [PLAYER_1] [0] = Inputs.SportsPad_XY [PLAYER_2] [0] = 0;
    Inputs.SportsPad_XY [PLAYER_1] [1] = Inputs.SportsPad_XY [PLAYER_2] [0] = 0;
    Inputs.SportsPad_Latch [0] = Inputs.SportsPad_Latch [1] = 0;
}

// FIXME: This is terrible.
// 1. Rewrite Sports Pad emulation correctly (now that we know how latch workes)
// 2. Tune the function below so that it is playable with a mouse
void    SportsPad_Update_Axis (char *v, int move)
{
    int   vel;
    int   limit = 50; // Technically 63, but in practice it is much less

    vel = *v + (move / 2);

    if (vel > limit) vel = limit;
    else if (vel < -limit) vel = -limit;

    if (vel > 0) vel -= 1;
    if (vel < 0) vel += 1;

    if (vel >= 10) vel -= 10;
    else
        if (vel <= -10) vel += 10;

    *v = vel;
}

void    SportsPad_Update (int player, int device_x_rel, int device_y_rel)
{
    SportsPad_Update_Axis (&Inputs.SportsPad_XY [player] [0], -device_x_rel);
    SportsPad_Update_Axis (&Inputs.SportsPad_XY [player] [1], -device_y_rel);
}

//-----------------------------------------------------------------------------

