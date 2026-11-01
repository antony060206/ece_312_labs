
/*
 * File:   buzzer.c
 * Author: ktaggar, zfeng8
 *
 */

#include <avr/io.h>
#include "buzzer.h"
#include "songs.h"

#define UPPER_BIT PB2    
#define LOWER_BIT PB3     

#define T0_MODE_OFF ((1 << WGM01))
#define T1A_MODE_OFF (0)
#define T1B_MODE_OFF ((1 << WGM12))

#define T0_MODE_ON ((1 << COM0A0) | (1 << WGM01))
#define T1A_MODE_ON ((1 << COM1A0))

// initiate the port and TTCR settings
void buzzer_init(void)
{
    DDRB  |=  (1 << UPPER_BIT) | (1 << LOWER_BIT);
    PORTB &= ~((1 << UPPER_BIT) | (1 << LOWER_BIT));

    TCCR0A = T0_MODE_OFF;
    TCCR0B = 0;                 

    TCCR1A = T1A_MODE_OFF;
    TCCR1B = T1B_MODE_OFF;     
}

// buzzing the pitch
void buzzer_tone(uint8_t voice, uint8_t pitch)
{
    // if it is timer0
    if (voice == VOICE_UPPER) {
        timer0_cfg_t cfg = pitch_timer0(pitch);

        if (cfg.cs == 0) {
            buzzer_off(VOICE_UPPER);
            return;
        }
        
        //set up the noise
        TCCR0B = 0; // kill the clock     
        TCNT0  = 0; // counter back to zero            
        OCR0A  = cfg.ocr; // configure new TOP 
        TCCR0A = T0_MODE_ON; // attach OCOA, toggle mode
        TCCR0B = cfg.cs; // starts the sounds (how long each tick should last)

    } else if (voice == VOICE_LOWER) {
        uint16_t ocr = pitch_timer1(pitch);

        if (ocr == 0) {
            buzzer_off(VOICE_LOWER);
            return;
        }

        TCCR1B = T1B_MODE_OFF;  
        TCNT1  = 0;
        OCR1A  = ocr;                             
        TCCR1A = T1A_MODE_ON;
        TCCR1B = T1B_MODE_OFF | (1 << CS10);    
    }

  
}

// turns off buzzer depending the current timer that it is on
void buzzer_off(uint8_t voice)
{
    if (voice == VOICE_UPPER) {
        TCCR0B = 0;                      
        TCCR0A = T0_MODE_OFF;           
        PORTB &= ~(1 << UPPER_BIT);     

    } else if (voice == VOICE_LOWER) {
        TCCR1B = T1B_MODE_OFF;
        TCCR1A = T1A_MODE_OFF;
        PORTB &= ~(1 << LOWER_BIT);
    }

}

void buzzer_silence(void)
{
    buzzer_off(VOICE_UPPER);
    buzzer_off(VOICE_LOWER);
}