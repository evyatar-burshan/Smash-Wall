#include <Ticker.h>
#include "config.h";
#include "info_display.h"
#include "squares_display.h"
#include "sensors.h"

void tick_game_timer();
void hit_start_tick();

Ticker read_sensors_timer(read_sensors, READING_SENSORS_PERIOD_mS);
Ticker game_countdown_timer(tick_game_timer, 1000);
Ticker hit_start_timer(hit_start_tick, 3000);

uint16_t game_time;

sw_colors players_colors[2] = { PLAYER_1_COLOR, PLAYER_2_COLOR };
uint8_t players_points[2] = { 0, 0 };
uint8_t lighted_sqr[2];
uint8_t first_time = 0;
bool cur_word_hit = true;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  info_display_setup();
  sqrs_display_setup();
  sensors_setup();
  shut_all_sqrs();
  turn_off_all();

  randomSeed(analogRead(A10));
}

void loop() {
  //test_digits();
  //test_sqrs();
  //read_sensors_timer.start();
  print_sensors();
  //test_sensors(LIGHT_ON_HIT);
  //print_sensors();
  //set_digit_hebrew_letter(4, 'ק', Green);
  //display_title();
  //light_all_sqrs(White);
  //game_idle();
}
void hit_start_tick() {
  if (cur_word_hit) {
    display_start();
    shut_sqr(MID_SQUARE);
    cur_word_hit = false;
  } else {
    //display_hit();
    light_sqr(MID_SQUARE, Green);
    cur_word_hit = true;
  }
}

void game_idle() {
  light_sqr(MID_SQUARE, Green);
  hit_start_timer.start();

  while (!sensor_was_hit(MID_SQUARE)) {
    hit_start_timer.update();
    read_sensors_timer.update();
    //test_mode();
  }
  hit_start_timer.stop();
  read_sensors_timer.stop();
  shut_all_sqrs();
  start_game();
}

void start_game() {
  // reset info display
  update_time_diplay(GAME_TIME_S);

  game_time = GAME_TIME_S;
  //reset points
  players_points[PLAYER_1] = 0;
  players_points[PLAYER_2] = 0;
  update_players_points(0, 0);
  lighted_sqr[PLAYER_1] = get_random_sqr();
  lighted_sqr[PLAYER_2] = get_random_sqr();
  light_player_1_sqr(lighted_sqr[PLAYER_1]);
  light_player_2_sqr(lighted_sqr[PLAYER_2]);
  //game timers
  read_sensors_timer.start();
  game_countdown_timer.start();
  run_game();
}

void run_game() {
  while (game_time > 0) {
    game_countdown_timer.update();
    read_sensors_timer.update();
    check_hit(PLAYER_1);
    check_hit(PLAYER_2);
  }
}

void check_hit(uint8_t player) {

  if (sensor_was_hit(lighted_sqr[player])) {
    players_points[player] = players_points[player] + 1;
    update_players_points(players_points[PLAYER_1], players_points[PLAYER_2]);
    shut_sqr(lighted_sqr[player]);
    lighted_sqr[player] = get_random_sqr();
    light_sqr(lighted_sqr[player], players_colors[player]);
  }
}


void tick_game_timer() {
  if (game_time > 0) {
    game_time = game_time - 1;
    update_time_diplay(game_time);
    if (game_time == 0)
      stop_game();
  }
}

void stop_game() {
  game_countdown_timer.stop();
  read_sensors_timer.stop();
  if (players_points[PLAYER_1] > players_points[PLAYER_2])
    celebrate_win(PLAYER_1);
  else if (players_points[PLAYER_2] > players_points[PLAYER_1])
    celebrate_win(PLAYER_2);
  else
    even_score();
}

uint8_t get_random_sqr() {
  uint8_t r = random(10);
  while ((r == lighted_sqr[PLAYER_1]) || (r == lighted_sqr[PLAYER_2]))
    r = random(10);
  return r;
}

uint8_t get_random_sqr(bool noSquareTwo) {
  uint8_t r = random(10);
  while ((r == lighted_sqr[PLAYER_1]) || (r == lighted_sqr[PLAYER_2]) || (r == 1))
    r = random(10);
  return r;
}

void even_score() {
  uint8_t i;
  shut_all_sqrs();
  for (i = 0; i < CELEBRATE_BLINK; i++) {
    update_players_points(players_points[PLAYER_1], players_points[PLAYER_2]);
    delay(500);
    shut_player_point(PLAYER_1);
    shut_player_point(PLAYER_2);
    delay(500);
  }
}

void celebrate_win(uint8_t player) {
  uint8_t i;

  for (i = 0; i < CELEBRATE_BLINK; i++) {
    light_all_sqrs(players_colors[player]);
    update_players_points(players_points[PLAYER_1], players_points[PLAYER_2]);
    delay(500);
    shut_player_point(player);
    shut_all_sqrs();
    delay(500);
  }
}

void test_mode() {
  if (sensor_was_hit(1)) {
    hit_start_timer.update();
    read_sensors_timer.update();
    light_sqr(1, Yellow);
    delay(400);

    if (sensor_was_hit(7)) {
      hit_start_timer.update();
      read_sensors_timer.update();
      light_sqr(7, Yellow);
      delay(400);

      if (sensor_was_hit(3)) {
        hit_start_timer.update();
        read_sensors_timer.update();
        light_sqr(3, Yellow);
        delay(400);

        if (sensor_was_hit(5)) {
          hit_start_timer.stop();
          read_sensors_timer.stop();
          light_sqr(5, Yellow);
          delay(400);

          display_text(ENGLISH, LEFT, "TEST", Red);

          int chosen_test = get_hitted_sensor();
          if (chosen_test == 0) {
            test_digits();
          } else if (chosen_test == 1) {
            test_sqrs();
          } else if (chosen_test == 2) {
            test_sensors(LIGHT_AND_SHUT_ON_HIT);
          } else if (chosen_test == 3) {
            test_sensors(LIGHT_ON_HIT);
          }
        }
      }
    }
  }
}