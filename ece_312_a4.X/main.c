/* 
 * File:   main.c
 * Author: Antony Feng
 *
*/

/*
ECE 312 Assignment 4,
Question 1 code:
 * Configurations:
 * CKDIV8 selected by fuse bits
 * clock select bit; N = 8
 * OCR0A = 124
 * COMOA1/COMOA0 = 01
 * CTC mode WGM[2:0] = 010, TOP = OCRA
 * use the ocfoa to generate a flag
*/

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

typedef struct{
    uint16_t milliseconds;
    uint8_t seconds;
    uint8_t minutes; 
    uint8_t hours;
} time_struct;


//global variable for time
volatile time_struct clock_time = {0, 0, 0, 0};

ISR(TIMER0_COMPA_vect)
{
    clock_time.milliseconds++;
    if (clock_time.milliseconds == 1000) {
        clock_time.milliseconds = 0;
        clock_time.seconds++;
    }
    if (clock_time.seconds == 60) {
        clock_time.seconds = 0;
        clock_time.minutes++;
    }
    if (clock_time.minutes == 60) {
        clock_time.minutes = 0;
        clock_time.hours++;
    }
    if (clock_time.hours == 24) {
        clock_time.hours = 0;
    }
}

void check_full(void){
    
}

int main(void){
    
    //set up TCCR0A
    TCCR0A = 0x42;
    OCR0A  = 124;    
    
    //set up TCCROB
    TCCR0B = 0x02;
    
    TIMSK |= (1 << OCIE0A);
    sei();
    
    while(1){
        //loop
    }
}

