#ifndef LIB_UART_H
#define LIB_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SIZE	64

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATtiny2313A__)
	#include <avr/io.h>
#endif

/* Prototype */
void uart_initialize(uint32_t);
void uart_transmit_byte(uint8_t);
void uart_transmit_buffer(const uint8_t*, uint8_t);
uint8_t uart_receive_byte(void);
void uart_receive_buffer(uint8_t*);
void uart_flush();
void uart_print(const char*);

/*uint8_t USART_dataAvailable(); 
void printStr(const char *);
void printInt32(uint8_t count, ...);
void printInt16(uint8_t count, ...);
void printFlt(uint8_t count, ... );
void printHEX(uint32_t);
char *readStr();
int32_t readInt();*/

#ifdef __cplusplus
}
#endif

#endif
