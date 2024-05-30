#include "settings.h"

enum settings_states {
    STATE_WAITING,
    STATE_INIT,
    STATE_SETTINGS,
    STATE_SELECT,
    STATE_START,
    STATE_A,
    STATE_B,
    STATE_OPTION,
    STATE_WAIT_BTN_RELEASE
} settings_state;

static void draw_settings() {
    lcdDrawString(&dev, 0, 0, "Settings", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, 50, 40, "SELECT, START, B, and A change colors", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, 50, 60, "OPTION changes difficulty", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, 100, 90, "Enemy color", globals_get_enemy_color());
    lcdDrawString(&dev, 100, 110, "Player color", globals_get_player_color());
    lcdDrawString(&dev, 100, 130, "Plane color", globals_get_plane_color());
    lcdDrawString(&dev, 100, 150, "Plane missile color", globals_get_plane_missile_color());
    switch (globals_get_difficulty()) {
        case DIFFICULTY_EASY:
            lcdDrawString(&dev, 100, 180, "Difficulty: Easy", GREEN);
            break;
        case DIFFICULTY_MEDIUM:
            lcdDrawString(&dev, 100, 180, "Difficulty: Medium", ORANGE);
            break;
        case DIFFICULTY_HARD:
            lcdDrawString(&dev, 100, 180, "Difficulty: Hard", RED);
            break;
    }
}

void settings_init() {
    settings_state = STATE_WAITING;
}

void settings_tick() {
    // Transitions
    switch (settings_state) {
        case STATE_WAITING:
            if (globals_get_in_settings()) {
                settings_state = STATE_INIT;
            }
            break;
        case STATE_INIT:
            settings_state = STATE_WAIT_BTN_RELEASE;
            break;
        case STATE_SETTINGS:
            if (!pin_get_level(BTN_SELECT)) {
                settings_state = STATE_SELECT;
            } else if (!pin_get_level(BTN_START)) {
                settings_state = STATE_START;
            } else if (!pin_get_level(BTN_A)) {
                settings_state = STATE_A;
            } else if (!pin_get_level(BTN_B)) {
                settings_state = STATE_B;
            } else if (!pin_get_level(BTN_OPTION)) {
                settings_state = STATE_OPTION;
            }
            if (!globals_get_in_settings()) {
                settings_state = STATE_WAITING;
            }
            break;
        case STATE_SELECT:
            settings_state = STATE_WAIT_BTN_RELEASE;
            break;
        case STATE_START:
            settings_state = STATE_WAIT_BTN_RELEASE;
            break;
        case STATE_A:
            settings_state = STATE_WAIT_BTN_RELEASE;
            break;
        case STATE_B:
            settings_state = STATE_WAIT_BTN_RELEASE;
            break;
        case STATE_OPTION:
            settings_state = STATE_WAIT_BTN_RELEASE;
            break;
        case STATE_WAIT_BTN_RELEASE:
            if (pin_get_level(BTN_SELECT) && pin_get_level(BTN_START) && pin_get_level(BTN_A) && pin_get_level(BTN_B)) {
                settings_state = STATE_SETTINGS;
            }
            break;
    }

    // Actions
    switch (settings_state) {
        case STATE_WAITING:
            break;
        case STATE_INIT:
            break;
        case STATE_SETTINGS:
            draw_settings();
            break;
        case STATE_SELECT:
            globals_increment_enemy_color();
            draw_settings();
            break;
        case STATE_START:
            globals_increment_player_color();
            draw_settings();
            break;
        case STATE_A:
            globals_increment_plane_color();
            draw_settings();
            break;
        case STATE_B:
            globals_increment_plane_missile_color();
            draw_settings();
            break;
        case STATE_OPTION:
            globals_increment_difficulty();
            draw_settings();
            break;
        case STATE_WAIT_BTN_RELEASE:
            draw_settings();
            break;
    }
}