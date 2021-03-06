//
// Meka - PSG.H
// PSG Emulation, by Maxim Gready
// Tweaked by Omar Cornut for implementation in MEKA
//

//-----------------------------------------------------------------------------

int     PSG_Init        (void *user_data /* unused */);
void    PSG_Update      (int chip, void *buffer, int length);
void    PSG_Reset       (void);
void    PSG_Save        (FILE *f);
void    PSG_Load        (FILE *f, int version);
void    PSG_Regenerate  (void);
void    PSG_Mute        (void);

//-----------------------------------------------------------------------------

typedef struct
{
    signed short int    ToneFreqVal;            // Frequency register values (counters)
    signed       char   ToneFreqPos;            // Frequency channel flip-flops
    signed long  int    IntermediatePos;        // Intermediate values used at boundaries between + and -
  unsigned short int	Volume;                 // Current channel volume (0-900+...)
                 int    Active;                 // Set to 0 to mute
}                       t_psg_channel;

typedef struct
{
  t_psg_channel         Channels[4];            //
  unsigned short int	Registers[8];           //
                 int    LatchedRegister;        //
  unsigned       char   Stereo;                 //
  unsigned short int    NoiseShiftRegister;     //
    signed short int	NoiseFreq;              // regenerate
                 float  Clock;
                 float  dClock;
  unsigned       int    NumClocksForSample;
                 int    SamplingRate;           // fixed
}                       t_psg;

extern t_psg            PSG;

//-----------------------------------------------------------------------------

void    SN76489_Reset           (const unsigned long PSGClockValue, const unsigned long SamplingRate);
void    SN76489_ClockSet        (const unsigned long PSGClockValue);
void    SN76489_Write           (const unsigned char data);
void    SN76489_StereoWrite     (const unsigned char data);
void    SN76489_GetValues       (int *left, int *right);

//-----------------------------------------------------------------------------

