#ifndef __MY_UART_H
#define __MY_UART_H

#include "driver/uart.h"

#define ECHO_TEST_TXD (43)
#define ECHO_TEST_RXD (44)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define UART_PORT_NUM      (UART_NUM_0)
#define ECHO_UART_BAUD_RATE     (115200)
#define ECHO_TASK_STACK_SIZE    (2048)

void my_uart_start(void);
void LL_uart_add_to_queue(uint8_t *data,uint16_t len);

#endif