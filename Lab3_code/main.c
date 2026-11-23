/* 
 * File:   main.c
 * Author: zfeng8
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
	.extended = 0xFF, // EXTENDED {BODLEVEL=DISABLED}
};

LOCKBITS = 0xFF; // {LB=NO_LOCK, BLB0=NO_LOCK, BLB1=NO_LOCK}


void init(void){
    //initiate all modules 
    lcd_init();
    adc_init();
    uart_init();
    button_init();
    joystick_calibrate();
}

int main(void)
{
    //initiate all modules 
    init();
    
    //start-up
    fprintf(&uart_str, "\r\n$Q?");
    uart_gets();
    lcd_puts_centred(line, 0); 
    
    // asks for handle
    fprintf(&uart_str, "\r\n$Haaaaaa?");
    uart_gets();
    memcpy(handle, line + 1, 6);
    handle[6] = '\0';
    
    
    for (;;) {
        
        fprintf(&uart_str, "\r\nC%+04d%+04d%u", joystick_x(), joystick_y(), button_fire());
        fprintf(&uart_str, "\r\n$SaaaAaaa?");
        uart_gets();
        
        if (line[0] == 'S' && line[4] == 'A') {
            memcpy(score, line + 1, 3);
            memcpy(ammo,  line + 5, 3);
        }

        lcd_gotoxy(0, 1);
        fprintf(&lcd_str, "%s  %s  %s  ", handle, ammo, score);

        fprintf(&uart_str, "\n?");
        uart_gets();
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