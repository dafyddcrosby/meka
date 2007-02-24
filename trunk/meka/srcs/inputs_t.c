//-----------------------------------------------------------------------------
// MEKA - inputs_t.c
// Inputs Tools - Code
//-----------------------------------------------------------------------------

#include "shared.h"
#include "inputs_t.h"

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

int     Key_Alpha_Table [NUM_ALPHA_KEYS] =
  { KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I,
    KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
    KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z };
char    Alpha_Table [NUM_ALPHA_KEYS] =
  { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

static int  typematic_repeating = 0;
static int  typematic_repeat_counter = 0;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Inputs_Key_Eat (int keycode)
// Eat given key by removing the corresponding flag in the global key[] table
//-----------------------------------------------------------------------------
void    Inputs_Key_Eat(int keycode)
{
    key[keycode] = 0;
}

void    Inputs_KeyPressQueue_Remove(t_key_press *keypress)
{
    Inputs_Key_Eat(keypress->scancode); // FIXME

    list_remove(&Inputs.KeyPressedQueue, keypress);
    free(keypress);
}

void    Inputs_KeyPressQueue_Clear(void)
{
    list_free(&Inputs.KeyPressedQueue);
}

//-----------------------------------------------------------------------------
// Inputs_KeyPressed (int keycode, bool eat)
// Return weither given key was just pressed, then eat the key if asked for
//-----------------------------------------------------------------------------
int     Inputs_KeyPressed (int keycode, bool eat)
{
    // Check if requested key was just pressed
    if (key[keycode] && opt.Current_Key_Pressed == 0)
    {
        opt.Current_Key_Pressed = keycode;
        typematic_repeating = FALSE;
        typematic_repeat_counter = 0;
        if (eat)
            key[keycode] = 0;
        return (TRUE);
    }
    // Check if previously pressed key was released
    // FIXME: should be done in this function, but rather in a single inputs-update
    if (opt.Current_Key_Pressed != 0 && key [opt.Current_Key_Pressed] == 0)
        opt.Current_Key_Pressed = 0;
    return (FALSE);
}

//-----------------------------------------------------------------------------
// Inputs_KeyPressed_Repeat (int keycode, bool eat, int delay, int rate)
// Return weither given key was pressed, handing repetition,
// then eat the key if asked for.
//-----------------------------------------------------------------------------
// FIXME: this function is theorically incorrect, since it relies on
// static global data. Repeating two keys should mess the whole thing ?
//-----------------------------------------------------------------------------
int     Inputs_KeyPressed_Repeat (int keycode, bool eat, int delay, int rate)
{
    // hmm...
    Inputs_KeyPressed (keycode, eat);
    if (opt.Current_Key_Pressed != keycode)
        return (FALSE);

    // Increment counter
    typematic_repeat_counter++;

    // Delay
    if (typematic_repeating == FALSE)
    {
        // Return TRUE on first press
        if (typematic_repeat_counter == 1)
            return (TRUE);
        // Then wait for given delay
        if (typematic_repeat_counter == delay)
        {
            typematic_repeating = TRUE;
            typematic_repeat_counter = 0;
            return (TRUE);
        }
    }
    else
    {
        // Repeat
        if (typematic_repeat_counter == rate)
        {
            typematic_repeat_counter = 0;
            return (TRUE);
        }
    }
    return (FALSE);
}

//-----------------------------------------------------------------------------
