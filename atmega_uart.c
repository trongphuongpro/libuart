#include "libuart.h"
#include <string.h>


#define F_CPU	8000000UL
volatile uint8_t data;

void uart_initialize(uint32_t baudrate) {
	/* baudrate */
	uint8_t ubbr = F_CPU / (16 * baudrate) - 1;
	UBRR0H = ubbr >> 8;
	UBRR0L = ubbr;
	/* configure */
	UCSR0A = 0x00;
	//UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (3 << UCSZ00); // 8-bit
	
	//sei();
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


void uart_flush() {
	uint8_t dummy;
	while (UCSR0A & (1 << RXC0)) {
		dummy = UDR0;
	}
}

/*uint8_t USART_dataAvailable() {
	return (UCSR0A & (1 << RXC0));
}

void printStr(const char *text) {
	while (*text != '\0')
		USART_transmit(*text++);
	USART_transmit('\r');
	USART_transmit('\n');
}

void printInt32(uint8_t count, ...) {
	char *str = (char *)calloc(8, sizeof(uint32_t));
	va_list ap;
	va_start(ap, count);
	for (int i = 0; i < count; i++) {
		sprintf(str, "%lu", va_arg(ap, uint32_t));
		printStr(str);
	}
	va_end(ap);
}

void printInt16(uint8_t count, ...) {
	char *str = (char *)calloc(8, sizeof(uint16_t));
	va_list ap;
	va_start(ap, count);
	for (int i = 0; i < count; i++) {
		sprintf(str, "%u", va_arg(ap, uint16_t));
		printStr(str);
	}
	va_end(ap);
}



char *readStr() {
	int i = 0;
	char c;
	while (i < USARTBUFFER-1) {
		c = USART_receive();
		if (c == '\r' || c == '\n')
			break;

		buffer[i++] = c;
	}
	buffer[i] = '\0';
	return buffer;
}

void printHEX(uint32_t data) {
	for (int i = 7; i >= 0; i--) {
		uint8_t temp = (uint8_t) (data >> (i*4) & 0x0000000F);
		temp += (temp < 10) ? 48 : 55;
		USART_transmit(temp);
	}
	USART_transmit('\r');
	USART_transmit('\n');
}*/

/*
int32_t readInt() {
	
}
*/
/*
ISR (USART_RX_vect) {
	data = UDR0;
	UART_transmit(data);
}*/
