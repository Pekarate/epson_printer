/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "soc/soc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/timer.h"
#include "esp_clk_tree.h"
#include "esp_log.h"

#define TIMER_RESOLUTION_HZ   1000000 // 1MHz resolution
#define TIMER_ALARM_PERIOD_S  1     // Alarm period 1ms

#include "my_timer.h"

void __attribute__((weak)) timer_1_ms_callback(void) {

}
static const char *TAG = "timer";

/**
 * @brief A sample structure to pass events from the timer ISR to task
 */
typedef struct {
    uint64_t timer_count_value;
} example_timer_event_t;

/**
 * @brief Timer user data, will be pass to timer alarm callback
 */
typedef struct {
    QueueHandle_t user_queue;
    int timer_group;
    int timer_idx;
    int alarm_value;
    bool auto_reload;
} example_timer_user_data_t;

static bool IRAM_ATTR timer_group_isr_callback(void *args)
{
    BaseType_t high_task_awoken = pdFALSE;
    timer_1_ms_callback();
    return high_task_awoken == pdTRUE; // return whether a task switch is needed
}

static void example_tg_timer_init(example_timer_user_data_t *user_data)
{
    int group = user_data->timer_group;
    int timer = user_data->timer_idx;

    uint32_t clk_src_hz = 0;
    ESP_ERROR_CHECK(esp_clk_tree_src_get_freq_hz((soc_module_clk_t)TIMER_SRC_CLK_DEFAULT, ESP_CLK_TREE_SRC_FREQ_PRECISION_CACHED, &clk_src_hz));
    timer_config_t config = {
        .clk_src = TIMER_SRC_CLK_DEFAULT,
        .divider = clk_src_hz / TIMER_RESOLUTION_HZ,
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_PAUSE,
        .alarm_en = TIMER_ALARM_EN,
        .auto_reload = user_data->auto_reload,
    };
    ESP_ERROR_CHECK(timer_init(group, timer, &config));

    // For the timer counter to a initial value
    ESP_ERROR_CHECK(timer_set_counter_value(group, timer, 0));
    // Set alarm value and enable alarm interrupt
    ESP_ERROR_CHECK(timer_set_alarm_value(group, timer, user_data->alarm_value));
    ESP_ERROR_CHECK(timer_enable_intr(group, timer));
    // Hook interrupt callback
    ESP_ERROR_CHECK(timer_isr_callback_add(group, timer, timer_group_isr_callback, user_data, 0));
    // Start timer
    ESP_ERROR_CHECK(timer_start(group, timer));
}

static void example_tg_timer_deinit(int group, int timer)
{
    ESP_ERROR_CHECK(timer_isr_callback_remove(group, timer));
    ESP_ERROR_CHECK(timer_deinit(group, timer));
}

void my_timer_start(void)
{
    example_timer_user_data_t *user_data = calloc(1, sizeof(example_timer_user_data_t));
    assert(user_data);
    user_data->user_queue = xQueueCreate(10, sizeof(example_timer_event_t));
    assert(user_data->user_queue);
    user_data->timer_group = 0;
    user_data->timer_idx = 0;
    user_data->alarm_value = (TIMER_ALARM_PERIOD_S * TIMER_RESOLUTION_HZ)/1000;


    ESP_LOGI(TAG, "Init timer with auto-reload");
    user_data->auto_reload = true;
    example_tg_timer_init(user_data);
}
