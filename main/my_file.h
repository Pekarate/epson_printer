
#ifndef __MY_FILE_H
#define __MY_FILE_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "define.h"

FILE *bin_file_creat(char *file_path);
size_t write_data_to_bin_file(FILE *f,uint8_t *data,size_t dsize);
int file_close(FILE *f);

#endif
