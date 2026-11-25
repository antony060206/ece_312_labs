
#include "defines.h"
#include <avr/io.h>
#include "uart.h"


//public variable 
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
char line[17];

// init UART 
void uart_init(void){
    UBRR0 = 7; // set the baud rate to 115200 @14.7456Mhz, U2X on   
    UCSR0A = 0; // double speed off
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enable transmitter and receiver
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits with no parity bit (checking bit) and 1 stopping bit.
}

    
// The uart_putchar and uart_getchar send and receive 1 bit while waiting for the hardware to be ready.
// test 
int uart_putchar(char c, FILE *stream)
{
    while (!(UCSR0A & (1 << UDRE0)));   //wait until the buffer is free

    UDR0 = c;
    return 0;
}

// test
int uart_getchar(FILE *stream)
{
    while (!(UCSR0A & (1 << RXC0)));// wait for a byte to arrive
    return UDR0;
}

// Reads characters until a carriage retunr or newline is sent.
void uart_gets(){
    uint8_t i = 0; 
    
    for(;;){
       int c = fgetc(&uart_str);
        
        if (c == EOF) // if end of file aka new line or return 
            continue;
       
        if (c == '\r' || c == '\n') { // skips stray terminators
            if (i > 0){
                break;
            }
            continue;                 
        }
       
        if (c == 0x08 || c == 0x7F) {      /* backspace - step back */
            if (i > 0) i--;
            continue;
        }
       
        if (i < sizeof(line) - 1) // Line array is 17 bytes (16 characters and null terminator '\0'. This only stores the characters while i < 16 and throws away the rest. The '- 1' leaves '\0' (null terminator) at line[i].
            line[i++] = (char)c;
    }
    line[i] = '\0';
}
