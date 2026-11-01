/*
 * File:   main.c
 * Author: ktaggar, zfeng8
 *
 */

#define F_CPU 1000000UL
#define GAP_MS   30
#define ECHO_MIN_US 235
#define ECHO_MAX_US 471
#define T1_RISING     ((1 << ICNC1) | (1 << ICES1) | (1 << CS10))
#define T1_FALLING    ((1 << ICNC1) | (1 << CS10))

#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"
#include "songs.h"

//delay_ms() needs a compile-time constant, so a variable delay has to be
static void hold_ms(uint16_t ms)
{
    while (ms--) {
        _delay_ms(1);
    }
}

//play the voice (timer0) and lower voice (timer1)
static void play_voice(uint8_t voice)
{
    uint8_t i;
    uint8_t len = song_length(voice);
    note_t  n;
 
    for (i = 0; i < len; i++) {
        n = song_note(voice, i);
        buzzer_tone(voice, n.pitch);
        hold_ms((uint16_t)n.ticks * TICK_MS - GAP_MS);
        buzzer_off(voice);
        hold_ms(GAP_MS);
    }
}
    

// button test
//uint8_t button_pressed(void){
//    uint8_t j;
//    
//    j = PIND;
//    j = j & 0x1;
//    
//    if (j == 0x01) 
//    {
//        return 0;
//    }
//    else
//    {
//        return 1;
//    }
//}



static uint16_t hcsr04_read_us(void)
{
    uint16_t start, end;
 
    /* Timer1 free-running at 1 us per tick, capture on the rising edge. */
    TCCR1A = 0;
    TCCR1B = T1_RISING;
    TCNT1  = 0;                     /* so TCNT1 doubles as a timeout clock */
 
    /* --- the trigger pulse --- */
    PORTD |=  (1 << PD5);
    _delay_us(10);
    PORTD &= ~(1 << PD5);
 
    /* --- wait for Echo to go high --- *
     * ICF1 is cleared by WRITING A ONE to it, not by clearing the bit. */
    TIFR = (1 << ICF1);
    while (!(TIFR & (1 << ICF1))) {
        if (TCNT1 > 60000) {
            TCCR1B = 0;
            return 0;               /* nothing out there */
        }
    }
    start = ICR1;                   /* hardware timestamped the edge */
 
    /* --- now wait for it to go low --- *
     * Change the edge first, then clear the flag: switching ICES1 can set
     * ICF1 by itself. */
    TCCR1B = T1_FALLING;
    TIFR = (1 << ICF1);
    while (!(TIFR & (1 << ICF1))) {
        if (TCNT1 > 60000) {
            TCCR1B = 0;
            return 0;               /* echo never came back down */
        }
    }
    end = ICR1;
 
    TCCR1B = 0;                     /* stop Timer1 */
 
    /* Unsigned subtraction, so this is still correct if TCNT1 rolled over
     * between the two edges (e.g. 200 - 65000 gives 736 in a uint16_t). */
    return end - start;
}

static uint8_t sensor_detect(void){
    uint16_t a, b;

    a = hcsr04_read_us();
    hold_ms(80);                        /* ?60 ms between pings */
    b = hcsr04_read_us();

    return (a >= ECHO_MIN_US && a <= ECHO_MAX_US &&
            b >= ECHO_MIN_US && b <= ECHO_MAX_US);
           
}


static void play_both(uint8_t song)
{
    uint8_t iu = 0, il = 0;     /* which note each voice is on */
    uint8_t ru = 0, rl = 0;     /* ticks left in that note     */
    uint8_t len = song_length(VOICE_UPPER);
    note_t  n;

    while (iu < len || ru > 0) {

        if (ru == 0) {                      /* upper needs its next note */
            n = song_note(VOICE_UPPER, iu++);
            ru = n.ticks;
            buzzer_tone(VOICE_UPPER, n.pitch);
        }
        if (rl == 0) {                      /* lower needs its next note */
            n = song_note(VOICE_LOWER, il++);
            rl = n.ticks;
            buzzer_tone(VOICE_LOWER, n.pitch);
        }

        ru--;                               /* spend this tick */
        rl--;

        hold_ms(TICK_MS - GAP_MS);

        if (ru == 0) buzzer_off(VOICE_UPPER);
        if (rl == 0) buzzer_off(VOICE_LOWER);

        hold_ms(GAP_MS);
    }

    buzzer_silence();
}

static void play_song(uint8_t mode)
{
    if (mode == VOICE_COUNT) {
        play_both(mode);
    } else {
        play_voice(mode);
    }
    buzzer_silence();
}


int main(void)
{
    //initialize the buzzer settings
    DDRD |=  (1 << PD5);    
    DDRD &= ~(1 << PD6); 
    
    buzzer_init();
    while(1) {
        if (sensor_detect() == 1){
            play_song(VOICE_COUNT); //voice_count plays both
            buzzer_init(); 
        }
        hold_ms(100); // wait for 60 ms measurement cycle
    }
}
        
    



