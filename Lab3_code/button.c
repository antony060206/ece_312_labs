#include "defines.h"
#include <avr/io.h>
#include "button.h"      


// Make PB0 an input, pin reads 1 when released.
void button_init(void)
{
    DDRB  &= ~(1 << PB0);  
    PORTB |=  (1 << PB0);  
}

// Return 1 when PB0 reads low (i.e when it is pressed) and 0 otherwise.
uint8_t button_fire(void)
{
    return (PINB & (1 << PB0)) ? 0 : 1;   
}
