/*
 * File:   main.c
 * Author: ktaggar, zfeng8
 *
 */

#define F_CPU 1000000UL
#define GAP_MS   30
#define ECHO_MIN_US 230
#define ECHO_MAX_US 455
#define T1_RISING     ((1 << ICNC1) | (1 << ICES1) | (1 << CS10)) //ICES1 set to capture on rising edge, cs10 clock select 
#define T1_FALLING    ((1 << ICNC1) | (1 << CS10)) // flips the edge select bit

#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"
#include "songs.h"

//delay_ms() needs a compile-time constant, so a variable delay has to be
// this function the same as a delay
static void hold_ms(uint16_t ms)
{
    while (ms--) {
        _delay_ms(1);
    }
}

//play the voice (timer0) and lower voice (timer1)
// voice are timer choices 0 is timer0, 1 is timer1
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


// calculates the time it takes to travel back and forth in us for the wave between 4-8cm 
static uint16_t hcsr04_read_us(void)
{
    uint16_t start, end;
 
    //Timer1 in normal mode (just a plain counter), TCCR1B starts at 1us/tick begins the moment cs10 is set 
    TCCR1A = 0;
    TCCR1B = T1_RISING; // arm for rising
    TCNT1  = 0;                     
    
    // input for the trigger as recommended by the datasheet, 10us to start the ranging cycle then emits 8 cycles of 40MHz burst then raise echo
    PORTD |=  (1 << PD5);
    _delay_us(10);
    PORTD &= ~(1 << PD5);
 
    // Timer/counter interrupt flag as the input capture event
    TIFR = (1 << ICF1);
    while (!(TIFR & (1 << ICF1))) { // continues the loop to see if edge arrives on pd6
        if (TCNT1 > 60000) { // if the counter goes beyond 60000 ticks means the sensor isnt responding
            TCCR1B = 0;
            return 0;               
        }
    }
    start = ICR1; //holds a copy of TCNT1 (timer1) on rising 
 
    TCCR1B = T1_FALLING; //arm for falling
    TIFR = (1 << ICF1);
    while (!(TIFR & (1 << ICF1))) { 
        if (TCNT1 > 60000) {
            TCCR1B = 0;
            return 0;               // no echo back, no response
        }
    }
    end = ICR1;
 
    TCCR1B = 0;                     
 
    return end - start;
}

static uint8_t sensor_detect(void){
    uint16_t a; 
    // uint16_t b;

    a = hcsr04_read_us();
//    hold_ms(40);                       
//    b = hcsr04_read_us();

    return (a >= ECHO_MIN_US && a <= ECHO_MAX_US);
            //&& (b >= ECHO_MIN_US && b <= ECHO_MAX_US);
           
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
        
    
