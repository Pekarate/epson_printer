

#ifndef __ESCPOS_H
#define __ESCPOS_H

#include <stdint.h>
#include "define.h"

#define HT           0x09
#define LF           0x0A
#define FF           0x0C 
#define CR           0x0D
#define CAN          0x18
#define DLE          0x10
#define EOT                 0x04
#define ENQ                 0x05
#define DC4                 0x14
#define ESC                 0x1B
#define SP                  0x20
#define FS                  0x1C
#define GS                  0x1D

typedef struct {
	uint8_t key[10];
    uint8_t keysize;
    char  fn_name[100];
	void (*callback)(void *arg);
}__ESCPOS_callbak;

typedef enum {
    PR_OK =0,
    PR_ERR,
}__PR_typedef_result;


void epson_response_to_host(uint8_t *buf,uint16_t rx_size);

void esc_pos_check_frame(_frame_typedef frame);
#endif
