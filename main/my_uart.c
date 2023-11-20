/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "hal/uart_hal.h"
#include "my_uart.h"
/**
 * This is an example which echos any data it receives on configured UART back to the sender,
 * with hardware flow control turned off. It does not use UART driver event queue.
 *
 * - Port: configured UART
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: off
 * - Pin assignment: see defines below (See Kconfig)
 */



static const char *TAG = "UART";

#define BUF_SIZE (1024)
static QueueHandle_t uart_queue;

static void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    // uint8_t* dtmp = (uint8_t*) malloc(RD_BUF_SIZE);
    size_t  uart_size = 0;
    for(;;) {
        //Waiting for UART event.
        if(xQueueReceive(uart_queue, (void * )&event, (TickType_t)portMAX_DELAY)) {
            // bzero(dtmp, RD_BUF_SIZE);
            // ESP_LOGI(TAG, "uart[%d] event:", UART_PORT_NUM);
            switch(event.type) {
                //Event of UART receving data
                /*We'd better handler data event fast, there would be much more data events than
                other types of events. If we take too much time on data event, the queue might
                be full.*/
                case UART_DATA:
                    uart_size +=event.size;
                    if(!event.timeout_flag) {
                        // ESP_LOGE(TAG, "event.timeout_flag: :%d",event.size);
                    } else {
                        
                        ESP_LOGE(TAG, "total uart size: %u",uart_size);
                        uart_size = 0;
                    }
                    uint8_t *bufer = (uint8_t *)malloc(event.size+1);
                    if(bufer)
                    {
                        uart_read_bytes(UART_PORT_NUM, bufer, event.size, portMAX_DELAY);
                        LL_uart_add_to_queue(bufer,event.size);
                    }   
                    // ESP_LOGI(TAG, "[UART DATA]: %d", event.size);
                    // uart_read_bytes(UART_PORT_NUM, dtmp, event.size, portMAX_DELAY);
                    // ESP_LOGI(TAG, "[DATA EVT]:");
                    // uart_write_bytes(UART_PORT_NUM, (const char*) dtmp, event.size);
                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    // If fifo overflow happened, you should consider adding flow control for your application.
                    // The ISR has already reset the rx FIFO,
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(UART_PORT_NUM);
                    xQueueReset(uart_queue);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    // If buffer full happened, you should consider increasing your buffer size
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(UART_PORT_NUM);
                    xQueueReset(uart_queue);
                    break;
                //Event of UART RX break detected
                case UART_BREAK:
                    ESP_LOGI(TAG, "uart rx break");
                    break;
                //Event of UART parity check error
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error");
                    break;
                //Event of UART frame error
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error");
                    break;
                //UART_PATTERN_DET
                // case UART_PATTERN_DET:
                //     uart_get_buffered_data_len(UART_PORT_NUM, &buffered_size);
                //     int pos = uart_pattern_pop_pos(UART_PORT_NUM);
                //     ESP_LOGI(TAG, "[UART PATTERN DETECTED] pos: %d, buffered size: %d", pos, buffered_size);
                //     if (pos == -1) {
                //         // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
                //         // record the position. We should set a larger queue size.
                //         // As an example, we directly flush the rx buffer here.
                //         uart_flush_input(UART_PORT_NUM);
                //     } else {
                //         uart_read_bytes(UART_PORT_NUM, dtmp, pos, 100 / portTICK_PERIOD_MS);
                //         uint8_t pat[PATTERN_CHR_NUM + 1];
                //         memset(pat, 0, sizeof(pat));
                //         uart_read_bytes(UART_PORT_NUM, pat, PATTERN_CHR_NUM, 100 / portTICK_PERIOD_MS);
                //         ESP_LOGI(TAG, "read data: %s", dtmp);
                //         ESP_LOGI(TAG, "read pat : %s", pat);
                //     }
                //     break;
                //Others
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    // free(dtmp);
    // dtmp = NULL;
    vTaskDelete(NULL);
}

void my_uart_start(void)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
        .rx_flow_ctrl_thresh = 2,
    };
    int intr_alloc_flags = 0;


    ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM, BUF_SIZE * 2,BUF_SIZE,UART_QUEUE_LENGTH, &uart_queue, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));


    // Set timeout for TOUT interrupt (T3.5 modbus time)
    esp_err_t xErr = ESP_OK;
    xErr = uart_set_rx_timeout(UART_PORT_NUM, 3);
    if(xErr != ESP_OK)
            ESP_LOGI(TAG,"mb serial set rx timeout failure, uart_set_rx_timeout() returned (0x%x).", (int)xErr);

    uart_pattern_queue_reset(UART_PORT_NUM, UART_QUEUE_LENGTH);
    uart_flush(UART_PORT_NUM);
    xTaskCreate(uart_event_task, "uart_event_task", 4096, NULL, 12, NULL);
}
