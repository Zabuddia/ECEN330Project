#include "menu.h"

#define DCY_LOWER_THRESHOLD -200
#define DCY_UPPER_THRESHOLD 200
#define NUM_TICKS 5

#define GAME_X 150
#define GAME_Y 50
#define SETTINGS_X 150
#define SETTINGS_Y 100
#define CONTROLLER_X 150
#define CONTROLLER_Y 150
#define TIMER_X 150
#define TIMER_Y 200

// #define GAME_RECTANGLE_LOWER_X (GAME_X - 10)
// #define GAME_RECTANGLE_LOWER_Y (GAME_Y - 5)
// #define GAME_RECTANGLE_UPPER_X (GAME_X + 30)
// #define GAME_RECTANGLE_UPPER_Y (GAME_Y + 10)

// #define SETTINGS_RECTANGLE_LOWER_X (SETTINGS_X - 10)
// #define SETTINGS_RECTANGLE_LOWER_Y (SETTINGS_Y - 5)
// #define SETTINGS_RECTANGLE_UPPER_X (SETTINGS_X + 60)
// #define SETTINGS_RECTANGLE_UPPER_Y (SETTINGS_Y + 10)

// #define CONTROLLER_RECTANGLE_LOWER_X (CONTROLLER_X - 10)
// #define CONTROLLER_RECTANGLE_LOWER_Y (CONTROLLER_Y - 5)
// #define CONTROLLER_RECTANGLE_UPPER_X (CONTROLLER_X + 70)
// #define CONTROLLER_RECTANGLE_UPPER_Y (CONTROLLER_Y + 10)

// #define TIMER_RECTANGLE_LOWER_X (TIMER_X - 10)
// #define TIMER_RECTANGLE_LOWER_Y (TIMER_Y - 5)
// #define TIMER_RECTANGLE_UPPER_X (TIMER_X + 40)
// #define TIMER_RECTANGLE_UPPER_Y (TIMER_Y + 10)

enum menu_states {
    STATE_WAITING,
    STATE_INIT,
    STATE_GAME_SELECTED,
    STATE_SETTINGS_SELECTED,
    STATE_CONTROLLER_SELECTED,
    STATE_TIMER_SELECTED
} menu_state;

static int32_t dcx, dcy;

static uint32_t tick_counter;
static bool hold;

static const char *TAG = "menu";

static void draw_menu_game() {
    lcdDrawString(&dev, 0, 0, "Main Menu", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdSetFontBackground(&dev, CONFIG_COLOR_SELECT_TEXT_BACKGROUND);
    lcdDrawString(&dev, GAME_X, GAME_Y, "Game", CONFIG_COLOR_SELECT_TEXT);
    lcdSetFontBackground(&dev, CONFIG_COLOR_TEXT_BACKGROUND);
    lcdDrawString(&dev, SETTINGS_X, SETTINGS_Y, "Settings", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, CONTROLLER_X, CONTROLLER_Y, "Controller", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, TIMER_X, TIMER_Y, "Timer", CONFIG_COLOR_TOP_LEFT_TEXT);
}

static void draw_menu_settings() {
    lcdDrawString(&dev, 0, 0, "Main Menu", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, GAME_X, GAME_Y, "Game", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdSetFontBackground(&dev, CONFIG_COLOR_SELECT_TEXT_BACKGROUND);
    lcdDrawString(&dev, SETTINGS_X, SETTINGS_Y, "Settings", CONFIG_COLOR_SELECT_TEXT);
    lcdSetFontBackground(&dev, CONFIG_COLOR_TEXT_BACKGROUND);
    lcdDrawString(&dev, CONTROLLER_X, CONTROLLER_Y, "Controller", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, TIMER_X, TIMER_Y, "Timer", CONFIG_COLOR_TOP_LEFT_TEXT);
}

static void draw_menu_controller() {
    lcdDrawString(&dev, 0, 0, "Main Menu", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, GAME_X, GAME_Y, "Game", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, SETTINGS_X, SETTINGS_Y, "Settings", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdSetFontBackground(&dev, CONFIG_COLOR_SELECT_TEXT_BACKGROUND);
    lcdDrawString(&dev, CONTROLLER_X, CONTROLLER_Y, "Controller", CONFIG_COLOR_SELECT_TEXT);
    lcdSetFontBackground(&dev, CONFIG_COLOR_TEXT_BACKGROUND);
    lcdDrawString(&dev, TIMER_X, TIMER_Y, "Timer", CONFIG_COLOR_TOP_LEFT_TEXT);
}

static void draw_menu_timer() {
    lcdDrawString(&dev, 0, 0, "Main Menu", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, GAME_X, GAME_Y, "Game", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, SETTINGS_X, SETTINGS_Y, "Settings", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, CONTROLLER_X, CONTROLLER_Y, "Controller", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdSetFontBackground(&dev, CONFIG_COLOR_SELECT_TEXT_BACKGROUND);
    lcdDrawString(&dev, TIMER_X, TIMER_Y, "Timer", CONFIG_COLOR_SELECT_TEXT);
    lcdSetFontBackground(&dev, CONFIG_COLOR_TEXT_BACKGROUND);
}

void menu_init() {
    menu_state = STATE_WAITING;
    tick_counter = 0;
    hold = false;
    dcx = 0;
    dcy = 0;
}

void menu_tick() {
    // Transitions
    switch (menu_state) {
        case STATE_WAITING:
            if (globals_get_in_menu()) {
                menu_state = STATE_INIT;
            }
            break;
        case STATE_INIT:
            menu_state = STATE_GAME_SELECTED;
            break;
        case STATE_GAME_SELECTED:
            if (hold && tick_counter > NUM_TICKS) {
                if (dcy < DCY_LOWER_THRESHOLD) {
                    menu_state = STATE_TIMER_SELECTED;
                } else if (dcy > DCY_UPPER_THRESHOLD) {
                    menu_state = STATE_SETTINGS_SELECTED;
                }
                tick_counter = 0;
            }
            if (!globals_get_in_menu()) {
                menu_state = STATE_WAITING;
            }
            break;
        case STATE_SETTINGS_SELECTED:
            if (hold && tick_counter > NUM_TICKS) {
                if (dcy < DCY_LOWER_THRESHOLD) {
                    menu_state = STATE_GAME_SELECTED;
                } else if (dcy > DCY_UPPER_THRESHOLD) {
                    menu_state = STATE_CONTROLLER_SELECTED;
                }
                tick_counter = 0;
            }
            if (!globals_get_in_menu()) {
                menu_state = STATE_WAITING;
            }
            break;
        case STATE_CONTROLLER_SELECTED:
            if (hold && tick_counter > NUM_TICKS) {
                if (dcy < DCY_LOWER_THRESHOLD) {
                    menu_state = STATE_SETTINGS_SELECTED;
                } else if (dcy > DCY_UPPER_THRESHOLD) {
                    menu_state = STATE_TIMER_SELECTED;
                }
                tick_counter = 0;
            }
            if (!globals_get_in_menu()) {
                menu_state = STATE_WAITING;
            }
            break;
        case STATE_TIMER_SELECTED:
            if (hold && tick_counter > NUM_TICKS) {
                if (dcy < DCY_LOWER_THRESHOLD) {
                    menu_state = STATE_CONTROLLER_SELECTED;
                } else if (dcy > DCY_UPPER_THRESHOLD) {
                    menu_state = STATE_GAME_SELECTED;
                }
                tick_counter = 0;
            }
            if (!globals_get_in_menu()) {
                menu_state = STATE_WAITING;
            }
            break;
    }

    // Actions
    switch (menu_state) {
        case STATE_WAITING:
            globals_set_menu_state(MENU_STATE_WAITING);
            dcx = 0;
            dcy = 0;
            break;
        case STATE_INIT:
            globals_set_menu_state(MENU_STATE_INIT);
            tick_counter = 0;
            hold = false;
            dcx = 0;
            dcy = 0;
            joy_init();
            joy_get_displacement(&dcx, &dcy);
            break;
        case STATE_GAME_SELECTED:
            globals_set_menu_state(MENU_STATE_GAME_SELECTED);
            draw_menu_game();
            joy_get_displacement(&dcx, &dcy);
            tick_counter++;
            break;
        case STATE_SETTINGS_SELECTED:
            globals_set_menu_state(MENU_STATE_SETTINGS_SELECTED);
            draw_menu_settings();
            joy_get_displacement(&dcx, &dcy);
            tick_counter++;
            break;
        case STATE_CONTROLLER_SELECTED:
            globals_set_menu_state(MENU_STATE_CONTROLLER_SELECTED);
            draw_menu_controller();
            joy_get_displacement(&dcx, &dcy);
            tick_counter++;
            break;
        case STATE_TIMER_SELECTED:
            globals_set_menu_state(MENU_STATE_TIMER_SELECTED);
            draw_menu_timer();
            joy_get_displacement(&dcx, &dcy);
            tick_counter++;
            break;
    }

    if (dcy <  DCY_LOWER_THRESHOLD || dcy >  DCY_UPPER_THRESHOLD) {
        hold = true;
    } else {
        hold = false;
    }
}