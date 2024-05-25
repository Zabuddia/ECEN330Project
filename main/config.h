#ifndef CONFIG_H_
#define CONFIG_H_

#define CONFIG_GAME_TIMER_PERIOD 40.0E-3f

#define CONFIG_MAX_PLAYER_MISSILES 4
#define CONFIG_MAX_ENEMY_MISSILES  7
#define CONFIG_MAX_PLANE_MISSILES  1
#define CONFIG_MAX_TOTAL_MISSILES  \
  (CONFIG_MAX_ENEMY_MISSILES +     \
   CONFIG_MAX_PLAYER_MISSILES +    \
   CONFIG_MAX_PLANE_MISSILES)

// Speed of enemy missile (pixels/sec)
#define CONFIG_ENEMY_MISSILE_DISTANCE_PER_SECOND 35
#define CONFIG_ENEMY_MISSILE_DISTANCE_PER_TICK \
  (CONFIG_ENEMY_MISSILE_DISTANCE_PER_SECOND * CONFIG_GAME_TIMER_PERIOD)

// Speed of player missile (pixels/sec)
#define CONFIG_PLAYER_MISSILE_DISTANCE_PER_SECOND 350
#define CONFIG_PLAYER_MISSILE_DISTANCE_PER_TICK \
  (CONFIG_PLAYER_MISSILE_DISTANCE_PER_SECOND * CONFIG_GAME_TIMER_PERIOD)

// How fast explosion radius changes (pixels/sec)
#define CONFIG_EXPLOSION_RADIUS_CHANGE_PER_SECOND 30
#define CONFIG_EXPLOSION_RADIUS_CHANGE_PER_TICK \
  (CONFIG_EXPLOSION_RADIUS_CHANGE_PER_SECOND * CONFIG_GAME_TIMER_PERIOD)
#define CONFIG_EXPLOSION_MAX_RADIUS 25

// Speed of plane (pixels/sec)
#define CONFIG_PLANE_DISTANCE_PER_SECOND 40
#define CONFIG_PLANE_DISTANCE_PER_TICK \
  (CONFIG_PLANE_DISTANCE_PER_SECOND * CONFIG_GAME_TIMER_PERIOD)

// Plane off-screen time
#define CONFIG_PLANE_IDLE_TIME_SECONDS 4.0f
#define CONFIG_PLANE_IDLE_TIME_TICKS \
  ((uint32_t)(CONFIG_PLANE_IDLE_TIME_SECONDS / CONFIG_GAME_TIMER_PERIOD))

// Plane size
#define CONFIG_PLANE_WIDTH  20
#define CONFIG_PLANE_HEIGHT 10

// Colors
#define CONFIG_COLOR_BACKGROUND rgb565(0, 4, 16)
#define CONFIG_COLOR_TEXT_BACKGROUND rgb565(0, 4, 16)

#define CONFIG_COLOR_CURSOR WHITE
#define CONFIG_COLOR_STATUS WHITE

#define CONFIG_COLOR_ENEMY_MISSILE  RED
#define CONFIG_COLOR_PLAYER_MISSILE GREEN
#define CONFIG_COLOR_PLANE_MISSILE  BLUE

#define CONFIG_COLOR_PLANE WHITE

#include "lcd.h"
// Defined in main.c. Declared here so all modules can see it.
extern TFT_t dev; // Declare device handle for the display

#endif // CONFIG_H_