#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "btn.h"
#include "joy.h"
#include "lcd.h"
#include "pin.h"
#include "globals.h"
#include "bluetooth.h"

void controller_init();
void controller_tick();

#endif // CONTROL_H