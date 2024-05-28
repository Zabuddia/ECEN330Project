#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdint.h>
#include <stdbool.h>
#include "pin.h"
#include "btn.h"
#include "globals.h"

void interface_init();
void interface_tick();

#endif // INTERFACE_H