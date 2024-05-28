#include "settings.h"

enum settings_states {
    STATE_WAITING,
    STATE_INIT,
    STATE_SETTINGS,
    STATE_SELECT,
    STATE_START,
    STATE_A,
    STATE_B,
    STATE_WAIT_BTN_RELEASE
} settings_state;

static void draw_settings() {
    lcdDrawString(&dev, 0, 0, "Settings", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, 80, 50, "SELECT, START, A, and B change colors", CONFIG_COLOR_TOP_LEFT_TEXT);
    lcdDrawString(&dev, 100, 80, "Enemy color", globals_get_enemy_color());
    lcdDrawString(&dev, 100, 100, "Player color", globals_get_player_color());
    lcdDrawString(&dev, 100, 120, "Plane color", globals_get_plane_color());
    lcdDrawString(&dev, 100, 140, "Plane missile color", globals_get_plane_missile_color());
}

void settings_init() {
    settings_state = STATE_INIT;
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
            break;
        case STATE_START:
            globals_increment_player_color();
            break;
        case STATE_A:
            globals_increment_plane_color();
            break;
        case STATE_B:
            globals_increment_plane_missile_color();
            break;
        case STATE_WAIT_BTN_RELEASE:
            draw_settings();
            break;
    }
}