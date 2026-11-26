/* 
 * File:   uart.h
 * Author: zfeng8, ktaggar
 *
 * Created on November 22, 2026, 12:44 PM
 */

#ifndef UART_H
#define UART_H
#include <stdio.h>    
#include <stdint.h>    

extern FILE uart_str;
extern char line[17];

#include <stdio.h>

void uart_init(void);
int  uart_putchar(char c, FILE *stream);
int  uart_getchar(FILE *stream);
void uart_gets();

#endif
