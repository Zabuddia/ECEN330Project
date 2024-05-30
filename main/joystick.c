#include "joystick.h"

#define VOL_INC 20 // %
#define SAMPLE_RATE 48000 // Hz
#define VOLUME_DEFAULT (VOL_INC*3) // %
#define UP_PER 30 // Update period in ms
#define TIME_OUT 500 // ms

// Musical note frequencies
#define A3 220
#define A4 440
#define A5 880

#define OV 30 // Over scale by a margin
#define A2X(d) (((d)*(LCD_W/2+OV))/JOY_MAX_DISP+(LCD_W/2))
#define A2Y(d) (((d)*(LCD_H/2+OV))/JOY_MAX_DISP+(LCD_H/2))
#define CLIP(x,lo,hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

// sound support
// #include "audio/bcFire48k.c"
// #include "audio/gameBoyStartup48k.c"
// #include "audio/gameOver48k.c"
// #include "audio/gunEmpty48k.c"
// #include "audio/ouch48k.c"
// #include "audio/pacmanDeath48k.c"
#include "audio/powerUp48k.c"
// #include "audio/screamAndDie48k.c"

static int32_t dcx, dcy;
static uint32_t vol;
static tone_t tone;
static bool first_time;

static void cursor(int32_t x, int32_t y, uint16_t color) {
	int32_t s2 = CONFIG_CURSOR_SIZE >> 1; // size div 2
	lcdDrawHLine(&dev, x-s2, y,    CONFIG_CURSOR_SIZE, color);
	lcdDrawVLine(&dev, x,    y-s2, CONFIG_CURSOR_SIZE, color);
}

static void draw_status(void) {
	lcdDrawString(&dev, 0, 0, "Joystick", CONFIG_COLOR_TOP_LEFT_TEXT);
	char str[28];
	static char *ttab[] = {"sin", "squ", "tri", "saw"};
	sprintf(str, "x:%5ld y:%5ld v:%3lu t:%s", dcx, dcy, vol, ttab[tone]);
	lcdDrawString(&dev, 150, 0, str, CONFIG_COLOR_STATUS_BAR);
}

void joystick_init() {
	first_time = true;
	tone_set_volume(vol = VOLUME_DEFAULT); // Set the volume
	tone = SINE_T;
}

void joystick_tick() {
	if (!first_time && !globals_get_in_joystick()) {
		tone_deinit();
		first_time = true;
		return;
	}
	if (!globals_get_in_joystick()) {
		return;
	}
	if (first_time) {
		tone_init(SAMPLE_RATE); // Initialize tone and sample rate
		first_time = false;
		sound_start(powerUp48k, sizeof(powerUp48k), true);
	}
    static bool pressed = false;
    int32_t x, y;
    uint64_t btns;

    joy_get_displacement(&dcx, &dcy);
    btns = ~pin_get_in_reg() & BTN_MASK;
	if (!pressed && btns) {
		pressed = true;
		if (!pin_get_level(BTN_A))
			tone_start(tone, (dcy > 0) ? A4-(dcy*A3)/JOY_MAX_DISP : A4-(dcy*A4)/JOY_MAX_DISP);
		else if (!pin_get_level(BTN_SELECT))
			tone = (tone+1)%LAST_T;
		else if (!pin_get_level(BTN_START))
			tone_set_volume(vol = (vol <= MAX_VOL-VOL_INC) ? vol+VOL_INC : VOL_INC);
	} else if (pressed && !btns) {
		tone_stop();
		pressed = false;
	}
	draw_status();
	x = A2X(dcx); y = A2Y(dcy);
	x = CLIP(x, 0, LCD_W-1);
	y = CLIP(y, 0, LCD_H-1);
	cursor(x, y, CONFIG_COLOR_CURSOR);
}