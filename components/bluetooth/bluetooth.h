#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_bt_defs.h"
#include "esp_gap_bt_api.h"
#include "esp_spp_api.h"
#include "nvs_flash.h"
#include "esp_timer.h"

void bluetooth_init();

void send_bluetooth_message(uint8_t *data, uint32_t len);

#endif // BLUETOOTH_H