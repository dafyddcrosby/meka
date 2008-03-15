//-----------------------------------------------------------------------------
// MEKA - message.h
// Messaging System, Languages, Console - Headers
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

// Messages types
#define MSGT_USER_BOX                   (0x01)
#define MSGT_USER_INFOLINE              (0x02)
#define MSGT_ATTR_DEBUG                 (0x04)

#define MSGT_USER                       (MSGT_USER_BOX | MSGT_USER_INFOLINE)
#define MSGT_DEBUG                      (MSGT_USER_BOX | MSGT_ATTR_DEBUG)

//-----------------------------------------------------------------------------

// String used to enable WIP for a language
#define MSG_LANG_WIP_STR                "WIP"

// Messages definitions
enum
{
	MSG_NULL                                    = 0,

	MSG_Welcome,
	MSG_Window_Title,
	MSG_Quit,

	MSG_About_BoxTitle,
	MSG_About_Line_Meka_Date,
	MSG_About_Line_Authors,
	MSG_About_Line_Homepage,

	MSG_Ok,
	MSG_Failed,
	MSG_Error_Base,
	MSG_Error_Error,
	MSG_Error_Memory,
	MSG_Error_Param,
	MSG_Error_Syntax,

	MSG_Error_Video_Mode,
	MSG_Error_Video_Mode_Back_To_GUI,

	MSG_Error_File_Not_Found,
	MSG_Error_File_Read,
	MSG_Error_File_Empty,

	MSG_Error_ZIP_Not_Supported,
	MSG_Error_ZIP_Loading,
	MSG_Error_ZIP_Internal,

	MSG_Error_Directory_Open,

	MSG_Must_Reset,
	MSG_No_ROM,

	MSG_Init_Allegro,
	MSG_Init_GUI,
	MSG_Init_Completed,

	MSG_Setup_Running,
	MSG_Setup_Setup,
	MSG_Setup_Soundcard_Select,
	MSG_Setup_Soundcard_Select_Tips_DOS,
	MSG_Setup_Soundcard_Select_Tips_Win32,
	MSG_Setup_SampleRate_Select,
	MSG_Setup_Debugger_Enable,

	MSG_Capture_Done,
	MSG_Capture_Error,
	MSG_Capture_Error_File,
	
	MSG_SRAM_Loaded,
	MSG_SRAM_Load_Unable,
	MSG_SRAM_Wrote,
	MSG_SRAM_Write_Unable,
	
	MSG_93c46_Reset,
	MSG_93c46_Loaded,
	MSG_93c46_Load_Unable,
	MSG_93c46_Wrote,
	MSG_93c46_Write_Unable,
	
	MSG_TVType_Set,
	MSG_TVType_Info_Speed,
	
	MSG_Blitters_Loading,
	MSG_Blitters_Error_Not_Enough,
	MSG_Blitters_Error_Not_Found,
	MSG_Blitters_Error_Missing,
	MSG_Blitters_Error_Unrecognized,
	MSG_Blitters_Error_Incorrect_Value,
	MSG_Blitters_Set,
	
	MSG_NES_Activate,
	MSG_NES_Sucks,
	MSG_NES_Mapper_Unknown,
	MSG_NES_Deny_Facts,
	
	MSG_Debug_Init,
	MSG_Debug_Welcome,
	MSG_Debug_Not_Available,
	MSG_Debug_Brk_Need_Param,
	MSG_Debug_Trap_Read,
	MSG_Debug_Trap_Write,
	MSG_Debug_Trap_Port_Read,
	MSG_Debug_Trap_Port_Write,
	MSG_Debug_Symbols_Loaded,
	MSG_Debug_Symbols_Error,
	MSG_Debug_Symbols_Error_Line,
	
	MSG_DataDump_Mode_Ascii,
	MSG_DataDump_Mode_Raw,
	MSG_DataDump_Error,
	MSG_DataDump_Error_OB_Memory,
	MSG_DataDump_Error_Palette,
	MSG_DataDump_Error_Sprites,
	MSG_DataDump_Main,

	MSG_Doc_BoxTitle,
	MSG_Doc_File_Error,
	MSG_Doc_Enabled,
	MSG_Doc_Disabled,
	
	MSG_Flickering_Auto,
	MSG_Flickering_Yes,
	MSG_Flickering_No,
	
	MSG_Layer_BG_Disabled,
	MSG_Layer_BG_Enabled,
	MSG_Layer_Spr_Disabled,
	MSG_Layer_Spr_Enabled,

	MSG_FDC765_Unknown_Read,
	MSG_FDC765_Unknown_Write,
	MSG_FDC765_Disk_Too_Large1,
	MSG_FDC765_Disk_Too_Large2,
	MSG_FDC765_Disk_Too_Small1,
	MSG_FDC765_Disk_Too_Small2,
	
	MSG_TVOekaki_Pen_Touch,
	MSG_TVOekaki_Pen_Away,
	
	MSG_Palette_BoxTitle,
	MSG_Palette_Disabled,
	MSG_Palette_Enabled,
	
	MSG_Message_BoxTitle,
	MSG_Message_Disabled,
	MSG_Message_Enabled,
	
	MSG_TechInfo_BoxTitle,
	MSG_TechInfo_Disabled,
	MSG_TechInfo_Enabled,
	
	MSG_TilesViewer_BoxTitle,
	MSG_TilesViewer_Disabled,
	MSG_TilesViewer_Enabled,
	MSG_TilesViewer_Tile,
	
	MSG_MemoryEditor_BoxTitle,
	MSG_MemoryEditor_Disabled,
	MSG_MemoryEditor_Enabled,
	MSG_MemoryEditor_WriteZ80_Unable,
	MSG_MemoryEditor_Address_Out_of_Bound,

	MSG_RapidFire_JxBx_On,
	MSG_RapidFire_JxBx_Off,
	
	MSG_FM_Enabled,
	MSG_FM_Disabled,
	
	MSG_Country_European_US,
	MSG_Country_JAP,
	
	MSG_Patch_Loading,
	MSG_Patch_Missing,
	MSG_Patch_Unrecognized,
	MSG_Patch_Value_Not_a_Byte,
	MSG_Patch_Out_of_Bound,
	
	MSG_Glasses_Enabled,
	MSG_Glasses_Disabled,
	MSG_Glasses_Show_Both,
	MSG_Glasses_Show_Left,
	MSG_Glasses_Show_Right,
	MSG_Glasses_Com_Port,
	MSG_Glasses_Com_Port2,
	MSG_Glasses_Com_Port_Open_Error,
	MSG_Glasses_Unsupported,

	MSG_Inputs_Joy_Init,
	MSG_Inputs_Joy_Init_None,
	MSG_Inputs_Joy_Init_Found,
	MSG_Inputs_Joy_Calibrate_Error,

	MSG_Inputs_Joypad,
	MSG_Inputs_LightPhaser,
	MSG_Inputs_PaddleControl,
	MSG_Inputs_SportsPad,
	MSG_Inputs_TVOekaki,
	MSG_Inputs_Play_Digital,
	MSG_Inputs_Play_Mouse,
	MSG_Inputs_Play_Digital_Unrecommended,
	MSG_Inputs_Play_Pen,
	MSG_Inputs_SK1100_Enabled,
	MSG_Inputs_SK1100_Disabled,

	MSG_Inputs_Config_BoxTitle,
	MSG_Inputs_Config_Peripheral_Click,
	MSG_Inputs_Config_Source_Enabled,
	MSG_Inputs_Config_Source_Player,
	MSG_Inputs_Config_Source_Emulate_Joypad,

	MSG_Inputs_Src_Loading,
	MSG_Inputs_Src_Not_Enough,
	MSG_Inputs_Src_Missing,
	MSG_Inputs_Src_Equal,
	MSG_Inputs_Src_Unrecognized,
	MSG_Inputs_Src_Syntax_Param,
	MSG_Inputs_Src_Inconsistency,
	MSG_Inputs_Src_Map_Keyboard,
	MSG_Inputs_Src_Map_Keyboard_Ok,
	MSG_Inputs_Src_Map_Joypad,
	MSG_Inputs_Src_Map_Joypad_Ok_A,
	MSG_Inputs_Src_Map_Joypad_Ok_B,
	MSG_Inputs_Src_Map_Mouse,
	MSG_Inputs_Src_Map_Mouse_Ok_B,
	MSG_Inputs_Src_Map_Mouse_No_A,
	MSG_Inputs_Src_Map_Cancelled,

	MSG_Machine_Pause,
	MSG_Machine_Resume,
	MSG_Machine_Reset,
	
	MSG_FDB_Loading,

	MSG_DB_Loading,
	MSG_DB_Name_Default,
	MSG_DB_Name_NoCartridge,
	MSG_DB_SyntaxError,

	MSG_Config_Loading,
	
	MSG_Datafile_Loading,
	
	MSG_Driver_Unknown,
	
	MSG_OverDump,
	
	MSG_Sound_Init,
	MSG_Sound_Init_Error_SEAL,
	MSG_Sound_Init_Error_Audio,
	MSG_Sound_Init_Error_Blaster,
	MSG_Sound_Init_Error_Blaster_A,
	MSG_Sound_Init_Error_Voices,
	MSG_Sound_Init_Error_Voice_N,
	MSG_Sound_Init_Soundcard,
	MSG_Sound_Init_Soundcard_No,
	MSG_Sound_Init_SN76496,
	MSG_Sound_Init_YM2413_OPL,
	MSG_Sound_Init_YM2413_Digital,
	MSG_Sound_Rate_Changed,
	MSG_Sound_Stream_Error,
	MSG_Sound_Volume_Changed,
	
	MSG_Theme_Loading,
	MSG_Theme_Error_Not_Enough,
	MSG_Theme_Error_Missing_Theme_Name,
	MSG_Theme_Error_Syntax,
	MSG_Theme_Error_Attribute_Defined,
	MSG_Theme_Error_Out_of_Bound,
	MSG_Theme_Error_Theme_Missing_Data,
	MSG_Theme_Error_BG_Big,
	MSG_Theme_Error_BG,
	MSG_Theme_Error_BG_FileName,
	
	MSG_LoadROM_Loading,
	MSG_LoadROM_Success,
	MSG_LoadDisk_Success,
	MSG_LoadROM_Comment,
	MSG_LoadROM_SMSGG_Mode_Comment,
	MSG_LoadROM_Warning,
	MSG_LoadROM_Bad_Dump_Long,
	MSG_LoadROM_Bad_Dump_Short,
	MSG_LoadROM_Product_Num,
	MSG_LoadROM_SDSC,
	MSG_LoadROM_SDSC_Name,
	MSG_LoadROM_SDSC_Version,
	MSG_LoadROM_SDSC_Date,
	MSG_LoadROM_SDSC_Author,
	MSG_LoadROM_SDSC_Release_Note,
	MSG_LoadROM_SDSC_Unknown,
	MSG_LoadROM_SDSC_Error,
	MSG_LoadROM_Reload_Reloaded,
	MSG_LoadROM_Reload_No_ROM,

	MSG_FileBrowser_BoxTitle,
	MSG_FileBrowser_Drive,
	MSG_FileBrowser_Load,
	MSG_FileBrowser_Close,
	MSG_FileBrowser_LoadNames,
	MSG_FileBrowser_ReloadDir,

	MSG_FM_Editor_BoxTitle,
	MSG_FM_Editor_Enabled,
	MSG_FM_Editor_Disabled,
	
	MSG_Frameskip_Auto,
	MSG_Frameskip_Standard,
	MSG_FPS_Counter_Enabled,
	MSG_FPS_Counter_Disabled,
	
	MSG_Log_Need_Param,
	MSG_Log_Session_Start,
	
	MSG_Load_Need_Param,
	MSG_Load_Error,
	MSG_Load_Not_Valid,
	MSG_Load_Success,
	MSG_Load_Version,
	MSG_Load_Wrong_System,
	MSG_Load_Massage,
	MSG_Save_Not_in_BIOS,
	MSG_Save_Error,
	MSG_Save_Success,
	MSG_Save_Slot,
	
	MSG_Options_BoxTitle,
	MSG_Options_Close,
	MSG_Options_BIOS_Enable,
	MSG_Options_DB_Display,
	MSG_Options_Product_Number,
	MSG_Options_Bright_Palette,
	MSG_Options_Allow_Opposite_Directions,
	MSG_Options_Load_Close,
	MSG_Options_Load_FullScreen,
	MSG_Options_FullScreen_Messages,
	MSG_Options_GUI_VSync,
	MSG_Options_Capture_Crop_Align,
	MSG_Options_NES_Enable,
	
	MSG_Language_Set,
	MSG_Language_Set_Warning,
	
	MSG_Sound_Dumping_Start,
	MSG_Sound_Dumping_Stop,
	MSG_Sound_Dumping_Error_File_1,
	MSG_Sound_Dumping_Error_File_2,
	MSG_Sound_Dumping_VGM_Acc_Frame,
	MSG_Sound_Dumping_VGM_Acc_Sample,
	MSG_Sound_Dumping_VGM_Acc_Change,

	MSG_Menu_Main,
	MSG_Menu_Main_LoadROM,
	MSG_Menu_Main_FreeROM,
	MSG_Menu_Main_SaveState,
	MSG_Menu_Main_LoadState,
	MSG_Menu_Main_Options,
	MSG_Menu_Main_Language,
	MSG_Menu_Main_Quit,
	
	MSG_Menu_Debug,
	MSG_Menu_Debug_Enabled,
	MSG_Menu_Debug_Reload_ROM,
	MSG_Menu_Debug_Dump,
	
	MSG_Menu_Machine,
	MSG_Menu_Machine_Power,
	MSG_Menu_Machine_Power_On,
	MSG_Menu_Machine_Power_Off,
	MSG_Menu_Machine_Country,
	MSG_Menu_Machine_Country_EU,
	MSG_Menu_Machine_Country_Jap,
	MSG_Menu_Machine_TVType,
	MSG_Menu_Machine_TVType_NTSC,
	MSG_Menu_Machine_TVType_PALSECAM,
	MSG_Menu_Machine_HardPause,
	MSG_Menu_Machine_HardReset,
	
	MSG_Menu_Video,
	MSG_Menu_Video_FullScreen,
	MSG_Menu_Video_Themes,
	MSG_Menu_Video_Blitters,
	MSG_Menu_Video_Layers,
	MSG_Menu_Video_Layers_Sprites,
	MSG_Menu_Video_Layers_Background,
	MSG_Menu_Video_Flickering,
	MSG_Menu_Video_Flickering_Auto,
	MSG_Menu_Video_Flickering_Yes,
	MSG_Menu_Video_Flickering_No,
	MSG_Menu_Video_3DGlasses,
	MSG_Menu_Video_3DGlasses_Enabled,
	MSG_Menu_Video_3DGlasses_ShowBothSides,
	MSG_Menu_Video_3DGlasses_ShowLeftSide,
	MSG_Menu_Video_3DGlasses_ShowRightSide,
	MSG_Menu_Video_3DGlasses_UsesCOMPort,
	MSG_Menu_Video_Capture,
	MSG_Menu_Video_Capture_CaptureScreen,
	MSG_Menu_Video_Capture_CaptureScreenAll,
	MSG_Menu_Video_Capture_IncludeGui,
	
	MSG_Menu_Sound,
	MSG_Menu_Sound_FM,
	MSG_Menu_Sound_FM_Enabled,
	MSG_Menu_Sound_FM_Disabled,
	MSG_Menu_Sound_FM_Emulator,
	MSG_Menu_Sound_FM_Emulator_OPL,
	MSG_Menu_Sound_FM_Emulator_Digital,
	MSG_Menu_Sound_FM_Editor,
	MSG_Menu_Sound_Volume,
	MSG_Menu_Sound_Volume_Mute,
	MSG_Menu_Sound_Volume_Value,
	MSG_Menu_Sound_Rate,
	MSG_Menu_Sound_Rate_Hz,
	MSG_Menu_Sound_Channels,
	MSG_Menu_Sound_Channels_Tone,
	MSG_Menu_Sound_Channels_Noises,
	MSG_Menu_Sound_Dump,
	MSG_Menu_Sound_Dump_WAV_Start,
	MSG_Menu_Sound_Dump_WAV_Stop,
	MSG_Menu_Sound_Dump_VGM_Start,
	MSG_Menu_Sound_Dump_VGM_Stop,
	MSG_Menu_Sound_Dump_VGM_SampleAccurate,
	
	MSG_Menu_Inputs,
	MSG_Menu_Inputs_Joypad,
	MSG_Menu_Inputs_LightPhaser,
	MSG_Menu_Inputs_PaddleControl,
	MSG_Menu_Inputs_SportsPad,
	MSG_Menu_Inputs_GraphicBoard,
	MSG_Menu_Inputs_SK1100,
	MSG_Menu_Inputs_RapidFire,
	MSG_Menu_Inputs_RapidFire_PxBx,
	MSG_Menu_Inputs_Configuration,
	
	MSG_Menu_Tools,
	MSG_Menu_Tools_Messages,
	MSG_Menu_Tools_Palette,
	MSG_Menu_Tools_TilesViewer,
	MSG_Menu_Tools_TilemapViewer,
	MSG_Menu_Tools_TechInfo,
	MSG_Menu_Tools_MemoryEditor,
	
	MSG_Menu_Help,
	MSG_Menu_Help_Documentation,
	MSG_Menu_Help_Documentation_W,
	MSG_Menu_Help_Documentation_U,
	MSG_Menu_Help_Compat,
	MSG_Menu_Help_Multiplayer_Games,
	MSG_Menu_Help_Changes,
	MSG_Menu_Help_Debugger,
	MSG_Menu_Help_About,

	// Number of messages
	MSG_MAX,
};

//-----------------------------------------------------------------------------

#ifdef __MESSAGE_C__
#define __MSG_ADD(ID)   { #ID, ID }
static const S2I_TYPE Msg_Translation_Table [] =
{
	__MSG_ADD(MSG_Welcome),
	__MSG_ADD(MSG_Window_Title),
	__MSG_ADD(MSG_Quit),

	__MSG_ADD(MSG_About_BoxTitle),
	__MSG_ADD(MSG_About_Line_Meka_Date),
	__MSG_ADD(MSG_About_Line_Authors),
	__MSG_ADD(MSG_About_Line_Homepage),

	__MSG_ADD(MSG_Ok),
	__MSG_ADD(MSG_Failed),
	__MSG_ADD(MSG_Error_Base),
	__MSG_ADD(MSG_Error_Error),
	__MSG_ADD(MSG_Error_Memory),
	__MSG_ADD(MSG_Error_Param),
	__MSG_ADD(MSG_Error_Syntax),

	__MSG_ADD(MSG_Error_Video_Mode),
	__MSG_ADD(MSG_Error_Video_Mode_Back_To_GUI),

	__MSG_ADD(MSG_Error_File_Not_Found),
	__MSG_ADD(MSG_Error_File_Read),
	__MSG_ADD(MSG_Error_File_Empty),

	__MSG_ADD(MSG_Error_ZIP_Not_Supported),
	__MSG_ADD(MSG_Error_ZIP_Loading),
	__MSG_ADD(MSG_Error_ZIP_Internal),

	__MSG_ADD(MSG_Error_Directory_Open),

	__MSG_ADD(MSG_Must_Reset),
	__MSG_ADD(MSG_No_ROM),

	__MSG_ADD(MSG_Init_Allegro),
	__MSG_ADD(MSG_Init_GUI),
	__MSG_ADD(MSG_Init_Completed),

	__MSG_ADD(MSG_Setup_Running),
	__MSG_ADD(MSG_Setup_Setup),
	__MSG_ADD(MSG_Setup_Soundcard_Select),
	__MSG_ADD(MSG_Setup_Soundcard_Select_Tips_DOS),
	__MSG_ADD(MSG_Setup_Soundcard_Select_Tips_Win32),
	__MSG_ADD(MSG_Setup_SampleRate_Select),
	__MSG_ADD(MSG_Setup_Debugger_Enable),

	__MSG_ADD(MSG_Capture_Done),
	__MSG_ADD(MSG_Capture_Error),
	__MSG_ADD(MSG_Capture_Error_File),

	__MSG_ADD(MSG_SRAM_Loaded),
	__MSG_ADD(MSG_SRAM_Load_Unable),
	__MSG_ADD(MSG_SRAM_Wrote),
	__MSG_ADD(MSG_SRAM_Write_Unable),

	__MSG_ADD(MSG_93c46_Reset),
	__MSG_ADD(MSG_93c46_Loaded),
	__MSG_ADD(MSG_93c46_Load_Unable),
	__MSG_ADD(MSG_93c46_Wrote),
	__MSG_ADD(MSG_93c46_Write_Unable),

	__MSG_ADD(MSG_TVType_Set),
	__MSG_ADD(MSG_TVType_Info_Speed),

	__MSG_ADD(MSG_Blitters_Loading),
	__MSG_ADD(MSG_Blitters_Error_Not_Enough),
	__MSG_ADD(MSG_Blitters_Error_Not_Found),
	__MSG_ADD(MSG_Blitters_Error_Missing),
	__MSG_ADD(MSG_Blitters_Error_Unrecognized),
	__MSG_ADD(MSG_Blitters_Error_Incorrect_Value),
	__MSG_ADD(MSG_Blitters_Set),

	__MSG_ADD(MSG_NES_Activate),
	__MSG_ADD(MSG_NES_Sucks),
	__MSG_ADD(MSG_NES_Mapper_Unknown),
	__MSG_ADD(MSG_NES_Deny_Facts),

	__MSG_ADD(MSG_Debug_Init),
	__MSG_ADD(MSG_Debug_Welcome),
	__MSG_ADD(MSG_Debug_Not_Available),
	__MSG_ADD(MSG_Debug_Brk_Need_Param),
	__MSG_ADD(MSG_Debug_Trap_Read),
	__MSG_ADD(MSG_Debug_Trap_Write),
	__MSG_ADD(MSG_Debug_Trap_Port_Read),
	__MSG_ADD(MSG_Debug_Trap_Port_Write),
	__MSG_ADD(MSG_Debug_Symbols_Loaded),
	__MSG_ADD(MSG_Debug_Symbols_Error),
	__MSG_ADD(MSG_Debug_Symbols_Error_Line),

	__MSG_ADD(MSG_DataDump_Mode_Ascii),
	__MSG_ADD(MSG_DataDump_Mode_Raw),
	__MSG_ADD(MSG_DataDump_Error),
	__MSG_ADD(MSG_DataDump_Error_OB_Memory),
	__MSG_ADD(MSG_DataDump_Error_Palette),
	__MSG_ADD(MSG_DataDump_Error_Sprites),
	__MSG_ADD(MSG_DataDump_Main),

	__MSG_ADD(MSG_Doc_BoxTitle),
	__MSG_ADD(MSG_Doc_File_Error),
	__MSG_ADD(MSG_Doc_Enabled),
	__MSG_ADD(MSG_Doc_Disabled),

	__MSG_ADD(MSG_Flickering_Auto),
	__MSG_ADD(MSG_Flickering_Yes),
	__MSG_ADD(MSG_Flickering_No),

	__MSG_ADD(MSG_Layer_BG_Disabled),
	__MSG_ADD(MSG_Layer_BG_Enabled),
	__MSG_ADD(MSG_Layer_Spr_Disabled),
	__MSG_ADD(MSG_Layer_Spr_Enabled),

	__MSG_ADD(MSG_FDC765_Unknown_Read),
	__MSG_ADD(MSG_FDC765_Unknown_Write),
	__MSG_ADD(MSG_FDC765_Disk_Too_Large1),
	__MSG_ADD(MSG_FDC765_Disk_Too_Large2),
	__MSG_ADD(MSG_FDC765_Disk_Too_Small1),
	__MSG_ADD(MSG_FDC765_Disk_Too_Small2),

	__MSG_ADD(MSG_TVOekaki_Pen_Touch),
	__MSG_ADD(MSG_TVOekaki_Pen_Away),

	__MSG_ADD(MSG_Palette_BoxTitle),
	__MSG_ADD(MSG_Palette_Disabled),
	__MSG_ADD(MSG_Palette_Enabled),

	__MSG_ADD(MSG_Message_BoxTitle),
	__MSG_ADD(MSG_Message_Disabled),
	__MSG_ADD(MSG_Message_Enabled),

	__MSG_ADD(MSG_TechInfo_BoxTitle),
	__MSG_ADD(MSG_TechInfo_Disabled),
	__MSG_ADD(MSG_TechInfo_Enabled),

	__MSG_ADD(MSG_TilesViewer_BoxTitle),
	__MSG_ADD(MSG_TilesViewer_Disabled),
	__MSG_ADD(MSG_TilesViewer_Enabled),
	__MSG_ADD(MSG_TilesViewer_Tile),

	__MSG_ADD(MSG_MemoryEditor_BoxTitle),
	__MSG_ADD(MSG_MemoryEditor_Disabled),
	__MSG_ADD(MSG_MemoryEditor_Enabled),
	__MSG_ADD(MSG_MemoryEditor_WriteZ80_Unable),
	__MSG_ADD(MSG_MemoryEditor_Address_Out_of_Bound),

	__MSG_ADD(MSG_RapidFire_JxBx_On),
	__MSG_ADD(MSG_RapidFire_JxBx_Off),

	__MSG_ADD(MSG_FM_Enabled),
	__MSG_ADD(MSG_FM_Disabled),

	__MSG_ADD(MSG_Country_European_US),
	__MSG_ADD(MSG_Country_JAP),

	__MSG_ADD(MSG_Patch_Loading),
	__MSG_ADD(MSG_Patch_Missing),
	__MSG_ADD(MSG_Patch_Unrecognized),
	__MSG_ADD(MSG_Patch_Value_Not_a_Byte),
	__MSG_ADD(MSG_Patch_Out_of_Bound),

	__MSG_ADD(MSG_Glasses_Enabled),
	__MSG_ADD(MSG_Glasses_Disabled),
	__MSG_ADD(MSG_Glasses_Show_Both),
	__MSG_ADD(MSG_Glasses_Show_Left),
	__MSG_ADD(MSG_Glasses_Show_Right),
	__MSG_ADD(MSG_Glasses_Com_Port),
	__MSG_ADD(MSG_Glasses_Com_Port2),
	__MSG_ADD(MSG_Glasses_Com_Port_Open_Error),
	__MSG_ADD(MSG_Glasses_Unsupported),

	__MSG_ADD(MSG_Inputs_Joy_Init),
	__MSG_ADD(MSG_Inputs_Joy_Init_None),
	__MSG_ADD(MSG_Inputs_Joy_Init_Found),
	__MSG_ADD(MSG_Inputs_Joy_Calibrate_Error),

	__MSG_ADD(MSG_Inputs_Joypad),
	__MSG_ADD(MSG_Inputs_LightPhaser),
	__MSG_ADD(MSG_Inputs_PaddleControl),
	__MSG_ADD(MSG_Inputs_SportsPad),
	__MSG_ADD(MSG_Inputs_TVOekaki),
	__MSG_ADD(MSG_Inputs_Play_Digital),
	__MSG_ADD(MSG_Inputs_Play_Mouse),
	__MSG_ADD(MSG_Inputs_Play_Digital_Unrecommended),
	__MSG_ADD(MSG_Inputs_Play_Pen),
	__MSG_ADD(MSG_Inputs_SK1100_Enabled),
	__MSG_ADD(MSG_Inputs_SK1100_Disabled),

	__MSG_ADD(MSG_Inputs_Config_BoxTitle),
	__MSG_ADD(MSG_Inputs_Config_Peripheral_Click),
	__MSG_ADD(MSG_Inputs_Config_Source_Enabled),
	__MSG_ADD(MSG_Inputs_Config_Source_Player),
	__MSG_ADD(MSG_Inputs_Config_Source_Emulate_Joypad),

	__MSG_ADD(MSG_Inputs_Src_Loading),
	__MSG_ADD(MSG_Inputs_Src_Not_Enough),
	__MSG_ADD(MSG_Inputs_Src_Missing),
	__MSG_ADD(MSG_Inputs_Src_Equal),
	__MSG_ADD(MSG_Inputs_Src_Unrecognized),
	__MSG_ADD(MSG_Inputs_Src_Syntax_Param),
	__MSG_ADD(MSG_Inputs_Src_Inconsistency),
	__MSG_ADD(MSG_Inputs_Src_Map_Keyboard),
	__MSG_ADD(MSG_Inputs_Src_Map_Keyboard_Ok),
	__MSG_ADD(MSG_Inputs_Src_Map_Joypad),
	__MSG_ADD(MSG_Inputs_Src_Map_Joypad_Ok_A),
	__MSG_ADD(MSG_Inputs_Src_Map_Joypad_Ok_B),
	__MSG_ADD(MSG_Inputs_Src_Map_Mouse),
	__MSG_ADD(MSG_Inputs_Src_Map_Mouse_Ok_B),
	__MSG_ADD(MSG_Inputs_Src_Map_Mouse_No_A),
	__MSG_ADD(MSG_Inputs_Src_Map_Cancelled),

	__MSG_ADD(MSG_Machine_Pause),
	__MSG_ADD(MSG_Machine_Resume),
	__MSG_ADD(MSG_Machine_Reset),

	__MSG_ADD(MSG_FDB_Loading),

	__MSG_ADD(MSG_DB_Loading),
	__MSG_ADD(MSG_DB_Name_Default),
	__MSG_ADD(MSG_DB_Name_NoCartridge),
	__MSG_ADD(MSG_DB_SyntaxError),

	__MSG_ADD(MSG_Config_Loading),

	__MSG_ADD(MSG_Datafile_Loading),

	__MSG_ADD(MSG_Driver_Unknown),

	__MSG_ADD(MSG_OverDump),

	__MSG_ADD(MSG_Sound_Init),
	__MSG_ADD(MSG_Sound_Init_Error_SEAL),
	__MSG_ADD(MSG_Sound_Init_Error_Audio),
	__MSG_ADD(MSG_Sound_Init_Error_Blaster),
	__MSG_ADD(MSG_Sound_Init_Error_Blaster_A),
	__MSG_ADD(MSG_Sound_Init_Error_Voices),
	__MSG_ADD(MSG_Sound_Init_Error_Voice_N),
	__MSG_ADD(MSG_Sound_Init_Soundcard),
	__MSG_ADD(MSG_Sound_Init_Soundcard_No),
	__MSG_ADD(MSG_Sound_Init_SN76496),
	__MSG_ADD(MSG_Sound_Init_YM2413_OPL),
	__MSG_ADD(MSG_Sound_Init_YM2413_Digital),
	__MSG_ADD(MSG_Sound_Rate_Changed),
	__MSG_ADD(MSG_Sound_Stream_Error),
	__MSG_ADD(MSG_Sound_Volume_Changed),

	__MSG_ADD(MSG_Theme_Loading),
	__MSG_ADD(MSG_Theme_Error_Not_Enough),
	__MSG_ADD(MSG_Theme_Error_Missing_Theme_Name),
	__MSG_ADD(MSG_Theme_Error_Syntax),
	__MSG_ADD(MSG_Theme_Error_Attribute_Defined),
	__MSG_ADD(MSG_Theme_Error_Out_of_Bound),
	__MSG_ADD(MSG_Theme_Error_Theme_Missing_Data),
	__MSG_ADD(MSG_Theme_Error_BG_Big),
	__MSG_ADD(MSG_Theme_Error_BG),
	__MSG_ADD(MSG_Theme_Error_BG_FileName),

	__MSG_ADD(MSG_LoadROM_Loading),
	__MSG_ADD(MSG_LoadROM_Success),
	__MSG_ADD(MSG_LoadDisk_Success),
	__MSG_ADD(MSG_LoadROM_Comment),
	__MSG_ADD(MSG_LoadROM_SMSGG_Mode_Comment),
	__MSG_ADD(MSG_LoadROM_Warning),
	__MSG_ADD(MSG_LoadROM_Bad_Dump_Long),
	__MSG_ADD(MSG_LoadROM_Bad_Dump_Short),
	__MSG_ADD(MSG_LoadROM_Product_Num),
	__MSG_ADD(MSG_LoadROM_SDSC),
	__MSG_ADD(MSG_LoadROM_SDSC_Name),
	__MSG_ADD(MSG_LoadROM_SDSC_Version),
	__MSG_ADD(MSG_LoadROM_SDSC_Date),
	__MSG_ADD(MSG_LoadROM_SDSC_Author),
	__MSG_ADD(MSG_LoadROM_SDSC_Release_Note),
	__MSG_ADD(MSG_LoadROM_SDSC_Unknown),
	__MSG_ADD(MSG_LoadROM_SDSC_Error),
	__MSG_ADD(MSG_LoadROM_Reload_Reloaded),
	__MSG_ADD(MSG_LoadROM_Reload_No_ROM),

	__MSG_ADD(MSG_FileBrowser_BoxTitle),
	__MSG_ADD(MSG_FileBrowser_Drive),
	__MSG_ADD(MSG_FileBrowser_Load),
	__MSG_ADD(MSG_FileBrowser_Close),
	__MSG_ADD(MSG_FileBrowser_LoadNames),
	__MSG_ADD(MSG_FileBrowser_ReloadDir),

	__MSG_ADD(MSG_FM_Editor_BoxTitle),
	__MSG_ADD(MSG_FM_Editor_Enabled),
	__MSG_ADD(MSG_FM_Editor_Disabled),

	__MSG_ADD(MSG_Frameskip_Auto),
	__MSG_ADD(MSG_Frameskip_Standard),
	__MSG_ADD(MSG_FPS_Counter_Enabled),
	__MSG_ADD(MSG_FPS_Counter_Disabled),

	__MSG_ADD(MSG_Log_Need_Param),
	__MSG_ADD(MSG_Log_Session_Start),

	__MSG_ADD(MSG_Load_Need_Param),
	__MSG_ADD(MSG_Load_Error),
	__MSG_ADD(MSG_Load_Not_Valid),
	__MSG_ADD(MSG_Load_Success),
	__MSG_ADD(MSG_Load_Version),
	__MSG_ADD(MSG_Load_Wrong_System),
	__MSG_ADD(MSG_Load_Massage),
	__MSG_ADD(MSG_Save_Not_in_BIOS),
	__MSG_ADD(MSG_Save_Error),
	__MSG_ADD(MSG_Save_Success),
	__MSG_ADD(MSG_Save_Slot),

	__MSG_ADD(MSG_Options_BoxTitle),
	__MSG_ADD(MSG_Options_Close),
	__MSG_ADD(MSG_Options_BIOS_Enable),
	__MSG_ADD(MSG_Options_DB_Display),
	__MSG_ADD(MSG_Options_Product_Number),
	__MSG_ADD(MSG_Options_Bright_Palette),
	__MSG_ADD(MSG_Options_Allow_Opposite_Directions),
	__MSG_ADD(MSG_Options_Load_Close),
	__MSG_ADD(MSG_Options_Load_FullScreen),
	__MSG_ADD(MSG_Options_FullScreen_Messages),
	__MSG_ADD(MSG_Options_GUI_VSync),
	__MSG_ADD(MSG_Options_Capture_Crop_Align),
	__MSG_ADD(MSG_Options_NES_Enable),

	__MSG_ADD(MSG_Language_Set),
	__MSG_ADD(MSG_Language_Set_Warning),

	__MSG_ADD(MSG_Sound_Dumping_Start),
	__MSG_ADD(MSG_Sound_Dumping_Stop),
	__MSG_ADD(MSG_Sound_Dumping_Error_File_1),
	__MSG_ADD(MSG_Sound_Dumping_Error_File_2),
	__MSG_ADD(MSG_Sound_Dumping_VGM_Acc_Frame),
	__MSG_ADD(MSG_Sound_Dumping_VGM_Acc_Sample),
	__MSG_ADD(MSG_Sound_Dumping_VGM_Acc_Change),

	__MSG_ADD(MSG_Menu_Main),
	__MSG_ADD(MSG_Menu_Main_LoadROM),
	__MSG_ADD(MSG_Menu_Main_FreeROM),
	__MSG_ADD(MSG_Menu_Main_SaveState),
	__MSG_ADD(MSG_Menu_Main_LoadState),
	__MSG_ADD(MSG_Menu_Main_Options),
	__MSG_ADD(MSG_Menu_Main_Language),
	__MSG_ADD(MSG_Menu_Main_Quit),

	__MSG_ADD(MSG_Menu_Debug),
	__MSG_ADD(MSG_Menu_Debug_Enabled),
	__MSG_ADD(MSG_Menu_Debug_Reload_ROM),
	__MSG_ADD(MSG_Menu_Debug_Dump),

	__MSG_ADD(MSG_Menu_Machine),
	__MSG_ADD(MSG_Menu_Machine_Power),
	__MSG_ADD(MSG_Menu_Machine_Power_On),
	__MSG_ADD(MSG_Menu_Machine_Power_Off),
	__MSG_ADD(MSG_Menu_Machine_Country),
	__MSG_ADD(MSG_Menu_Machine_Country_EU),
	__MSG_ADD(MSG_Menu_Machine_Country_Jap),
	__MSG_ADD(MSG_Menu_Machine_TVType),
	__MSG_ADD(MSG_Menu_Machine_TVType_NTSC),
	__MSG_ADD(MSG_Menu_Machine_TVType_PALSECAM),
	__MSG_ADD(MSG_Menu_Machine_HardPause),
	__MSG_ADD(MSG_Menu_Machine_HardReset),

	__MSG_ADD(MSG_Menu_Video),
	__MSG_ADD(MSG_Menu_Video_FullScreen),
	__MSG_ADD(MSG_Menu_Video_Themes),
	__MSG_ADD(MSG_Menu_Video_Blitters),
	__MSG_ADD(MSG_Menu_Video_Layers),
	__MSG_ADD(MSG_Menu_Video_Layers_Sprites),
	__MSG_ADD(MSG_Menu_Video_Layers_Background),
	__MSG_ADD(MSG_Menu_Video_Flickering),
	__MSG_ADD(MSG_Menu_Video_Flickering_Auto),
	__MSG_ADD(MSG_Menu_Video_Flickering_Yes),
	__MSG_ADD(MSG_Menu_Video_Flickering_No),
	__MSG_ADD(MSG_Menu_Video_3DGlasses),
	__MSG_ADD(MSG_Menu_Video_3DGlasses_Enabled),
	__MSG_ADD(MSG_Menu_Video_3DGlasses_ShowBothSides),
	__MSG_ADD(MSG_Menu_Video_3DGlasses_ShowLeftSide),
	__MSG_ADD(MSG_Menu_Video_3DGlasses_ShowRightSide),
	__MSG_ADD(MSG_Menu_Video_3DGlasses_UsesCOMPort),
	__MSG_ADD(MSG_Menu_Video_Capture),
	__MSG_ADD(MSG_Menu_Video_Capture_CaptureScreen),
	__MSG_ADD(MSG_Menu_Video_Capture_CaptureScreenAll),
	__MSG_ADD(MSG_Menu_Video_Capture_IncludeGui),

	__MSG_ADD(MSG_Menu_Sound),
	__MSG_ADD(MSG_Menu_Sound_FM),
	__MSG_ADD(MSG_Menu_Sound_FM_Enabled),
	__MSG_ADD(MSG_Menu_Sound_FM_Disabled),
	__MSG_ADD(MSG_Menu_Sound_FM_Emulator),
	__MSG_ADD(MSG_Menu_Sound_FM_Emulator_OPL),
	__MSG_ADD(MSG_Menu_Sound_FM_Emulator_Digital),
	__MSG_ADD(MSG_Menu_Sound_FM_Editor),
	__MSG_ADD(MSG_Menu_Sound_Volume),
	__MSG_ADD(MSG_Menu_Sound_Volume_Mute),
	__MSG_ADD(MSG_Menu_Sound_Volume_Value),
	__MSG_ADD(MSG_Menu_Sound_Rate),
	__MSG_ADD(MSG_Menu_Sound_Rate_Hz),
	__MSG_ADD(MSG_Menu_Sound_Channels),
	__MSG_ADD(MSG_Menu_Sound_Channels_Tone),
	__MSG_ADD(MSG_Menu_Sound_Channels_Noises),
	__MSG_ADD(MSG_Menu_Sound_Dump),
	__MSG_ADD(MSG_Menu_Sound_Dump_WAV_Start),
	__MSG_ADD(MSG_Menu_Sound_Dump_WAV_Stop),
	__MSG_ADD(MSG_Menu_Sound_Dump_VGM_Start),
	__MSG_ADD(MSG_Menu_Sound_Dump_VGM_Stop),
	__MSG_ADD(MSG_Menu_Sound_Dump_VGM_SampleAccurate),

	__MSG_ADD(MSG_Menu_Inputs),
	__MSG_ADD(MSG_Menu_Inputs_Joypad),
	__MSG_ADD(MSG_Menu_Inputs_LightPhaser),
	__MSG_ADD(MSG_Menu_Inputs_PaddleControl),
	__MSG_ADD(MSG_Menu_Inputs_SportsPad),
	__MSG_ADD(MSG_Menu_Inputs_GraphicBoard),
	__MSG_ADD(MSG_Menu_Inputs_SK1100),
	__MSG_ADD(MSG_Menu_Inputs_RapidFire),
	__MSG_ADD(MSG_Menu_Inputs_RapidFire_PxBx),
	__MSG_ADD(MSG_Menu_Inputs_Configuration),

	__MSG_ADD(MSG_Menu_Tools),
	__MSG_ADD(MSG_Menu_Tools_Messages),
	__MSG_ADD(MSG_Menu_Tools_Palette),
	__MSG_ADD(MSG_Menu_Tools_TilesViewer),
	__MSG_ADD(MSG_Menu_Tools_TilemapViewer),
	__MSG_ADD(MSG_Menu_Tools_TechInfo),
	__MSG_ADD(MSG_Menu_Tools_MemoryEditor),

	__MSG_ADD(MSG_Menu_Help),
	__MSG_ADD(MSG_Menu_Help_Documentation),
	__MSG_ADD(MSG_Menu_Help_Documentation_W),
	__MSG_ADD(MSG_Menu_Help_Documentation_U),
	__MSG_ADD(MSG_Menu_Help_Compat),
	__MSG_ADD(MSG_Menu_Help_Multiplayer_Games),
	__MSG_ADD(MSG_Menu_Help_Changes),
	__MSG_ADD(MSG_Menu_Help_Debugger),
	__MSG_ADD(MSG_Menu_Help_About),

	{ NULL, MSG_NULL }
};
#undef __MSG_ADD
#endif

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

// Structure storing messages for one supported language
typedef struct
{
    char *      Name;
    char *      Messages[MSG_MAX];
    int         WIP;
}               t_lang;

//-----------------------------------------------------------------------------

void            Lang_Set_by_Name (char *name);
void            Langs_Menu_Add (int menu_id);

//-----------------------------------------------------------------------------

// Structure storing localization basis stuff and all supported languages
typedef struct
{
    char        FileName [FILENAME_LEN];      // path to the MEKA.MSG file
    t_lang *    Lang_Cur;
    t_lang *    Lang_Default;
    t_list *    Langs;
}               t_messages;

t_messages      Messages;

//-----------------------------------------------------------------------------
// Functions - Message
//-----------------------------------------------------------------------------

// Load messages from MEKA.MSG file (path given in structure)
// Return a MEKA_ERR_xxx code
int     Messages_Init (void);

// Get specified message string
static INLINE const char *    Msg_Get(int n)
{
    return Messages.Lang_Cur->Messages[n];
}

// Send a message to the user and/or debugging message
void    Msg (int attr, const char *format, ...) FORMAT_PRINTF (2);

//-----------------------------------------------------------------------------
// Functions - Console
//-----------------------------------------------------------------------------

void    ConsoleInit         (void);
void    ConsoleClose        (void);
void    ConsolePrintf       (const char *format, ...) FORMAT_PRINTF (1);
void    ConsolePrint        (const char *msg);
void    ConsoleEnablePause  (void);
bool    ConsoleWaitForAnswer(bool allow_run);

//-- Old Messages (friends versions) ------------------------------------------
// #define Message_Welcome_Joseph   "Joyeux Anniversaire Joseph !! ^_^"
// #define Message_Welcome_Arnaud   "Que demander de mieux qu'un entourage de personnes a la fois passionnantes et talentueuses ? .. Donc voila une superbe version dedicacee de Mekarno, et tout et tout. Tu pourras meme prendre des captures avec F12 et les accrocher sur tes murs - j'en suis sur que tu le feras d'abord, hein avoues! Finissons donc cette dedicace avec des mots offrant le plus doux tes spectacles a ton ame talentueuse. Que le bonheur t'ennivre milles et une fois et que chaque moment puisse t'etre unique et jouissif a sa facon. Mine de rien je pourrais faire poete si je ne suis pas programmeur. Hehehe. Amuse toi bien! (PS: je passes chercher les cartons de jeux SMS quand tu veux! :) (PS2: et je te prend a n'importe quel jeu!)"

//-----------------------------------------------------------------------------
