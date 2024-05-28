#ifndef MENU_H
#define MENU_H

#include <stdint.h>
#include <stdbool.h>
#include "pin.h"
#include "btn.h"
#include "joy.h"
#include "lcd.h"
#include "globals.h"
#include "config.h"

#include "esp_log.h"

void menu_init();
void menu_tick();

#endif // MENU_H