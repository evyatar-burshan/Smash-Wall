#include "config.h"
#include "info_display.h"
#include "digits.h"
#include "arduino.h"

/**
* Sets up the info display digits and resets them
*/
void info_display_setup() {

  digits_setup();
  update_time_diplay(0);
  update_points_1(0);
  update_points_2(0);
}

/**
* Updates the info display digits according to the specified points of player 1 and player 2
*
* @param p1 Specifies the points of player 1
* @param p2 Specifies the points of player 2
*/
void update_players_points(uint8_t p1, uint8_t p2) {
  update_points_1(p1);
  update_points_2(p2);
}

/**
* Shuts off a specified player's points
*
* @param player Specifies which players points to shut off
*/
void shut_player_point(uint8_t player) {
  if (player == PLAYER_1)
    turn_off_player_1_points();
  else
    turn_off_player_2_points();
}

/**
* Updates the info display digits according to the specified time
*
* @param t Specifies the time
*/
void update_time_diplay(uint16_t t) {
  uint8_t d0, d1, d2;

  d0 = t % 10;
  t = t / 10;
  d1 = t % 10;
  t = t / 10;
  d2 = t % 10;
  t = t / 10;

  set_digit_num(TIMER_DIGIT_0, d0, TIMER_COLOR);
  set_digit_num(TIMER_DIGIT_1, d1, TIMER_COLOR);
  set_digit_num(TIMER_DIGIT_2, d2, TIMER_COLOR);

  refresh_digits();
}

/**
* Turns off the digits of player 1
*/
void turn_off_player_1_points() {
  turn_off_digit(POINTS_1_DIGIT_0);
  turn_off_digit(POINTS_1_DIGIT_1);
  refresh_digits();
}

/**
* Turns off the digits of player 2
*/
void turn_off_player_2_points() {
  turn_off_digit(POINTS_2_DIGIT_0);
  turn_off_digit(POINTS_2_DIGIT_1);
  refresh_digits();
}

/**
* Updates player 1's points according to the specified amount of points
*
* @param p Specifies how many points the player has
*/
void update_points_1(uint8_t p) {
  uint8_t d0, d1;

  d0 = p % 10;
  p = p / 10;
  d1 = p % 10;

  set_digit_num(POINTS_1_DIGIT_0, d0, PLAYER_1_COLOR);
  set_digit_num(POINTS_1_DIGIT_1, d1, PLAYER_1_COLOR);

  refresh_digits();
}

/**
* Updates player 2's points according to the specified amount of points
*
* @param p Specifies how many points the player has
*/
void update_points_2(uint8_t p) {
  uint8_t d0, d1;

  d0 = p % 10;
  p = p / 10;
  d1 = p % 10;

  set_digit_num(POINTS_2_DIGIT_0, d0, PLAYER_2_COLOR);
  set_digit_num(POINTS_2_DIGIT_1, d1, PLAYER_2_COLOR);

  refresh_digits();
}

/**
* Turns off all the info display digits
*/
void turn_off_all() {
  uint8_t i;
  for (i = 0; i < NUM_OF_DIGITS; i++) {
    turn_off_digit(i);
  }
  refresh_digits();
}

/**
* Displays the word "HIT" in the color of the timer on the info display
*/
void display_hit() {
  display_text(ENGLISH, CENTER, "HIT", TIMER_COLOR);
}

/**
* Displays the game's title in the color of the timer on the info display
*/
void display_title() {
  set_digit_hebrew_letter(6, 23, Green);
  set_digit_hebrew_letter(5, 9, Green);
  set_digit_hebrew_letter(4, 24, Green);
  set_digit_hebrew_letter(3, 4, Green);
  set_digit_hebrew_letter(2, 14, Green);
  set_digit_hebrew_letter(1, 7, Green);
  set_digit_hebrew_letter(0, 21, Green);
}

/**
* Displays the word "START" in the color of the timer on the info display
*/
void display_start() {
  display_text(ENGLISH, CENTER, "START", TIMER_COLOR);
}

void display_end() {
}

/**
* Tests if the info diplay digits can display all numbers
*/
void test_nums_digits() {
  for (int i = 0; i < 7; i++) {
    turn_off_digit(i);
  }
  refresh_digits();
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
      set_digit_num(j, i, PLAYER_1_COLOR);
    }
    refresh_digits();
    delay(800);
  }
}

/**
* Tests if the info diplay digits can display all english letters
*/
void test_eng_letters_digits() {
  for (int i = 0; i < 7; i++) {
    turn_off_digit(i);
  }
  refresh_digits();
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 7; j++) {
      set_digit_letter(j, static_cast<char>('A' - 1 + i), PLAYER_1_COLOR);
    }
    refresh_digits();
    delay(1500);
  }
}

/**
* Tests if the info diplay digits can display all hebrew letters
*/
void test_heb_letters_digits() {
  for (int i = 0; i < 7; i++) {
    turn_off_digit(i);
  }
  refresh_digits();
  for (int i = 0; i < 27; i++) {
    for (int j = 0; j < 7; j++) {
      Serial.println(i);
      set_digit_hebrew_letter(j, i, PLAYER_1_COLOR);
    }
    refresh_digits();
    delay(1500);
  }
}

/**
* Tests if the info diplay digits can display all english letters, hebrew letters and numbers
*/
void test_digits() {
  test_nums_digits();
  test_eng_letters_digits();
  test_heb_letters_digits();
}

/**
* @brief Displays text in alignment to the left
* Displays a specified text in a specified language in a specified color in alignment to the left of the info display
*
* @param language Specifies in what language the text is
* @param text Specifies what text to display
* @param color Specifies in what color the text will be displayed
*/
void display_text_left(uint8_t language, String text, sw_colors color) {
  int start = 0;
  int len_text = text.length();
  turn_off_all();
  if (language == ENGLISH) {
    for (int i = 0; i < len_text; i++) {
      if (i > 6) {
        for (int j = 0; j < 7; j++) {
          Serial.println(i - 6 + start);
          set_digit_letter(j, text[i - 6 + start], color);
          delay(500);
          refresh_digits();
          start++;
        }
        Serial.println();
      } else {
        set_digit_letter(i, text[i], color);
        refresh_digits();
      }
    }
  } else if (language == HEBREW) {
    for (int i = 0; i < len_text; i++) {
      if (i > 6) {
        for (int j = 0; j < 7; j++) {
          set_digit_hebrew_letter(j, text[len_text - i - 1 - start], color);
          delay(500);
          refresh_digits();
        }
        start++;
      } else {
        set_digit_hebrew_letter(i, text[len_text - i], color);
        refresh_digits();
      }
    }
  }
}

/**
* @brief Displays text in alignment to the right
* Displays a specified text in a specified language in a specified color in alignment to the right of the info display
*
* @param language Specifies in what language the text is
* @param text Specifies what text to display
* @param color Specifies in what color the text will be displayed
*/
void display_text_right(uint8_t language, String text, sw_colors color) {
  int start = 0;
  int len_text = text.length();
  turn_off_all();
  if (language == ENGLISH) {
    for (int i = len_text - 1; i >= 0; i--) {
      if (i < 0) {
        for (int j = 7; j >= 0; j--) {
          set_digit_letter(j, text[len_text - i - 1 + start], color);
          delay(500);
          refresh_digits();
        }
        start--;
      } else {
        set_digit_letter(i, text[len_text - i], color);
        refresh_digits();
      }
    }
  } else if (language == HEBREW) {
    for (int i = len_text - 1; i >= 0; i--) {
      if (i < 0) {
        for (int j = 7; j >= 0; j--) {
          set_digit_hebrew_letter(j, text[i + 6 + start], color);
          delay(500);
          refresh_digits();
        }
        start--;
      } else {
        set_digit_hebrew_letter(i, text[i], color);
        refresh_digits();
      }
    }
  }
}

/**
* @brief Displays text in alignment to the center
* Displays a specified text in a specified language in a specified color in alignment to the center of the info display
*
* @param language Specifies in what language the text is
* @param text Specifies what text to display
* @param color Specifies in what color the text will be displayed
*/
void display_text_center(uint8_t language, String text, sw_colors color) {
  int len_text = text.length();
  turn_off_all();
  if (language == ENGLISH) {
    if (len_text > 5) {
      display_text_left(ENGLISH, text, color);
    } else {
      for (int i = 0; i < len_text; i++) {
        if (len_text > 3) {
          set_digit_letter(i + 1, text[i], color);
        } else if (len_text > 1) {
          set_digit_letter(i + 2, text[i], color);
        } else if (len_text == 1) {
          set_digit_letter(i + 3, text[i], color);
        }
      }
      refresh_digits();
    }
  } else if (language == HEBREW) {
    if (len_text > 5) {
      display_text_right(HEBREW, text, color);
    } else {
      for (int i = len_text - 1; i >= 0; i--) {
        if (len_text > 0) {
          set_digit_letter(i + 3, text[i], color);
        } else if (len_text > 2) {
          set_digit_letter(i + 2, text[i], color);
        } else if (len_text == 5) {
          set_digit_letter(i + 1, text[i], color);
        }
      }
      refresh_digits();
    }
  }
}

/**
* @brief Displays text on the info display
* Displays a specified text in a specified language in a specified color in a specified alignment
*
* @param language Specifies in what language the text is
* @param alignment Specifies in which alignment the text will be displayed
* @param text Specifies what text to display
* @param color Specifies in what color the text will be displayed
*/
void display_text(uint8_t language, uint8_t alignment, String text, sw_colors color) {
  turn_off_all();
  if (alignment == LEFT) {
    display_text_left(language, text, color);
  } else if (alignment == CENTER) {
    display_text_center(language, text, color);
  } else if (alignment == RIGHT) {
    display_text_right(language, text, color);
  }
}