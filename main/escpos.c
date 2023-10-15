
#include "escpos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "esp_log.h"
static const char *TAG = "ESCPOS";

void horizontal_tab(void *arg);
void print_and_line_feed(void *arg);
void print_and_return_to_standard_mode(void *arg);
void print_and_carriage_return(void *arg);
void cancel_print_data_in_page_mode(void *arg);
void transmit_real_time_status(void *arg);
void send_real_time_request_to_printer(void *arg);
void generate_pulse_in_real_time(void *arg);
void execute_power_off_sequence(void *arg);
void clear_buffer_s_(void *arg);
void print_data_in_page_mode(void *arg);
void set_right_side_character_spacing(void *arg);
void select_print_mode_s_(void *arg);
void set_absolute_print_position(void *arg);
void select_cancel_user_defined_character_set(void *arg);
void define_user_defined_characters(void *arg);
void select_bit_image_mode(void *arg);
void turn_underline_mode_on_off(void *arg);
void select_default_line_spacing(void *arg);
void set_line_spacing(void *arg);
void select_peripheral_device(void *arg);
void cancel_user_defined_characters(void *arg);
void initialize_printer(void *arg);
void set_horizontal_tab_positions(void *arg);
void turn_emphasized_mode_on_off(void *arg);
void turn_double_strike_mode_on_off(void *arg);
void print_and_feed_paper(void *arg);
void select_page_mode(void *arg);
void select_character_font(void *arg);
void select_an_international_character_set(void *arg);
void select_standard_mode(void *arg);
void select_print_direction_in_page_mode(void *arg);
void turn_90__clockwise_rotation_mode_on_off(void *arg);
void set_print_area_in_page_mode(void *arg);
void set_relative_print_position(void *arg);
void select_justification(void *arg);
void select_paper_sensor_s__to_output_paper_end_signals(void *arg);
void select_paper_sensor_s__to_stop_printing(void *arg);
void select_character_size(void *arg);
void enable_disable_panel_buttons(void *arg);
void print_and_feed_n_lines(void *arg);
void partial_cut__one_point_left_uncut_(void *arg);
void partial_cut__three_points_left_uncut_(void *arg);
void generate_pulse(void *arg);
void transmit_peripheral_device_status(void *arg);
void transmit_paper_sensor_status(void *arg);
void select_character_code_table(void *arg);
void turn_upside_down_print_mode_on_off(void *arg);
void write_to_nv_user_memory(void *arg);
void read_from_nv_user_memory(void *arg);
void print_nv_bit_image(void *arg);
void execute_test_print(void *arg);
void enable_disable_real_time_command(void *arg);
void set_user_setup_commands(void *arg);
void request_transmission_of_response_or_status(void *arg);
void select_print_control_method_s_(void *arg);
void define_nv_bit_image(void *arg);
void select_character_effects(void *arg);
void set_up_and_print_the_symbol(void *arg);
void set_absolute_vertical_print_position_in_page_mode(void *arg);
void define_downloaded_bit_image(void *arg);
void print_downloaded_bit_image(void *arg);
void start_end_macro_definition(void *arg);
void turn_white_black_reverse_print_mode_on_off(void *arg);
void select_print_position_of_hri_characters(void *arg);
void transmit_printer_id(void *arg);
void set_left_margin(void *arg);
void set_horizontal_and_vertical_motion_units(void *arg);
void select_cut_mode_and_cut_paper(void *arg);
void set_print_area_width(void *arg);
void set_relative_vertical_print_position_in_page_mode(void *arg);
void execute_macro(void *arg);
void enable_disable_automatic_status_back__asb_(void *arg);
void turn_smoothing_mode_on_off(void *arg);
void select_font_for_hri_characters(void *arg);
void initialize_maintenance_counter(void *arg);
void transmit_maintenance_counter(void *arg);
void set_bar_code_height(void *arg);
void print_bar_code(void *arg);
void transmit_status(void *arg);
void print_raster_bit_image(void *arg);
void set_bar_code_width(void *arg);
void set_print_mode_s__for_kanji_characters(void *arg);
void select_kanji_character_mode(void *arg);
void turn_underline_mode_on_off_for_kanji_characters(void *arg);
void cancel_kanji_character_mode(void *arg);
void define_user_defined_kanji_characters(void *arg);
void select_kanji_character_code_system(void *arg);
void set_kanji_character_spacing(void *arg);
void turn_quadruple_size_mode_on_off(void *arg);


__ESCPOS_callbak escpos[] = {
    {.keysize = 1, .key = {HT}                  ,.callback =horizontal_tab},
    {.keysize = 1, .key = {LF}                  ,.callback =print_and_line_feed},
    {.keysize = 1, .key = {FF}                  ,.callback =print_and_return_to_standard_mode},
    {.keysize = 1, .key = {CR}                  ,.callback =print_and_carriage_return},
    {.keysize = 1, .key = {CAN}                 ,.callback =cancel_print_data_in_page_mode},
    {.keysize = 2, .key = {DLE,EOT}             ,.callback =transmit_real_time_status},
    {.keysize = 2, .key = {DLE,ENQ}             ,.callback =send_real_time_request_to_printer},
    {.keysize = 3, .key = {DLE,DC4,0x01}        ,.callback =generate_pulse_in_real_time},
    {.keysize = 3, .key = {DLE,DC4,0x02}        ,.callback =execute_power_off_sequence},
    {.keysize = 3, .key = {DLE,DC4,0x08}        ,.callback =clear_buffer_s_},
    {.keysize = 2, .key = {ESC,FF}              ,.callback =print_data_in_page_mode},
    {.keysize = 2, .key = {ESC,SP}              ,.callback =set_right_side_character_spacing},
    {.keysize = 2, .key = {ESC,'!'}             ,.callback =select_print_mode_s_},
    {.keysize = 2, .key = {ESC,'$'}             ,.callback =set_absolute_print_position},
    {.keysize = 2, .key = {ESC,'%'}             ,.callback =select_cancel_user_defined_character_set},
    {.keysize = 2, .key = {ESC,'&'}             ,.callback =define_user_defined_characters},
    {.keysize = 2, .key = {ESC,'*'}             ,.callback =select_bit_image_mode},
    {.keysize = 2, .key = {ESC,'-'}             ,.callback =turn_underline_mode_on_off},
    {.keysize = 2, .key = {ESC,'2'}             ,.callback =select_default_line_spacing},
    {.keysize = 2, .key = {ESC,'3'}             ,.callback =set_line_spacing},
    {.keysize = 2, .key = {ESC,'='}             ,.callback =select_peripheral_device},
    {.keysize = 2, .key = {ESC,'?'}             ,.callback =cancel_user_defined_characters},
    {.keysize = 2, .key = {ESC,'@'}             ,.callback =initialize_printer},
    {.keysize = 2, .key = {ESC,'D'}             ,.callback =set_horizontal_tab_positions},
    {.keysize = 2, .key = {ESC,'E'}             ,.callback =turn_emphasized_mode_on_off},
    {.keysize = 2, .key = {ESC,'G'}             ,.callback =turn_double_strike_mode_on_off},
    {.keysize = 2, .key = {ESC,'J'}             ,.callback =print_and_feed_paper},
    {.keysize = 2, .key = {ESC,'L'}             ,.callback =select_page_mode},
    {.keysize = 2, .key = {ESC,'M'}             ,.callback =select_character_font},
    {.keysize = 2, .key = {ESC,'R'}             ,.callback =select_an_international_character_set},
    {.keysize = 2, .key = {ESC,'S'}             ,.callback =select_standard_mode},
    {.keysize = 2, .key = {ESC,'T'}             ,.callback =select_print_direction_in_page_mode},
    {.keysize = 2, .key = {ESC,'V'}             ,.callback =turn_90__clockwise_rotation_mode_on_off},
    {.keysize = 2, .key = {ESC,'W'}             ,.callback =set_print_area_in_page_mode},
    {.keysize = 2, .key = {ESC,'\\'}            ,.callback =set_relative_print_position},
    {.keysize = 2, .key = {ESC,'a'}             ,.callback =select_justification},
    {.keysize = 3, .key = {ESC,'c','3'}         ,.callback =select_paper_sensor_s__to_output_paper_end_signals},
    {.keysize = 3, .key = {ESC,'c','4'}         ,.callback =select_paper_sensor_s__to_stop_printing},
    {.keysize = 2, .key = {GS,'!'}              ,.callback =select_character_size},
    {.keysize = 3, .key = {ESC,'c','5'}         ,.callback =enable_disable_panel_buttons},
    {.keysize = 2, .key = {ESC,'d'}             ,.callback =print_and_feed_n_lines},
    {.keysize = 2, .key = {ESC,'i'}             ,.callback =partial_cut__one_point_left_uncut_},
    {.keysize = 2, .key = {ESC,'m'}             ,.callback =partial_cut__three_points_left_uncut_},
    {.keysize = 2, .key = {ESC,'p'}             ,.callback =generate_pulse},
    {.keysize = 2, .key = {ESC,'u'}             ,.callback =transmit_peripheral_device_status},
    {.keysize = 2, .key = {ESC,'v'}             ,.callback =transmit_paper_sensor_status},
    {.keysize = 2, .key = {ESC,'t'}             ,.callback =select_character_code_table},
    {.keysize = 2, .key = {ESC,'{'}             ,.callback =turn_upside_down_print_mode_on_off},
    {.keysize = 3, .key = {FS,'g','1'}         ,.callback =write_to_nv_user_memory},
    {.keysize = 3, .key = {FS,'g','2'}         ,.callback =read_from_nv_user_memory},
    {.keysize = 2, .key = {FS,'p'}             ,.callback =print_nv_bit_image},
    {.keysize = 3, .key = {GS,'(','A'}         ,.callback =execute_test_print},
    {.keysize = 3, .key = {GS,'(','D'}         ,.callback =enable_disable_real_time_command},
    {.keysize = 3, .key = {GS,'(','E'}         ,.callback =set_user_setup_commands},
    {.keysize = 3, .key = {GS,'(','H'}         ,.callback =request_transmission_of_response_or_status},
    {.keysize = 3, .key = {GS,'(','K'}         ,.callback =select_print_control_method_s_},
    {.keysize = 3, .key = {GS,'(','L'}         ,.callback =define_nv_bit_image},
    {.keysize = 3, .key = {GS,'(','N'}         ,.callback =select_character_effects},
    {.keysize = 3, .key = {GS,'(','k'}         ,.callback =set_up_and_print_the_symbol},
    {.keysize = 2, .key = {GS,'$'}             ,.callback =set_absolute_vertical_print_position_in_page_mode},
    {.keysize = 2, .key = {GS,'*'}             ,.callback =define_downloaded_bit_image},
    {.keysize = 2, .key = {GS,'/'}             ,.callback =print_downloaded_bit_image},
    {.keysize = 2, .key = {GS,':'}             ,.callback =start_end_macro_definition},
    {.keysize = 2, .key = {GS,'B'}             ,.callback =turn_white_black_reverse_print_mode_on_off},
    {.keysize = 2, .key = {GS,'H'}             ,.callback =select_print_position_of_hri_characters},
    {.keysize = 2, .key = {GS,'I'}             ,.callback =transmit_printer_id},
    {.keysize = 2, .key = {GS,'L'}             ,.callback =set_left_margin},
    {.keysize = 2, .key = {GS,'P'}             ,.callback =set_horizontal_and_vertical_motion_units},
    {.keysize = 2, .key = {GS,'V'}             ,.callback =select_cut_mode_and_cut_paper},
    {.keysize = 2, .key = {GS,'W'}             ,.callback =set_print_area_width},
    {.keysize = 2, .key = {GS,'\\'}            ,.callback =set_relative_vertical_print_position_in_page_mode},
    {.keysize = 2, .key = {GS,'^'}             ,.callback =execute_macro},
    {.keysize = 2, .key = {GS,'a'}             ,.callback =enable_disable_automatic_status_back__asb_},
    {.keysize = 2, .key = {GS,'b'}             ,.callback =turn_smoothing_mode_on_off},
    {.keysize = 2, .key = {GS,'f'}             ,.callback =select_font_for_hri_characters},
    {.keysize = 3, .key = {GS,'g','0'}         ,.callback =initialize_maintenance_counter},
    {.keysize = 3, .key = {GS,'g','2'}         ,.callback =transmit_maintenance_counter},
    {.keysize = 2, .key = {GS,'h'}             ,.callback =set_bar_code_height},
    {.keysize = 2, .key = {GS,'k'}             ,.callback =print_bar_code},
    {.keysize = 2, .key = {GS,'r'}             ,.callback =transmit_status},
    {.keysize = 3, .key = {GS,'v','0'}         ,.callback =print_raster_bit_image},
    {.keysize = 2, .key = {GS,'w'}             ,.callback =set_bar_code_width},
    {.keysize = 2, .key = {FS,'!'}             ,.callback =set_print_mode_s__for_kanji_characters},
    {.keysize = 2, .key = {FS,'&'}             ,.callback =select_kanji_character_mode},
    {.keysize = 2, .key = {FS,'-'}             ,.callback =turn_underline_mode_on_off_for_kanji_characters},
    {.keysize = 2, .key = {FS,'.'}             ,.callback =cancel_kanji_character_mode},
    {.keysize = 2, .key = {FS,'2'}             ,.callback =define_user_defined_kanji_characters},
    {.keysize = 2, .key = {FS,'C'}             ,.callback =select_kanji_character_code_system},
    {.keysize = 2, .key = {FS,'S'}             ,.callback =set_kanji_character_spacing},
    {.keysize = 2, .key = {FS,'W'}             ,.callback =turn_quadruple_size_mode_on_off}
};

__PR_typedef_result esc_pos_check_command(__ESCPOS_callbak cmd,_frame_typedef frame) {
    if(cmd.keysize > frame.len) return PR_ERR;
    for(int i =0;i<cmd.keysize;i++) {
        if(cmd.key[i] != frame.data[i])
            return PR_ERR;
    }
    return PR_OK;
}

void esc_pos_check_frame(_frame_typedef frame) {
    int ss = sizeof(escpos) / sizeof (__ESCPOS_callbak);
    for(int i =0;i<ss;i++)
    {
        // ESP_LOGI(TAG,"%d",escpos[i].keysize);
        if(esc_pos_check_command(escpos[i],frame) == PR_OK){
            if(escpos[i].callback != NULL) {
                escpos[i].callback(&frame);
            }
        }
    }
}


void horizontal_tab(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_and_line_feed(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_and_return_to_standard_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_and_carriage_return(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void cancel_print_data_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void transmit_real_time_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void send_real_time_request_to_printer(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void generate_pulse_in_real_time(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void execute_power_off_sequence(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void clear_buffer_s_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_data_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_right_side_character_spacing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_print_mode_s_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_absolute_print_position(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_cancel_user_defined_character_set(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void define_user_defined_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_bit_image_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_underline_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_default_line_spacing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_line_spacing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_peripheral_device(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void cancel_user_defined_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void initialize_printer(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_horizontal_tab_positions(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_emphasized_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_double_strike_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_and_feed_paper(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_character_font(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_an_international_character_set(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_standard_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_print_direction_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_90__clockwise_rotation_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_print_area_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_relative_print_position(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_justification(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_paper_sensor_s__to_output_paper_end_signals(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_paper_sensor_s__to_stop_printing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_character_size(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void enable_disable_panel_buttons(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_and_feed_n_lines(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void partial_cut__one_point_left_uncut_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void partial_cut__three_points_left_uncut_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void generate_pulse(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void transmit_peripheral_device_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void transmit_paper_sensor_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_character_code_table(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_upside_down_print_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void write_to_nv_user_memory(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void read_from_nv_user_memory(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_nv_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void execute_test_print(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void enable_disable_real_time_command(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_user_setup_commands(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void request_transmission_of_response_or_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_print_control_method_s_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void define_nv_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_character_effects(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_up_and_print_the_symbol(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_absolute_vertical_print_position_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void define_downloaded_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_downloaded_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void start_end_macro_definition(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_white_black_reverse_print_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_print_position_of_hri_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}

//{37}{25}{00}{14}{00}{00}{0F}{5F}{54}{4D}{2D}{54}{38}{38}{56}{00}
void transmit_printer_id(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_left_margin(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_horizontal_and_vertical_motion_units(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_cut_mode_and_cut_paper(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_print_area_width(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_relative_vertical_print_position_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void execute_macro(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void enable_disable_automatic_status_back__asb_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_smoothing_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_font_for_hri_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void initialize_maintenance_counter(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void transmit_maintenance_counter(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_bar_code_height(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_bar_code(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void transmit_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void print_raster_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_bar_code_width(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_print_mode_s__for_kanji_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_kanji_character_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_underline_mode_on_off_for_kanji_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void cancel_kanji_character_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void define_user_defined_kanji_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void select_kanji_character_code_system(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void set_kanji_character_spacing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
void turn_quadruple_size_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
}
