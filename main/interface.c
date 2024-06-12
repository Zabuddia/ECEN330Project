#include "interface.h"

enum interface_states {
    STATE_MAIN_MENU,
    STATE_RESET,
    STATE_SETTINGS,
    STATE_GAME,
    STATE_CONTROLLER,
    STATE_TIMER,
    STATE_JOYSTICK,
    STATE_CUBE
} interface_state;

static void menu_transition() {
    switch (globals_get_menu_state()) {
        case MENU_STATE_WAITING:
            break;
        case MENU_STATE_INIT:
            break;
        case MENU_STATE_GAME_SELECTED:
            if (!pin_get_level(BTN_SELECT)) {
                interface_state = STATE_GAME;
            }
            break;
        case MENU_STATE_SETTINGS_SELECTED:
            if (!pin_get_level(BTN_SELECT)) {
                interface_state = STATE_SETTINGS;
            }
            break;
        case MENU_STATE_CONTROLLER_SELECTED:
            if (!pin_get_level(BTN_SELECT)) {
                interface_state = STATE_CONTROLLER;
            }
            break;
        case MENU_STATE_TIMER_SELECTED:
            if (!pin_get_level(BTN_SELECT)) {
                interface_state = STATE_TIMER;
            }
            break;
        case MENU_STATE_JOYSTICK_SELECTED:
            if (!pin_get_level(BTN_SELECT)) {
                interface_state = STATE_JOYSTICK;
            }
            break;
        case MENU_STATE_CUBE_SELECTED:
            if (!pin_get_level(BTN_SELECT)) {
                interface_state = STATE_CUBE;
            }
            break;
    }
}

void interface_init() {
    interface_state = STATE_MAIN_MENU;
}

void interface_tick() {
    // Transitions
    switch (interface_state) {
        case STATE_MAIN_MENU:
            menu_transition();
            break;
        case STATE_RESET:
            break;
        case STATE_SETTINGS:
            if (!pin_get_level(BTN_MENU)) {
                interface_state = STATE_MAIN_MENU;
            }
            break;
        case STATE_GAME:
            if (!pin_get_level(BTN_MENU)) {
                interface_state = STATE_MAIN_MENU;
            }
            break;
        case STATE_CONTROLLER:
            if (!pin_get_level(BTN_MENU)) {
                interface_state = STATE_MAIN_MENU;
            }
            break;
        case STATE_TIMER:
            if (!pin_get_level(BTN_MENU)) {
                interface_state = STATE_MAIN_MENU;
            }
            break;
        case STATE_JOYSTICK:
            if (!pin_get_level(BTN_MENU)) {
                interface_state = STATE_MAIN_MENU;
            }
            break;
        case STATE_CUBE:
            if (!pin_get_level(BTN_MENU)) {
                interface_state = STATE_MAIN_MENU;
            }
            break;
    }

    // Actions
    switch (interface_state) {
        case STATE_MAIN_MENU:
            globals_set_in_menu(true);
            globals_set_in_settings(false);
            globals_set_in_game(false);
            globals_set_in_controller(false);
            globals_set_in_timer(false);
            globals_set_in_joystick(false);
            globals_set_in_cube(false);
            break;
        case STATE_RESET:
            break;
        case STATE_SETTINGS:
            globals_set_in_settings(true);
            globals_set_in_menu(false);
            globals_set_in_game(false);
            globals_set_in_controller(false);
            globals_set_in_timer(false);
            globals_set_in_joystick(false);
            globals_set_in_cube(false);
            break;
        case STATE_GAME:
            globals_set_in_game(true);
            globals_set_in_menu(false);
            globals_set_in_settings(false);
            globals_set_in_controller(false);
            globals_set_in_timer(false);
            globals_set_in_joystick(false);
            globals_set_in_cube(false);
            break;
        case STATE_CONTROLLER:
            globals_set_in_controller(true);
            globals_set_in_menu(false);
            globals_set_in_settings(false);
            globals_set_in_game(false);
            globals_set_in_timer(false);
            globals_set_in_joystick(false);
            globals_set_in_cube(false);
            break;
        case STATE_TIMER:
            globals_set_in_timer(true);
            globals_set_in_menu(false);
            globals_set_in_settings(false);
            globals_set_in_game(false);
            globals_set_in_controller(false);
            globals_set_in_joystick(false);
            globals_set_in_cube(false);
            break;
        case STATE_JOYSTICK:
            globals_set_in_joystick(true);
            globals_set_in_menu(false);
            globals_set_in_settings(false);
            globals_set_in_game(false);
            globals_set_in_controller(false);
            globals_set_in_timer(false);
            globals_set_in_cube(false);
            break;
        case STATE_CUBE:
            globals_set_in_cube(true);
            globals_set_in_menu(false);
            globals_set_in_settings(false);
            globals_set_in_game(false);
            globals_set_in_controller(false);
            globals_set_in_timer(false);
            globals_set_in_joystick(false);
            break;
    }
}