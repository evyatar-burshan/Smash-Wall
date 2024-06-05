#ifndef SQUARES_DISP_H
#define SQUARES_DISP_H

void sqrs_display_setup();
void light_sqr(uint8_t sqr_idx, sw_colors color);
void light_player_1_sqr(uint8_t sqr_idx);
void light_player_2_sqr(uint8_t sqr_idx);
void shut_sqr(uint8_t sqr_idx);
void light_all_sqrs(sw_colors color);
void shut_all_sqrs();
void test_sqrs();



#endif
