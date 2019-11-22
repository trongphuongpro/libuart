#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"


static int uart_putchar_printf(char, FILE*);
static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar_printf, NULL, _FDEV_SETUP_WRITE);


void uart_init(uint32_t baudrate) {
	/* baudrate */
	uint8_t ubbr = F_CPU / (16 * baudrate) - 1;
	UBRR0H = ubbr >> 8;
	UBRR0L = ubbr;

	/* configure */
	UCSR0A = 0x00;

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00); // 8-bit

	stdout = &uart_stdout;
}


void uart_transmit_byte(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0))) {
		// wait
	}
	UDR0 = data;
}


void uart_transmit_buffer(const void* buffer, uint32_t len) {
	const uint8_t *data = (uint8_t*)buffer;

	for (uint8_t i = 0; i < len; i++) {
		uart_transmit_byte(data[i]);
	}
}


void uart_putchar(char c) {
	if (c == '\n') {
		uart_transmit_byte('\r');
	}
	uart_transmit_byte(c);
}


int uart_putchar_printf(char c, FILE *stream) {
	uart_putchar(c);

	return 0;
}


void uart_print(const char* buffer) {
	for (int i = 0; i < strlen(buffer); i++) {
		uart_putchar(buffer[i]);
	}
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