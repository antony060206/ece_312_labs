#define F_CPU 1000000UL
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <button_config.h>
#include <avr/io.h>


uint8_t button_pressed(){
    uint8_t j;
    
    DDRD &= 0XFE; // set the PD0 to be the input pin
    PORTD |= 0X00; // no pull-up resistor for switch all 0
    
    j=PIND;
    j=j&0X01;
    
    if(j==0x00) //button not pressed
    {
        return 0;
    }
    else if (j==0x01) // button pressed
    {
        return 1;
    }
    
}

