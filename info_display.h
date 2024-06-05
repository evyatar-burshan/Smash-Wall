#ifndef INFO_DISP_H
#define INFO_DISP_H

#include "Arduino.h"

void info_display_setup();
void update_time_diplay(uint16_t t);
void update_points_1(uint8_t p);
void update_points_2(uint8_t p);
void update_players_points(uint8_t p1, uint8_t p2);
void shut_player_point(uint8_t player);
void turn_off_player_1_points();
void turn_off_player_2_points();
void turn_off_all();
void display_hit();
void display_start();
void display_title();
void display_text(uint8_t language, uint8_t alignment, String text, sw_colors color);
void display_end();
void test_digits();



#endif
