//-----------------------------------------------------------------------------
// Meka - video_m5.c
// SMS/GG Video Mode Rendering - Code
//-----------------------------------------------------------------------------
// Note: 'video_m5.h' is a legacy name. Should be renamed to video_m4 ?
//-----------------------------------------------------------------------------

#include "shared.h"
#include "fskipper.h"
#include "palette.h"
#include "vdp.h"
#include "video_m5.h"

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

static u16 *    GFX_Line16;

       int      Sprites_on_Line;
       int      Do_Collision;
static byte     Sprites_Draw_Mask [SMS_RES_X + 16];

#define         Sprites_Collision_Table_Len (SMS_RES_X + 32)
int             Sprites_Collision_Table_Start[Sprites_Collision_Table_Len + 32];
int *           Sprites_Collision_Table = Sprites_Collision_Table_Start + 16;

//-----------------------------------------------------------------------------
// Color configuration
// (Note: absolutly uses those define, so it'll be easier to switch to direct
//  24/32 output someday)
//-----------------------------------------------------------------------------

#define PIXEL_TYPE              u16
#define PIXEL_LINE_DST          GFX_Line16
#define PIXEL_PALETTE_TABLE     Palette_EmulationToHost16

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// Note: this is used by tools only (not actual emulation refresh)
void    VDP_Mode4_DrawTile(BITMAP *dst, const u8 *pixels, const int *palette_host, int x, int y, int flip)
{
    // FIXME-DEPTH
    switch (dst->vtable->color_depth)
    {
    case 16:
        {
            int i;
            if (flip & 0x0400)
            {
                y += 7;
                if (flip & 0x0200)
                {
                    // 0x0600 : HV Flip
                    for (i = 0; i != 8; i++)
                    {
                        u16 *dst8 = (u16 *)dst->line[y] + x;
                        dst8[7] = palette_host[*pixels++];
                        dst8[6] = palette_host[*pixels++];
                        dst8[5] = palette_host[*pixels++];
                        dst8[4] = palette_host[*pixels++];
                        dst8[3] = palette_host[*pixels++];
                        dst8[2] = palette_host[*pixels++];
                        dst8[1] = palette_host[*pixels++];
                        dst8[0] = palette_host[*pixels++];
                        y--;
                    }
                }
                else
                {
                    // 0x0400 : V flip
                    for (i = 0; i != 8; i++)
                    {
                        u16 *dst8 = (u16 *)dst->line[y] + x;
                        dst8[0] = palette_host[*pixels++];
                        dst8[1] = palette_host[*pixels++];
                        dst8[2] = palette_host[*pixels++];
                        dst8[3] = palette_host[*pixels++];
                        dst8[4] = palette_host[*pixels++];
                        dst8[5] = palette_host[*pixels++];
                        dst8[6] = palette_host[*pixels++];
                        dst8[7] = palette_host[*pixels++];
                        y--;
                    }
                }
            }
            else
            {
                if (flip & 0x0200)
                {
                    // 0x0200 : H Flip
                    for (i = 0; i != 8; i++)
                    {
                        u16 *dst8 = (u16 *)dst->line[y] + x;
                        dst8[7] = palette_host[*pixels++];
                        dst8[6] = palette_host[*pixels++];
                        dst8[5] = palette_host[*pixels++];
                        dst8[4] = palette_host[*pixels++];
                        dst8[3] = palette_host[*pixels++];
                        dst8[2] = palette_host[*pixels++];
                        dst8[1] = palette_host[*pixels++];
                        dst8[0] = palette_host[*pixels++];
                        y++;
                    }
                }
                else
                {
                    // 0x0000 : No flip
                    for (i = 0; i != 8; i++)
                    {
                        u16 *dst8 = (u16 *)dst->line[y] + x;
                        dst8[0] = palette_host[*pixels++];
                        dst8[1] = palette_host[*pixels++];
                        dst8[2] = palette_host[*pixels++];
                        dst8[3] = palette_host[*pixels++];
                        dst8[4] = palette_host[*pixels++];
                        dst8[5] = palette_host[*pixels++];
                        dst8[6] = palette_host[*pixels++];
                        dst8[7] = palette_host[*pixels++];
                        y++;
                    }
                }
            }
            break;
        }
    case 32:
        {
            int i;
            if (flip & 0x0400)
            {
                y += 7;
                if (flip & 0x0200)
                {
                    // 0x0600 : HV Flip
                    for (i = 0; i != 8; i++)
                    {
                        u32 *dst8 = (u32 *)dst->line[y] + x;
                        dst8[7] = palette_host[*pixels++];
                        dst8[6] = palette_host[*pixels++];
                        dst8[5] = palette_host[*pixels++];
                        dst8[4] = palette_host[*pixels++];
                        dst8[3] = palette_host[*pixels++];
                        dst8[2] = palette_host[*pixels++];
                        dst8[1] = palette_host[*pixels++];
                        dst8[0] = palette_host[*pixels++];
                        y--;
                    }
                }
                else
                {
                    // 0x0400 : V flip
                    for (i = 0; i != 8; i++)
                    {
                        u32 *dst8 = (u32 *)dst->line[y] + x;
                        dst8[0] = palette_host[*pixels++];
                        dst8[1] = palette_host[*pixels++];
                        dst8[2] = palette_host[*pixels++];
                        dst8[3] = palette_host[*pixels++];
                        dst8[4] = palette_host[*pixels++];
                        dst8[5] = palette_host[*pixels++];
                        dst8[6] = palette_host[*pixels++];
                        dst8[7] = palette_host[*pixels++];
                        y--;
                    }
                }
            }
            else
            {
                if (flip & 0x0200)
                {
                    // 0x0200 : H Flip
                    for (i = 0; i != 8; i++)
                    {
                        u32 *dst8 = (u32 *)dst->line[y] + x;
                        dst8[7] = palette_host[*pixels++];
                        dst8[6] = palette_host[*pixels++];
                        dst8[5] = palette_host[*pixels++];
                        dst8[4] = palette_host[*pixels++];
                        dst8[3] = palette_host[*pixels++];
                        dst8[2] = palette_host[*pixels++];
                        dst8[1] = palette_host[*pixels++];
                        dst8[0] = palette_host[*pixels++];
                        y++;
                    }
                }
                else
                {
                    // 0x0000 : No flip
                    for (i = 0; i != 8; i++)
                    {
                        u32 *dst8 = (u32 *)dst->line[y] + x;
                        dst8[0] = palette_host[*pixels++];
                        dst8[1] = palette_host[*pixels++];
                        dst8[2] = palette_host[*pixels++];
                        dst8[3] = palette_host[*pixels++];
                        dst8[4] = palette_host[*pixels++];
                        dst8[5] = palette_host[*pixels++];
                        dst8[6] = palette_host[*pixels++];
                        dst8[7] = palette_host[*pixels++];
                        y++;
                    }
                }
            }
            break;
        }
    default:
        assert(0);
        Msg(MSGT_USER, "TileViewer: unsupported color depth!");
        break;
    }

}

// REDRAW A SCREEN LINE -------------------------------------------------------
void    Refresh_Line_5 (void)
{
#ifdef CLOCK
	int clock_save = Clock[CLOCK_GFX_BACK].time;
#endif

	// Point to current video line
	GFX_Line16 = (u16 *)screenbuffer->line[tsms.VDP_Line];

	if (fskipper.Show_Current_Frame == TRUE)
	{
#ifdef CLOCK
		Clock_Start (CLOCK_GFX_BACK);
#endif

        // Scroll lock, update in X latch table (for tilemap viewer)
        if (Top_No_Scroll && tsms.VDP_Line < 16)
            cur_machine.VDP.scroll_x_latched_table[tsms.VDP_Line] = 0;

        // Display Background & Foreground
		if ((opt.Layer_Mask & LAYER_BACKGROUND) && Display_ON)
		{
			Display_BackGround_Line_5 ();
		}
		else
		{
			// Display is off
			// Select SMS/GG backdrop color, unless background layer display was disabled by user, then use custom color for easier sprite extraction
			const u16 backdrop_color = (opt.Layer_Mask & LAYER_BACKGROUND) ? Palette_EmulationToHost16[16 | (sms.VDP[7] & 15)] : makecol16(222,222,101);
			int n;
			u16 *p = GFX_Line16;
			for (n = 256; n != 0; n--)
				*p++ = backdrop_color;

			// Clear sprite draw mask, so that all sprite will be displayed
			memset(Sprites_Draw_Mask, 0, 256);
		}

#ifdef CLOCK
		Clock_Stop (CLOCK_GFX_BACK);
		Clock [CLOCK_GFX_BACK].time += clock_save;
		clock_save = Clock[CLOCK_GFX_SPRITES].time;
		Clock_Start (CLOCK_GFX_SPRITES);
#endif

		Refresh_Sprites_5 (Display_ON && (opt.Layer_Mask & LAYER_SPRITES));

#ifdef CLOCK
		Clock_Stop (CLOCK_GFX_SPRITES);
#endif

		// Mask left columns with black if necessary
		if (Mask_Left_8)
		{
			// FIXME-BORDER
			GFX_Line16[0] = COLOR_BLACK;
			GFX_Line16[1] = COLOR_BLACK;
			GFX_Line16[2] = COLOR_BLACK;
			GFX_Line16[3] = COLOR_BLACK;
			GFX_Line16[4] = COLOR_BLACK;
			GFX_Line16[5] = COLOR_BLACK;
			GFX_Line16[6] = COLOR_BLACK;
			GFX_Line16[7] = COLOR_BLACK;
		}
	}
	else
	{
		// Only update collision if frame is being skipped
		Refresh_Sprites_5 (FALSE);
	}
}

// DISPLAY A BACKGROUND LINE --------------------------------------------------
void    Display_BackGround_Line_5_C (void)
{
    PIXEL_TYPE *dst_buf;
    u8 *        src_map;
    u8 *        sprite_mask;
    int         x, x_scroll, x_ignore_vscroll, y;
    int         tile_x, tile_line;

    // X scrolling computations
    x_scroll = ((Top_No_Scroll) && (tsms.VDP_Line < 16)) ? 0 : cur_machine.VDP.scroll_x_latched;
    x = x_scroll & 7;  // x = x_scroll % 8
    x_scroll >>= 3;    // x_scroll /= 8
    if (x_scroll == 0)
        x_scroll = 32;

    // Set destination address
    dst_buf = PIXEL_LINE_DST;
    sprite_mask = Sprites_Draw_Mask;

    // Fill first 'non existents' pixels
    // (see SMS "Scrolling Test" for exemple of this)
    if (x > 0)
    {
        // If left column is masked, no need to care about what we put there
        // and not even the Sprite_Mask (it can stay undefined!)
        if (Mask_Left_8)
        {
            dst_buf += x;
            sprite_mask += x;
        }
        else
        {
            PIXEL_TYPE color = PIXEL_PALETTE_TABLE[0];
            int i;
            for (i = x; i != 0; i--)
            {
                *dst_buf++ = color;
                *sprite_mask++ = 0;
            }
        }
    }

    // Y scrolling computations
    y = tsms.VDP_Line + cur_machine.VDP.scroll_y_latched;
    if (Wide_Screen_28)
    {
        y &= 255; // y %= 256, Wrap at 256
        //y -= 32;
    }
    else
    {
        y %= 224;
    }

    // Bit 0 of Register 2 act as a mask on the 315-5124
    if (cur_machine.VDP.model == VDP_MODEL_315_5124)
        if ((sms.VDP[2] & 1) == 0)
            y &= 127;

    // Calculate source address & line in tile
    src_map = BACK_AREA + ((y & 0xFFFFFFF8) * 8) + (2 * (32 - x_scroll));
    tile_line = (y & 0x07) * 8;

    // Calculate position where vertical scrolling will be ignored
    x_ignore_vscroll = (Right_No_Scroll) ? 23 : -1;

    // Drawing loop
    tile_x = 0;
    while (tile_x < 32)
    {
        // Part of Horizontal Line not refreshed in Game Gear mode
        if ((cur_drv->id != DRV_GG) || ((tile_x > 4) && (tile_x < 26)))
        {
            int      tile_n;
            u8       tile_attr;
            int *    tile_palette;
            u8 *     tile_pixels;

            // Draw tile line
            tile_attr = src_map[1];
            tile_n = *((u16 *)src_map) & 511;
            if (tgfx.Tile_Dirty [tile_n] & TILE_DIRTY_DECODE)
            {
                Decode_Tile(tile_n);
                tgfx.Tile_Dirty [tile_n] = TILE_DIRTY_REDRAW;
            }

            tile_palette = (tile_attr & 0x08) ? &PIXEL_PALETTE_TABLE[16] : &PIXEL_PALETTE_TABLE[0];
            tile_pixels = tgfx.Tile_Decoded[tile_n] + ((tile_attr & 0x04) ? (7 * 8) - tile_line : tile_line);

            switch (tile_attr & 0x12)
            {
            case 0x00: 
                {
                    // 0x00 - Not Flipped - Background Tile
                    dst_buf[0] = tile_palette[tile_pixels[0]];
                    dst_buf[1] = tile_palette[tile_pixels[1]];
                    dst_buf[2] = tile_palette[tile_pixels[2]];
                    dst_buf[3] = tile_palette[tile_pixels[3]];
                    dst_buf[4] = tile_palette[tile_pixels[4]];
                    dst_buf[5] = tile_palette[tile_pixels[5]];
                    dst_buf[6] = tile_palette[tile_pixels[6]];
                    dst_buf[7] = tile_palette[tile_pixels[7]];
                    ((int *)sprite_mask)[0] = 0;
                    ((int *)sprite_mask)[1] = 0;
                    break;
                }
            case 0x02: 
                {
                    // 0x02 -  X Flipped - Background Tile
                    dst_buf[0] = tile_palette[tile_pixels[7]];
                    dst_buf[1] = tile_palette[tile_pixels[6]];
                    dst_buf[2] = tile_palette[tile_pixels[5]];
                    dst_buf[3] = tile_palette[tile_pixels[4]];
                    dst_buf[4] = tile_palette[tile_pixels[3]];
                    dst_buf[5] = tile_palette[tile_pixels[2]];
                    dst_buf[6] = tile_palette[tile_pixels[1]];
                    dst_buf[7] = tile_palette[tile_pixels[0]];
                    ((int *)sprite_mask)[0] = 0;
                    ((int *)sprite_mask)[1] = 0;
                    break;
                }
            case 0x10: 
                {
                    // 0x10 - Not Flipped - Foreground Tile
                    int color;
                    color = tile_pixels[0]; dst_buf[0] = tile_palette[color]; sprite_mask[0] = (color ? 1 : 0);
                    color = tile_pixels[1]; dst_buf[1] = tile_palette[color]; sprite_mask[1] = (color ? 1 : 0);
                    color = tile_pixels[2]; dst_buf[2] = tile_palette[color]; sprite_mask[2] = (color ? 1 : 0);
                    color = tile_pixels[3]; dst_buf[3] = tile_palette[color]; sprite_mask[3] = (color ? 1 : 0);
                    color = tile_pixels[4]; dst_buf[4] = tile_palette[color]; sprite_mask[4] = (color ? 1 : 0);
                    color = tile_pixels[5]; dst_buf[5] = tile_palette[color]; sprite_mask[5] = (color ? 1 : 0);
                    color = tile_pixels[6]; dst_buf[6] = tile_palette[color]; sprite_mask[6] = (color ? 1 : 0);
                    color = tile_pixels[7]; dst_buf[7] = tile_palette[color]; sprite_mask[7] = (color ? 1 : 0);
                    break;
                }
            case 0x12:
                {
                    // 0x12 - X Flipped - Foreground Tile
                    int color;
                    color = tile_pixels[7]; dst_buf[0] = tile_palette[color]; sprite_mask[0] = (color ? 1 : 0);
                    color = tile_pixels[6]; dst_buf[1] = tile_palette[color]; sprite_mask[1] = (color ? 1 : 0);
                    color = tile_pixels[5]; dst_buf[2] = tile_palette[color]; sprite_mask[2] = (color ? 1 : 0);
                    color = tile_pixels[4]; dst_buf[3] = tile_palette[color]; sprite_mask[3] = (color ? 1 : 0);
                    color = tile_pixels[3]; dst_buf[4] = tile_palette[color]; sprite_mask[4] = (color ? 1 : 0);
                    color = tile_pixels[2]; dst_buf[5] = tile_palette[color]; sprite_mask[5] = (color ? 1 : 0);
                    color = tile_pixels[1]; dst_buf[6] = tile_palette[color]; sprite_mask[6] = (color ? 1 : 0);
                    color = tile_pixels[0]; dst_buf[7] = tile_palette[color]; sprite_mask[7] = (color ? 1 : 0);
                    break;
                }
            } // switch
        }

        if (tile_x == x_ignore_vscroll)
        {
            //if (Wide_Screen_28)
            //{
            //    src_map = BACK_AREA + (((tsms.VDP_Line - 32) & 0xFFFFFFF8) * 8) + ((2 * (32 - x_scroll + tile_x)) & 63);
            //    tile_line = ((tsms.VDP_Line - 32) & 0x07) * 8;
            //}
            //else
            //{
                src_map = BACK_AREA + ((tsms.VDP_Line & 0xFFFFFFF8) * 8) + ((2 * (32 - x_scroll + tile_x)) & 63);
                tile_line = (tsms.VDP_Line & 0x07) * 8;
            //}
        }

        if (++tile_x == x_scroll)
        {
            src_map -= (64 - 2);
        }
        else
        {
            src_map += 2;
        }

        dst_buf += 8;
        sprite_mask += 8;
        // x += 8 // It is not necessary to maintain 'x' in the loop
    }
}

// PROCESS COLLISION FOR A SPRITE LINE ----------------------------------------
INLINE void     Sprite_Collide_Line_C (byte *p_src, int x)
{
    int *       p_collision_table;

    p_collision_table = &Sprites_Collision_Table [x];
    if (p_src[0]) { if ((p_collision_table[0])++ > 0) goto collide; }
    if (p_src[1]) { if ((p_collision_table[1])++ > 0) goto collide; }
    if (p_src[2]) { if ((p_collision_table[2])++ > 0) goto collide; }
    if (p_src[3]) { if ((p_collision_table[3])++ > 0) goto collide; }
    if (p_src[4]) { if ((p_collision_table[4])++ > 0) goto collide; }
    if (p_src[5]) { if ((p_collision_table[5])++ > 0) goto collide; }
    if (p_src[6]) { if ((p_collision_table[6])++ > 0) goto collide; }
    if (p_src[7]) { if ((p_collision_table[7])++ > 0) goto collide; }
    return;
collide:
    sms.VDP_Status |= VDP_STATUS_SpriteCollision; 
    Do_Collision = FALSE;
}

// PROCESS COLLISION FOR A DOUBLED SPRITE LINE --------------------------------
INLINE void     Sprite_Collide_Line_Double (byte *p_src, int x)
{
    int *       p_collision_table;

    p_collision_table = &Sprites_Collision_Table [x];
    if (p_src[0]) { if ((p_collision_table[ 0])++ > 0 || (p_collision_table[ 1])++ > 0) goto collide; }
    if (p_src[1]) { if ((p_collision_table[ 2])++ > 0 || (p_collision_table[ 3])++ > 0) goto collide; }
    if (p_src[2]) { if ((p_collision_table[ 4])++ > 0 || (p_collision_table[ 5])++ > 0) goto collide; }
    if (p_src[3]) { if ((p_collision_table[ 6])++ > 0 || (p_collision_table[ 7])++ > 0) goto collide; }
    if (p_src[4]) { if ((p_collision_table[ 8])++ > 0 || (p_collision_table[ 9])++ > 0) goto collide; }
    if (p_src[5]) { if ((p_collision_table[10])++ > 0 || (p_collision_table[11])++ > 0) goto collide; }
    if (p_src[6]) { if ((p_collision_table[12])++ > 0 || (p_collision_table[13])++ > 0) goto collide; }
    if (p_src[7]) { if ((p_collision_table[14])++ > 0 || (p_collision_table[15])++ > 0) goto collide; }
    return;
collide:
    sms.VDP_Status |= VDP_STATUS_SpriteCollision; 
    Do_Collision = FALSE;
}

//-----------------------------------------------------------------------------
// Sprite_Draw_Line(const u8 *tile_line, int x)
// Draw a sprite line (8 pixels)
//-----------------------------------------------------------------------------
INLINE void     Sprite_Draw_Line(const u8 *tile_line, int x)
{
    int             color;
    PIXEL_TYPE *    dst;
    u8 *            sprite_mask;

    dst = &PIXEL_LINE_DST[x];
    sprite_mask = &Sprites_Draw_Mask[x];

    color = tile_line[0]; if (!sprite_mask[0] && color) dst[0] = PIXEL_PALETTE_TABLE[16 + color]; // Note: PIXEL_PALETTE_TABLE should be a table (not a pointer) so the +16 is free
    color = tile_line[1]; if (!sprite_mask[1] && color) dst[1] = PIXEL_PALETTE_TABLE[16 + color];
    color = tile_line[2]; if (!sprite_mask[2] && color) dst[2] = PIXEL_PALETTE_TABLE[16 + color];
    color = tile_line[3]; if (!sprite_mask[3] && color) dst[3] = PIXEL_PALETTE_TABLE[16 + color];
    color = tile_line[4]; if (!sprite_mask[4] && color) dst[4] = PIXEL_PALETTE_TABLE[16 + color];
    color = tile_line[5]; if (!sprite_mask[5] && color) dst[5] = PIXEL_PALETTE_TABLE[16 + color];
    color = tile_line[6]; if (!sprite_mask[6] && color) dst[6] = PIXEL_PALETTE_TABLE[16 + color];
    color = tile_line[7]; if (!sprite_mask[7] && color) dst[7] = PIXEL_PALETTE_TABLE[16 + color];
}

//-----------------------------------------------------------------------------
// Sprite_Draw_Line_Double(const u8 *tile_line, int x)
// Draw a sprite line where each pixel is repeated twice (8 -> 16 pixels)
//-----------------------------------------------------------------------------
INLINE void     Sprite_Draw_Line_Double(const u8 *tile_line, int x)
{
    int             color;
    PIXEL_TYPE *    dst;
    u8 *            sprite_mask;

    dst  = &PIXEL_LINE_DST[x];
    sprite_mask = &Sprites_Draw_Mask[x];

    color = tile_line[0]; if (color) { color = PIXEL_PALETTE_TABLE[16 + color]; if (!sprite_mask[ 0]) dst[ 0] = color; if (!sprite_mask[ 1]) dst[ 1] = color; }
    color = tile_line[1]; if (color) { color = PIXEL_PALETTE_TABLE[16 + color]; if (!sprite_mask[ 2]) dst[ 2] = color; if (!sprite_mask[ 3]) dst[ 3] = color; }
    color = tile_line[2]; if (color) { color = PIXEL_PALETTE_TABLE[16 + color]; if (!sprite_mask[ 4]) dst[ 4] = color; if (!sprite_mask[ 5]) dst[ 5] = color; }
    color = tile_line[3]; if (color) { color = PIXEL_PALETTE_TABLE[16 + color]; if (!sprite_mask[ 6]) dst[ 6] = color; if (!sprite_mask[ 7]) dst[ 7] = color; }
    color = tile_line[4]; if (color) { color = PIXEL_PALETTE_TABLE[16 + color]; if (!sprite_mask[ 8]) dst[ 8] = color; if (!sprite_mask[ 9]) dst[ 9] = color; }
    color = tile_line[5]; if (color) { color = PIXEL_PALETTE_TABLE[16 + color]; if (!sprite_mask[10]) dst[10] = color; if (!sprite_mask[11]) dst[11] = color; }
    color = tile_line[6]; if (color) { color = PIXEL_PALETTE_TABLE[16 + color]; if (!sprite_mask[12]) dst[12] = color; if (!sprite_mask[13]) dst[13] = color; }
    color = tile_line[7]; if (color) { color = PIXEL_PALETTE_TABLE[16 + color]; if (!sprite_mask[14]) dst[14] = color; if (!sprite_mask[15]) dst[15] = color; }
}

void        Refresh_Sprites_5 (bool draw)
{
    // 1. Count the number of sprites to render on this line
    {
        // Calculate Sprite Height
        int height = 8;
        if (Sprites_Double) 
			height <<= 1;
        if (Sprites_8x16)   
			height <<= 1;

        Sprite_Last = 0;
        Sprites_on_Line = 0;
        Find_Last_Sprite (Wide_Screen_28, height, tsms.VDP_Line);

        // Return if there's no sprite on this line
        if (Sprites_on_Line == 0)
            return;
    }

    // Check if we have or not to process sprite collisions
    Do_Collision = (!(sms.VDP_Status & VDP_STATUS_SpriteCollision)
        && (Sprites_on_Line > 1));

    // If sprites do not have to be drawn, only update collisions
    if (draw == FALSE)
    {
        // If we don't have to process collisions, there's no point to continue
        if (Do_Collision == FALSE)
            return;
        // Setting value to 64+9 will never draw sprites (only update collisions)
        // since sprites are drawn only if Sprites_On_Line < 9
        Sprites_on_Line = 64 + 9;
    }
    // Draw all sprites on line if flickering is not enabled
    else if (!(Configuration.sprite_flickering & SPRITE_FLICKERING_ENABLED))
    {
        Sprites_on_Line = 0;
    }

    // Process all sprites in 224 (28*8) lines mode
    // if (Wide_Screen_28)
    //    Sprite_Last = 63;

    // Clear Sprite Collision Table
    if (Do_Collision)
        memset(Sprites_Collision_Table_Start, 0, sizeof (int) * Sprites_Collision_Table_Len);

    // 3. Draw sprites
    {
        int     x, y, n;
        byte *  p_src;
        int     j;
        byte *  spr_map_xn = &sprite_attribute_table[0x80];
        int     spr_map_xn_offset;
        int     spr_map_n_mask = 0x01FF;

        // Bit 0 of Register 5 and Bits 0-1 of Register 6 act as masks on the 315-5124
        if (cur_machine.VDP.model == VDP_MODEL_315_5124)
        {
            if ((sms.VDP[5] & 1) == 0)
                spr_map_xn = &sprite_attribute_table[0x00];
            if ((sms.VDP[6] & 1) == 0)
                spr_map_n_mask &= ~0x0080;
            if ((sms.VDP[6] & 2) == 0)
                spr_map_n_mask &= ~0x0040;
			// FIXME: Should be the same, untested thought
			spr_map_n_mask &= (~0x00C0) | ((sms.VDP[6] & 3) << 6);
        }

        // Now process actual sprites
        switch (sms.VDP[1] & (1 | 2))
        {
        case 0: // 8x8 sprites
            {
                for (j = Sprite_Last; j >= 0; j --)
                {
                    // Fetch Y & clip
                    y = sprite_attribute_table[j];
                    // if (y == 224) continue;
                    if (y > 224) y -= 256;

                    // Now Y will contains the sprite line to render
                    y = tsms.VDP_Line - y - 1;
                    if (y < 0 || y >= 8) continue;

                    // Fetch N & X
                    spr_map_xn_offset = j << 1;
                    n = ((int)spr_map_xn [spr_map_xn_offset + 1] | cur_machine.VDP.sprite_pattern_base_index) & spr_map_n_mask;
                    x = spr_map_xn [spr_map_xn_offset] - cur_machine.VDP.sprite_shift_x;

                    // Decode tile if it isn't decoded yet
                    if (tgfx.Tile_Dirty [n] & TILE_DIRTY_DECODE)
                    { Decode_Tile (n); tgfx.Tile_Dirty [n] = TILE_DIRTY_REDRAW; }
                    p_src = &tgfx.Tile_Decoded [n] [y << 3];

                    // Process collision & draw
                    if (Do_Collision)
                        Sprite_Collide_Line(p_src, x);
                    if (Sprites_on_Line-- < 9)
                        Sprite_Draw_Line(p_src, x);
                }
            } break;
        case 1: // 8x8 sprites zoomed
            {
                for (j = Sprite_Last; j >= 0; j --)
                {
                    // Fetch Y & clip
                    y = sprite_attribute_table[j];
                    // if (y == 224) continue;
                    if (y > 224) y -= 256;

                    // Now Y will contains the sprite line to render
                    y = tsms.VDP_Line - y - 1;
                    if (y < 0 || y >= 16) continue;

                    // Fetch N & X
                    spr_map_xn_offset = j << 1;
                    n = ((int)spr_map_xn [spr_map_xn_offset + 1] | cur_machine.VDP.sprite_pattern_base_index) & spr_map_n_mask;
                    x = spr_map_xn [spr_map_xn_offset] - cur_machine.VDP.sprite_shift_x;

                    // Decode tile if it isn't decoded yet
                    if (tgfx.Tile_Dirty [n] & TILE_DIRTY_DECODE)
                    { Decode_Tile (n); tgfx.Tile_Dirty [n] = TILE_DIRTY_REDRAW; }
                    p_src = &tgfx.Tile_Decoded [n] [(y >> 1) << 3];

                    // Process collision & draw
                    if (Do_Collision)
                        Sprite_Collide_Line_Double (p_src, x);
                    if (Sprites_on_Line-- < 9)
                        Sprite_Draw_Line_Double (p_src, x);
                }
            } break;
        case 2: // 8x16 sprites
            {
                spr_map_n_mask &= ~0x01;
                for (j = Sprite_Last; j >= 0; j --)
                {
                    // Fetch Y & clip
                    y = sprite_attribute_table[j];
                    // if (y == 224) continue;
                    if (y > 224) y -= 256;

                    // Now Y will contains the sprite line to render
                    y = tsms.VDP_Line - y - 1;
                    if (y < 0 || y >= 16) continue;

                    // Fetch N & X
                    // Increase N on the sprite second tile
                    spr_map_xn_offset = j << 1;
                    n = ((int)spr_map_xn [spr_map_xn_offset + 1] | cur_machine.VDP.sprite_pattern_base_index) & spr_map_n_mask;
                    if (y & 8) // >= 8
                    {
                        n ++;
                        y &= 7;
                    }
                    x = spr_map_xn [spr_map_xn_offset] - cur_machine.VDP.sprite_shift_x;

                    // Decode tile if it isn't decoded yet
                    if (tgfx.Tile_Dirty [n] & TILE_DIRTY_DECODE)
                    { Decode_Tile (n); tgfx.Tile_Dirty [n] = TILE_DIRTY_REDRAW; }
                    p_src = &tgfx.Tile_Decoded [n] [y << 3];

                    // Process collision & draw
                    if (Do_Collision)
                        Sprite_Collide_Line (p_src, x);
                    if (Sprites_on_Line-- < 9)
                        Sprite_Draw_Line(p_src, x);
                }
            } break;
        case 3: // 8x16 sprites zoomed
            {
                spr_map_n_mask &= ~0x01;
                for (j = Sprite_Last; j >= 0; j --)
                {
                    // Fetch Y & clip
                    y = sprite_attribute_table[j];
                    // if (y == 224) continue;
                    if (y > 224) y -= 256;

                    // Now Y will contains the sprite line to render
                    y = tsms.VDP_Line - y - 1;
                    if (y < 0 || y >= 32) continue;

                    // Fetch N & X
                    // Increase N on the sprite second tile
                    spr_map_xn_offset = j << 1;
                    n = ((int)spr_map_xn [spr_map_xn_offset + 1] | cur_machine.VDP.sprite_pattern_base_index) & spr_map_n_mask;
                    if (y & 16) // >= 16
                    {
                        n ++;
                        y &= 15;
                    }
                    x = spr_map_xn [spr_map_xn_offset] - cur_machine.VDP.sprite_shift_x;

                    // Decode tile if it isn't decoded yet
                    if (tgfx.Tile_Dirty [n] & TILE_DIRTY_DECODE)
                    { Decode_Tile (n); tgfx.Tile_Dirty [n] = TILE_DIRTY_REDRAW; }
                    p_src = &tgfx.Tile_Decoded [n] [(y >> 1) << 3];

                    // Process collision & draw
                    if (Do_Collision)
                        Sprite_Collide_Line_Double (p_src, x);
                    if (Sprites_on_Line-- < 9)
                        Sprite_Draw_Line_Double (p_src, x);
                }
            } break;
        } // end of switch

    }
}

//-----------------------------------------------------------------------------

