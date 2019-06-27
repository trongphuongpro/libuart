#ifndef LIB_UART_H
#define LIB_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Prototype */
void uart_initialize(uint32_t);
void uart_transmit_byte(uint8_t);
void uart_transmit_buffer(const uint8_t*, uint8_t);
uint8_t uart_receive_byte(void);
void uart_receive_buffer(uint8_t*);
void uart_flush();
void uart_print(const char*);


#ifdef __cplusplus
}
#endif

#endif