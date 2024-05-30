#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "lcd.h"
#include "joy.h"
#include "tone.h"
#include "btn.h"
#include "config.h"
#include "pin.h"
#include "globals.h"

void joystick_init();
void joystick_tick();

#endif // JOYSTICK_H