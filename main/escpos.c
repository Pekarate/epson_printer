
#include "escpos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "esp_log.h"

#include "epson_nv_memory.h"

static const char *TAG = "ESCPOS";

int function_not_parse_01(void *arg);
int function_not_support_4(void *arg);
int transmit_top_bottom_logo_printing(void *arg);
int transmit_key_code_list_for_define_NV_graphic(void *arg);
int horizontal_tab(void *arg);
int print_and_line_feed(void *arg);
int print_and_return_to_standard_mode(void *arg);
int print_and_carriage_return(void *arg);
int cancel_print_data_in_page_mode(void *arg);
int transmit_real_time_status(void *arg);
int send_real_time_request_to_printer(void *arg);
int generate_pulse_in_real_time(void *arg);
int execute_power_off_sequence(void *arg);
int clear_buffer_s_(void *arg);
int print_data_in_page_mode(void *arg);
int set_right_side_character_spacing(void *arg);
int select_print_mode_s_(void *arg);
int set_absolute_print_position(void *arg);
int select_cancel_user_defined_character_set(void *arg);
int define_user_defined_characters(void *arg);
int select_bit_image_mode(void *arg);
int turn_underline_mode_on_off(void *arg);
int select_default_line_spacing(void *arg);
int set_line_spacing(void *arg);
int select_peripheral_device(void *arg);
int cancel_user_defined_characters(void *arg);
int initialize_printer(void *arg);
int set_horizontal_tab_positions(void *arg);
int turn_emphasized_mode_on_off(void *arg);
int turn_double_strike_mode_on_off(void *arg);
int print_and_feed_paper(void *arg);
int select_page_mode(void *arg);
int select_character_font(void *arg);
int select_an_international_character_set(void *arg);
int select_standard_mode(void *arg);
int select_print_direction_in_page_mode(void *arg);
int turn_90__clockwise_rotation_mode_on_off(void *arg);
int set_print_area_in_page_mode(void *arg);
int set_relative_print_position(void *arg);
int select_justification(void *arg);
int select_paper_sensor_s__to_output_paper_end_signals(void *arg);
int select_paper_sensor_s__to_stop_printing(void *arg);
int select_character_size(void *arg);
int enable_disable_panel_buttons(void *arg);
int print_and_feed_n_lines(void *arg);
int partial_cut__one_point_left_uncut_(void *arg);
int partial_cut__three_points_left_uncut_(void *arg);
int generate_pulse(void *arg);
int transmit_peripheral_device_status(void *arg);
int transmit_paper_sensor_status(void *arg);
int select_character_code_table(void *arg);
int turn_upside_down_print_mode_on_off(void *arg);
int write_to_nv_user_memory(void *arg);
int read_from_nv_user_memory(void *arg);
int print_nv_bit_image(void *arg);
int execute_test_print(void *arg);
int enable_disable_real_time_command(void *arg);
int transmit_customized_setting_values(void *arg);
int transmit_configuration_item_for_serial_interface(void *arg);
int transmit_condition_for_usb_interface(void *arg);
int set_user_setup_commands(void *arg);
int request_transmission_of_response_or_status(void *arg);
int select_print_control_method_s_(void *arg);
int transmit_related_capacity_NV_memory(void *arg);
int store_the_graphics_data_in_the_print_buffer(void *arg);
int select_character_effects(void *arg);
int set_up_and_print_the_symbol(void *arg);
int set_absolute_vertical_print_position_in_page_mode(void *arg);
int define_downloaded_bit_image(void *arg);
int print_downloaded_bit_image(void *arg);
int start_end_macro_definition(void *arg);
int turn_white_black_reverse_print_mode_on_off(void *arg);
int select_print_position_of_hri_characters(void *arg);
int transmit_printer_id(void *arg);
int set_left_margin(void *arg);
int set_horizontal_and_vertical_motion_units(void *arg);
int select_cut_mode_and_cut_paper(void *arg);
int set_print_area_width(void *arg);
int set_relative_vertical_print_position_in_page_mode(void *arg);
int execute_macro(void *arg);
int enable_disable_automatic_status_back__asb_(void *arg);
int turn_smoothing_mode_on_off(void *arg);
int select_font_for_hri_characters(void *arg);
int initialize_maintenance_counter(void *arg);
int transmit_maintenance_counter(void *arg);
int set_bar_code_height(void *arg);
int print_bar_code(void *arg);
int transmit_status(void *arg);
int print_raster_bit_image(void *arg);
int set_bar_code_width(void *arg);
int set_print_mode_s__for_kanji_characters(void *arg);
int select_kanji_character_mode(void *arg);
int turn_underline_mode_on_off_for_kanji_characters(void *arg);
int cancel_kanji_character_mode(void *arg);
int define_user_defined_kanji_characters(void *arg);
int select_kanji_character_code_system(void *arg);
int set_kanji_character_spacing(void *arg);
int turn_quadruple_size_mode_on_off(void *arg);


__ESCPOS_callbak escpos[] = {
    {.keysize = 6, .key = {ESC,0x28,0x73,0x04,0x00,0x31} ,.callback =function_not_parse_01},
    {.keysize = 3, .key = {DLE,0x14,0x07}                  ,.callback =function_not_support_4},
    {.keysize = 7, .key = {FS,0x28,0x45,0x03,0x00,0x3d,0x02}                  ,.callback =transmit_top_bottom_logo_printing},
    {.keysize = 9, .key = {GS,0x28,0x4C,0x04,0x00,0x30,0x40,0x4B,0x43}                  ,.callback =transmit_key_code_list_for_define_NV_graphic},
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
    {.keysize = 6, .key = {GS,'(','E',0x02,0x00,0x06}         ,.callback =transmit_customized_setting_values},
    {.keysize = 6, .key = {GS,'(','E',0x02,0x00,0x0C}         ,.callback =transmit_configuration_item_for_serial_interface},
    {.keysize = 6, .key = {GS,'(','E',0x02,0x00,0x10}         ,.callback =transmit_condition_for_usb_interface},
    {.keysize = 3, .key = {GS,'(','E'}         ,.callback =set_user_setup_commands},
    {.keysize = 3, .key = {GS,'(','H',0x06,0x00,0x30,0x30},.callback =request_transmission_of_response_or_status},
    {.keysize = 3, .key = {GS,'(','K'}         ,.callback =select_print_control_method_s_},
    {.keysize = 6, .key = {GS,'(','L',0x02,0x00,0x30}         ,.callback =transmit_related_capacity_NV_memory},
    {.keysize = 10, .key = {GS,'8','L',DONT_CARE,DONT_CARE,DONT_CARE,DONT_CARE,0x30,0x70,0x30} ,.callback = store_the_graphics_data_in_the_print_buffer},
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

int is_start_a_cmd(uint8_t bytestart)
{
    switch (bytestart)
    {
        case HT  :      //0x09:
        case LF  :      //0x0A:
        case FF  :      //0x0C:
        case CR  :      //0x0D:
        case CAN :      //0x18:
        case DLE :      //0x10:
        case EOT :      //0x04:
        case ENQ :      //0x05:
        case DC4 :      //0x14:
        case ESC :      //0x1B:
        case SP  :      //0x20:
        case FS  :      //0x1C:
        case GS  :      //0x1D:
            return 1;
            break;
    
        default:
            return 0;
            break;
    }
}

__PR_typedef_result esc_pos_check_command(__ESCPOS_callbak cmd,_frame_typedef frame) {
    if(cmd.keysize > frame.len) return PR_ERR;
    for(int i =0;i<cmd.keysize;i++) {
        if(cmd.key[i] != frame.data[i])
            return PR_ERR;
    }
    return PR_OK;
}

uint8_t is_cut_command = 0;
void esc_pos_check_frame(_frame_typedef frame) {
    int i =0;
    int ss = sizeof(escpos) / sizeof (__ESCPOS_callbak);
    _frame_typedef check_frame = frame;
    uint16_t index =0;
    uint16_t len = check_frame.len;
    while (index<len)
    {
        check_frame.data = frame.data + index;
        check_frame.len = frame.len - index;
        if(is_start_a_cmd(check_frame.data[0])) {
            for(i =0;i<ss;i++)
            {
                if(esc_pos_check_command(escpos[i],check_frame) == PR_OK){
                    if(escpos[i].callback != NULL) {
                        index += escpos[i].callback(&check_frame);
                    }
                    break;
                }
            }
            if (i==ss) {
            // ESP_LOGW(TAG,"not support this fuction");
            // while ( (frame.data[index] == 0) && (index<len))
            // {
                index+=1;
            // }
            }
        } else {
            index+=1;
        }

    }
}

/*
0x3fca1284   1b 28 73 04 00 31 41 2d  f2                       |.(s..1A-.|

0x3fca1214   1b 28 73 04 00 31 41 10  c9   |.(s..1A..|
*/
#define MIN_RANGE 1000
#define MAX_RANGE 65536
extern const char* cmd41[];
extern const char* cmd42[];
int function_not_parse_01(void *arg){
    ESP_LOGI(TAG,"%s",__func__);
    _frame_typedef *frame = (_frame_typedef *)arg; 
    if(frame->len < 9)
    {
        ESP_LOGE(TAG,"LEN NOT MATCH");
        return frame ->len;
    }
    char tmp[50];
    int size=0;
    uint16_t code = frame->data[7];
    code = code*256+ frame->data[8];
    if((code >=MIN_RANGE) && (code <=MAX_RANGE)) {
        switch (frame->data[6])
        {
            case 0x41:
                size=sprintf(tmp,"{ A%s",cmd41[code - MIN_RANGE]);
                size ++;
                break;
            case 0x42:
                size=sprintf(tmp,"{ B%s",cmd42[code - MIN_RANGE]);
                size ++;
                break;
            default:
                ESP_LOGW(TAG,"function_not_parse_01 not found: :%X",frame->data[6]);
                break;
        }
       
    } else {
        ESP_LOGW(TAG,"NOT IMPLEMENT SUB FUN :%X",code);
    }
    if(size) {
        epson_response_to_host((uint8_t *)tmp,size);
    }
    return 9;
}

/*
[Name] Transmit specified status in real time
    ASCIIDLE DC4 fn m
    Hex 10 14 fn m
    Decimal 16 20 fn m
    [Range] fn = 7
    TM-P60: m = 1, 5
    [Printers not featuring this command] TM-J2000/J2100, TM-T90, TM-T20, TM-T88IV, TM-T88V, TM-T70, TM-L90,
    TM-U230, TM-U220
*/
int function_not_support_4(void *arg)
{
    LOG2(TAG,"%s",__func__); 
    return 4;
}
/*[Name] Transmit set values for top/bottom logo printing
[Format] ASCII FS ( E pL pH fn m c
        Hex 1C 28 45 pL pH fn m c
        Decimal 28 40 69 pL pH fn m c
        [Range] (pL + pH × 256) = 3 (pL = 3, pH = 0)
fn = 61
m = 2
c = 48, 49, 50*/
int transmit_top_bottom_logo_printing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *frame = (_frame_typedef *)arg; 
    char tmp[15];
    int size=0;
    switch (frame->data[7])
    {
        case 0x30:
            size=sprintf(tmp,"7H20");
            size ++;
            break;
        case 0x31:
            size=sprintf(tmp,"7H21");
            size ++;
            break;
        case 0x32:
            size=sprintf(tmp,"7H22210110");
            size ++;
            break;
        default:
            ESP_LOGE(TAG,"NOT IMPLEMENT SUB FUN :%d",frame->data[7]);
            break;
    }
    if(size) {
        epson_response_to_host((uint8_t *)tmp,size);
    }
    return 8;
}

/*
[Name] Transmit the key code list for defined NV graphics.
[Format] ASCII GS ( L pL pH m fn d1 d2
Hex 1D 28 4C 04 00 30 40 4B 43
Decimal 29 40 76 4 0 48 64 75 67
*/
int transmit_key_code_list_for_define_NV_graphic(void *arg) {     //done
    ESP_LOGI(TAG,"%s",__func__); 
    char tmp[15];
    int size=0;
    size=sprintf(tmp,"7r@");
    size++;
    epson_response_to_host((uint8_t *)tmp,size);
    return 9;
}

/*[Name] Horizontal tab
[Format] ASCII HT
Hex 09
Decimal 9
*/
int horizontal_tab(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1; //return 0 to add LF to log file
}

/*[Name] Print and line feed
[Format] ASCII LF
Hex 0A
*/
int print_and_line_feed(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1; //return 0 to add LF to log file
}

/*
[Name] Print and return to standard mode (in page mode)
[Format] ASCII FF
Hex 0C
*/
int print_and_return_to_standard_mode(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    //no data need to return
    return 1;
}

/*
[Name] Print and carriage return
[Format] ASCII CR
Hex 0D
Decimal 13
*/
int print_and_carriage_return(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1;
}

/*
[Name] Cancel print data in page mode
[Format] ASCII CAN
Hex 18
Decimal 24
*/
int cancel_print_data_in_page_mode(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    //No data need to return
    return 1;
}

/*
[Name] Transmit real-time status
[Format] ASCII DLE EOT n [a]
Hex 10 04 n [a]
Decimal 16 4 n [a]
*/
int transmit_real_time_status(void *arg) {
    int cmd_size =0;
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *frame = (_frame_typedef *)arg; 
    uint8_t ret_code = 0;
    if(frame->len < 3)
    {
        ESP_LOGE(TAG,"LEN NOT MATCH");
        return frame ->len;
    }
    switch (frame->data[2])
    {
        case 1:
            ret_code = 0x16;
            cmd_size =3;
            break;
        case 2:
        case 3:
        case 4:
            ret_code = 0x12;
            cmd_size =3;
            break;
        case 0:
        case 5:
        case 6:
        case 7:
        case 8:
            cmd_size =4;
            break;
        default:
            ESP_LOGE(TAG,"NOT IMPLEMENT SUB FUN :%d",frame->data[2]);
            cmd_size =3;
            break;
    }
    if (ret_code)
    {
        epson_response_to_host(&ret_code,1);
    }
    if(frame ->len == 4)
        return 4;
    return cmd_size;
}

/*
[Name] Send real-time request to printer
[Format] ASCII DLE ENQ n
Hex 10 05 n
Decimal 16 5 n
*/
int send_real_time_request_to_printer(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Generate pulse in real-time
[Format] ASCII DLE DC4 n m t
Hex 10 14 n m t
Decimal 16 20 n m t
[Printers not featuring this command] TM-P60, TM-U230
[Range] n = 1
m = 0, 1
1 ≤ t ≤ 8
*/
int generate_pulse_in_real_time(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 5;
}

/*
[Name] Execute power-off sequence
[Format] ASCII DLE DC4 fn a b
Hex 10 14 02 a b
Decimal 16 20 2 a b
[Printers not featuring this command] TM-U230, TM-U220
[Range] fn = 2
a = 1
b = 8
*/
int execute_power_off_sequence(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 5;
}

/*
[Name] Clear buffer (s)
[Format] ASCII DLE DC4 fn d1...d7
Hex 10 14 08 d1...d7
Decimal 16 20 8 d1...d7
[Printers not featuring this command] TM-U230, TM-U220
[Range] fn = 8
d1 = 1, d2 = 3, d3 = 20, d4 = 1, d5 = 6, d6 = 2, d7 = 8
*/
int clear_buffer_s_(void *arg) {   //done
    ESP_LOGI(TAG,"%s",__func__); 
    uint8_t rsp[3] = {0x37,0x25,0x00};
    epson_response_to_host(rsp,3);
    return 10;
}

/*[Name] Print data in page mode
[Format] ASCII ESC FF
Hex 1B 0C
Decimal 27 12*/
int print_data_in_page_mode(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 2;
}

/*
[Name] Set right-side character spacing
[Format] ASCII ESC SP n
Hex 1B 20 n
Decimal 27 32 n
[Range] 0 ≤ n ≤ 255
[Default] n = 0
*/
int set_right_side_character_spacing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Select print mode(s)
[Format] ASCII ESC ! n
Hex 1B 21 n
Decimal 27 33 n
[Range] 0 ≤ n ≤ 255
*/
int select_print_mode_s_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Set absolute print position
[Format] ASCII ESC $ nL nH
Hex 1B 24 nL nH
Decimal 27 36 nL nH
[Range] 0 ≤ nL ≤ 255
0 ≤ nH ≤ 255
*/
int set_absolute_print_position(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    //NO DATA NEED TO RETURN
    return 4;
}

/*
[Name] Select/cancel user-defined character set
[Format] ASCII ESC % n
Hex 1B 25 n
Decimal 27 37 n
[Range] 0 ≤ n ≤ 255
[Default] n = 0
*/
int select_cancel_user_defined_character_set(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Define user-defined characters
[Format] ASCII ESC & y c1 c2 [x1 d1 ... d(y × x1)] ... [xk d1 ... d(y × xk)]
Hex 1B 26 y c1 c2 [x1 d1 ... d(y × x1)] ... [xk d1 ... d(y × xk)]
Decimal 27 38 y c1 c2 [x1 d1 ... d(y × x1)] ... [xk d1 ... d(y × xk)]
*/
int define_user_defined_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT & RETURN SIZE");
    return 1000;
}

/*[Name] Select bit-image mode
[Format] ASCII ESC ✻ m nL nH d1 ... dk
Hex 1B 2A m nL nH d1 ... dk
Decimal 27 42 m nL nH d1 ... dk
*/
int select_bit_image_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT & RETURN SIZE");
    return 1000;
}

/*
[Name] Turn underline mode on/off
[Format] ASCII ESC – n
        Hex 1B 2D n
        Decimal 27 45 n
*/
int turn_underline_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*[Name] Select default line spacing
[Format] ASCII ESC 2
Hex 1B 32
Decimal 27 50
*/
int select_default_line_spacing(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    //NO DATA RETURN
    return 2;
}

/*
[Name] Set line spacing
[Format] ASCII ESC 3 n
Hex 1B 33 n
Decimal 27 51 n
*/
int set_line_spacing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Select peripheral device
[Format] ASCII   ESC = n
        Hex      1B 3D n
        Decimal  27 61 n
*/
int select_peripheral_device(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *frame = (_frame_typedef *)arg; 
    if(frame->len < 3)
    {
        ESP_LOGE(TAG,"LEN NOT MATCH");
        return frame ->len;
    }
    switch (frame->data[2])
    {
        case 1: 
        case 3:
            ESP_LOGI(TAG,"Enables printer.");
            break;
        case 2:
            ESP_LOGI(TAG,"Disables printer");
            break;
        default:
            ESP_LOGE(TAG,"NOT IMPLEMENT SUB FUN :%d",frame->data[2]);
            break;
    }
    return 3;
}

/*
[Name] Cancel user-defined characters
[Format] ASCII ESC ? n
        Hex 1B 3F n
        Decimal 27 63 n
        [Range] 32 ≤ n ≤ 126
*/
int cancel_user_defined_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Initialize printer
[Format] ASCII ESC @
        Hex 1B 40
        Decimal 27 64
*/
int initialize_printer(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 2;
}

/*
[Name] Set horizontal tab positions
[Format] ASCII ESC D n1 ... nk NUL
        Hex 1B 44 n1 ... nk 00
        Decimal 27 68 n1 ... nk 0
        [Range] 1 ≤ n ≤ 255
        0 ≤ k ≤ 32
*/
int set_horizontal_tab_positions(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}

/*
[Name] Turn emphasized mode on/off
[Format] ASCII ESC E n
        Hex 1B 45 n
        Decimal 27 69 n
        [Range] 0 ≤ n ≤ 255
        [Default] n = 0
*/
int turn_emphasized_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Turn double-strike mode on/off
[Format] ASCII ESC G n
        Hex 1B 47 n
        Decimal 27 71 n
        [Range] 0 ≤ n ≤ 255
        [Default] n = 0
*/
int turn_double_strike_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Print and feed paper
[Format] ASCII ESC J n
        Hex 1B 4A n
        Decimal 27 74 n
        [Range] 0 ≤ n ≤ 255
        [Default] N
*/
int print_and_feed_paper(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    //no data need to return
    return 3;
}

/*
[Name] Select page mode
[Format] ASCII ESC L
    Hex 1B 4C
    Decimal 27 76
    [Range] None
    [Default] N
*/

int select_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 2;
}

/*
[Name] Select character font
[Format] ASCII ESC M n
        Hex 1B 4D n
        Decimal 27 77 n
*/
int select_character_font(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Select an international character set
[Format] ASCII ESC R n
        Hex 1B 52 n
        Decimal 27 82 n
*/
int select_an_international_character_set(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    //NO DATA NEED TO RETURN
    return 3;
}

/*
[Name] Select standard mode
[Format] ASCII ESC S
        Hex 1B 53
        Decimal 27 83
*/
int select_standard_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 2;
}

/*
[Name] Select print direction in page mode
[Format] ASCII ESC T n
        Hex 1B 54 n
        Decimal 27 84 n
        [Range] 0 ≤ n ≤ 3, 48 ≤ n ≤ 51
        [Default] n = 0
*/
int select_print_direction_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Turn 90° clockwise rotation mode on/off
[Format] ASCII ESC V n
        Hex 1B 56 n
        Decimal 27 86 n
        [Range] 0 ≤ n ≤ 2, 48 ≤ n ≤ 50
        [Default] n = 0
*/
int turn_90__clockwise_rotation_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Set print area in page mode
[Format] ASCII ESC W xL xH yL yH dxL dxH dyL dyH
        Hex 1B 57 xL xH yL yH dxL dxH dyL dyH
        Decimal 27 87 xL xH yL yH dxL dxH dyL dyH
        [Range] 0 ≤ xL, xH, yL, yH, dxL, dxH, dyL, dyH ≤ 255
        (except for dxL = dxH = 0 or dyL = dyH = 0)
        [Default] Horizontal logical origin and vertical logical origin= 0
        xL = 0, xH = 0, yL = 0, yH = 0
*/
int set_print_area_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 10;
}

/*  
[Name] Set relative print position
[Format] ASCII ESC \ nL nH
        Hex 1B 5C nL nH
        Decimal 27 92 nL nH
[Range] –32768 ≤ (nL + nH × 256) ≤ 32767
*/
int set_relative_print_position(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 4;
}

/*
[Name] Select justification
[Format] ASCII ESC a n
        Hex 1B 61 n
        Decimal 27 97 n
[Range] 0 ≤ n ≤ 2, 48 ≤ n ≤ 50
[Default] n = 0
*/
int select_justification(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Select paper sensor(s) to output paper-end signals
[Format] ASCII ESC c 3 n
            Hex 1B 63 33 n
            Decimal 27 99 51 n
[Range] 0 ≤ n ≤ 255
*/
int select_paper_sensor_s__to_output_paper_end_signals(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT"); 
    //NO DATA RETURN
    return 4;
}

/*
[Name] Select paper sensor(s) to stop printing
[Format] ASCII ESC c 4 n
        Hex 1B 63 34 n
        Decimal 27 99 52 n
[Range] 0 ≤ n ≤ 255
[Default] n = 0
*/
int select_paper_sensor_s__to_stop_printing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 4;
}

/*
[Name] Select character size
[Format] ASCII GS ! n
        Hex 1D 21 n
        Decimal 29 33 n
*/
int select_character_size(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Enable/disable panel buttons
[Format] ASCII ESC c 5 n
        Hex 1B 63 35 n
        Decimal 27 99 53 n
[Range] 0 ≤ n ≤ 255
[Default] n = 0
*/
int enable_disable_panel_buttons(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 4;
}

/*
[Name] Print and feed n lines
[Format] ASCII ESC d n
        Hex 1B 64 n
        Decimal 27 100 n
[Range] 0 ≤ n ≤ 255
[Default] None
*/
int print_and_feed_n_lines(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
ESC i
[Name] Partial cut (one point left uncut)
[Format] ASCII ESC i
        Hex 1B 69
        Decimal 27 105
[Range] None
*/

int partial_cut__one_point_left_uncut_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 2;
}

/*
[Name] Partial cut (three points left uncut)
[Format] ASCII ESC m
        Hex 1B 6D
        Decimal 27 109
*/
int partial_cut__three_points_left_uncut_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 2;
}

/*
[Name] Generate pulse
[Format] ASCII ESC p m t1 t2
        Hex 1B 70 m t1 t2
        Decimal 27 112 m t1 t2
        [Range] m = 0, 1, 48, 49
        0 ≤ t1 ≤ 255
        0 ≤ t2 ≤ 255
*/
int generate_pulse(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 5;
}

/*
[Name] Transmit peripheral device status
[Format] ASCII ESC u n
        Hex 1B 75 n
        Decimal 27 117 n
        [Range] n = 0, 48   
*/
int transmit_peripheral_device_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Transmit paper sensor status
[Format] ASCII ESC v
        Hex 1B 76
        Decimal 27 118
*/
int transmit_paper_sensor_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 2;
}

/*
[Name] Select character code table
[Format] ASCII ESC t n
        Hex 1B 74 n
        Decimal 27 116 n
*/
int select_character_code_table(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    //NO DATA RETURN
    return 3;
}

/*
[Name] Turn upside-down print mode on/off
[Format] ASCII ESC { n
        Hex     1B 7B n
        Decimal 27 123 n
        [Range] 0 ≤ n ≤ 255
        [Default] n = 0
*/
int turn_upside_down_print_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 3;
}

/*
[Name] Write to NV user memory
[Format] ASCII FS g 1 m a1 a2 a3 a4 nL nH d1...dk
    Hex 1C 67 31 m a1 a2 a3 a4 nL nH d1...dk
    Decimal 28 103 49 m a1 a2 a3 a4 nL nH d1...dk
*/
int write_to_nv_user_memory(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}

/*
[Name] Read from NV user memory
[Format] ASCII FS g 2 m a1 a2 a3 a4 nL nH
    Hex 1C 67 32 m a1 a2 a3 a4 nL nH
    Decimal 28 103 50 m a1 a2 a3 a4 nL nH
*/
int read_from_nv_user_memory(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}

/*
[Name] Print NV bit image
[Format] ASCII FS p n m
        Hex 1C 70 n m
        Decimal 28 112 n m
*/
int print_nv_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 4;
}

/*
[Name] Execute test print
[Format] ASCII GS ( A pL pH n m
        Hex 1D 28 41 02 00 n m
        Decimal 29 40 65 2 0 n m
*/
int execute_test_print(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 7;
}

/*
[Name] Enable/disable real-time command
[Format] ASCII GS ( D pL pH m [a1 b1]...[ak bk]
Hex 1D 28 44 pL pH 14 [a1 b1]...[ak bk]
Decimal 29 40 68 pL pH 20 [a1 b1]...[ak bk]
*/
int enable_disable_real_time_command(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}

/*
[Name] Transmit the customized setting values
[Format] ASCII GS ( E pL pH fn a
    Hex 1D 28 45 02 00 06 a
    Decimal 29 40 69 2 0 6 a
    [Range] (pL + pH × 256) = 2 (pL = 2, pH = 0)
fn = 6
*/
int transmit_customized_setting_values(void *arg){
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    if(newframe->len < 7) {
        ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
        return newframe->len;
    }
    char tmp[15];
    int size =0;
    tmp[0] = 0x37;
    tmp[1] = 0x27;
    switch (newframe->data[6])
    {  
        case 3:
            ESP_LOGI(TAG,"transmit paper witdh");
            tmp[2] = '3';
            tmp[3] = 0x1f;
            tmp[4] = '6';
            tmp[5] = 0;
            size = 6;
            break;
        case 5:
            size = sprintf(tmp,"7'%d%c100",newframe->data[6],0x1F);
            size++;
            break;
        case 6:
            size = sprintf(tmp,"7'%d%c13",newframe->data[6],0x1F);
            size++;
            break;
        case 8:
        case 9:
        case 10:
            size = sprintf(tmp,"7'%d%c0",newframe->data[6],0x1F);
            size++;
            break;
        case 97:
            size = sprintf(tmp,"7'%d%c1",newframe->data[6],0x1F);
            size++;
            break;
        case 98:
            size = sprintf(tmp,"7'%d%c2",newframe->data[6],0x1F);
            size++;
            break;
        case 112:
            size = sprintf(tmp,"7'%d%c1",newframe->data[6],0x1F);
            size++;
            break;

        case 100:
        case 101:
        case 102:
        case 103:
        case 104:
        case 105:
        case 111:
        case 117:
        case 119:
            size = sprintf(tmp,"7'%d%c0",newframe->data[6],0x1F);
            size++;
            break;
        case 120:
            size = sprintf(tmp,"7'%d%c65535",newframe->data[6],0x1F);
            size++;
            break;
        case 121:
        case 122:
        case 123:
        case 124:
            size = sprintf(tmp,"7'%d%c1",newframe->data[6],0x1F);
            size++;
            break;
        case 125:
            size = sprintf(tmp,"7'%d%c2",newframe->data[6],0x1F);
            size++;
            break;
        case 126:
            size = sprintf(tmp,"7'%d%c1",newframe->data[6],0x1F);
            size++;
            break;
        default :
            ESP_LOGW(TAG,"NOT IMPLEMENT: %d",newframe->data[6] );
            break;
    }
    if(size) {
        epson_response_to_host((uint8_t *)tmp,size);
    }
    return 7;
}

/*
[Name] Transmit the configuration item for the serial interface
[Format] ASCII GS ( E pL pH fn a
    Hex 1D 28 45 pL pH 0B a
    Decimal 29 40 69 pL pH 11 a
    [Range] (pL + pH × 256) = 2 (pL = 2, pH = 0)
    fn = 12
*/
int transmit_configuration_item_for_serial_interface(void *arg){
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    if(newframe->len < 7) {
        ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
        return newframe->len;
    }
    char tmp[15];
    int size =0;
    switch (newframe->data[6])
    {  
        case 1:  //Transmission speed
            size = sprintf(tmp,"73%d%c9600",newframe->data[6],0x1F);
            size++;
            break;
        default :
            ESP_LOGW(TAG,"NOT IMPLEMENT: %d",newframe->data[6] );
            break;
    }
    if(size) {
        epson_response_to_host((uint8_t *)tmp,size);
    }
    return 7;
}


/*
[Name] Transmit conditions for USB interface communication
[Format] ASCII GS ( E pL pH fn a
        Hex 1D 28 45 pL pH fn a
        Decimal 29 40 69 pL pH fn a
        [Range] (pL + pH × 256) = 2 (pL = 2, pH= 0)
        fn = 16
        a = 1
*/
int transmit_condition_for_usb_interface(void *arg){  //done
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    if(newframe->len < 7) {
        ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
        return newframe->len;
    }
    char tmp[15];
    int size =0;
    size = sprintf(tmp,"7R1%c1",0x1F);
    size++;
    epson_response_to_host((uint8_t *)tmp,size);
    return 7;
}

int set_user_setup_commands(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}

/*
    GS ( H pL pH fn m d1 d2 d3 d4 <Function 48>
    [Format] ASCII GS ( H pL pH fn m d1 d2 d3 d4
    Hex 1D 28 48 06 00 30 30 d1 d2 d3 d4
    Decimal 29 40 72 6 0 48 48 d1 d2 d3 d4
*/
int request_transmission_of_response_or_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    if(newframe->len <11) {
        ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
        return newframe->len;
    }
    uint8_t rsp[7];
    rsp[0] = 0x37;
    rsp[1] = 0x22;
    rsp[2] = newframe->data[7];
    rsp[3] = newframe->data[8];
    rsp[4] = newframe->data[9];
    rsp[5] = newframe->data[10];
    rsp[6] = 0x00;
    epson_response_to_host((uint8_t *)rsp,7);
    return 11;
}


int select_print_control_method_s_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int transmit_related_capacity_NV_memory(void *arg) {

    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    if(newframe->len < 7) {
        ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
        return newframe->len;
    }
    char tmp[15];
    int size = 0; 
    switch (newframe->data[6])
    {  
        case 00:
        case 48:
            ESP_LOGI(TAG," Transmit the NV graphics memory capacity");
            size= sprintf(tmp,"71%d",epson_nv_get_size());
            size++;
            break;
        case 2:
        case 50:
            ESP_LOGI(TAG," Print the graphics data in the print buffer"); //no data need to return
            // size= sprintf(tmp,"71%d",epson_nv_get_size());
            // size++;
            break;
        case 3:
        case 51:
            ESP_LOGI(TAG,"Transmit the remaining capacity of the NV graphics memory");
            size= sprintf(tmp,"71%d",epson_nv_get_remaining_size());
            size++;
            break;
        default :
            ESP_LOGW(TAG,"NOT IMPLEMENT: %d",newframe->data[6] );
            break;
    }
    if(size) {
        epson_response_to_host((uint8_t *)tmp,size);
    }
    return 7;
}

/*
[Name] Store the graphics data in the print buffer (raster format).
    [Format] ASCII GS ( L pL pH m fn a bx by c xL xH yL yH d1...dk
    Hex 1D 28 4C pL pH 30 70 30 bx by c xL xH yL yH d1...dk
    Decimal 29 40 76 pL pH 48 112 48 bx by c xL xH yL yH d1...dk
    ASCII GS 8 L p1 p2 p3 p4 m fn a bx by c xL xH yL yH d1...dk
    Hex 1D 38 4C p1 p2 p3 p4 30 70 30 bx by c xL xH yL yH d1...dk
    Decimal 29 56 76 p1 p2 p3 p4 48 112 48 bx by c xL xH yL yH d1...dk
*/
int store_the_graphics_data_in_the_print_buffer(void *arg) {

    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    // if(newframe->len < 10) {
    //     ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
    //     return newframe->len;
    // }
    // char tmp[15];
    // int size = 0; 
    // switch (newframe->data[6])
    // {  
    //     case 00:
    //     case 48:
    //         ESP_LOGI(TAG," Transmit the NV graphics memory capacity");
    //         size= sprintf(tmp,"71%d",epson_nv_get_size());
    //         size++;
    //         break;
    //     case 3:
    //     case 51:
    //         ESP_LOGI(TAG,"Transmit the remaining capacity of the NV graphics memory");
    //         size= sprintf(tmp,"71%d",epson_nv_get_remaining_size());
    //         size++;
    //         break;
    //     default :
    //         ESP_LOGW(TAG,"NOT IMPLEMENT: %d",newframe->data[6] );
    //         break;
    // }
    // if(size) {
    //     epson_response_to_host((uint8_t *)tmp,size);
    // }
    return 7;
}

int select_character_effects(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int set_up_and_print_the_symbol(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int set_absolute_vertical_print_position_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int define_downloaded_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int print_downloaded_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int start_end_macro_definition(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int turn_white_black_reverse_print_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int select_print_position_of_hri_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}

//{37}{25}{00}{14}{00}{00}{0F}{5F}{54}{4D}{2D}{54}{38}{38}{56}{00}
int transmit_printer_id(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    if(newframe->len < 3) {
        ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
        return newframe->len;
    }
    char tmp[15];
    int size =0;
    
    switch (newframe->data[2])
    {   
        case 1: //Printer model
        case 49:
        {
            tmp[0] = 0x20;
            size = 1;
            break;
        }
        case 2:  //Printer type
        case 50:
        {
            tmp[0] = 0x02;
            size = 1;
            break;
        }    
        case 3:  //Firmware version
        case 51:
        {
            tmp[0] = 0x64;
            size = 1;
            break;
        }
        case 65://  Printer model
        {
            size = sprintf(tmp,"_30.21 ESC/POS");
            size++;
            break;
        } 
        case 66://  Printer model
        {
            size = sprintf(tmp,"_EPSON");
            size++;
            break;
        }   
        case 67://  Printer model
        {
            size = sprintf(tmp,PRINTER_MODEL);
            size++;
            break;
        }
        case 68://  Printer model
        {
            size = sprintf(tmp,"_TESF807101");
            size++;
            break;
        }
        case 69://  Printer model
        {
            size = sprintf(tmp,"_");
            size++;
            break;
        }
        case 35:
        case 96://  See [Printer information]
        case 110://  See [Printer information]
        {
            size = sprintf(tmp,"=`I");
            size++;
            break;
        }
        case 111://  Printer model
        {
            size = sprintf(tmp,"_@D@@");
            size++;
            break;
        }
        case 113://  Printer model
        {
            size = sprintf(tmp,"_1");
            size++;
            break;
        }    
        case 112://  Printer model
        case 114://  Printer model
        {
            size = sprintf(tmp,"_0");
            size++;
            break;
        }    
        default :
            ESP_LOGW(TAG,"NOT IMPLEMENT: %d",newframe->data[2] );
            break;
    }
    if(size) {
        epson_response_to_host((uint8_t *)tmp,size);
    }
    return 3;

}
int set_left_margin(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int set_horizontal_and_vertical_motion_units(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int select_cut_mode_and_cut_paper(void *arg) {
    ESP_LOGI(TAG,"%s",__func__);
    is_cut_command = 1; 
    return 1000;
}
int set_print_area_width(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int set_relative_vertical_print_position_in_page_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int execute_macro(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int enable_disable_automatic_status_back__asb_(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    if(newframe->len < 3) {
        ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
        return newframe->len;
    }
    // char tmp[15];
    // int size =0;
    switch (newframe->data[2])
    {
        case 255://  ff
        {
            uint8_t rsp[] = {0x14, 0x00, 0x00, 0x0F};
            epson_response_to_host(rsp,4);
            break;
        }    
        default :
            ESP_LOGW(TAG,"NOT IMPLEMENT: %d",newframe->data[2] );
            break;
    }
    return 3;
    
}

/*

[Name] Turn smoothing mode on/off
[Format] ASCII GS b n
Hex 1D 62 n
Decima 29 98 n
[Range] 0 ≤ n ≤ 255
[Default] n = 0
*/
int turn_smoothing_mode_on_off(void *arg) {
    LOG2(TAG,"%s",__func__); 
    // ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    //no data need to return
    return 3;
}
int select_font_for_hri_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int initialize_maintenance_counter(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int transmit_maintenance_counter(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int set_bar_code_height(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int print_bar_code(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int transmit_status(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    _frame_typedef *newframe = (_frame_typedef *)arg;
    if(newframe->len < 3) {
        ESP_LOGW(TAG,"LEN NOT FETCH : %d",newframe->len);
        return newframe->len;
    }
    uint8_t res =0;
    switch (newframe->data[2])
    {   
        case 1:
        case 49:
            res = 0x00;
            break;
        case 2:
        case 50:
            res = 0x00;
            break;
        default :
            ESP_LOGW(TAG,"NOT IMPLEMENT: %d",newframe->data[2] );
        break;
    }
    epson_response_to_host(&res,1);
    return 3;
}
int print_raster_bit_image(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int set_bar_code_width(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int set_print_mode_s__for_kanji_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int select_kanji_character_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int turn_underline_mode_on_off_for_kanji_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int cancel_kanji_character_mode(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int define_user_defined_kanji_characters(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int select_kanji_character_code_system(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int set_kanji_character_spacing(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
int turn_quadruple_size_mode_on_off(void *arg) {
    ESP_LOGI(TAG,"%s",__func__); 
    ESP_LOGW(TAG,"FUNCTION NOT IMPLEMENT");
    return 1000;
}
