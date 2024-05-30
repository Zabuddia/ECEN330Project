#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>
#include "lcd.h"

extern bool in_menu;
extern bool in_game;
extern bool in_settings;
extern bool in_controller;
extern bool in_timer;
extern bool in_joystick;

enum GAME_COLORS_PLAYER {
    PLAYER_COLOR_RED,
    PLAYER_COLOR_GREEN,
    PLAYER_COLOR_BLUE,
    PLAYER_COLOR_YELLOW,
    PLAYER_COLOR_PURPLE,
    PLAYER_COLOR_CYAN,
    PLAYER_COLOR_WHITE,
    PLAYER_COLOR_GRAY
};
extern enum GAME_COLORS_PLAYER player_color;

enum GAME_COLORS_ENEMY {
    ENEMY_COLOR_RED,
    ENEMY_COLOR_GREEN,
    ENEMY_COLOR_BLUE,
    ENEMY_COLOR_YELLOW,
    ENEMY_COLOR_PURPLE,
    ENEMY_COLOR_CYAN,
    ENEMY_COLOR_WHITE,
    ENEMY_COLOR_GRAY
};
extern enum GAME_COLORS_ENEMY enemy_color;

enum GAME_COLORS_PLANE {
    PLANE_COLOR_RED,
    PLANE_COLOR_GREEN,
    PLANE_COLOR_BLUE,
    PLANE_COLOR_YELLOW,
    PLANE_COLOR_PURPLE,
    PLANE_COLOR_CYAN,
    PLANE_COLOR_WHITE,
    PLANE_COLOR_GRAY
};
extern enum GAME_COLORS_PLANE plane_color;

enum GAME_COLORS_PLANE_MISSILE {
    PLANE_MISSILE_COLOR_RED,
    PLANE_MISSILE_COLOR_GREEN,
    PLANE_MISSILE_COLOR_BLUE,
    PLANE_MISSILE_COLOR_YELLOW,
    PLANE_MISSILE_COLOR_PURPLE,
    PLANE_MISSILE_COLOR_CYAN,
    PLANE_MISSILE_COLOR_WHITE,
    PLANE_MISSILE_COLOR_GRAY
};
extern enum GAME_COLORS_PLANE_MISSILE plane_missile_color;

enum GAME_DIFFICULTY {
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD
};
extern enum GAME_DIFFICULTY difficulty;

enum MENU_STATES {
    MENU_STATE_WAITING,
    MENU_STATE_INIT,
    MENU_STATE_GAME_SELECTED,
    MENU_STATE_SETTINGS_SELECTED,
    MENU_STATE_CONTROLLER_SELECTED,
    MENU_STATE_TIMER_SELECTED,
    MENU_STATE_JOYSTICK_SELECTED
};
extern enum MENU_STATES global_menu_state;

void globals_set_menu_state(enum MENU_STATES state);
enum MENU_STATES globals_get_menu_state();

int32_t globals_get_player_color();
void globals_increment_player_color();
void globals_increment_enemy_color();
void globals_increment_plane_color();
void globals_increment_plane_missile_color();
int32_t globals_get_enemy_color();
int32_t globals_get_plane_color();
int32_t globals_get_plane_missile_color();
int32_t globals_get_difficulty();
void globals_increment_difficulty();

bool globals_get_in_menu();
bool globals_get_in_game();
bool globals_get_in_settings();
bool globals_get_in_controller();
bool globals_get_in_timer();
bool globals_get_in_joystick();
void globals_set_in_menu(bool value);
void globals_set_in_game(bool value);
void globals_set_in_settings(bool value);
void globals_set_in_controller(bool value);
void globals_set_in_timer(bool value);
void globals_set_in_joystick(bool value);

#endif // GLOBALS_H