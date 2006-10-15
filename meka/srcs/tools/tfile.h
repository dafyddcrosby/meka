//-----------------------------------------------------------------------------
// MEKA - tfile.c
// Text file reading functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------

typedef struct
{
  int           size;
  char *        data_raw;
  t_list *      data_lines;
}               t_tfile;

//-----------------------------------------------------------------------------
// Methods
//-----------------------------------------------------------------------------

t_tfile *       tfile_read(const char *filename);
void            tfile_free(t_tfile *tf);

//-----------------------------------------------------------------------------
