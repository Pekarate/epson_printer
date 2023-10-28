
#ifndef __MY_GPIO_H
#define __MY_GPIO_H

void my_gpio_init(void);

#define GPIO_OUTPUT_DSR    12
#define GPIO_OUTPUT_CTR    10
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_DSR) | (1ULL<<GPIO_OUTPUT_CTR))
/*
 * Let's say, GPIO_OUTPUT_IO_0=18, GPIO_OUTPUT_IO_1=19
 * In binary representation,
 * 1ULL<<GPIO_OUTPUT_IO_0 is equal to 0000000000000000000001000000000000000000 and
 * 1ULL<<GPIO_OUTPUT_IO_1 is equal to 0000000000000000000010000000000000000000
 * GPIO_OUTPUT_PIN_SEL                0000000000000000000011000000000000000000
 * */
#define GPIO_INPUT_DTR     9
#define GPIO_INPUT_RTS     11
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_DTR) | (1ULL<<GPIO_INPUT_RTS))
#endif