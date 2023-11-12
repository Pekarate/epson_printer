/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <stdint.h>
#include <dirent.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tinyusb.h"
#include "tusb_cdc_acm.h"
#include "sdkconfig.h"
#include "nvs_flash.h"
#include "time.h"
#include <sys/time.h>

#include "device/usbd.h"
#include "device/usbd_pvt.h"

#include "queue.h"

#include "define.h"
#include "escpos.h"

#include <errno.h>
#include <sys/stat.h>
#include "esp_partition.h"
#include "esp_check.h"
#include "tinyusb.h"
#include "tusb_msc_storage.h"
#include "tusb_cdc_acm.h"

#include "my_timer.h"
#include "my_uart.h"
#include "my_gpio.h"
#include "my_file.h"
#include "esp_random.h"


extern uint8_t is_cut_command;

QueueHandle_t xStructQueue = NULL;
extern void set_dsr(uint8_t itf, bool value);
static const char *TAG = "example";
static uint8_t buf[CONFIG_TINYUSB_CDC_RX_BUFSIZE + 1];



void timer_1_ms_callback(void){
    static uint32_t cnt = 0;
    cnt++;
    static size_t length = 0;
    static size_t now_length = 0;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_PORT_NUM,&now_length));
    if(now_length != length) {
        length = now_length;
    } else if(now_length) 
    {
        _frame_typedef newframe;
        newframe.data = (uint8_t *)malloc(now_length+1);
        uart_read_bytes(UART_PORT_NUM, newframe.data, now_length, 100 / portTICK_PERIOD_MS);
        newframe.len = now_length;
        xQueueSend(xStructQueue,( void * ) &newframe,( TickType_t ) 100 );
        now_length = length = 0;
    }
}

void LL_uart_add_to_queue(uint8_t *data,uint16_t len)
{
    _frame_typedef newframe;
    newframe.data = data;
    newframe.len = len;
    xQueueSend(xStructQueue,( void * ) &newframe,( TickType_t ) 100 );
}

void epson_response_to_host(uint8_t *buf,uint16_t rx_size){
    ESP_LOG_BUFFER_HEXDUMP("SEND", buf, rx_size, ESP_LOG_INFO);
#if 0
    if(tinyusb_cdcacm_write_queue(0, buf, rx_size) != rx_size) {
        ESP_LOGE(TAG,"tinyusb_cdcacm_write_queue failse");
    }
    if(tinyusb_cdcacm_write_flush(0, 1000) != 0) {
        ESP_LOGE(TAG,"tinyusb_cdcacm_write_flush failse");
    } else {
        // ESP_LOGI(TAG,"tinyusb_cdcacm_write_flush done");
    }
#else
    uart_write_bytes(UART_PORT_NUM,buf,rx_size);
    ESP_ERROR_CHECK(uart_wait_tx_done(UART_PORT_NUM, 100));
#endif
}




void tinyusb_cdc_rx_callback(int itf, cdcacm_event_t *event)
{
    /* initialization */
    size_t rx_size = 0;

    /* read */
    esp_err_t ret = tinyusb_cdcacm_read(itf, buf, CONFIG_TINYUSB_CDC_RX_BUFSIZE, &rx_size);
    if (ret == ESP_OK) {
        // ESP_LOGI(TAG, "Data from channel %d:", itf);
        _frame_typedef newframe;
        newframe.data = (uint8_t *)malloc(rx_size+1);
        memcpy(newframe.data,buf,rx_size);
        newframe.len = rx_size;
        xQueueSend(xStructQueue,( void * ) &newframe,( TickType_t ) 100 );
    } else {
        ESP_LOGE(TAG, "Read error");
    }

    /* write back */
    // tinyusb_cdcacm_write_queue(itf, buf, rx_size);
    // tinyusb_cdcacm_write_flush(itf, 0);
}

// void set_dsr(uint8_t itf, bool value) {

//     printf("HOANG: %s %d\n",__func__,value);
//     cdcd_interface_t* p_cdc = &_cdcd_itf[itf];

//     uint8_t packet[10];

//     packet[0] = 0xA1;                        //   bmRequestType
//     packet[1] = CDC_NOTIF_SERIAL_STATE;                //   bNotification
//     packet[2] = 0x00;                        //   wValue
//     packet[3] = 0x00;
//     packet[4] = 0x00;                        //   wIndex
//     packet[5] = 0x00;
//     packet[6] = 0x02;                        //   wLength
//     packet[7] = 0x00;
//     packet[8] = value ?  0x02 : 0x00; 
//     packet[9] = 0x00;

//     usbd_edpt_xfer(TUD_OPT_RHPORT, p_cdc->ep_notif, packet, 10);

// }

uint8_t XON = 0x11;
int dtr = 0;
void tinyusb_cdc_line_state_changed_callback(int itf, cdcacm_event_t *event)
{
    dtr = event->line_state_changed_data.dtr;
    int rts = event->line_state_changed_data.rts;
    ESP_LOGI(TAG, "Line state changed on channel %d: DTR:%d, RTS:%d", itf, dtr, rts);
    // set_dsr(itf,dtr);
    // if(dtr){
    //         vTaskDelay(5);
    //         ESP_LOGI("HARDWARE","%s %d",__func__,0);
    //         set_dsr(itf,0);
    //         ESP_LOGI("HARDWARE","%s %d",__func__,1);
    //         set_dsr(itf,1);
           
    // }
    // else {
    //         ESP_LOGI("HARDWARE","%s %d",__func__,0);
    //         set_dsr(itf,0);
    // }


}



static esp_err_t storage_init_spiflash(wl_handle_t *wl_handle)
{
    ESP_LOGI(TAG, "Initializing wear levelling");

    const esp_partition_t *data_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_FAT, NULL);
    if (data_partition == NULL) {
        ESP_LOGE(TAG, "Failed to find FATFS partition. Check the partition table.");
        return ESP_ERR_NOT_FOUND;
    }

    return wl_mount(data_partition, wl_handle);
}


// mount the partition and show all the files in BASE_PATH
static void _mount(void)
{
    ESP_LOGI(TAG, "Mount storage...");
    ESP_ERROR_CHECK(tinyusb_msc_storage_mount(BASE_PATH));


    // List all the files in this directory
    ESP_LOGI(TAG, "\nls command output:");
    struct dirent *d;
    DIR *dh = opendir(BASE_PATH);
    if (!dh) {
        if (errno == ENOENT) {
            //If the directory is not found
            ESP_LOGE(TAG, "Directory doesn't exist %s", BASE_PATH);
        } else {
            //If the directory is not readable then throw error and exit
            ESP_LOGE(TAG, "Unable to read directory %s", BASE_PATH);
        }
        return;
    }
    //While the next entry is not readable we will print directory files
    while ((d = readdir(dh)) != NULL) {
        printf("%s\n", d->d_name);
    }
    return;
}

extern void my_wifi_start(void);
void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    // my_wifi_start();
    ESP_LOGI(TAG, "Initializing storage...");

    static wl_handle_t wl_handle = WL_INVALID_HANDLE;
    ESP_ERROR_CHECK(storage_init_spiflash(&wl_handle));

    const tinyusb_msc_spiflash_config_t config_spi = {
        .wl_handle = wl_handle
    };
    ESP_ERROR_CHECK(tinyusb_msc_storage_init_spiflash(&config_spi));
    _mount();

    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL,
        .string_descriptor = NULL,
        .string_descriptor_count = 0,
        .external_phy = false,
        .configuration_descriptor = NULL,
    };

    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));

    tinyusb_config_cdcacm_t acm_cfg = {
        .usb_dev = TINYUSB_USBDEV_0,
        .cdc_port = TINYUSB_CDC_ACM_0,
        .rx_unread_buf_sz = 64,
        .callback_rx = &tinyusb_cdc_rx_callback, // the first way to register a callback
        .callback_rx_wanted_char = NULL,
        .callback_line_state_changed = NULL,
        .callback_line_coding_changed = NULL
    };

    ESP_ERROR_CHECK(tusb_cdc_acm_init(&acm_cfg));
    /* the second way to register a callback */
    ESP_ERROR_CHECK(tinyusb_cdcacm_register_callback(
                        TINYUSB_CDC_ACM_0,
                        CDC_EVENT_LINE_STATE_CHANGED,
                        &tinyusb_cdc_line_state_changed_callback));
    
    ESP_LOGI(TAG, "USB initialization DONE");
    xStructQueue = xQueueCreate(
                         /* The number of items the queue can hold. */
                         30,
                         /* Size of each item is big enough to hold the
                         whole structure. */
                         sizeof( _frame_typedef) );
    my_uart_start();
    my_timer_start();
    my_gpio_init();
    vTaskDelay(100);
    // set_dsr(0,1);
    _frame_typedef newframe;
    if (tinyusb_msc_storage_in_use_by_usb_host()) {
        ESP_LOGE(TAG, "storage exposed over USB. Application can't write to storage.");
        ESP_LOGE(TAG, "Please eject usb storage in your computer");
    }            
    FILE *stream = NULL;
    struct timeval tv_now;
    // gettimeofday(&tv_now, NULL);
    // int64_t time_us = (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;
    // ESP_LOGW(TAG, "time_us: %llu",time_us);
    while (1)
    {
        if( xQueueReceive( xStructQueue,&(newframe),( TickType_t ) 10 ) == pdPASS )
        {   

            ESP_LOG_BUFFER_HEXDUMP("RECV: ", newframe.data, newframe.len, ESP_LOG_INFO);
            esc_pos_check_frame(newframe);
            if (tinyusb_msc_storage_in_use_by_usb_host()) {
                ESP_LOGE(TAG, "storage exposed over USB. Application can't write to storage.");
            }else {
                if(stream == NULL) 
                {
                    gettimeofday(&tv_now, NULL);
                    int64_t time_us = (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;
                    ESP_LOGW(TAG, "time_us: %llu",time_us);
                    char file_name[40];
                    sprintf(file_name,"/data/raw%3d.bin",(int)(time_us%1000));
                    stream =bin_file_creat(file_name);
                }
                if(stream) {
                    if(write_data_to_bin_file(stream,newframe.data,newframe.len) != newframe.len) {
                        ESP_LOGE(TAG, "write to file error");
                    }
                } 
            }
            if(is_cut_command) {
                is_cut_command =0;
                file_close(stream);
                stream = NULL;
            }
            free(newframe.data);
        }
        // vTaskDelay(1);
    }
    
}


/*I (1718774) example: 0x3fca1d2c   00 00 00 00 1b 3d 01                              |.....=.|
W (1718774) ESCPOS: not support this fuction
I (1719304) example: 0x3fca1d2c   1b 3d 01 10 04 01 10 14  07 01                    |.=........|*/