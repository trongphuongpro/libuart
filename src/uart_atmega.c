#include <avr/io.h>
#include <string.h>
#include "uart.h"


void uart_initialize(uint32_t baudrate) {
	/* baudrate */
	uint8_t ubbr = F_CPU / (16 * baudrate) - 1;
	UBRR0H = ubbr >> 8;
	UBRR0L = ubbr;

	/* configure */
	UCSR0A = 0x00;

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00); // 8-bit
}

void uart_transmit_byte(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0))) {
		// wait
	}
	UDR0 = data;
}


void uart_transmit_buffer(const uint8_t* buffer, uint8_t n) {
	for (uint8_t i = 0; i < n; i++) {
		uart_transmit_byte(buffer[i]);
	}
}


void uart_print(const char* buffer) {
	uart_transmit_buffer((const uint8_t*)buffer, strlen(buffer));
}


uint8_t uart_receive_byte() {
	while (!(UCSR0A & (1 << RXC0))) {
		// wait
	}
	return UDR0;
}


uint8_t uart_flush() {
	uint8_t dummy = 0;
	while (UCSR0A & (1 << RXC0)) {
		dummy = UDR0;
	}
	return dummy;
}
