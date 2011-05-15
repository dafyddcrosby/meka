//-----------------------------------------------------------------------------
// MEKA - fskipper.h
// Frame Skipper - Headers
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

#define FRAMESKIP_MODE_AUTO     (0)
#define FRAMESKIP_MODE_STANDARD (1)

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

int     Frame_Skipper (void);
void    Frame_Skipper_Auto_Adjust_Handler (void);
void    Frame_Skipper_Auto_Install_Handler (void);
void    Frame_Skipper_Auto_Reinstall_Handler (void);
void    Frame_Skipper_Configure (int v);
void    Frame_Skipper_Switch (void);
void    Frame_Skipper_Switch_FPS_Counter (void);
void    Frame_Skipper_Show (void);
void    Frame_Skipper_Init (void);
void    Frame_Skipper_Init_Values (void);

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

struct t_fskipper
{
    // Frame skipper    
    int             Mode;                   // Automatic (sync) or standard
    int             Automatic_Speed;
    volatile int    Automatic_Frame_Elapsed;
    int             Standard_Frameskip;
    int             Standard_Counter;
    bool            Show_Current_Frame;

    // FPS Counter
    int             FPS;
    bool            FPS_Display;
    //s64           FPS_LastComputedTime;
    volatile bool   New_Second;
    int             Frame_Rendered;         // Number of frames rendered (this second)
};

extern volatile t_fskipper fskipper;

//-----------------------------------------------------------------------------

