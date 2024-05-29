#include "controller.h"

#define DCX_LOWER_THRESHOLD -200
#define DCX_UPPER_THRESHOLD 200

enum controller_states {
    CONTROLLER_STATE_WAITING,
    CONTROLLER_STATE_INIT,
    CONTROLLER_STATE_NONE,
    CONTROLLER_STATE_LEFT,
    CONTROLLER_STATE_RIGHT,
    CONTROLLER_STATE_UP,
    CONTROLLER_STATE_DOWN,
    CONTROLLER_STATE_CHANGE_SPEED
} controller_state;

static int32_t dcx, dcy;

static const char *TAG = "controller";

void controller_init() {
    controller_state = CONTROLLER_STATE_WAITING;
}

void controller_tick() {
    // Transitions
    switch (controller_state) {
        case CONTROLLER_STATE_WAITING:
            if (globals_get_in_controller()) {
                controller_state = CONTROLLER_STATE_INIT;
            }
            break;
        case CONTROLLER_STATE_INIT:
            controller_state = CONTROLLER_STATE_NONE;
            break;
        case CONTROLLER_STATE_NONE:
            if (dcx < DCX_LOWER_THRESHOLD) {
                controller_state = CONTROLLER_STATE_LEFT;
            } else if (dcx > DCX_UPPER_THRESHOLD) {
                controller_state = CONTROLLER_STATE_RIGHT;
            } else if (!pin_get_level(BTN_A)) {
                controller_state = CONTROLLER_STATE_UP;
            } else if (!pin_get_level(BTN_B)) {
                controller_state = CONTROLLER_STATE_DOWN;
            } else if (!pin_get_level(BTN_START)) {
                controller_state = CONTROLLER_STATE_CHANGE_SPEED;
            } else if (!globals_get_in_controller()) {
                controller_state = CONTROLLER_STATE_WAITING;
            }
            break;
        case CONTROLLER_STATE_LEFT:
            if (!(dcx < DCX_LOWER_THRESHOLD)) {
                controller_state = CONTROLLER_STATE_NONE;
            }
            break;
        case CONTROLLER_STATE_RIGHT:
            if (!(dcx > DCX_UPPER_THRESHOLD)) {
                controller_state = CONTROLLER_STATE_NONE;
            }
            break;
        case CONTROLLER_STATE_UP:
            if (pin_get_level(BTN_A)) {
                controller_state = CONTROLLER_STATE_NONE;
            }
            break;
        case CONTROLLER_STATE_DOWN:
            if (pin_get_level(BTN_B)) {
                controller_state = CONTROLLER_STATE_NONE;
            }
            break;
        case CONTROLLER_STATE_CHANGE_SPEED:
            if (pin_get_level(BTN_START)) {
                controller_state = CONTROLLER_STATE_NONE;
            }
            break;
    }
    // Actions
    switch (controller_state) {
        case CONTROLLER_STATE_WAITING:
            dcx = 0;
            dcy = 0;
            break;
        case CONTROLLER_STATE_INIT:
            dcx = 0;
            dcy = 0;
            joy_init();
            //bluetooth_init();
            joy_get_displacement(&dcx, &dcy);
            break;
        case CONTROLLER_STATE_NONE:
            //send_bluetooth_message((uint8_t *) "0", 1);
            joy_get_displacement(&dcx, &dcy);
            break;
        case CONTROLLER_STATE_LEFT:
            //send_bluetooth_message((uint8_t *) "4", 1);
            joy_get_displacement(&dcx, &dcy);
            break;
        case CONTROLLER_STATE_RIGHT:
            //send_bluetooth_message((uint8_t *) "2", 1);
            joy_get_displacement(&dcx, &dcy);
            break;
        case CONTROLLER_STATE_UP:
            //send_bluetooth_message((uint8_t *) "1", 1);
            joy_get_displacement(&dcx, &dcy);
            break;
        case CONTROLLER_STATE_DOWN:
            //send_bluetooth_message((uint8_t *) "3", 1);
            joy_get_displacement(&dcx, &dcy);
            break;
        case CONTROLLER_STATE_CHANGE_SPEED:
            //send_bluetooth_message((uint8_t *) "5", 1);
            joy_get_displacement(&dcx, &dcy);
            break;
    }
}