#ifndef __UART__
#define __UART__

#ifdef __cplusplus
extern "C" {
#endif

void uart_init(uint32_t);
void uart_transmit_byte(uint8_t);
void uart_transmit_buffer(const void*, uint32_t);
uint8_t uart_receive_byte(void);
void uart_receive_buffer(uint8_t*);
uint8_t uart_flush();
void uart_print(const char*);
void uart_putchar(char);

#ifdef __cplusplus
}
#endif

#endif /* __UART__ */