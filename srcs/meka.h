//-----------------------------------------------------------------------------
// MEKA - meka.h
// Main variables, headers, prototypes and constants
//-----------------------------------------------------------------------------

// Z80 CPU Clock (3.579540 MHz) -----------------------------------------------
// FIXME: this should be obsoleted by what is in TVTYPE.C/.H
#define Z80_DEFAULT_CPU_CLOCK   (3579540 /*3579545*/)

// Emulated screen resolutions ------------------------------------------------
#define SMS_RES_X               (256)
#define SMS_RES_Y               (192)
#define SMS_RES_Y_TOTAL         (224)
#define GG_RES_X                (160)
#define GG_RES_Y                (144)
#define NES_RES_X               (256)
#define NES_RES_Y               (240)
#define MAX_RES_X               (256)   // SMS/NES_RES_X
#define MAX_RES_Y               (240)   // NES_RES_Y

// Max length of a message ----------------------------------------------------
#define MSG_MAX_LEN             (16384)

// Max tiles (in video mode 5)
#define MAX_TILES               (512)

// Fixed colors
//// FIXME: Currently call makecol(), should refer to a precomputed table
#define COLOR_BLACK				(0x00000000)	//makecol(0,0,0)
#define COLOR_WHITE             (0xFFFFFFFF)	//makecol(255,255,255)

#ifdef MDK_Z80
 int    Z80_IRQ;
#endif

u8      RAM[0x10000];               // RAM
u8      SRAM[0x8000];               // Save RAM
u8      VRAM[0x4000];               // Video RAM
u8 *    PRAM;
u8      PRAM_Static[0x40];          // Palette RAM
u8 *    ROM;                        // Emulated ROM
u8 *    Game_ROM;                   // Cartridge ROM
u8 *    Game_ROM_Computed_Page_0;   // Cartridge ROM computed first page
u8 *    Mem_Pages [8];              // Pointer to memory pages

u8 *    BACK_AREA;
u8 *    SG_BACK_TILE;
u8 *    SG_BACK_COLOR;

// Flags for layer handling ---------------------------------------------------
#define LAYER_BACKGROUND            (0x01)
#define LAYER_SPRITES               (0x02)

// Main MEKA state ------------------------------------------------------------
int     Meka_State;
#define MEKA_STATE_INIT             (0)
#define MEKA_STATE_FULLSCREEN       (1)
#define MEKA_STATE_GUI              (2)
#define MEKA_STATE_SHUTDOWN         (3)

// Battery Backed RAM Macros --------------------------------------------------
#define SRAM_Active             (sms.Mapping_Register & 0x08)
#define SRAM_Page               (sms.Mapping_Register & 0x04)
//-----------------------------------------------------------------------------

// On Board RAM Macros (currently only for Ernie Els Golf)
#define ONBOARD_RAM_EXIST       (0x20)
#define ONBOARD_RAM_ACTIVE      (0x40)
//-----------------------------------------------------------------------------

// Variables needed by one emulated SMS
// FIXME: reconceptualize those stuff, this is pure, old crap
struct SMS_TYPE
{
    // CPU State
#ifdef MARAT_Z80
    Z80   R;                              // CPU Registers (Marat Faizullin)
#elif NEIL_Z80
    CONTEXTMZ80 CPU;                      // CPU Registers (Neil Bradley)
#elif MDK_Z80
    Z80_Regs R;                           // CPU Registers (Marcel de Kogel)
#elif RAZE_Z80
    void *CPU;                            // CPU Registers (Richard Mitton)
#elif MAME_Z80
    // nothing. currently implemented as global
#endif
    // Other State
    u8      VDP [16];                      // VDP Registers
    u8      __UNUSED__PRAM_Address;        // Current palette address
    // NOTE: variable below (VDP_Status) is modified from videoasm.asm, do NOT move it
    u8      VDP_Status;                    // Current VDP status
    u16     VDP_Address;                   // Current VDP address
    u8      VDP_Access_Mode;               // 0: Address Low - 1: Address High
    u8      VDP_Access_First;              // Address Low Latch
    u8      VDP_ReadLatch;                      // Read Latch
    u8      VDP_Pal;                       // Currently Reading Palette ?
    u8      Country;                       // 0: English - 1: Japanese
    int     Lines_Left;                    // Lines Left before H-Blank
    u8      Need_HBlank;
    u8      __UNUSED__Need_VBlank;
    u8      Glasses_Register;              // 3-D Glasses Register
    u8      SRAM_Pages;                    // SRAM pages used
    u8      Mapping_Register;              // SRAM status + mapping offset
    u8      FM_Magic;                      // FM Latch (for detection)
    u8      FM_Register;                   // FM Register
    u8      Input_Mode;   // Port 0xDE     // 0->6: Keyboard - 7: Joypads
    u8      Pages_Reg [3];                 // Paging registers
};

// Tempory (not saved) data for one machine
// FIXME: reconceptualize those stuff, this is pure, old crap
struct TSMS_TYPE
{
    u16     Control [8];                   // 0->6 = Keyboard - 7: Joypads
    u8      Control_GG;
    u8      Control_Check_GUI;
    u8      Control_Start_Pause;
    int     VDP_Line;
    int     Pages_Mask_8k,  Pages_Count_8k;
    int     Pages_Mask_16k, Pages_Count_16k;
    long    Size_ROM;
    u8      Periph_Nat;
    int     VDP_VideoMode, VDP_New_VideoMode;
    int     VDP_Video_Change;
};

// Pointer to current line on emulated screen buffer
byte *  GFX_Line;   // FIXME: Obsolete

// Bits for gfx.Tile_Dirty
#define TILE_DIRTY_DECODE       (0x01)
#define TILE_DIRTY_REDRAW       (0x02)

// Variables related to graphics - not saved in savestate
typedef struct
{
 byte    Tile_Dirty [MAX_TILES];
 byte    Tile_Decoded [MAX_TILES] [64];
} TGFX_TYPE;

typedef struct
{
    bool        GUI_Inited;
    bool        Fullscreen_Cursor;
    int         IPeriod, IPeriod_Coleco, IPeriod_Sg1000_Sc3000, IPeriod_NES, Cur_IPeriod;
    int         Layer_Mask;
    int         Current_Key_Pressed;
    //----
    bool        Force_Quit;                         // Set to TRUE for program to quit
    int         State_Current;                      // Current savestate number
    int         State_Load;                         // Set to != 1 to set and load a state on Machine_Reset();
    bool        Setup_Interactive_Execute;          // Set to TRUE to execute an interactive setup on startup
    int         Debug_Step;
    int         GUI_Current_Page;
} OPT_TYPE;

// FIXME: define to MAXPATHLEN ?
#define FILENAME_LEN (256+64)

// Generic 512-Character-Wide buffer
// (Not to be used accross functions calls! etc...)
// FIXME: Make obsoletes
char    GenericBuffer [512];

OPT_TYPE          opt;
TGFX_TYPE         tgfx;

// Declare one 'sms' and one 'tsms'
struct SMS_TYPE   sms;
struct TSMS_TYPE  tsms;

typedef struct
{
    char *  name;
    int     value;
} S2I_TYPE;

//-----------------------------------------------------------------------------
// NEW STRUCTURES
// Below are new structures which should one day obsolete everything above.
// Right now they are quite empty but new members can be added here, or old 
// members moved from time to time.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Emulated machine
//-----------------------------------------------------------------------------

typedef struct
{
    int                     model;
    int                     sprite_shift_x;						// 0 or 8
	int						sprite_pattern_base_index;			// 0 or 256, SMS/GG only
	u8 *					sprite_pattern_base_address;

    // Scrolling latches
    u8                      scroll_x_latched;
    u8                      scroll_y_latched;
    u8                      scroll_x_latched_table[MAX_RES_Y];
} t_machine_vdp_smsgg;

// FIXME: Global because accessed by videoasm.asm
// Figure out a proper way to deal with this (export structure members offsets as definitions, etc)
u8 *						sprite_attribute_table;

typedef struct
{
    int                     driver_id;
    int                     mapper;
    t_machine_vdp_smsgg     VDP;
    struct t_tv_type *      TV;
    int                     TV_lines;   // Copy of TV->screen_lines
} t_machine;

t_machine   cur_machine;

//-----------------------------------------------------------------------------
// Runtime environment
//-----------------------------------------------------------------------------

typedef struct
{
    char    EmulatorDirectory       [FILENAME_LEN];
    char    StartingDirectory       [FILENAME_LEN];
    char    ConfigurationFile       [FILENAME_LEN];
    char    DataBaseFile            [FILENAME_LEN];
    char    DataFile                [FILENAME_LEN];
    char    SkinFile                [FILENAME_LEN];
    char    ScreenshotDirectory     [FILENAME_LEN];
    char    SavegameDirectory       [FILENAME_LEN];
    char    BatteryBackedMemoryFile [FILENAME_LEN];
    char    MusicDirectory          [FILENAME_LEN];
    char    DebugDirectory          [FILENAME_LEN];

    char    MediaImageFile          [FILENAME_LEN];     // FIXME: abstract media (per type/slot)

    char    DocumentationMain       [FILENAME_LEN];
#ifdef WIN32
    char    DocumentationMainW      [FILENAME_LEN];
#elif UNIX
    char    DocumentationMainU      [FILENAME_LEN];
#endif
    char    DocumentationCompat     [FILENAME_LEN];
    char    DocumentationMulti      [FILENAME_LEN];
    char    DocumentationChanges    [FILENAME_LEN];
    char    DocumentationDebugger   [FILENAME_LEN];
    // FIXME: add and use TECH.TXT ?
} t_meka_env_paths;

typedef struct
{
    t_meka_env_paths    Paths;
    int                 mouse_installed;
	int					argc;
	char **				argv;
} t_meka_env;

t_meka_env  g_Env;

//-----------------------------------------------------------------------------
// Configuration
// All MEKA configuration options
// Note: this is dependant of runtime emulation configuration, which can
// be affected by various factors.
// This structure should basically reflect the content of MEKA.CFG
//-----------------------------------------------------------------------------

// Values for g_Configuration.sprite_flickering
#define SPRITE_FLICKERING_NO        (0)
#define SPRITE_FLICKERING_ENABLED   (1)
#define SPRITE_FLICKERING_AUTO      (2) // Default

typedef struct
{
    // Country
    int     country;                    // Country to use (session)
    int     country_cfg;                // " given by configuration file and saved back
    int     country_cl;                 // " given by command-line

    // Debug Mode
    bool    debug_mode;                 // Set if debug mode enabled (session)
    bool    debug_mode_cfg;             // " given by configuration file and saved back
    bool    debug_mode_cl;              // " given by command-line

    // Miscellaneous
    int     sprite_flickering;          // Set to emulate sprite flickering.
    bool    slash_nirv;                 // Increase FPS counter by many. Old private joke for NiRV.
    bool    allow_opposite_directions;  // Allows pressing of LEFT-RIGHT / UP-DOWN simultaneously.
    bool    enable_BIOS;
    bool    enable_NES;             
    bool    show_fullscreen_messages;
    bool    show_product_number;
    bool    start_in_gui;

    // Applet: Game Screen
    int     game_screen_scale;

    // Applet: File Browser
    bool    fb_close_after_load;
    bool    fb_uses_DB;
    bool    fullscreen_after_load;

    // Applet: Debugger
    int     debugger_console_lines;
    int     debugger_disassembly_lines;
    bool    debugger_disassembly_display_labels;
    bool    debugger_log_enabled;

    // Applet: Memory Editor
    int     memory_editor_lines;
    int     memory_editor_columns;

    // Video
    int     video_mode_desktop_depth;
    int     video_mode_gui_depth;
    int     video_mode_gui_depth_cfg;
    long    video_mode_gui_driver;
    int     video_mode_gui_res_x;
    int     video_mode_gui_res_y;
    bool    video_mode_gui_vsync;
    int     video_mode_gui_refresh_rate;
    int     video_mode_gui_access_mode;         // Make obsolete

} t_meka_configuration;

t_meka_configuration    g_Configuration;

//-----------------------------------------------------------------------------
// Media image
// Old image of a loaded media (ROM, disk, etc...).
//-----------------------------------------------------------------------------

typedef struct
{
    u32         v[2];
} t_meka_crc;

#define MEDIA_IMAGE_ROM     (0)

typedef struct
{
    int         type;
    u8 *        data;
    int         data_size;
    t_meka_crc  mekacrc;
    u32         crc32;
    // char *   filename ?
} t_media_image;

// Currently a global to hold ROM infos.
// Note that the structure is currently only half used and supported.
// We only use the 'meka_checksum' and 'crc32' fields yet.
t_media_image   media_ROM;

//-----------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------

// Border Color
// FIXME
#define Border_Color                    (COLOR_BLACK) /*((sms.VDP[7] & 15) + 16)*/
#define Border_Color_x4                 (Border_Color) | (Border_Color << 8) | (Border_Color << 16) | (Border_Color << 24)

// Debugging
#define Debug_Stepping(a)               { if (opt.Debug_Step) ConsolePrintf(a); }
#define Debug_Trace(a)                  { ConsolePrintf("%s\n", a); /* Font_Write (screen, a, 10, 10, Border_Color); delay (200); */ }
#define Debug_Pause                     { Refresh_Screen (); while (!key[KEY_SPACE]); while (key[KEY_SPACE]); }
int     Debug_Generic_Value;
bool    Debug_Print_Infos;

//-----------------------------------------------------------------------------
// Data (video buffers)
//-----------------------------------------------------------------------------

// Emulated Screen ------------------------------------------------------------
BITMAP *screenbuffer, *screenbuffer_next;  // Pointers to screen memory buffers
BITMAP *screenbuffer_1, *screenbuffer_2;   // Screen memory buffers
// FullScreen / Video Memory --------------------------------------------------
BITMAP *fs_out;                            // Fullscreen video buffer
BITMAP *fs_page_0, *fs_page_1, *fs_page_2; // Fullscreen video buffer pointers (for page flipping & triple buffering)
// GUI ------------------------------------------------------------------------
BITMAP *gui_buffer;                        // GUI memory buffer
BITMAP *gui_page_0, *gui_page_1;           // GUI video buffers when using page flipping
BITMAP *gui_background;                    // GUI Background

//-----------------------------------------------------------------------------
