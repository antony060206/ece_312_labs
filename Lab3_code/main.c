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

#define ADC_VRX 0
#define ADC_VRY 1
#define DEADBAND 3 

// field variables
static FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
static uint16_t x_centre, y_centre;


void adc_init(void){
   DDRC &= ~((1 << PC0) | (1 << PC1)); // resets and set PC0 and PC1 to input 
   PORTC &= ~((1 << PC0) | (1 << PC1)); // pull-ups 
   DIDR0 |=  (1 << ADC1D) | (1 << ADC0D); // digital buffer off
   
   ADMUX = (1 << REFS0); // set AVCC reference  
   ADCSRA = (1 << ADEN)| (1 << ADPS1)|(1 << ADPS0);// set the ADC configuration and prescalling to 8 (8Mhz/8 = 125khz) falls within 50-200
}


// convert int to percentage
int16_t adc_conversion(uint16_t pos, uint16_t centre)
{
    int16_t d = (int16_t)pos - (int16_t)centre;
    int16_t pct;

    if (d >= 0) pct = ((int32_t)d * 100) / (1023 - centre);
    else        pct = ((int32_t)d * 100) / centre;

    if (pct >  100) pct =  100;
    if (pct < -100) pct = -100;
    if (pct > -DEADBAND && pct < DEADBAND) pct = 0;

    return pct;
}

int16_t adc_read(uint16_t channel){
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // begin
    ADCSRA |= (1 << ADSC); //start conversion
              
    while (ADCSRA & (1 << ADSC));   // check for conversion status 
    
    return ADC;
}

// calibrate the joystick centre with 16 sampless
void joystick_calibrate(void)
{
    uint32_t sx = 0, sy = 0;
    for (uint8_t i = 0; i < 16; i++) {
        sx += adc_read(ADC_VRX );
        sy += adc_read(ADC_VRY);
        _delay_ms(2);
    }
    x_centre = sx / 16;
    y_centre = sy / 16;
}

int main(void)
{
    lcd_init();
    adc_init();    
    lcd_gotoxy(0, 0); // start from the position 1 of row 1
    lcd_puts("ECE312 Lab3");
    joystick_calibrate();
    
    for (;;) {
        int16_t x = adc_read(ADC_VRX);
        int16_t y = adc_read(ADC_VRY);
        
        // for testing counter 
        lcd_gotoxy(0, 1);
        fprintf(&lcd_str, "x=%+1d y=%+1d", adc_conversion(x, x_centre), adc_conversion(y, y_centre));
        _delay_ms(200);
    }
}
