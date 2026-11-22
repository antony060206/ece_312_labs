/* 
 * File:   main.c
 * Author: zfeng8
 *
 * Created on November 21, 2026, 5:51 PM
 */

#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

#include <util/delay.h>
#include "lcd.h"

// field variables
static FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
int ADC_VRX = 0;
int ADC_VRY = 1;
/*
 * 
 */
int main(void)
{
    lcd_init();
    adc_init();    
    lcd_gotoxy(0, 0); // start from the position 1 of row 1
    lcd_puts("ECE312 Lab3");
    
    for (;;) {
        uint16_t x = adc_read(ADC_VRX);
        uint16_t y = adc_read(ADC_VRY);
        
        // for testing counter 
        lcd_gotoxy(0, 1);
        fprintf(&lcd_str, "x=%u y=%u", x, y);
        _delay_ms(200);
    }
}

void adc_init(void){
   DDRC &= ~((1 << PC0) | (1 << PC1)); // resets and set PC0 and PC1 to input 
   PORTC &= ~((1 << PC0) | (1 << PC1)); // pull-ups 
   DIDR0 |=  (1 << ADC1D) | (1 << ADC0D); // digital buffer off
   
   ADMUX = (1 << REFS0); // set AVCC reference  
   ADCSRA = (1 << ADEN)| (1 << ADPS1)|(1 << ADPS0);// set the ADC configuration and prescalling to 8 (8Mhz/8 = 125khz) falls within 50-200
}

uint16_t adc_read(uint16_t channel){
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // begin
    ADCSRA |= (1 << ADSC); //start conversion
              
    while (ADCSRA & (1 << ADSC));   // check for conversion status 
    
    return ADC;
}
