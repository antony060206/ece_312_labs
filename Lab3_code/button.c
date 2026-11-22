#include "defines.h"
#include <avr/io.h>
#include "button.h"      

void button_init(void)
{
    DDRB  &= ~(1 << PB0);  
    PORTB |=  (1 << PB0);  
}

uint8_t button_fire(void)
{
    return (PINB & (1 << PB0)) ? 0 : 1;   
}