//-----------------------------------------------------------------------------
// MEKA - palette.c
// Palette management - Code
//-----------------------------------------------------------------------------
// Dynamic palette management which reference count and attempting to
// minimize hardware palette change.
//-----------------------------------------------------------------------------

#include "shared.h"
#include "blit.h"
#include "blitintf.h"
#include "palette.h"
#include "nes.h"
#include "video_m2.h"

// #define DEBUG_PALETTE

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

RGB     Palette_Emulation[PALETTE_EMU_GAME_SIZE];
int     Palette_EmulationToHost[PALETTE_EMU_GAME_SIZE];
int     Palette_EmulationToHost16[PALETTE_EMU_GAME_SIZE];
int     Palette_EmulationFlags[PALETTE_EMU_GAME_SIZE];
bool    Palette_EmulationDirtyAny;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Palette_Init ()
// Initialize palette engine
//-----------------------------------------------------------------------------
void    Palette_Init (void)
{

    Palette_Emulation_Reset();

#if 0
    int   i;
    // Clear hardware palette
    Palette_Dirty_All = TRUE;
    for (i = 0; i < 256; i++)
    {
        RGB *c = &Palette_Current[i];
        c->r = c->g = c->b = c->filler = 0;
    }

    // Clear emulation palette
    Palette_Emu_Cycle_Start = 0;
    Palette_Emu_Dirty_Any = FALSE;
    for (i = 0; i != PALETTE_EMU_GAME_SIZE; i++)
    {
        t_color_infos *ci = &Palette_Emu_Infos[i];
        ci->idx   = i;  // Palette_Infos[] cover first 64 colors linearly
        ci->refs  = 0;  // No references yet
        ci->dirty = FALSE; // Not changed
        ci->lock  = FALSE; // Not locked
    }

    // Clear emulation references
    Palette_Refs_Dirty_Any = FALSE;
    for (i = 0; i < PALETTE_EMU_GAME_SIZE ; i++)
    {
        Palette_Refs [i] = 0;
        Palette_Refs_Dirty [i] = FALSE;
    }
#endif
}

//-----------------------------------------------------------------------------
// Palette_Close ()
// Close palette engine
//-----------------------------------------------------------------------------
void    Palette_Close (void)
{
}

void    Palette_UpdateAfterRedraw()
{
    // Clear dirty flags
    int i;
    for (i = 0; i != PALETTE_EMU_GAME_SIZE; i++)
        Palette_EmulationFlags[i] &= ~PALETTE_EMULATION_FLAGS_DIRTY;
    Palette_EmulationDirtyAny = FALSE;
}

void    Palette_Emulation_Reset()
{
    int i;
    for (i = 0; i != PALETTE_EMU_GAME_SIZE; i++)
    {
        Palette_Emulation[i].r = Palette_Emulation[i].g = Palette_Emulation[i].b = Palette_Emulation[i].filler = 0;
        Palette_EmulationToHost[i] = COLOR_BLACK;
        Palette_EmulationToHost16[i] = COLOR_BLACK;
        Palette_EmulationFlags[i] = PALETTE_EMULATION_FLAGS_DIRTY;
    }
    Palette_EmulationDirtyAny = TRUE;
    Palette_Emulation_Reload();
}

// Reload palette data (fixed or from PRAM) -----------------------------------
// Called when changing video mode on the fly ---------------------------------
void    Palette_Emulation_Reload (void)
{
    int   i;
    RGB   color;

    switch (cur_drv->vdp)
    {
    case VDP_TMS9918:  
        TMS9918_Palette_Set();
        return;
    case VDP_NES:
        NES_Palette_Set();
        return;
    }

    // cur_drv->vdp == VDP_SMSGG
    // SMS/GG Palette will be reloaded
#ifdef DEBUG_PALETTE
    Msg (MSGT_DEBUG, "Palette_Emulation_Reload() SMS/GG");
#endif

    switch (cur_drv->id)
    {
    case DRV_SMS:
        for (i = 0; i != 32; i++)
        {
            Palette_Compute_RGB_SMS(&color, i);
            Palette_Emulation_SetColor(i, color);
        }
        break;
    case DRV_GG:
        for (i = 0; i != 32; i++)
        {
            Palette_Compute_RGB_GG(&color, i * 2);
            Palette_Emulation_SetColor(i, color);
        }
        break;
    }
}

void    Palette_Emulation_SetColor(int idx, RGB color)
{
    assert(idx >= 0 && idx < 32);
    Palette_Emulation[idx] = color;
    Palette_EmulationToHost[idx] = makecol(color.r, color.g, color.b);
    Palette_EmulationToHost16[idx] = makecol16(color.r, color.g, color.b);
    Palette_EmulationFlags[idx] |= PALETTE_EMULATION_FLAGS_DIRTY;
    Palette_EmulationDirtyAny = TRUE;
}

//-----------------------------------------------------------------------------

// FIXME: Use tables instead of the functions below?

void    Palette_Compute_RGB_SMS (RGB *out_color, int i)
{
	RGB tmp;
    int v;

    v = PRAM[i] & 0x03;
    tmp.r = (v) | (v << 2) | (v << 4) | (v << 6);

    v = (PRAM[i] >> 2) & 0x03;
    tmp.g = (v) | (v << 2) | (v << 4) | (v << 6);

    v = (PRAM[i] >> 4) & 0x03;
    tmp.b = (v) | (v << 2) | (v << 4) | (v << 6);

    // FIXME: Is this still needed?
    tmp.filler = 0;

    // Save output
	*out_color = tmp;
}

// Note: if changing the meaning of 'i', please update datadump.c which uses it
void    Palette_Compute_RGB_GG (RGB *out_color, int i)
{
	RGB tmp;
    int v;

    // ----bbbb ggggrrrr (GG) -> --rrrrrr --gggggg --bbbbbb (RGB)
	v = PRAM[i] & 0x0F;
	tmp.r = (v) | (v << 4);

	v = PRAM[i] & 0xF0;
	tmp.g = (v >> 4) | (v);

	v = PRAM[i + 1] & 0x0F;
	tmp.b = (v) | (v << 4);

    // FIXME: Is this still needed?
    tmp.filler = 0;

    // Save output
	*out_color = tmp;
}

//-----------------------------------------------------------------------------
