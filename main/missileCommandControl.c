
#include <stdio.h>
#include <stdlib.h> // rand

#include "config.h"
#include "lcd.h"
#include "cursor.h"
#include "pin.h"
#include "btn.h"
#include "missile.h"
#include "plane.h"
#include "missileCommandControl.h"

// M3: Define stats constants
#define STAT_LENGTH 20
#define IMPACTED_POSITION 160

// All missiles
missile_t missiles[CONFIG_MAX_TOTAL_MISSILES];

// Alias into missiles array
missile_t *enemy_missiles = missiles+0;
missile_t *player_missiles = missiles+CONFIG_MAX_ENEMY_MISSILES;
missile_t *plane_missile = missiles+CONFIG_MAX_ENEMY_MISSILES+
									CONFIG_MAX_PLAYER_MISSILES;

// M3: Declare stats variables
uint64_t shots;
uint64_t impacts;

// Global variables for cursor
int32_t cursor_x, cursor_y;

// Draw the cursor on the screen
void cursor(int32_t x, int32_t y, uint16_t color) {
	int32_t s2 = CONFIG_CURSOR_SIZE >> 1; // size div 2
	lcdDrawHLine(&dev, x-s2, y,    CONFIG_CURSOR_SIZE, color);
	lcdDrawVLine(&dev, x,    y-s2, CONFIG_CURSOR_SIZE, color);
}

// Initialize the game control logic.
// This function initializes all missiles, planes, stats, etc.
void gameControl_init(void) {
	cursor_init(CONFIG_PER_MS);
	// Initialize missiles
	for (uint32_t i = 0; i < CONFIG_MAX_ENEMY_MISSILES; i++)
		missile_init_enemy(enemy_missiles+i);
	for (uint32_t i = 0; i < CONFIG_MAX_PLAYER_MISSILES; i++)
		missile_init_idle(player_missiles+i);
	missile_init_idle(plane_missile);

	// M3: Initialize plane
	plane_init(plane_missile);
	// M3: Initialize stats
	shots = 0;
	impacts = 0;
}

// Update the game control logic.
// This function calls the missile & plane tick functions, reinitializes
// idle enemy missiles, handles button presses, fires player missiles,
// detects collisions, and updates statistics.
void gameControl_tick(void) {
	if (!globals_get_in_game()) return;
	// Tick missiles in one batch
	for (uint32_t i = 0; i < CONFIG_MAX_TOTAL_MISSILES; i++)
		missile_tick(missiles+i);

	// Reinitialize idle enemy missiles
	for (uint32_t i = 0; i < CONFIG_MAX_ENEMY_MISSILES; i++)
		if (missile_is_idle(enemy_missiles+i))
			missile_init_enemy(enemy_missiles+i);

	// M2: Check for button press. If so, launch a free player missile.
	static bool pressed = false;
	coord_t x, y;
	uint64_t btns;
	btns = ~pin_get_in_reg() & BTN_MISSILE_FIRE_MASK;
	// Checks to see if any buttons are pressed
	if (!pressed && btns) {
		pressed = true;
		cursor_get_pos(&x, &y);
		// Cycles through the player missiles
		for (uint32_t i = 0; i < CONFIG_MAX_PLAYER_MISSILES; i++)
			// Shoots a missile if there is one that is not idle
			if (missile_is_idle(player_missiles+i)) {
				missile_init_player(player_missiles+i, x, y);
				shots++;
				break;
			}
	} else if (pressed && !btns) {
		pressed = false;
	}

	// M2: Check for moving non-player missile collision with an explosion.
	// Cycles through the player missiles
	for (uint32_t i = 0; i < CONFIG_MAX_PLAYER_MISSILES; i++) {
		// Checks if the player missile is colliding with the plane missile
		if (missile_is_colliding(player_missiles+i, plane_missile->x_current, plane_missile->y_current)) {
				missile_explode(player_missiles+i);
				missile_explode(plane_missile);
			}
			// Cycles through the enemy missiles
		for (uint32_t j = 0; j < CONFIG_MAX_ENEMY_MISSILES; j++) {
			// Checks if the player missile is colliding with the enemy missile
			if (missile_is_colliding(player_missiles+i, (enemy_missiles+j)->x_current, (enemy_missiles+j)->y_current)) {
				missile_explode(player_missiles+i);
				missile_explode(enemy_missiles+j);
			}
		}
	}

	// M3: Count non-player impacted missiles
	if (missile_is_impacted(plane_missile)) impacts++;
	// Cycles thorugh all of the enemy missiles
	for (uint32_t i = 0; i < CONFIG_MAX_ENEMY_MISSILES; i++) {
		if (missile_is_impacted(enemy_missiles+i)) impacts++;
	}

	// M3: Tick plane & draw stats
	plane_tick();
	char shot[STAT_LENGTH];
	char impacted[STAT_LENGTH];
	sprintf(shot, "Shots: %lld", shots);
	sprintf(impacted, "Impacted: %lld", impacts);
	lcdDrawString(&dev, 0, 0, shot, CONFIG_COLOR_STATUS);
	lcdDrawString(&dev, IMPACTED_POSITION, 0, impacted, CONFIG_COLOR_STATUS);

	// M3: Check for flying plane collision with an explosion.
	coord_t x_plane, y_plane;
	plane_get_pos(&x_plane, &y_plane);
	// Cycles through all of the player missiles
	for (uint32_t i = 0; i < CONFIG_MAX_PLAYER_MISSILES; i++) {
		// Checks to see if the player missile is colliding with the plane
		if (missile_is_colliding(player_missiles+i, x_plane, y_plane)) {
			missile_explode(player_missiles+i);
			plane_explode();
		}
	}

	cursor_tick();
	cursor_get_pos(&cursor_x, &cursor_y);
	cursor(cursor_x, cursor_y, CONFIG_COLOR_CURSOR);
}