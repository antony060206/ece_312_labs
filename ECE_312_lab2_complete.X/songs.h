/*
 * File:   songs.h
 * Author: ktaggar, zfeng8
 *
 */

#ifndef SONGS_H
#define SONGS_H

#include <stdint.h>

#define TICK_MS  250  

// voice 
#define VOICE_UPPER   0
#define VOICE_LOWER   1
#define VOICE_COUNT   2 // 0 for ode to joy, 1 for jingle bell adn 2 for both


// Duration (120 BPM -> 500 ms per one beat meaning 4/4 = 500ms )
#define D_8    1   //250 ms
#define D_Q    2   // 500ms 
#define D_DQ   3   // 750 ms
#define D_H    4   // 1000 ms
#define D_W    8   //2000 ms

// Generated pitches and their corresponding frequency
#define P_REST 0xFF
#define P_C3    0   /*   130.81 Hz */
#define P_CS3   1   /*   138.59 Hz */
#define P_D3    2   /*   146.83 Hz */
#define P_DS3   3   /*   155.56 Hz */
#define P_E3    4   /*   164.81 Hz */
#define P_F3    5   /*   174.61 Hz */
#define P_FS3   6   /*   185.00 Hz */
#define P_G3    7   /*   196.00 Hz */
#define P_GS3   8   /*   207.65 Hz */
#define P_A3    9   /*   220.00 Hz */
#define P_AS3  10   /*   233.08 Hz */
#define P_B3   11   /*   246.94 Hz */
#define P_C4   12   /*   261.63 Hz */
#define P_CS4  13   /*   277.18 Hz */
#define P_D4   14   /*   293.66 Hz */
#define P_DS4  15   /*   311.13 Hz */
#define P_E4   16   /*   329.63 Hz */
#define P_F4   17   /*   349.23 Hz */
#define P_FS4  18   /*   369.99 Hz */
#define P_G4   19   /*   392.00 Hz */
#define P_GS4  20   /*   415.30 Hz */
#define P_A4   21   /*   440.00 Hz */
#define P_AS4  22   /*   466.16 Hz */
#define P_B4   23   /*   493.88 Hz */
#define P_C5   24   /*   523.25 Hz */
#define P_CS5  25   /*   554.37 Hz */
#define P_D5   26   /*   587.33 Hz */
#define P_DS5  27   /*   622.25 Hz */
#define P_E5   28   /*   659.26 Hz */
#define P_F5   29   /*   698.46 Hz */
#define P_FS5  30   /*   739.99 Hz */
#define P_G5   31   /*   783.99 Hz */
#define P_GS5  32   /*   830.61 Hz */
#define P_A5   33   /*   880.00 Hz */
#define P_AS5  34   /*   932.33 Hz */
#define P_B5   35   /*   987.77 Hz */
#define P_C6   36   /*  1046.50 Hz */


// defined pitch and ticks as struct in c for a note
typedef struct {
    uint8_t pitch;    
    uint8_t ticks;    
} note_t;

// write to register value
typedef struct {
    uint8_t ocr;     // write to OCROA (how many ticks to count before flipping the pin)
    uint8_t cs;      // write to TCCROB (how long per tick based on prescaler)
} timer0_cfg_t;


//Number of notes in one voice of `song`. 
uint8_t  song_length(uint8_t voice);


note_t   song_note(uint8_t voice, uint8_t i);

timer0_cfg_t pitch_timer0(uint8_t pitch);
uint16_t     pitch_timer1(uint8_t pitch); 

#endif 