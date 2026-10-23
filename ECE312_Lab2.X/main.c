/*
 * File:   main.c
 * Author: ktaggar, zfeng8
 * modules to be inlcluded:
 * (main program (generate frequency), buzzer module, HC_SR04 module 
 * 
 * Created on October 23, 2026, 1:53 PM
 */


#define F_CPU 1000000UL
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define timer0 (1<<PB2)
#define timer1 (1<<PB3)


int main(int argc, char** argv) {

    DDRB |= timer0 | timer1;
    
    // 8 bit timer 
    //set as compare toggle
    TCCR0A = (1<<COM0A0) | (1<<WGM01);
    // set the prescalling factor to 8
    TCCR0B = (1<<CS01);
    // sets the frequency per flip 
    OCR0A = 238;
    
   
    // 16 bit timer: 
    // set as compare toggle
    TCCR1A = (1<<COM1A0);
    TCCR1B = (1<<CS10);
    OCR1A = 1135;
    
    while(1);
}

