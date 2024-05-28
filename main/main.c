#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/gptimer.h"
#include "driver/rtc_io.h"
#include "driver/uart.h"

#include "config.h"
#include "btn.h"
#include "lcd.h"
#include "cursor.h"
#include "joy.h"
#include "pin.h"
#include "missileCommandControl.h"
#include "interface.h"
#include "menu.h"
#include "settings.h"
#include "timer.h"
#include "controller.h"

#define RESOLUTION  1000000
#define ALARM_COUNT (RESOLUTION/20)

static const char* TAG = "main";

TFT_t dev;
gptimer_handle_t gptimer;
bool interrupt_flag;

// Callback function that the timer calls when the alarm is triggered. The parameters are not used and it doesn't matter what it returns
static bool timer_on_alarm_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx) {
	return (interrupt_flag = true);
}

void configure_and_start_gptimer() {
    // Configuring the timer to the default source and to count up and with 1Mhz resolution
	gptimer_config_t timer_config = {
		.clk_src = GPTIMER_CLK_SRC_DEFAULT,
		.direction = GPTIMER_COUNT_UP,
		.resolution_hz = RESOLUTION,
	};
    gptimer_new_timer(&timer_config, &gptimer);

	// Saying that the timer will do the callback function when the alarm is triggered
	gptimer_event_callbacks_t cbs = {
		.on_alarm = timer_on_alarm_cb,
	};
    gptimer_register_event_callbacks(gptimer, &cbs, NULL);

	// Configuring the alarm to trigger every 50ms
	gptimer_alarm_config_t alarm_config = {
	 	.reload_count = 0,
	 	.alarm_count = ALARM_COUNT,
		.flags.auto_reload_on_alarm = true,
	};
    gptimer_set_alarm_action(gptimer, &alarm_config);

    gptimer_enable(gptimer);

    gptimer_start(gptimer);
}

void app_main() {
    interrupt_flag = false;

    lcdInit(&dev);
    //lcdFrameEnable(&dev);
    lcdFillScreen(&dev, CONFIG_COLOR_BACKGROUND);
    lcdSetFontBackground(&dev, CONFIG_COLOR_TEXT_BACKGROUND);

    // Configure I/O pins for buttons
	pin_reset(BTN_A);
	pin_input(BTN_A, true);
	pin_reset(BTN_B);
	pin_input(BTN_B, true);
	pin_reset(BTN_MENU);
	pin_input(BTN_MENU, true);
	pin_reset(BTN_OPTION);
	pin_input(BTN_OPTION, true);
	pin_reset(BTN_SELECT);
	pin_input(BTN_SELECT, true);
	pin_reset(BTN_START);
	pin_input(BTN_START, true);

    configure_and_start_gptimer();

    interface_init();
    menu_init();
    settings_init();
    gameControl_init();
    timer_init();
    controller_init();


    while (1) {
        while (!interrupt_flag) ;
        interrupt_flag = false;
        lcdFillScreen(&dev, CONFIG_COLOR_BACKGROUND);
        interface_tick();
        menu_tick();
        settings_tick();
        gameControl_tick();
        timer_tick();
        controller_tick();
        //lcdWriteFrame(&dev);
    }
}