#include "plane.h"

// Constants for the plane
#define TOP_QUARTER 4

// Struct for the plane
typedef struct {
    coord_t x;
    coord_t y;
    missile_t *missile;
    bool flying;
    bool exploding;
    int32_t state;
    coord_t fire_x;
} plane_t;

// All of the states for the plane state machine
static enum plane_SM_states {
    INITIALIZING,
    MOVING,
    SHOOTING,
    MOVING_AFTER_SHOOTING,
    EXPLODING,
    IDLE
};

static plane_t plane;

static uint64_t idle_ticks;

// Initialize the plane state machine. Pass a pointer to the missile
// that will be (re)launched by the plane. It will only have one missile.
void plane_init(missile_t *plane_missile) {
    plane.x = LCD_W;
    plane.y = LCD_H / TOP_QUARTER;
    plane.missile = plane_missile;
    plane.flying = false;
    plane.exploding = false;
    plane.state = INITIALIZING;
    plane.fire_x = rand() % LCD_W;
}

// Trigger the plane to explode.
void plane_explode(void) {
    plane.exploding = true;
}

// State machine tick function.
void plane_tick(void) {
    // Transitions
    switch (plane.state) {
        case INITIALIZING:
            plane.state = MOVING;
            break;
        case MOVING:
            // Checks if the plane has made it to where it will fire a missile or if the plane is exploding
            if (plane.x <= plane.fire_x) {
                plane.state = SHOOTING;
            } else if (plane.exploding) {
                plane.state = EXPLODING;
            }
            break;
        case SHOOTING:
            plane.state = MOVING_AFTER_SHOOTING;
            break;
        case MOVING_AFTER_SHOOTING:
            // Checks if the plane has reached the end of the screen or if it is exploding
            if (plane.x <= 0) {
                plane.state = IDLE;
            } else if (plane.exploding) {
                plane.state = EXPLODING;
            }
            break;
        case EXPLODING:
            plane.state = IDLE;
            break;
        case IDLE:
            // Checks if the plane has waited long enough to come back
            if (idle_ticks >= CONFIG_PLANE_IDLE_TIME_TICKS) {
                plane.state = INITIALIZING;
            }
            break;
    }

    // Actions
    switch (plane.state) {
        case INITIALIZING:
            idle_ticks = 0;
            plane.x = LCD_W;
            plane.exploding = false;
            plane.flying = true;
            plane.fire_x = rand() % LCD_W;
            break;
        case MOVING:
            plane.x -= CONFIG_PLANE_DISTANCE_PER_TICK;
            lcdFillArrow(&dev, plane.x, plane.y, plane.x - CONFIG_PLANE_WIDTH, plane.y, CONFIG_PLANE_HEIGHT, globals_get_plane_color());
            break;
        case SHOOTING:
            missile_init_plane(plane.missile, plane.x, plane.y);
            break;
        case MOVING_AFTER_SHOOTING:
            plane.x -= CONFIG_PLANE_DISTANCE_PER_TICK;
            lcdFillArrow(&dev, plane.x, plane.y, plane.x - CONFIG_PLANE_WIDTH, plane.y, CONFIG_PLANE_HEIGHT, globals_get_plane_color());
            break;
        case EXPLODING:
            break;
        case IDLE:
            plane.flying = false;
            idle_ticks++;
            break;
    }
}

// Return the current plane position through the pointers *x,*y.
void plane_get_pos(coord_t *x, coord_t *y) {
    *x = plane.x;
    *y = plane.y;
}

// Return whether the plane is flying.
bool plane_is_flying(void) {
    return plane.flying;
}