#include "globals.h"

bool go_to_menu = false;
bool go_to_settings = false;
bool go_to_game = false;
bool go_to_controller = false;
bool go_to_timer = false;

bool in_menu = false;
bool in_game = false;
bool in_settings = false;
bool in_controller = false;
bool in_timer = false;

enum GAME_COLORS_PLAYER player_color = PLAYER_COLOR_GREEN;
enum GAME_COLORS_ENEMY enemy_color = ENEMY_COLOR_RED;
enum GAME_COLORS_PLANE plane_color = PLANE_COLOR_WHITE;
enum GAME_COLORS_PLANE_MISSILE plane_missile_color = PLANE_MISSILE_COLOR_BLUE;
enum GAME_DIFFICULTY difficulty = DIFFICULTY_EASY;

enum MENU_STATES global_menu_state = MENU_STATE_WAITING;

enum MENU_STATES globals_get_menu_state() {
    return global_menu_state;
}

void globals_set_menu_state(enum MENU_STATES state) {
    global_menu_state = state;
}

int32_t globals_get_player_color() {
    switch (player_color) {
        case PLAYER_COLOR_RED:
            return RED;
        case PLAYER_COLOR_GREEN:
            return GREEN;
        case PLAYER_COLOR_BLUE:
            return BLUE;
        case PLAYER_COLOR_YELLOW:
            return YELLOW;
        case PLAYER_COLOR_PURPLE:
            return PURPLE;
        case PLAYER_COLOR_CYAN:
            return CYAN;
        case PLAYER_COLOR_WHITE:
            return WHITE;
        case PLAYER_COLOR_GRAY:
            return GRAY;
    }
    return RED;
}

void globals_increment_player_color() {
    player_color = (player_color + 1) % 8;
}

void globals_increment_enemy_color() {
    enemy_color = (enemy_color + 1) % 8;
}

void globals_increment_plane_color() {
    plane_color = (plane_color + 1) % 8;
}

void globals_increment_plane_missile_color() {
    plane_missile_color = (plane_missile_color + 1) % 8;
}

int32_t globals_get_enemy_color() {
    switch (enemy_color) {
        case ENEMY_COLOR_RED:
            return RED;
        case ENEMY_COLOR_GREEN:
            return GREEN;
        case ENEMY_COLOR_BLUE:
            return BLUE;
        case ENEMY_COLOR_YELLOW:
            return YELLOW;
        case ENEMY_COLOR_PURPLE:
            return PURPLE;
        case ENEMY_COLOR_CYAN:
            return CYAN;
        case ENEMY_COLOR_WHITE:
            return WHITE;
        case ENEMY_COLOR_GRAY:
            return GRAY;
    }
    return RED;
}

int32_t globals_get_plane_color() {
    switch (plane_color) {
        case PLANE_COLOR_RED:
            return RED;
        case PLANE_COLOR_GREEN:
            return GREEN;
        case PLANE_COLOR_BLUE:
            return BLUE;
        case PLANE_COLOR_YELLOW:
            return YELLOW;
        case PLANE_COLOR_PURPLE:
            return PURPLE;
        case PLANE_COLOR_CYAN:
            return CYAN;
        case PLANE_COLOR_WHITE:
            return WHITE;
        case PLANE_COLOR_GRAY:
            return GRAY;
    }
    return RED;
}

int32_t globals_get_plane_missile_color() {
    switch (plane_missile_color) {
        case PLANE_MISSILE_COLOR_RED:
            return RED;
        case PLANE_MISSILE_COLOR_GREEN:
            return GREEN;
        case PLANE_MISSILE_COLOR_BLUE:
            return BLUE;
        case PLANE_MISSILE_COLOR_YELLOW:
            return YELLOW;
        case PLANE_MISSILE_COLOR_PURPLE:
            return PURPLE;
        case PLANE_MISSILE_COLOR_CYAN:
            return CYAN;
        case PLANE_MISSILE_COLOR_WHITE:
            return WHITE;
        case PLANE_MISSILE_COLOR_GRAY:
            return GRAY;
    }
    return RED;
}

int32_t globals_get_difficulty() {
    return difficulty;
}

void globals_increment_difficulty() {
    difficulty = (difficulty + 1) % 3;
}

bool globals_get_go_to_menu() {
    return go_to_menu;
}

bool globals_get_go_to_settings() {
    return go_to_settings;
}

bool globals_get_go_to_game() {
    return go_to_game;
}

bool globals_get_go_to_controller() {
    return go_to_controller;
}

bool globals_get_go_to_timer() {
    return go_to_timer;
}

void globals_set_go_to_menu(bool value) {
    go_to_menu = value;
}

void globals_set_go_to_settings(bool value) {
    go_to_settings = value;
}

void globals_set_go_to_game(bool value) {
    go_to_game = value;
}

void globals_set_go_to_controller(bool value) {
    go_to_controller = value;
}

void globals_set_go_to_timer(bool value) {
    go_to_timer = value;
}

bool globals_get_in_menu() {
    return in_menu;
}

bool globals_get_in_game() {
    return in_game;
}

bool globals_get_in_settings() {
    return in_settings;
}

bool globals_get_in_controller() {
    return in_controller;
}

bool globals_get_in_timer() {
    return in_timer;
}

void globals_set_in_menu(bool value) {
    in_menu = value;
}

void globals_set_in_game(bool value) {
    in_game = value;
}

void globals_set_in_settings(bool value) {
    in_settings = value;
}

void globals_set_in_controller(bool value) {
    in_controller = value;
}

void globals_set_in_timer(bool value) {
    in_timer = value;
}