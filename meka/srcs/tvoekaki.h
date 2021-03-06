//-----------------------------------------------------------------------------
// MEKA - tvoekaki.h
// TV Oekaki / Graphic Table Emulation - Headers
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void    TVOekaki_Init (void);
void    TVOekaki_Update (int device_x, int device_y, int device_b_field);
void    TVOekaki_Mouse_Range (void);

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

#define TVOEKAKI_BIT_AXIS      (1)
#define TVOEKAKI_BIT_PRESSED   (2)
#define TVOEKAKI_BIT_ON_BOARD  (4)

#define TVOEKAKI_AXIS_X        ((TVOekaki.Infos & TVOEKAKI_BIT_AXIS) == 0)
#define TVOEKAKI_AXIS_Y        ((TVOekaki.Infos & TVOEKAKI_BIT_AXIS) != 0)
#define TVOEKAKI_PRESSED       ((TVOekaki.Infos & TVOEKAKI_BIT_PRESSED) != 0)
#define TVOEKAKI_NOT_PRESSED   ((TVOekaki.Infos & TVOEKAKI_BIT_PRESSED) == 0)
#define TVOEKAKI_ON_BOARD      ((TVOekaki.Infos & TVOEKAKI_BIT_ON_BOARD) != 0)
#define TVOEKAKI_NOT_ON_BOARD  ((TVOekaki.Infos & TVOEKAKI_BIT_ON_BOARD) == 0)

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

typedef struct
{
 int            X, Y;
 byte           Infos;
}               t_tvoekaki;

t_tvoekaki      TVOekaki;

//-----------------------------------------------------------------------------

