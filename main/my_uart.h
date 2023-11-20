#ifndef __MY_UART_H
#define __MY_UART_H

#include "driver/uart.h"


#define UART_PORT_NUM      (UART_NUM_1)

#if 0
#define ECHO_TEST_TXD (43)
#define ECHO_TEST_RXD (44)
#else 
#define ECHO_TEST_TXD (14)
#define ECHO_TEST_RXD (13)
#endif 

#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)


#define ECHO_UART_BAUD_RATE     (9600)
#define ECHO_TASK_STACK_SIZE    (2048)

#define UART_QUEUE_LENGTH       (50)

void my_uart_start(void);
void LL_uart_add_to_queue(uint8_t *data,uint16_t len);

#endif