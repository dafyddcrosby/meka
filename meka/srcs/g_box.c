//-----------------------------------------------------------------------------
// MEKA - g_box.c
// GUI Boxes - Code
//-----------------------------------------------------------------------------

#include "shared.h"
#include "desktop.h"
#include "g_widget.h"

//-----------------------------------------------------------------------------
// Macros (useless)
//-----------------------------------------------------------------------------

#define qblit(b1, b2, sx, sy, lx, ly) blit(b1, b2, sx, sy, sx, sy, lx, ly);

//-----------------------------------------------------------------------------
// Functions (crap, horrible, painful)
//-----------------------------------------------------------------------------

// CHECK IF USER DO SOMETHING TO A BOX ----------------------------------------
void        gui_update_boxes (void)
{
    bool        will_move = FALSE;
    int         i = 0;
    int         j;
    t_gui_box * b = NULL;
    t_gui_box * b_hover = NULL;

    if ((gui_mouse.pressed_on == PRESSED_ON_DESKTOP) || (gui_mouse.pressed_on == PRESSED_ON_MENUS))
        return;

    // FIND ON WHICH BOX IS THE MOUSE CURSOR --------------------------------------
    for (i = 0; i < gui.box_last; i ++)
    {
        int     mouse_x;
        int     mouse_y;

        b = gui.box[gui.box_plan [i]];
        if (!(b->attr & A_Show)) // Skip invisible boxes
            continue;

        mouse_x = gui_mouse.x - b->frame.pos.x;
        mouse_y = gui_mouse.y - b->frame.pos.y;
        will_move = widgets_update_box (b, mouse_x, mouse_y);

        if (b_hover == NULL)
            if ((gui_mouse_area(b->frame.pos.x - 2, b->frame.pos.y - 20, b->frame.pos.x + b->frame.size.x + 2, b->frame.pos.y + b->frame.size.y + 2))
                ||
                ((gui_mouse.on_box == gui.box_plan [i]) && (gui_mouse.button & 1)))
            {
                b_hover = b;
                break;
            }
    }
    if (b_hover == NULL)
    {
        if ((gui_mouse.button) && (gui_mouse.pressed_on == PRESSED_ON_NOTHING))
            gui_mouse.pressed_on = PRESSED_ON_DESKTOP;
        return;
    }

    if ((gui_mouse.on_box != -1) && (gui_mouse.on_box != b_hover->stupid_id))
        return;

    /*
    will_move = YES;
    if ((b->n_widgets > 0) && (gui_mouse.pressed_on != PRESSED_ON_BOX))
        will_move = widgets_update_box (b, cx, cy);
    */

    if ((gui_mouse.button & 1) == 0)
        return;

    gui_mouse.on_box = b->stupid_id;    // FIXME: make obsolete
    gui_box_set_focus (b);
    b->must_redraw = YES;
    // gui.info.must_redraw = YES;

    //Msg(MSGT_DEBUG, "will_move=%d", will_move);

    // ELSE, MOVE THE BOX --------------------------------------------------------
    if ((will_move) && (gui_mouse.pressed_on != PRESSED_ON_WIDGET) && (gui_mouse.button & 1))
    {
        int mx, my;
        int ax1, ay1, ax2, ay2;
        int bx1, by1, bx2, by2;

        Show_Mouse_In (NULL);

        if (gui_mouse.pressed_on != PRESSED_ON_BOX)
        {
            gui_mouse.pressed_on = PRESSED_ON_BOX;
            mx = my = 0;
        }
        else
        {
            mx = gui_mouse.x - gui_mouse.px;
            my = gui_mouse.y - gui_mouse.py;
            // if ((!mx) && (!my)) continue;
        }

        if (mx >= 0)
        {
            if (my >= 0)
            { // mx > 0 - my > 0
                ax1 = b->frame.pos.x                                          -  2 ;
                ay1 = b->frame.pos.y                                          - 20 ;
                ax2 = b->frame.pos.x + b->frame.size.x + 1                    +  2 ;
                ay2 = b->frame.pos.y + Limit(b->frame.size.y + 22, my) + 1    - 20 ;

                bx1 = b->frame.pos.x                                          -  2 ;
                by1 = b->frame.pos.y + Limit(b->frame.size.y + 22, my) + 1    - 20 ;
                bx2 = b->frame.pos.x + Limit(b->frame.size.x, mx) + 1         +  2 ;
                by2 = b->frame.pos.y + b->frame.size.y + 1                    +  2 ;
            }
            else
            { // mx > 0 - my < 0
                ax1 = b->frame.pos.x                                          -  2 ;
                ay1 = b->frame.pos.y                                          - 20 ;
                ax2 = b->frame.pos.x + Limit(b->frame.size.x, mx) + 1         +  2 ;
                ay2 = b->frame.pos.y + b->frame.size.y - Limit(b->frame.size.y + 22, -my)  +  2 ;

                bx1 = b->frame.pos.x                                          -  2 ;
                by1 = b->frame.pos.y + b->frame.size.y - Limit(b->frame.size.y + 22, -my)  +  2 ;
                bx2 = b->frame.pos.x + b->frame.size.x + 1                    +  2 ;
                by2 = b->frame.pos.y + b->frame.size.y + 1                    +  2 ;
            }
        }
        else
        {
            if (my >= 0)
            { // mx < 0 - my > 0
                ax1 = b->frame.pos.x                                          -  2 ;
                ay1 = b->frame.pos.y                                          - 20 ;
                ax2 = b->frame.pos.x + b->frame.size.x + 1                    +  2 ;
                ay2 = b->frame.pos.y + Limit(b->frame.size.y + 22, my) + 1    - 20 ;

                bx1 = b->frame.pos.x + b->frame.size.x - Limit(b->frame.size.x, -mx)       -  2 ;
                by1 = b->frame.pos.y + Limit(b->frame.size.y + 22, my) + 1    - 20 ;
                bx2 = b->frame.pos.x + b->frame.size.x + 1                    +  2 ;
                by2 = b->frame.pos.y + b->frame.size.y + 1                    +  2 ;
            }
            else
            { // mx < 0 - my < 0
                ax1 = b->frame.pos.x + b->frame.size.x - Limit(b->frame.size.x, -mx)       -  2 ;
                ax2 = b->frame.pos.x + b->frame.size.x + 1                    +  2 ;
                ay1 = b->frame.pos.y                                          - 20 ;
                ay2 = b->frame.pos.y + b->frame.size.y - Limit(b->frame.size.y + 22, -my)  +  2 ;

                bx1 = b->frame.pos.x                                   -  2 ;
                by1 = b->frame.pos.y + b->frame.size.y - Limit(b->frame.size.y + 22, -my)  +  2 ;
                bx2 = b->frame.pos.x + b->frame.size.x + 1                       +  2 ;
                by2 = b->frame.pos.y + b->frame.size.y + 1                       +  2 ;
            }
        }

        qblit(gui_background, gui_buffer, ax1, ay1, ax2 - ax1, ay2 - ay1);
        qblit(gui_background, gui_buffer, bx1, by1, bx2 - bx1, by2 - by1);
        // qblit (color_buffer, gui_buffer, ax1, ay1, ax2 - ax1, ay2 - ay1);
        // qblit (color2_buffer, gui_buffer, bx1, by1, bx2 - bx1, by2 - by1);
        // qblit (gui_buffer, screen, 0, 0, 640, 480);

        // Update 'must_redraw' flag for other boxes
        for (j = i + 1; j < gui.box_last; j ++)
        {
            t_gui_box *b2 = gui.box[gui.box_plan [j]];
            if (((b2->frame.pos.x + b2->frame.size.x + 2 >= ax1) && (b2->frame.pos.x - 2 <= ax2) && (b2->frame.pos.y + b2->frame.size.y + 2 >= ay1) && (b2->frame.pos.y - 20 <= ay2))
                ||
                ((b2->frame.pos.x + b2->frame.size.x + 2 >= bx1) && (b2->frame.pos.x - 2 <= bx2) && (b2->frame.pos.y + b2->frame.size.y + 2 >= by1) && (b2->frame.pos.y - 20 <= by2)))
            {
                b2->must_redraw = YES;
            }
        }

        // Update position
        b->frame.pos.x += mx;
        b->frame.pos.y += my;
        gui_box_clip_position (b);

        Show_Mouse_In (gui_buffer);
    } // Move Box -------------------------------------------------------------
}

// CREATE A NEW BOX WITH DEFAULT VALUES ---------------------------------------
int     gui_box_create (int pos_x, int pos_y, int size_x, int size_y, char label[])
{
    int           id;
    t_gui_box *   box;

    id = gui.box_last;
    if (id >= MAX_BOX)
        return (-1);

    box = (t_gui_box *)malloc(sizeof (t_gui_box));
    if (box == NULL)
        return (-1);
    gui.box [id] = box;

    box->stupid_id = id;
    box->frame.pos.x = pos_x;
    box->frame.pos.y = pos_y;
    box->frame.size.x = size_x;
    box->frame.size.y = size_y;
    box->type = GUI_BOX_TYPE_NOTHING;
    box->must_redraw = YES;
    box->n_widgets = 0;
    box->focus_inputs_exclusive = NO;

    // Set default attributes
    box->attr = A_Show;

    box->update = NULL;
    box->title = strdup (label);

    gui.box_image [id] = create_bitmap (size_x, size_y);

    gui.box_plan [id] = id;

    gui.box_last ++;
    gui.info.must_redraw = YES;

    gui_box_set_focus (box);        // Note: be sure to call this after gui.box_last++
    gui_box_clip_position (box);

    return (id);
}

// CREATE DEFAULT BOXES -------------------------------------------------------
void    gui_init_default_box (void)
{
    static u8 fixed_1 = 1;
    apps.id_game = gamebox_create (35, 132);
    if (apps.id_game != -1)
        Desktop_Register_Box ("GAME", apps.id_game, 1, &fixed_1);
}

// SET A BOX TO SHOW A BITMAP -------------------------------------------------
void    gui_set_image_box (int which, BITMAP *bitmap)
{
    gui.box [which]->type = GUI_BOX_TYPE_BITMAP;
    gui.box_image [which] = bitmap;
    clear_to_color (gui.box_image [which], GUI_COL_FILL);
}

void    gui_box_delete (int box_n)
{
    // int i;
}

//-----------------------------------------------------------------------------
// gui_box_find_plan (t_gui_box *)
// Get plan number (Z) of given box
// FIXME: should avoid use of that crap
//-----------------------------------------------------------------------------
int             gui_box_find_plan (t_gui_box *box)
{
    int         i;

    for (i = 0; i < gui.box_last; i++)
        if (gui.box_plan [i] == box->stupid_id)
            return (i);
    return (-1);
}

//-----------------------------------------------------------------------------
// gui_box_show (t_gui_box *box, bool enable, bool focus)
// Enable/disable given box
//-----------------------------------------------------------------------------
void            gui_box_show (t_gui_box *box, bool enable, bool focus)
{
    if (enable)
    {
        // Show box
        box->attr |= A_Show;

        // Set focus
        if (focus)
            gui_box_set_focus(box);
    }
    else
    {
        // Hide box
        box->attr &= ~A_Show;

        // If this box had the focus, let give focus to the following one
        if (focus && gui_box_has_focus(box))
            gui_box_set_focus(gui.box[gui.box_plan[1]]);
    }

    // Set global redraw flag
    gui.info.must_redraw = YES;
}

//-----------------------------------------------------------------------------
// gui_box_set_focus (t_gui_box *)
// Set focus to given box
//-----------------------------------------------------------------------------
void            gui_box_set_focus (t_gui_box *box)
{
    t_gui_box * box_current_focus;
    int         i;
    int         box_plan;

    box_plan = gui_box_find_plan (box);
    box_current_focus = gui.box[gui.box_plan[0]];
    if (box_current_focus == box)
        return;

    // Set redraw flag for old focused box
    box_current_focus->must_redraw = YES;

    // Shift plan/z buffer by one
    for (i = box_plan; i > 0; i--)
        gui.box_plan[i] = gui.box_plan[i - 1];
    gui.box_plan[0] = box->stupid_id;
}

//-----------------------------------------------------------------------------
// gui_box_has_focus (t_gui_box *)
// Return wether given box has the focus
//-----------------------------------------------------------------------------
int     gui_box_has_focus (t_gui_box *box)
{
    return (gui.box_plan[0] == box->stupid_id);
}

//-----------------------------------------------------------------------------
// gui_box_set_title (t_gui_box *, char *)
// Set title of given box
//-----------------------------------------------------------------------------
void    gui_box_set_title (t_gui_box *box, char *title)
{
    free (box->title);
    box->title = strdup (title);
}


//-----------------------------------------------------------------------------
// gui_box_clip_position (t_gui_box *box)
// Clip position of given box so that it shows on desktop.
//-----------------------------------------------------------------------------
void    gui_box_clip_position (t_gui_box *box)
{
    if (box->frame.pos.x < gui.info.screen_pad.x - box->frame.size.x)
        box->frame.pos.x = (gui.info.screen_pad.x - box->frame.size.x);
    if (box->frame.pos.x > gui.info.screen.x - gui.info.screen_pad.x)
        box->frame.pos.x = (gui.info.screen.x - gui.info.screen_pad.x);
    if (box->frame.pos.y < gui.info.screen_pad.y - box->frame.size.y + gui.info.bars_height)
        box->frame.pos.y = (gui.info.screen_pad.y - box->frame.size.y + gui.info.bars_height);
    if (box->frame.pos.y > gui.info.screen.y - gui.info.screen_pad.y - gui.info.bars_height)
        box->frame.pos.y = (gui.info.screen.y - gui.info.screen_pad.y - gui.info.bars_height);
}

//-----------------------------------------------------------------------------
