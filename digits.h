#ifndef DIGITS_H
#define DIGITS_H

void static set_segment(uint8_t digit_idx, uint8_t state, uint8_t segment, sw_colors color);

void digits_setup();
void set_digit_num(uint8_t digit_idx, uint8_t num, sw_colors color);
void set_digit_letter(uint8_t digit_idx, uint8_t letter, sw_colors color);
void set_digit_hebrew_letter(uint8_t digit_idx, uint8_t letter, sw_colors color);
void turn_off_digit(uint8_t digit_idx);
void refresh_digits();

#endif
