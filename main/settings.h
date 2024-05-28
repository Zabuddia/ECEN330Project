#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>
#include <stdbool.h>
#include "pin.h"
#include "btn.h"
#include "lcd.h"
#include "globals.h"
#include "config.h"

void settings_init();
void settings_tick();

#endif // SETTINGS_H