//-----------------------------------------------------------------------------
// MEKA - debugger.h
// Z80 Debugger - Headers
//-----------------------------------------------------------------------------

#ifdef MEKA_Z80_DEBUGGER

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

#define BREAKPOINT_ACCESS_R             (0x01)
#define BREAKPOINT_ACCESS_W             (0x02)
#define BREAKPOINT_ACCESS_X             (0x04)
#define BREAKPOINT_ACCESS_RW            (BREAKPOINT_ACCESS_R | BREAKPOINT_ACCESS_W)
#define BREAKPOINT_ACCESS_RWX           (BREAKPOINT_ACCESS_R | BREAKPOINT_ACCESS_W | BREAKPOINT_ACCESS_X)

#define BREAKPOINT_LOCATION_CPU         (0)
#define BREAKPOINT_LOCATION_IO          (1)
#define BREAKPOINT_LOCATION_VRAM        (2)
#define BREAKPOINT_LOCATION_PRAM        (3)
#define BREAKPOINT_LOCATION_MAX_        (4)

#define BREAKPOINT_TYPE_BREAK           (0)
#define BREAKPOINT_TYPE_WATCH           (1)

typedef struct
{
    int         enabled;
    int         id;
    int         type;
    int         location;
    int         access_flags;
    int         address_range[2];               // If single address, both values are equal
    int         auto_delete;                    // If -1, decrement on each break, delete when 0
    char *      desc;
} t_debugger_breakpoint;

typedef struct
{
    int         Enabled;                        // Enabled and initialized
    byte        Active;                         // Currently showing on GUI // FIXME: is a byte because of Desktop_Register_Box()
    bool        trap_set;
    u16         trap_address;
    int         stepping;                       // Set when we are doing a single step
    int         stepping_trace_after;
    t_list *    breakpoints;
    t_list *    breakpoints_cpu_space[0x10000]; // 0000-FFFF : each Z80 address has its list of appliable breakpoints
    t_list *    breakpoints_io_space[0x100];
    t_list *    breakpoints_vram_space[0x4000];
    t_list *    breakpoints_pram_space[0x40];
    FILE *      log_file;
    char *      log_filename;
    int         watch_counter;                  // For current frame
} t_debugger;

t_debugger      Debugger;

// This is like with breakpoints_cpu_space but with direct access to merged CPU read breakpoints. 
// The Z80 emulator use that to trap CPU read of first opcode byte *BEFORE* execution started.
// Otherwise, breakpoints works by stopping CPU after the even happened.
int             Debugger_CPU_Exec_Traps[0x10000];

// PC log queue (for trackback feature)
u16             Debugger_Z80_PC_Last;
u16             Debugger_Z80_PC_Log_Queue[256];
int             Debugger_Z80_PC_Log_Queue_Write;
int             Debugger_Z80_PC_Log_Queue_First;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// Init
void                        Debugger_Init_Values(void);
void                        Debugger_Init(void);
void                        Debugger_Close(void);

// Main
void                        Debugger_MachineReset(void);
void                        Debugger_Enable(void);
void                        Debugger_Update(void);
void                        Debugger_Switch(void);

void                        Debugger_Printf(const char *format, ...);

// Hooks
int                         Debugger_Hook(Z80 *R);
void                        Debugger_RdVRAM_Hook(register int addr, register u8 value);
void                        Debugger_WrVRAM_Hook(register int addr, register u8 value);
void                        Debugger_WrPRAM_Hook(register int addr, register u8 value);

//-----------------------------------------------------------------------------
// Functions - Line
//-----------------------------------------------------------------------------

static INLINE 
void  Debugger_Z80_PC_Log_Queue_Add(unsigned short pc)
{
    Debugger_Z80_PC_Log_Queue[Debugger_Z80_PC_Log_Queue_Write] = pc;
    Debugger_Z80_PC_Log_Queue_Write = (Debugger_Z80_PC_Log_Queue_Write + 1) & 255;
    if (Debugger_Z80_PC_Log_Queue_Write == Debugger_Z80_PC_Log_Queue_First)
        Debugger_Z80_PC_Log_Queue_First = (Debugger_Z80_PC_Log_Queue_First + 1) & 255;
}

//-----------------------------------------------------------------------------

#endif
