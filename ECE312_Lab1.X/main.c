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

    DDRD &= ~(1 << PD0); // set PD0 to be the input pin
    PORTD |= (1 << PD0); // enable pull-up resistor for switch

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
    DDRB |= 0x1C;      // PB2, PB3, PB4 as outputs (0b00011100)
    PORTB = led_off;

    uint8_t color = red; // start on a known color instead of reading PINB

    while (1) {

        // switch color and check for button
        switch(color){
            case red:
                if (button_pressed() == 1){
                    while (button_pressed()); // wait for release (debounce)
                    _delay_ms(1000);
                    color = (PORTB & led_off) | yellow;
                    break;
                }
                break;
            case yellow:
                if (button_pressed() == 1){
                    while (button_pressed());
                    _delay_ms(1000);
                    color = (PORTB & led_off) | green;
                    break;
                }
                break;
            case green:
                if (button_pressed() == 1){
                    while (button_pressed());
                    _delay_ms(1000);
                    color = (PORTB & led_off) | cyan;
                    break;
                }
                break;
            case cyan:
                if (button_pressed() == 1){
                    while (button_pressed());
                    _delay_ms(1000);
                    color = (PORTB & led_off) | blue;
                    break;
                }
                break;
            case blue:
                if (button_pressed() == 1){
                    while (button_pressed());
                    _delay_ms(1000);
                    color = (PORTB & led_off) | magenta;
                    break;
                }
                break;
            case magenta:
                if (button_pressed() == 1){
                    while (button_pressed());
                    _delay_ms(1000);
                    color = (PORTB & led_off) | white;
                    break;
                }
                break;
            case white:
                // check if button pressed
                if (button_pressed() == 1){
                    while (button_pressed());
                    _delay_ms(1000);
                    color = (PORTB & led_off) | red;
                    break;
                }
                break;

            default: // default is led off
                if (button_pressed() == 1){
                    while (button_pressed());
                    _delay_ms(1000);
                    color = (PORTB & led_off) | red;
                    break;
                }
                break;
        }

        PORTB = (PORTB & ~0x1C) | color; // drive the current color out
        _delay_ms(1000);
        PORTB &= ~(1 << PB2); // Turn off PB2
        _delay_ms(1000);
    }
}