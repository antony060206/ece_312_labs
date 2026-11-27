/* 
 * File:   main.c
 * Name: Antony Feng, Komaldeep Taggar
 * CCID: zfeng8, ktaggar
 *
 * AI usage for learning and research purposes (50%), human code (50%)
 *
 * Created on November 21, 2026, 5:51 PM
 */
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"
#include "joystick.h"
#include "uart.h"
#include "button.h"

char buf[20], handle[7], score[4] = "000", ammo[4] = "000";

// field variables
static FILE lcd_str = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

// external crystal config (needs to enable fuse programming)
FUSES = {
	.low = 0xFF, // LOW {SUT_CKSEL=EXTXOSC_8MHZ_XX_16KCK_14CK_65MS, CKOUT=CLEAR, CKDIV8=CLEAR}
	.high = 0xD9, // HIGH {BOOTRST=CLEAR, BOOTSZ=2048W_3800, EESAVE=CLEAR, WDTON=CLEAR, SPIEN=SET, DWEN=CLEAR, RSTDISBL=CLEAR}
	.extended = 0xFD, // EXTENDED {BODLEVEL=Enabled}
};

LOCKBITS = 0xFF; // {LB=NO_LOCK, BLB0=NO_LOCK, BLB1=NO_LOCK}


void init(void){
    //initiate all modules
    uart_init();
    
    lcd_init();
    adc_init();
    button_init();
    joystick_calibrate();
}

int main(void)
{
    
    //initiate all modules 
    init();
    
    //start-up, ask for the game name
    fprintf(&uart_str, "\r\n$Q?");
    uart_gets();
    lcd_puts_centred(line, 0); 
    
    // asks for handle
    fprintf(&uart_str, "\r\n$Haaaaaa?");
    uart_gets();
    memcpy(handle, line + 1, 6);
    handle[6] = '\0';
    
    
    for (;;) {

		// Send the controller status. '%+04d' gives show the sign and fill upto 4 characters.
		// Ex: Stick centered at X-axis (X = 0 = +000), 50% down in Y (Y = -50 = -050), and button pressed (1) gives: C+000-0501.
        fprintf(&uart_str, "\r\nC%+04d%+04d%u", joystick_x(), joystick_y(), button_fire());

		// Ask for score and ammo. If statement checks for formatting, (if mistyped then keep old score and ammo), if valid then copy 3 digits after 'S' into score, and 3 digits after the 'A" into ammo.
		// Positions 1-3 go into score, Positions 5-7 go into ammo.
        fprintf(&uart_str, "\r\n$SaaaAaaa?");
        uart_gets();
        if (line[0] == 'S' && line[4] == 'A') {
            memcpy(score, line + 1, 3);
            memcpy(ammo,  line + 5, 3);
        }

		// Update the lcd. Move cursor to second row and write the handle, ammo and score.
        lcd_gotoxy(0, 1);
        fprintf(&lcd_str, "%s  %s  %s  ", handle, ammo, score);

		// Print question mark, and get response.
        fprintf(&uart_str, "\n?");
        uart_gets();
		
		// Look at the first letter typed, and check if it matches. If it matches then print the score or ammo value. For unknown values send error message.
        if (line[0] == 'S') {
            fprintf(&uart_str, "\r\nS%s", score);
        }
        
        else if (line[0] == 'A') {
            fprintf(&uart_str, "\r\nA%s", ammo);
        }
        
        else {
            fprintf(&uart_str, "\r\n-Error");
        }
        
    }
}
