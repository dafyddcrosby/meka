//-----------------------------------------------------------------------------
// MEKA - g_init.c
// GUI Initialization - Code
//-----------------------------------------------------------------------------

#include "shared.h"
#include "app_about.h"
#include "app_game.h"
#include "app_mapview.h"
#include "app_memview.h"
#include "app_palview.h"
#include "app_options.h"
#include "app_techinfo.h"
#include "app_textview.h"
#include "app_tileview.h"
#include "datadump.h"
#include "debugger.h"
#include "desktop.h"
#include "g_file.h"
#include "inputs_c.h"
#include "skin_bg.h"

//-----------------------------------------------------------------------------
// Forward Declaration
//-----------------------------------------------------------------------------

static void    GUI_InitApplets(void);

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void    GUI_Init()
{
    opt.GUI_Inited = TRUE;

    gui_buffer = NULL;
    gui_background = NULL;

    gui.info.screen_pad.x = 2;
    gui.info.screen_pad.y = 2;
    gui.info.bars_height = 19;
    gui.info.grid_distance = 32;

    gui.boxes = NULL;
    gui.boxes_count = 0;

	gui.info.screen.x = g_Configuration.video_mode_gui_res_x;
    gui.info.screen.y = g_Configuration.video_mode_gui_res_y;
	GUI_CreateVideoBuffers();

    Desktop_Init();
    GUI_InitApplets();
    special_effects_init ();

    // Create game box
    {
        static bool active_dummy = TRUE;
        gamebox_instance = gamebox_create (35, 132);
        Desktop_Register_Box ("GAME", gamebox_instance, 1, &active_dummy);
    }

    Desktop_SetStateToBoxes ();     // Set all boxes state based on MEKA.DSK data
    gui_menus_init ();              // Create menus (Note: need to be done after Desktop_SetStateToBoxes because it uses the 'active' flags to check items)
    gui_init_mouse ();
}

void	GUI_SetupNewVideoMode()
{
	gui.info.must_redraw = TRUE;
	gui.info.screen.x = g_Configuration.video_mode_gui_res_x;
    gui.info.screen.y = g_Configuration.video_mode_gui_res_y;
	GUI_CreateVideoBuffers();

    Skins_Background_Redraw();
    Skins_StartupFadeIn();

    // Fix windows position
    for (t_list* boxes = gui.boxes; boxes != NULL; boxes = boxes->next)
    {
        t_gui_box* box = (t_gui_box*)boxes->elem;;
        gui_box_clip_position(box);
        box->flags |= GUI_BOX_FLAGS_DIRTY_REDRAW;
    }
}

void	GUI_CreateVideoBuffers()
{
    // Destroy existing buffers (if any)
    if (gui_buffer != NULL)
    {
        al_destroy_bitmap(gui_buffer);
        gui_buffer = NULL;
        assert(gui_background != NULL);
        al_destroy_bitmap(gui_background);
        gui_background = NULL;
    }

	const int color_depth = g_Configuration.video_mode_gui_depth;

    // Setup buffers
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	al_set_new_bitmap_format((color_depth == 16) ? ALLEGRO_PIXEL_FORMAT_BGR_565 : ALLEGRO_PIXEL_FORMAT_ABGR_8888);
    gui_buffer = al_create_bitmap(gui.info.screen.x, gui.info.screen.x);
    al_set_target_bitmap(gui_buffer);
	al_clear_to_color(COLOR_BLACK);

	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	al_set_new_bitmap_format((color_depth == 16) ? ALLEGRO_PIXEL_FORMAT_BGR_565 : ALLEGRO_PIXEL_FORMAT_ABGR_8888);
    gui_background = al_create_bitmap(gui.info.screen.x, gui.info.screen.x);

    // Recreate existing windows buffers
    for (t_list* boxes = gui.boxes; boxes != NULL; boxes = boxes->next)
    {
        t_gui_box* box = (t_gui_box*)boxes->elem;;
		gui_box_create_video_buffer(box);
	}
}

void	GUI_Close(void)
{
    // FIXME: Nice.
}

void    GUI_InitApplets(void)
{
    // About box
    AboutBox_Init();

    // Message Log
    TB_Message_Init();

    // Memory Viewer
    MemoryViewer_MainInstance = MemoryViewer_New(TRUE, -1, -1);

    // Tilemap Viewer
    TilemapViewer_MainInstance = TilemapViewer_New(TRUE);

    // Text Viewer
    TextViewer_Init(&TextViewer);
    // FIXME: save current file in meka.cfg
    if (TextViewer_Open(&TextViewer, Msg_Get(MSG_Doc_BoxTitle), g_env.Paths.DocumentationMain) != MEKA_ERR_OK)
        Msg (MSGT_USER, Msg_Get(MSG_Doc_File_Error));
    TextViewer.current_file = 0; // FIXME: Remove this field

    // Technical Information
    TechInfo_Init ();

    // Tiles Viewer
    TileViewer_Init ();

    // Palette Viewer
    PaletteViewer_Init(&PaletteViewer);

    // FM Instruments Editor
    // FM_Editor_Init ();

    // File Browser
    FB_Init ();

    // Options
    Options_Init_Applet ();

    // Inputs Configuration
    Inputs_CFG_Init_Applet ();

    // Debugger
    #ifdef MEKA_Z80_DEBUGGER
    if (g_Configuration.debug_mode)
    {
        Debugger_Enable ();
        Debugger_Init ();
        DataDump_Init ();
    }
    #endif
}

//-----------------------------------------------------------------------------
