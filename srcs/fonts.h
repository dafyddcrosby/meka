//-----------------------------------------------------------------------------
// MEKA - fonts.h
// Fonts Tools (mostly wrapping Allegro functionalities) - Headers
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

#define         F_LARGE                 (0)
#define         F_MIDDLE                (1)
#define         F_SMALL                 (2)
#define         MEKA_FONT_MAX           (3)

#define         MEKA_FONT_STR_STAR      "\xC2\x80"	// 128 in UTF8
#define         MEKA_FONT_STR_CHECKED   "\xC2\x81"	// 129 in UTF8
#define         MEKA_FONT_STR_ARROW     ">"			// (not using the one stored at 130)

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

struct t_font
{
    int				id;
    ALLEGRO_FONT *	library_data;
    int				height;
};

extern t_font		Fonts[MEKA_FONT_MAX];
extern t_font *		FontCurrent;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void    Fonts_Init          (void);
void    Fonts_Close         (void);
void    Fonts_DeclareFont   (int font_id, ALLEGRO_FONT *library_data);

//-----------------------------------------------------------------------------

void    Font_SetCurrent     (int font_id);
void    Font_Print          (int font_id, ALLEGRO_BITMAP *dst, const char *text, int x, int y, ALLEGRO_COLOR color);
void    Font_PrintCentered  (int font_id, ALLEGRO_BITMAP *dst, const char *text, int x, int y, ALLEGRO_COLOR color);
int     Font_Height         (int font_id);
int     Font_TextLength     (int font_id, const char *text);

//-----------------------------------------------------------------------------

