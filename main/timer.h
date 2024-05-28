#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_log.h"
#include "watch.h"
#include "config.h"
#include "globals.h"
#include "pin.h"
#include "btn.h"

void timer_init();
void timer_tick();

#endif // TIMER_H