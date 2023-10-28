#ifndef __MY_UART_H
#define __MY_UART_H

#include "driver/uart.h"

#define ECHO_TEST_TXD 14
#define ECHO_TEST_RXD 13
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define UART_PORT_NUM      (UART_NUM_2)
#define ECHO_UART_BAUD_RATE     (9600)
#define ECHO_TASK_STACK_SIZE    (2048)

void my_uart_start(void);



#endif