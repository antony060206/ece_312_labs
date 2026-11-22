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
#include "joystick.h"
#include "uart.h"
#include "button.h"

// field variables
static FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);


int main(void)
{
    //initiate all modules 
    lcd_init();
    adc_init();
    uart_init();
    button_init();
    
    lcd_gotoxy(0, 0); // start from the position 1 of row 1
    lcd_puts_padded("ECE312 Lab3", 0);
    joystick_calibrate();
   
    
    for (;;) {
        // for testing counter 
        lcd_gotoxy(0, 1);
        
        // test 1 joystick
        // fprintf(&lcd_str, "x=%+4d y=%+4d", joystick_x(), joystick_y());
        
        // test 2 UART connection
//        fprintf(&uart_str, "Hello\r\n");
//        _delay_ms(500);
//        
//        uart_gets();
//        lcd_puts_padded(line, 1);
//        _delay_ms(500);
        
        //test 3 button
        butt
    }
}