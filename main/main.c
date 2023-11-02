/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <stdint.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tinyusb.h"
#include "tusb_cdc_acm.h"
#include "sdkconfig.h"

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

#define BASE_PATH "/usb" // base path to mount the partition
#include "my_timer.h"
#include "my_uart.h"
#include "my_gpio.h"

QueueHandle_t xStructQueue = NULL;
extern void set_dsr(uint8_t itf, bool value);
static const char *TAG = "example";
static uint8_t buf[CONFIG_TINYUSB_CDC_RX_BUFSIZE + 1];

#define BASE_PATH "/usb" // base path to mount the partition

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


static bool file_exists(const char *file_path)
{
    struct stat buffer;
    return stat(file_path, &buffer) == 0;
}

static void file_operations(void)
{
    const char *directory = "/usb/esp";
    const char *file_path = "/usb/esp/test.txt";

    struct stat s = {0};
    bool directory_exists = stat(directory, &s) == 0;
    if (!directory_exists) {
        if (mkdir(directory, 0775) != 0) {
            ESP_LOGE(TAG, "mkdir failed with errno: %s", strerror(errno));
        }
    }

    if (!file_exists(file_path)) {
        ESP_LOGI(TAG, "Creating file");
        FILE *f = fopen(file_path, "w");
        if (f == NULL) {
            ESP_LOGE(TAG, "Failed to open file for writing");
            return;
        }
        fprintf(f, "Hello World!\n");
        fclose(f);
    }

    FILE *f;
    ESP_LOGI(TAG, "Reading file");
    f = fopen(file_path, "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    // strip newline
    char *pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    ESP_LOGI(TAG, "Read from file: '%s'", line);
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



void app_main(void)
{

    ESP_LOGI(TAG, "Initializing storage...");

    static wl_handle_t wl_handle = WL_INVALID_HANDLE;
    ESP_ERROR_CHECK(storage_init_spiflash(&wl_handle));

    const tinyusb_msc_spiflash_config_t config_spi = {
        .wl_handle = wl_handle
    };
    ESP_ERROR_CHECK(tinyusb_msc_storage_init_spiflash(&config_spi));
    ESP_ERROR_CHECK(tinyusb_msc_storage_mount(BASE_PATH));
    file_operations();

    ESP_LOGI(TAG, "USB Composite initialization");
    const tinyusb_config_t tusb_msc = {
        .device_descriptor = NULL,
        .string_descriptor = NULL,
        .string_descriptor_count = 0,
        .external_phy = false,
        .configuration_descriptor = NULL,
    };
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_msc));

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

#if (CONFIG_TINYUSB_CDC_COUNT > 1)
    acm_cfg.cdc_port = TINYUSB_CDC_ACM_1;
    ESP_ERROR_CHECK(tusb_cdc_acm_init(&acm_cfg));
    ESP_ERROR_CHECK(tinyusb_cdcacm_register_callback(
                        TINYUSB_CDC_ACM_1,
                        CDC_EVENT_LINE_STATE_CHANGED,
                        &tinyusb_cdc_line_state_changed_callback));
#endif
    
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
    
    while (1)
    {
        // if(dtr){
        //     for(int i =0;i<10 ;i++)
        //     {
        //         vTaskDelay(100);
        //         epson_response_to_host(&XON,1);
        //     }
        // }
        if( xQueueReceive( xStructQueue,&(newframe),( TickType_t ) 10 ) == pdPASS )
        {   
            int c =0;
            for( c=0;c< newframe.len;c++)
            {
                if(newframe.data[c])
                    break;
            }
            if(c != newframe.len) {
                ESP_LOG_BUFFER_HEXDUMP("RECV: ", newframe.data, newframe.len, ESP_LOG_INFO);
                esc_pos_check_frame(newframe);
            } else {
                ESP_LOGI(TAG, "message %d byte: full 0",newframe.data[c]);
            }
            
            free(newframe.data);
        }
        // vTaskDelay(1);
    }
    
}


/*I (1718774) example: 0x3fca1d2c   00 00 00 00 1b 3d 01                              |.....=.|
W (1718774) ESCPOS: not support this fuction
I (1719304) example: 0x3fca1d2c   1b 3d 01 10 04 01 10 14  07 01                    |.=........|*/