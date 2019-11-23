#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"


static int uart_putchar_io(char, FILE*);
static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar_io, NULL, _FDEV_SETUP_WRITE);

//static int uart_getchar_io(FILE*);
//static FILE uart_stdin = FDEV_SETUP_STREAM(NULL, uart_getchar_io, _FDEV_SETUP_READ);


void uart_open(uint32_t baudrate) {
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


void uart_write(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0))) {
		// wait
	}
	UDR0 = data;
}


void uart_writeBuffer(const void* buffer, uint32_t len) {
	const uint8_t *data = (uint8_t*)buffer;

	for (uint8_t i = 0; i < len; i++) {
		uart_write(data[i]);
	}
}


void uart_putchar(char c) {
	if (c == '\n') {
		uart_write('\r');
	}

	uart_write(c);

	if (c == '\r') {
		uart_write('\n');
	}
}


void uart_print(const char* buffer) {
	for (int i = 0; i < strlen(buffer); i++) {
		uart_putchar(buffer[i]);
	}
}


uint8_t uart_read() {
	while (!(UCSR0A & (1 << RXC0))) {
		// wait
	}
	return UDR0;
}


char uart_getchar() {
	return uart_read();
}


uint8_t uart_flush() {
	uint8_t dummy = 0;
	while (UCSR0A & (1 << RXC0)) {
		dummy = UDR0;
	}
	return dummy;
}


static int uart_putchar_io(char c, FILE *stream) {
	uart_putchar(c);

	return 0;
}


/*static int uart_getchar_io(FILE *stream) {
	char c = uart_read();
	uart_putchar(c);

	return c;
}*/