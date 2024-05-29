#include "missile.h"

// Constants for the missiles
#define TOP_QUARTER 4
#define LAUNCH_SITE_1 80
#define LAUNCH_SITE_1_THRESHOLD 120
#define LAUNCH_SITE_2 160
#define LAUNCH_SITE_2_THRESHOLD 200
#define LAUNCH_SITE_3 240

// All of the states for the missile state machine
static enum missile_SM_states {
    INITIALIZING,
    MOVING,
    EXPLODING_GROWING,
    EXPLODING_SHRINKING,
    IMPACTED,
    IDLE
};

// Helper function for initializing the missiles
void missile_init_helper(missile_t *missile) {
    missile->length = 0;
    missile->explode_me = false;
    int32_t temp_y = missile->y_dest - missile->y_origin;
    int32_t temp_x = missile->x_dest - missile->x_origin;
    temp_y *= temp_y;
    temp_x *= temp_x;
    missile->total_length = sqrtf(temp_y + temp_x);
    missile->x_current = missile->x_origin;
    missile->y_current = missile->y_origin;
    missile->length = 0;
    missile->explode_me = false;
    missile->radius = 0;
}

// Initializes an idle missile
void missile_init_idle(missile_t *missile) {
    missile->type = 0;
    missile->x_origin = 0;
    missile->y_origin = 0;
    missile->x_dest = 0;
    missile->y_dest = 0;
    missile->currentState = IDLE;
    missile_init_helper(missile);
}

// Initializes a player missile with a specific destination
void missile_init_player(missile_t *missile, coord_t x_dest, coord_t y_dest) {
    missile->type = MISSILE_TYPE_PLAYER;
    // Determines where the missile should be launched from
    if (x_dest <= LAUNCH_SITE_1_THRESHOLD) {
        missile->x_origin = LAUNCH_SITE_1;
    } else if (x_dest <= LAUNCH_SITE_2_THRESHOLD) {
        missile->x_origin = LAUNCH_SITE_2;
    } else {
        missile->x_origin = LAUNCH_SITE_3;
    }
    missile->y_origin = LCD_H;
    missile->x_dest = x_dest;
    missile->y_dest = y_dest;
    missile->currentState = INITIALIZING;
    missile_init_helper(missile);
}

// Initializes an enemy missile
void missile_init_enemy(missile_t *missile) {
    missile->type = MISSILE_TYPE_ENEMY;
    missile->x_origin = rand() % LCD_W;
    missile->y_origin = rand() % (LCD_H / TOP_QUARTER);
    missile->x_dest = rand() % LCD_W;
    missile->y_dest = LCD_H;
    missile->currentState = INITIALIZING;
    missile_init_helper(missile);
}

// Initializes a plane missile from where the plane is
void missile_init_plane(missile_t *missile, coord_t x_orig, coord_t y_orig) {
    missile->type = MISSILE_TYPE_PLANE;
    missile->x_origin = x_orig;
    missile->y_origin = y_orig;
    missile->x_dest = rand() % LCD_W;
    missile->y_dest = LCD_H;
    missile->currentState = INITIALIZING;
    missile_init_helper(missile);
}

// Used to indicate that a moving missile should be detonated. This occurs
// when an enemy or a plane missile is located within an explosion zone.
void missile_explode(missile_t *missile) {
    missile->explode_me = true;
}

// Returns the color of the misile based on the type of the missile
uint16_t determine_color(missile_t *missile) {
    // Switch statement to determine the color based on the type
    switch (missile->type) {
        case MISSILE_TYPE_ENEMY:
            return globals_get_enemy_color();
            break;
        case MISSILE_TYPE_PLANE:
            return globals_get_plane_missile_color();
            break;
        case MISSILE_TYPE_PLAYER:
            return globals_get_player_color();
            break;
    }
    return CONFIG_COLOR_ENEMY_MISSILE;
}

// The actions to be taken when in the moving state for a missile
void state_moving(missile_t *missile) {
    // Determines how far the missile moves based on the type of missile
    switch (missile->type) {
        case MISSILE_TYPE_ENEMY:
            missile->length += CONFIG_ENEMY_MISSILE_DISTANCE_PER_TICK;
            break;
        case MISSILE_TYPE_PLANE:
            missile->length += CONFIG_ENEMY_MISSILE_DISTANCE_PER_TICK;
            break;
        case MISSILE_TYPE_PLAYER:
            missile->length += CONFIG_PLAYER_MISSILE_DISTANCE_PER_TICK;
            break;
    }
    float fraction = missile->length / missile->total_length;
    missile->x_current = missile->x_origin + fraction * (missile->x_dest - missile->x_origin);
    missile->y_current = missile->y_origin + fraction * (missile->y_dest - missile->y_origin);
    lcdDrawLine(&dev, missile->x_origin, missile->y_origin, missile->x_current, missile->y_current, determine_color(missile));
}

// The actions to be taken when in the exploding growing state for a missile
void state_exploding_growing(missile_t *missile) {
    missile->radius += CONFIG_EXPLOSION_RADIUS_CHANGE_PER_TICK;
    lcdFillCircle(&dev, missile->x_current, missile->y_current, missile->radius, determine_color(missile));
}

// The actions to be taken when in the exploding shrinking state for a missile
void state_exploding_shrinking(missile_t *missile) {
    missile->radius -= CONFIG_EXPLOSION_RADIUS_CHANGE_PER_TICK;
    lcdFillCircle(&dev, missile->x_current, missile->y_current, missile->radius, determine_color(missile));
}

// Tick the state machine for a single missile.
void missile_tick(missile_t *missile) {
    // Transitions
    switch (missile->currentState) {
        case INITIALIZING:
            missile->currentState = MOVING;
            break;
        case MOVING:
            // Determines if the missile is exploding or what type of missile it is
            if (missile->explode_me == true) {
                missile->currentState = EXPLODING_GROWING;
            } else if ((missile->type == MISSILE_TYPE_ENEMY) || (missile->type == MISSILE_TYPE_PLANE)) {
                // Checks if the missile has reached the destination
                if (missile->y_current >= missile->y_dest) {
                    missile->currentState = IMPACTED;
                }
            } else {
                // Checks if the missile has reached the destination
                if (missile->y_current <= missile->y_dest) {
                    missile->currentState = EXPLODING_GROWING;
                }
            }
            break;
        case EXPLODING_GROWING:
            // Checks if the explosion has reached the max radius
            if (missile->radius >= CONFIG_EXPLOSION_MAX_RADIUS) {
                missile->currentState = EXPLODING_SHRINKING;
            }
            break;
        case EXPLODING_SHRINKING:
            // Checks if the explosion radius is 0
            if (missile->radius <= 0) {
                missile->currentState = IDLE;
            }
            break;
        case IMPACTED:
            missile->currentState = IDLE;
            break;
        case IDLE:
            break;
    }

    // Actions
    switch (missile->currentState) {
        case INITIALIZING:
            break;
        case MOVING:
            state_moving(missile);
            break;
        case EXPLODING_GROWING:
            state_exploding_growing(missile);
            break;
        case EXPLODING_SHRINKING:
            state_exploding_shrinking(missile);
            break;
        case IMPACTED:
            break;
        case IDLE:
            break;
    }
}

// Return the current missile position through the pointers *x,*y.
void missile_get_pos(missile_t *missile, coord_t *x, coord_t *y) {
    *x = missile->x_current;
    *y = missile->y_current;
}

// Return the missile type.
missile_type_t missile_get_type(missile_t *missile) {
    return missile->type;
}

// Return whether the given missile is moving.
bool missile_is_moving(missile_t *missile) {
    // Checks if the missile is currently moving
    if (missile->currentState == MOVING) {
        return true;
    } else {
        return false;
    }
}

// Return whether the given missile is exploding. If this missile
// is exploding, it can explode another intersecting missile.
bool missile_is_exploding(missile_t *missile) {
    // Checks if the missile is currently exploding
    if ((missile->currentState == EXPLODING_GROWING) || (missile->currentState == EXPLODING_SHRINKING)) {
        return true;
    } else {
        return false;
    }
}

// Return whether the given missile is idle.
bool missile_is_idle(missile_t *missile) {
    // Checks if the missile is idle
    if (missile->currentState == IDLE) {
        return true;
    } else {
        return false;
    }
}

// Return whether the given missile is impacted.
bool missile_is_impacted(missile_t *missile) {
    // Checks if the missile is impacted
    if (missile->currentState == IMPACTED) {
        return true;
    } else {
        return false;
    }
}

// Return whether an object (e.g., missile or plane) at the specified
// (x,y) position is colliding with the given missile. For a collision
// to occur, the missile needs to be exploding and the specified
// position needs to be within the explosion radius.
bool missile_is_colliding(missile_t *missile, coord_t x, coord_t y) {
    // Makes sure the missile is exploding
    if (!missile_is_exploding(missile)) {
        return false;
    } else {
        int32_t delta_y = abs(missile->y_current - y);
        int32_t delta_x = abs(missile->x_current - x);
        int32_t radius_squared = missile->radius * missile->radius;
        delta_y *= delta_y;
        delta_x *= delta_x;
        // Checks if the object is in the missile's radius
        if ((delta_y + delta_x) <= radius_squared) {
            return true;
        } else {
            return false;
        }
    }
}