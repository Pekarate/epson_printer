#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "esp_log.h"

static const char *TAG = "FILE";

FILE *stream = NULL;

FILE *bin_file_creat(char *file_path){
    ESP_LOGI(TAG,"%s: %s",__func__,file_path); 
    FILE *f = fopen(file_path, "wb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return NULL;
    }
    return f;
}

size_t write_data_to_bin_file(FILE *f,uint8_t *data,size_t dsize){
    size_t res =0;
    if(f) {
        res = fwrite(data, 1, dsize, f);
    } else {
        ESP_LOGE(TAG,"file not exist, can't write"); 
    }
    return res;
}

int file_close(FILE *f) {
    ESP_LOGI(TAG,"%s",__func__); 
    return fclose(f);
}
