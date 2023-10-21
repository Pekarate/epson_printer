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

extern void set_dsr(uint8_t itf, bool value);
static const char *TAG = "example";
static uint8_t buf[CONFIG_TINYUSB_CDC_RX_BUFSIZE + 1];


void epson_response_to_host(uint8_t *buf,uint16_t rx_size){
    if(tinyusb_cdcacm_write_queue(0, buf, rx_size) != rx_size) {
        ESP_LOGE(TAG,"tinyusb_cdcacm_write_queue failse");
    }
    if(tinyusb_cdcacm_write_flush(0, 1000) != 0) {
        ESP_LOGE(TAG,"tinyusb_cdcacm_write_flush failse");
    } else {
        ESP_LOGI(TAG,"tinyusb_cdcacm_write_flush done");
    }
}


QueueHandle_t xStructQueue = NULL;

void tinyusb_cdc_rx_callback(int itf, cdcacm_event_t *event)
{
    /* initialization */
    size_t rx_size = 0;

    /* read */
    esp_err_t ret = tinyusb_cdcacm_read(itf, buf, CONFIG_TINYUSB_CDC_RX_BUFSIZE, &rx_size);
    if (ret == ESP_OK) {
        // ESP_LOGI(TAG, "Data from channel %d:", itf);
        _frame_typedef newframe;
        newframe.data = buf;
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

void app_main(void)
{
    ESP_LOGI(TAG, "USB initialization");
    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL,
        .string_descriptor = NULL,
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
                         10,
                         /* Size of each item is big enough to hold the
                         whole structure. */
                         sizeof( _frame_typedef) );
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
            ESP_LOG_BUFFER_HEXDUMP(TAG, newframe.data, newframe.len, ESP_LOG_INFO);
            esc_pos_check_frame(newframe);
        }
        vTaskDelay(1);
    }
    
}
