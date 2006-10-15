//-----------------------------------------------------------------------------
// MEKA - patch.c
// Patching System - Code
//-----------------------------------------------------------------------------

// #define DEBUG_PATCHES
#include "shared.h"
#include "patch.h"

//-----------------------------------------------------------------------------
// Patch_New (void)
// Create a new patch
//-----------------------------------------------------------------------------
t_patch *       Patch_New (void)
{
    t_patch *   patch;

    // Allocate new patch
    patch = malloc (sizeof (t_patch));
    if (patch == NULL)
        return (NULL); // FIXME: abort?

    // Clear with default values
    patch->rom_patches      = NULL;
    patch->mem_patches      = NULL;
    patch->crc_type         = PATCH_CRC_TYPE_MEKACRC;
    patch->crc_mekacrc.v[0] = 0x00000000;
    patch->crc_mekacrc.v[1] = 0x00000000;
    patch->crc_crc32        = 0x00000000;

    // Add to global patch list
    list_add (&Patches.patches, patch);

    return (patch);
}

//-----------------------------------------------------------------------------
// Patch_Action_New (void)
// Create a new patch action
//-----------------------------------------------------------------------------
t_patch_action *        Patch_Action_New (void)
{
    t_patch_action *    action;

    action = malloc (sizeof (t_patch_action));
    if (action == NULL)
        return (NULL); // FIXME: abort

    // Clear with default values
    action->address     = 0x0000;
    action->data        = NULL;
    action->data_length = 0;

    return (action);
}

//-----------------------------------------------------------------------------
// Patches_List_Parse_Line (char *line)
// Parse and handle content of a line from MEKA.PAT
//-----------------------------------------------------------------------------
int                     Patches_List_Parse_Line (char *line)
{
    char *p;
    char s[256];

    // ConsolePrintf("line = %s\n", line);

    // Check if we're on a new patch entry
    if (line[0] == '[') // && (line[17] == ']')
    {
        // Create the new patch
        t_patch *patch = Patch_New ();
        if (patch == NULL)
            return (1); // Not enough memory
        Patches.patch_current = patch;

        // Find checksum type and value
        p = strchr (line+1, ']');
        if (p == NULL)
            return (2); // Unrecognized instruction
        strncpy (s, line+1, p-(line+1));
        s[p-(line+1)] = 0;

        // - Match all ROM
        if (strcmp(s, "*") == 0)
        {
            patch->crc_type = PATCH_CRC_TYPE_NONE;
            return (0);
        }

        // Specify CRC type
        p = strchr (s, ':');
        if (p == NULL)
        {
            // Default to MekaCRC type
            patch->crc_type = PATCH_CRC_TYPE_MEKACRC;
            sscanf (s, "%08X%08X", &patch->crc_mekacrc.v[0], &patch->crc_mekacrc.v[1]);
            return (0);
        }

        // - CRC32
        if (strncmp(s, "crc32:", 6) == 0)
        {
            patch->crc_type = PATCH_CRC_TYPE_CRC32;
            sscanf  (s+6, "%08X", &patch->crc_crc32);
            return (0);
        }

        // - MekaCRC
        if (strncmp(s, "mekacrc:", 8) == 0)
        {
            patch->crc_type = PATCH_CRC_TYPE_MEKACRC;
            sscanf (s+8, "%08X%08X", &patch->crc_mekacrc.v[0], &patch->crc_mekacrc.v[1]);
            return (0);
        }

        return (2); // Unrecognized instruction ... FIXME: should return a better error!
    }

    // Ensure that a patch was already created
    if (Patches.patch_current == NULL)
        return (3);

    {
        // Create new action
        t_patch_action *action = Patch_Action_New ();
        if (action == NULL)
            return (1); // Not enough memory

        // Add to ROM action list in patch
        // FIXME: this is ugly parsing...
        if (strnicmp (line, "ROM[", 4) == 0)
            list_add_to_end (&Patches.patch_current->rom_patches, action);
        else if (strnicmp (line, "MEM[", 4) == 0)
            list_add_to_end (&Patches.patch_current->mem_patches, action);
        else
            return (2);

        // Get address
        action->address = GetNbrHex (line + 4);
        // ConsolePrintf("Address = %x\n", action->address);

        p = strchr(line, '=');
        if (p == NULL)
            return (2);

        // Get values
        p++;
        do
        {
            int value;
            if (sscanf (p, "%X", &value) == 0)
                break;
            while (isxdigit (*p))
                p++;
            if ((action->data_length % 32) == 0)
            {
                action->data = realloc (action->data, action->data_length + 32);
                if (action->data == NULL)
                    return (1); // Not enough memory
            }
            // ConsolePrintf("data[%i] = %04x\n", action->data_length, value);
            action->data[action->data_length++] = value;
        }
        while (*p++ == ',');
    }
    return (0);
}

//-----------------------------------------------------------------------------
// Patches_List_Init (void)
// Load MEKA.PAT
//-----------------------------------------------------------------------------
void            Patches_List_Init (void)
{
    t_tfile *   tf;
    t_list *    lines;
    char *      line;
    int         line_cnt;

    ConsolePrint (Msg_Get (MSG_Patch_Loading));

    // Initializing system
    Patches.patches = NULL;
    Patches.patch_current = NULL;

    // Open and read MEKA.PAT file
    if ((tf = tfile_read (Patches.filename)) == NULL)
    {
        ConsolePrintf ("%s\n", meka_strerror());
        return;
    }

    // Ok
    ConsolePrint ("\n");

    // Parse each line
    line_cnt = 0;
    for (lines = tf->data_lines; lines; lines = lines->next)
    {
        char *p;

        line_cnt += 1;
        line = lines->elem;

        strlwr (line);

        // Remove comments and space
        if ((p = strchr (line, ';')) != NULL)
            *p = EOSTR;
        Remove_Spaces (line);
        if (line[0] == EOSTR)
            continue;

        switch (Patches_List_Parse_Line (line))
        {
        case 1: tfile_free (tf); Quit_Msg (Msg_Get (MSG_Error_Memory));                   break;
        case 2: tfile_free (tf); Quit_Msg (Msg_Get (MSG_Patch_Unrecognized), line_cnt);   break;
        case 3: tfile_free (tf); Quit_Msg (Msg_Get (MSG_Patch_Missing), line_cnt);        break;
        }
    }

    Patches.patch_current = NULL;

    // Free file data
    tfile_free (tf);
}

//-----------------------------------------------------------------------------
// Patch_Find ()
// Find patch for given media image
// Note: return the first patch only
//-----------------------------------------------------------------------------
t_patch *   Patch_Find (t_media_image *media_image)
{
    t_list *patches;

    #ifdef DEBUG_PATCHES
        Msg (MSGT_DEBUG, "Patch_Find()");
    #endif

    // Linear find
    for (patches = Patches.patches; patches != NULL; patches = patches->next)
    {
        t_patch *patch = patches->elem;

        #ifdef DEBUG_PATCHES
            Msg (MSGT_DEBUG, "- Comparing mekacrc:%08X.%08X, crc32:%08X", patch->crc_mekacrc.v[0], patch->crc_mekacrc.v[1], patch->crc_crc32);
        #endif

        if (patch->crc_type == PATCH_CRC_TYPE_NONE)
            return (patch);
        if (patch->crc_type == PATCH_CRC_TYPE_MEKACRC)
            if (media_image->mekacrc.v[0] == patch->crc_mekacrc.v[0] && media_image->mekacrc.v[1] == patch->crc_mekacrc.v[1])
                return (patch);
        if (patch->crc_type == PATCH_CRC_TYPE_CRC32)
            if (media_image->crc32 == patch->crc_crc32)
                return (patch);
    }

    // No patch found
    #ifdef DEBUG_PATCHES
        Msg (MSGT_DEBUG, "-> not found");
    #endif
    return (NULL);
}

//-----------------------------------------------------------------------------
// Patches_ROM_Initialize (void)
// Find patch for current ROM
//-----------------------------------------------------------------------------
void        Patches_ROM_Initialize (void)
{
    // Find patch for current ROM
    Patches.patch_current = Patch_Find (&media_ROM);
}

//-----------------------------------------------------------------------------
// Patches_ROM_Apply (void)
// Apply patches to current ROM
//-----------------------------------------------------------------------------
void        Patches_ROM_Apply (void)
{
    t_patch *patch = Patches.patch_current;
    t_list *actions;
    if (patch == NULL)
        return;

    // Apply ROM patches
    for (actions = patch->rom_patches; actions != NULL; actions = actions->next)
    {
        t_patch_action *action = actions->elem;

        // Apply all bytes
        int i;
        for (i = 0; i < action->data_length; i++)
        {
            int address = action->address + i;
            if (address < 0 || address >= tsms.Size_ROM)
            {
                Msg (MSGT_USER, Msg_Get (MSG_Patch_Out_of_Bound), "ROM", address);
                return;
            }
            #ifdef DEBUG_PATCHES
                Msg (MSGT_DEBUG, "Patch ROM[%04X] = %02X", address, action->data[i]);
            #endif
            ROM [address] = action->data[i];
        }
    }
}

//-----------------------------------------------------------------------------
// Patches_MEM_Apply (void)
// Apply real-time patches to memory map
//-----------------------------------------------------------------------------
void        Patches_MEM_Apply (void)
{
    t_patch *patch = Patches.patch_current;
    t_list *actions;
    if (patch == NULL)
        return;

    // Apply MEM patches
    for (actions = patch->mem_patches; actions != NULL; actions = actions->next)
    {
        t_patch_action *action = actions->elem;

        // Apply all bytes
        int i;
        int address = action->address;
        int length = action->data_length;
        if (address < 0x0000 || address > 0xFFFF || (address + length - 1) < 0x0000 || (address + length - 1) > 0xFFFF)
        {
            Msg (MSGT_USER, Msg_Get (MSG_Patch_Out_of_Bound), "MEM", address);
            return;
        }
        for (i = 0; i < length; i++)
        {
            #ifdef DEBUG_PATCHES
                Msg (MSGT_DEBUG, "Patch MEM[%04X] = %02X", address, action->data[i]);
            #endif
            Mem_Pages [address >> 13] [address] = action->data[i];
            address++;
        }
    }
}

//-----------------------------------------------------------------------------

