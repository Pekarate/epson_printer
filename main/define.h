
#ifndef __DEFINE_H
#define __DEFINE_H

#include "stdint.h"
#define BASE_PATH "/data" // base path to mount the partition

typedef struct {
    uint8_t *data;
    uint16_t len;
}_frame_typedef;

#define PRINTER_MODEL "_TM-T88V"

#define ENABLE_LOG2
#ifdef ENABLE_LOG2
#define LOG2(tag, format, ...) ESP_LOGE(tag, format, ##__VA_ARGS__)
#else
#define LOG2(tag, format, ...) ((void)0)
#endif


#endif
