/*
 * File:   songs.c
 * Author: ktaggar, zfeng8
 *
 */

#include <avr/pgmspace.h>
#include "songs.h"

#define PITCH_MIN  0
#define PITCH_MAX  36       


// stores all the notes and there corresponding (ticks and duration)
static const timer0_cfg_t timer0_tbl[] PROGMEM = {
    {  59, 0x03 },   /* P_C3     130.81 Hz ->   130.21 Hz  N=64    -0.46% ( -8.0 cents) */
    {  55, 0x03 },   /* P_CS3    138.59 Hz ->   139.51 Hz  N=64    +0.66% (+11.4 cents) */
    {  52, 0x03 },   /* P_D3     146.83 Hz ->   147.41 Hz  N=64    +0.39% ( +6.7 cents) */
    {  49, 0x03 },   /* P_DS3    155.56 Hz ->   156.25 Hz  N=64    +0.44% ( +7.6 cents) */
    {  46, 0x03 },   /* P_E3     164.81 Hz ->   166.22 Hz  N=64    +0.86% (+14.7 cents) */
    {  44, 0x03 },   /* P_F3     174.61 Hz ->   173.61 Hz  N=64    -0.57% (-10.0 cents) */
    {  41, 0x03 },   /* P_FS3    185.00 Hz ->   186.01 Hz  N=64    +0.55% ( +9.5 cents) */
    {  39, 0x03 },   /* P_G3     196.00 Hz ->   195.31 Hz  N=64    -0.35% ( -6.1 cents) */
    {  37, 0x03 },   /* P_GS3    207.65 Hz ->   205.59 Hz  N=64    -0.99% (-17.3 cents) */
    {  35, 0x03 },   /* P_A3     220.00 Hz ->   217.01 Hz  N=64    -1.36% (-23.7 cents) */
    {  33, 0x03 },   /* P_AS3    233.08 Hz ->   229.78 Hz  N=64    -1.42% (-24.7 cents) */
    { 252, 0x02 },   /* P_B3     246.94 Hz ->   247.04 Hz  N=8     +0.04% ( +0.7 cents) */
    { 238, 0x02 },   /* P_C4     261.63 Hz ->   261.51 Hz  N=8     -0.05% ( -0.8 cents) */
    { 224, 0x02 },   /* P_CS4    277.18 Hz ->   277.78 Hz  N=8     +0.21% ( +3.7 cents) */
    { 212, 0x02 },   /* P_D4     293.66 Hz ->   293.43 Hz  N=8     -0.08% ( -1.4 cents) */
    { 200, 0x02 },   /* P_DS4    311.13 Hz ->   310.95 Hz  N=8     -0.06% ( -1.0 cents) */
    { 189, 0x02 },   /* P_E4     329.63 Hz ->   328.95 Hz  N=8     -0.21% ( -3.6 cents) */
    { 178, 0x02 },   /* P_F4     349.23 Hz ->   349.16 Hz  N=8     -0.02% ( -0.3 cents) */
    { 168, 0x02 },   /* P_FS4    369.99 Hz ->   369.82 Hz  N=8     -0.05% ( -0.8 cents) */
    { 158, 0x02 },   /* P_G4     392.00 Hz ->   393.08 Hz  N=8     +0.28% ( +4.8 cents) */
    { 149, 0x02 },   /* P_GS4    415.30 Hz ->   416.67 Hz  N=8     +0.33% ( +5.7 cents) */
    { 141, 0x02 },   /* P_A4     440.00 Hz ->   440.14 Hz  N=8     +0.03% ( +0.6 cents) */
    { 133, 0x02 },   /* P_AS4    466.16 Hz ->   466.42 Hz  N=8     +0.05% ( +0.9 cents) */
    { 126, 0x02 },   /* P_B4     493.88 Hz ->   492.13 Hz  N=8     -0.36% ( -6.2 cents) */
    { 118, 0x02 },   /* P_C5     523.25 Hz ->   525.21 Hz  N=8     +0.37% ( +6.5 cents) */
    { 112, 0x02 },   /* P_CS5    554.37 Hz ->   553.10 Hz  N=8     -0.23% ( -4.0 cents) */
    { 105, 0x02 },   /* P_D5     587.33 Hz ->   589.62 Hz  N=8     +0.39% ( +6.7 cents) */
    {  99, 0x02 },   /* P_DS5    622.25 Hz ->   625.00 Hz  N=8     +0.44% ( +7.6 cents) */
    {  94, 0x02 },   /* P_E5     659.26 Hz ->   657.89 Hz  N=8     -0.21% ( -3.6 cents) */
    {  88, 0x02 },   /* P_F5     698.46 Hz ->   702.25 Hz  N=8     +0.54% ( +9.4 cents) */
    {  83, 0x02 },   /* P_FS5    739.99 Hz ->   744.05 Hz  N=8     +0.55% ( +9.5 cents) */
    {  79, 0x02 },   /* P_G5     783.99 Hz ->   781.25 Hz  N=8     -0.35% ( -6.1 cents) */
    {  74, 0x02 },   /* P_GS5    830.61 Hz ->   833.33 Hz  N=8     +0.33% ( +5.7 cents) */
    {  70, 0x02 },   /* P_A5     880.00 Hz ->   880.28 Hz  N=8     +0.03% ( +0.6 cents) */
    {  66, 0x02 },   /* P_AS5    932.33 Hz ->   932.84 Hz  N=8     +0.05% ( +0.9 cents) */
    {  62, 0x02 },   /* P_B5     987.77 Hz ->   992.06 Hz  N=8     +0.44% ( +7.5 cents) */
    {  59, 0x02 },   /* P_C6    1046.50 Hz ->  1041.67 Hz  N=8     -0.46% ( -8.0 cents) */
};

// since 16 bits can hold up to 65535
static const uint16_t timer1_tbl[] PROGMEM = {
     3821,   /* P_C3     130.81 Hz ->   130.82 Hz   +0.01% ( +0.1 cents) */
     3607,   /* P_CS3    138.59 Hz ->   138.58 Hz   -0.01% ( -0.1 cents) */
     3404,   /* P_D3     146.83 Hz ->   146.84 Hz   +0.01% ( +0.1 cents) */
     3213,   /* P_DS3    155.56 Hz ->   155.57 Hz   +0.00% ( +0.1 cents) */
     3033,   /* P_E3     164.81 Hz ->   164.80 Hz   -0.01% ( -0.2 cents) */
     2862,   /* P_F3     174.61 Hz ->   174.64 Hz   +0.02% ( +0.3 cents) */
     2702,   /* P_FS3    185.00 Hz ->   184.98 Hz   -0.01% ( -0.2 cents) */
     2550,   /* P_G3     196.00 Hz ->   196.00 Hz   +0.00% ( +0.0 cents) */
     2407,   /* P_GS3    207.65 Hz ->   207.64 Hz   -0.01% ( -0.1 cents) */
     2272,   /* P_A3     220.00 Hz ->   219.97 Hz   -0.01% ( -0.2 cents) */
     2144,   /* P_AS3    233.08 Hz ->   233.10 Hz   +0.01% ( +0.1 cents) */
     2024,   /* P_B3     246.94 Hz ->   246.91 Hz   -0.01% ( -0.2 cents) */
     1910,   /* P_C4     261.63 Hz ->   261.64 Hz   +0.01% ( +0.1 cents) */
     1803,   /* P_CS4    277.18 Hz ->   277.16 Hz   -0.01% ( -0.1 cents) */
     1702,   /* P_D4     293.66 Hz ->   293.60 Hz   -0.02% ( -0.4 cents) */
     1606,   /* P_DS4    311.13 Hz ->   311.14 Hz   +0.00% ( +0.1 cents) */
     1516,   /* P_E4     329.63 Hz ->   329.60 Hz   -0.01% ( -0.2 cents) */
     1431,   /* P_F4     349.23 Hz ->   349.16 Hz   -0.02% ( -0.3 cents) */
     1350,   /* P_FS4    369.99 Hz ->   370.10 Hz   +0.03% ( +0.5 cents) */
     1275,   /* P_G4     392.00 Hz ->   391.85 Hz   -0.04% ( -0.6 cents) */
     1203,   /* P_GS4    415.30 Hz ->   415.28 Hz   -0.01% ( -0.1 cents) */
     1135,   /* P_A4     440.00 Hz ->   440.14 Hz   +0.03% ( +0.6 cents) */
     1072,   /* P_AS4    466.16 Hz ->   465.98 Hz   -0.04% ( -0.7 cents) */
     1011,   /* P_B4     493.88 Hz ->   494.07 Hz   +0.04% ( +0.7 cents) */
      955,   /* P_C5     523.25 Hz ->   523.01 Hz   -0.05% ( -0.8 cents) */
      901,   /* P_CS5    554.37 Hz ->   554.32 Hz   -0.01% ( -0.1 cents) */
      850,   /* P_D5     587.33 Hz ->   587.54 Hz   +0.04% ( +0.6 cents) */
      803,   /* P_DS5    622.25 Hz ->   621.89 Hz   -0.06% ( -1.0 cents) */
      757,   /* P_E5     659.26 Hz ->   659.63 Hz   +0.06% ( +1.0 cents) */
      715,   /* P_F5     698.46 Hz ->   698.32 Hz   -0.02% ( -0.3 cents) */
      675,   /* P_FS5    739.99 Hz ->   739.64 Hz   -0.05% ( -0.8 cents) */
      637,   /* P_G5     783.99 Hz ->   783.70 Hz   -0.04% ( -0.6 cents) */
      601,   /* P_GS5    830.61 Hz ->   830.56 Hz   -0.01% ( -0.1 cents) */
      567,   /* P_A5     880.00 Hz ->   880.28 Hz   +0.03% ( +0.6 cents) */
      535,   /* P_AS5    932.33 Hz ->   932.84 Hz   +0.05% ( +0.9 cents) */
      505,   /* P_B5     987.77 Hz ->   988.14 Hz   +0.04% ( +0.7 cents) */
      477,   /* P_C6    1046.50 Hz ->  1046.03 Hz   -0.05% ( -0.8 cents) */
};

static const note_t ode_to_joy_upper[] PROGMEM = {
    {P_E4 , D_Q  }, {P_E4 , D_Q  }, {P_F4 , D_Q  }, {P_G4 , D_Q  },
    {P_G4 , D_Q  }, {P_F4 , D_Q  }, {P_E4 , D_Q  }, {P_D4 , D_Q  },
    {P_C4 , D_Q  }, {P_C4 , D_Q  }, {P_D4 , D_Q  }, {P_E4 , D_Q  },
    {P_E4 , D_Q  }, {P_D4 , D_Q  }, {P_D4 , D_H  }, {P_E4 , D_Q  },
    {P_E4 , D_Q  }, {P_F4 , D_Q  }, {P_G4 , D_Q  }, {P_G4 , D_Q  },
    {P_F4 , D_Q  }, {P_E4 , D_Q  }, {P_D4 , D_Q  }, {P_C4 , D_Q  },
    {P_C4 , D_Q  }, {P_D4 , D_Q  }, {P_E4 , D_Q  }, {P_D4 , D_Q  },
    {P_C4 , D_Q  }, {P_C4 , D_H  },
};
 
static const note_t ode_to_joy_lower[] PROGMEM = {
    {P_C4 , D_H  }, {P_C4 , D_H  }, {P_C4 , D_H  }, {P_G4 , D_H  },
    {P_C4 , D_H  }, {P_G4 , D_H  }, {P_G4 , D_H  }, {P_G4 , D_H  },
    {P_C4 , D_H  }, {P_C4 , D_H  }, {P_C4 , D_H  }, {P_G4 , D_H  },
    {P_C4 , D_H  }, {P_G4 , D_H  }, {P_G4 , D_H  }, {P_C4 , D_H  },
};


// categorize the 2 songs in 2d array 
typedef struct {
    const note_t *notes;
    uint8_t       len;
} voice_t;
 
static const voice_t songs[VOICE_COUNT] PROGMEM = {
    { ode_to_joy_upper, sizeof(ode_to_joy_upper) / sizeof(note_t) },
    { ode_to_joy_lower, sizeof(ode_to_joy_lower) / sizeof(note_t) },
};

// accessors
uint8_t song_length(uint8_t voice)
{
    return pgm_read_byte(&songs[voice].len);
}
 
note_t song_note(uint8_t voice, uint8_t i)
{
    const note_t *base = (const note_t *)pgm_read_word(&songs[voice].notes);
    note_t n;
 
    n.pitch = pgm_read_byte(&base[i].pitch);
    n.ticks = pgm_read_byte(&base[i].ticks);
    return n;
}



timer0_cfg_t pitch_timer0(uint8_t pitch)
{
    timer0_cfg_t cfg = { 0, 0 };     /* cs = 0 -> timer stopped -> silence */

    if (pitch > PITCH_MAX) {         /* catches P_REST (0xFF) too */
        return cfg;
    }
    cfg.ocr = pgm_read_byte(&timer0_tbl[pitch].ocr);
    cfg.cs  = pgm_read_byte(&timer0_tbl[pitch].cs);
    return cfg;
}

uint16_t pitch_timer1(uint8_t pitch)
{
    if (pitch > PITCH_MAX) {
        return 0;
    }
    return pgm_read_word(&timer1_tbl[pitch]);
}