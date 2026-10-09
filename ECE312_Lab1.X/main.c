/*
 * File:   main.c
 * Author: ktaggar
 *
 * Created on October 2, 2026, 2:24 PM
 */

#define F_CPU 1000000UL
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>

// define leds PB2 (Green), PB3 (Blue), PB4(Red)
#define led_mask ((1 << PB2) | (1 << PB3) | (1 << PB4))
#define led_off ((0 << PB2) | (0 << PB3) | (0 << PB4))
#define red ((0 << PB2) | (0<< PB3) | (1 << PB4))
#define yellow ((1 << PB2) | (0 << PB3) | (1 << PB4))
#define green ((1 << PB2) | (0 << PB3) | (0 << PB4))
#define cyan ((1 << PB2) | (1 << PB3) | (0 << PB4))
#define blue ((0 << PB2) | (1 << PB3) | (0 << PB4))
#define magenta ((0 << PB2) | (1 << PB3) | (1 << PB4))
#define white ((1 << PB2) | (1 << PB3) | (1 << PB4))

uint8_t button_pressed(void){
    uint8_t j;

    j = PIND;
    j = j & 0x01;

    if (j == 0x01) // pulled high -> button NOT pressed
    {
        return 0;
    }
    else // pulled low -> button pressed
    {
        return 1;
    }
}

int main(void) {
    
    // define LED lights
    DDRB |= led_mask;      // PB2, PB3, PB4 as outputs (0b00011100)
    PORTB &= ~led_mask;
    
    DDRD &= ~(1 << PD0); // set PD0 to be the input pin
    PORTD |= (1 << PD0); // enable pull-up resistor for switch

    uint8_t color = led_off; // start on a known color instead of reading PINB
    

    while (1) {
        
        if (button_pressed() == 1){
            _delay_ms(20);
            if (button_pressed() == 1) {
                switch(color){
                    case led_off:
                        color = red;
                        break;
                    case red:
                        color = yellow;
                        break;
                    case yellow:
                        color = green;
                        break;
                    case green:
                         color = cyan;
                            break;
                    case cyan:
                        color = blue;
                        break;
                    case blue:
                        color = magenta;
                        break;
                    case magenta:
                        color = white;
                        break;
                    case white:
                        color = red;
                        break;
                    default: // default is led off
                        color = led_off;
                        break;
                }
                PORTB = (PORTB & ~led_mask) | color;
                while (button_pressed());  // Wait for release
                _delay_ms(20);             // Debounce release
            }
        }
       
    }
}
