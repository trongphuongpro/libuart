/** 
 * @file uart_tiva.c
 * @brief Functions for UART communication protocol Tiva C.
 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date 2019 Dec 28
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "driverlib/uart.h"
#include "uart.h"


static uint32_t UARTBase;

void uart_open(uint32_t base) {
	UARTBase = base;
}


void uart_send(uint8_t data) {
	UARTCharPut(UARTBase, data);
}


void uart_sendBuffer(const void* buffer, uint32_t len) {
	const uint8_t *data = (uint8_t*)buffer;

	for (uint32_t i = 0; i < len; i++) {
		UARTCharPut(UARTBase, data[i]);
	}
}


void uart_putchar(char c) {
	if (c == '\n') {
		UARTCharPut(UARTBase, '\r');
	}

	UARTCharPut(UARTBase, c);

	if (c == '\r') {
		UARTCharPut(UARTBase, '\n');
	}
}


void uart_print(const char* string) {
	for (uint32_t i = 0; i < strlen(string); i++) {
		uart_putchar(string[i]);
	}
}


uint8_t uart_receive(void) {
	return UARTCharGet(UARTBase);
}


void uart_flush(void) {
	while (UARTCharsAvail(UARTBase)) {
		UARTCharGetNonBlocking(UARTBase);
	}
}