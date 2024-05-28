#include "timer.h"

#define TICKS_PER_TICK 5

volatile bool running;
static uint32_t timer_ticks;

static const char* TAG = "timer";

void timer_init() {
    running = false;
    timer_ticks = 0;
}

void timer_tick() {
    if (!globals_get_in_timer()) {
        return;
    }

    bool button_a_pressed = !pin_get_level(BTN_A);
    bool button_b_pressed = !pin_get_level(BTN_B);
    bool button_start_pressed = !pin_get_level(BTN_START);

    //If button A is pressed, set running to true. If button B is pressed, set running to false. If START is pressed, reset the timer and set running to false
	if (button_a_pressed) {
		running = true;
	} else if (button_b_pressed) {
		running = false;
	} else if (button_start_pressed) {
		running = false;
		timer_ticks = 0;
	}
    //If running is true, incrememt timer_ticks
	if (running) timer_ticks += TICKS_PER_TICK;
    watch_update(&dev, timer_ticks);
}