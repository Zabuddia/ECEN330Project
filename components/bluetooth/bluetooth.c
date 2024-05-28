#include "bluetooth.h"

#define SPP_SERVER_NAME "SPP_SERVER"
#define DEVICE_NAME "ESP32test"
#define PEER_BD_ADDR {0x98, 0xDA, 0x50, 0x02, 0x63, 0x6B}

static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_NONE;
static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;
static esp_bd_addr_t peer_bd_addr = PEER_BD_ADDR;

static uint32_t spp_handle;

static void spp_callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    switch (event) {
        case ESP_SPP_INIT_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_INIT_EVT");
            break;
        case ESP_SPP_DISCOVERY_COMP_EVT:
            if (param->disc_comp.status == ESP_SPP_SUCCESS) {
                ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_DISCOVERY_COMP_EVT");
                ESP_ERROR_CHECK(esp_spp_connect(sec_mask, role_slave, param->disc_comp.scn[0], (uint8_t*)peer_bd_addr));
            } else {
                ESP_LOGE(SPP_SERVER_NAME, "Discovery failed with status: %d", param->disc_comp.status);
            }
            break;
        case ESP_SPP_OPEN_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_OPEN_EVT handle=%" PRIu32, (uint32_t)param->open.handle);
            spp_handle = param->open.handle;
            break;
        case ESP_SPP_CLOSE_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_CLOSE_EVT");
            spp_handle = 0;
            break;
        case ESP_SPP_START_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_START_EVT");
            break;
        case ESP_SPP_CL_INIT_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_CL_INIT_EVT");
            break;
        case ESP_SPP_DATA_IND_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_DATA_IND_EVT len=%" PRIu32 " handle=%" PRIu32,
                     (uint32_t)param->data_ind.len, (uint32_t)param->data_ind.handle);
            esp_log_buffer_hex("", param->data_ind.data, param->data_ind.len);
            break;
        case ESP_SPP_CONG_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_CONG_EVT");
            break;
        case ESP_SPP_WRITE_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_WRITE_EVT len=%" PRIu32 " cong=%d",
                     (uint32_t)param->write.len, param->write.cong);
            break;
        case ESP_SPP_SRV_OPEN_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_SPP_SRV_OPEN_EVT");
            break;
        default:
            ESP_LOGW(SPP_SERVER_NAME, "Unhandled event: %d", event);
            break;
    }
}

static void gap_callback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {
    switch (event) {
        case ESP_BT_GAP_AUTH_CMPL_EVT:
            if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
                ESP_LOGI(SPP_SERVER_NAME, "authentication success: %s", param->auth_cmpl.device_name);
                esp_log_buffer_hex(SPP_SERVER_NAME, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
            } else {
                ESP_LOGE(SPP_SERVER_NAME, "authentication failed, status:%d", param->auth_cmpl.stat);
            }
            break;
        case ESP_BT_GAP_PIN_REQ_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_BT_GAP_PIN_REQ_EVT min_16_digit:%d", param->pin_req.min_16_digit);
            if (param->pin_req.min_16_digit) {
                ESP_LOGI(SPP_SERVER_NAME, "Input pin code: 0000 0000 0000 0000");
                esp_bt_pin_code_t pin_code = {0};
                ESP_ERROR_CHECK(esp_bt_gap_pin_reply(param->pin_req.bda, true, 16, pin_code));
            } else {
                ESP_LOGI(SPP_SERVER_NAME, "Input pin code: 1234");
                esp_bt_pin_code_t pin_code = {'1', '2', '3', '4'};
                ESP_ERROR_CHECK(esp_bt_gap_pin_reply(param->pin_req.bda, true, 4, pin_code));
            }
            break;
        case ESP_BT_GAP_CFM_REQ_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %ld", param->cfm_req.num_val);
            ESP_ERROR_CHECK(esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true));
            break;
        case ESP_BT_GAP_KEY_NOTIF_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%ld", param->key_notif.passkey);
            break;
        case ESP_BT_GAP_KEY_REQ_EVT:
            ESP_LOGI(SPP_SERVER_NAME, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
            break;
        default:
            ESP_LOGI(SPP_SERVER_NAME, "event: %u", event);
            break;
    }
}

void bluetooth_init() {
    esp_err_t ret;

    // Initialize NVS
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize Bluetooth controller
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT));  // Enable Classic BT mode

    // Initialize Bluedroid stack
    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    // Register SPP callback
    ESP_ERROR_CHECK(esp_spp_register_callback(spp_callback));

    // Initialize SPP with configuration
    esp_spp_cfg_t spp_cfg = {
        .mode = ESP_SPP_MODE_CB,
    };
    ESP_ERROR_CHECK(esp_spp_enhanced_init(&spp_cfg));

    // Set device name
    ESP_ERROR_CHECK(esp_bt_dev_set_device_name(DEVICE_NAME));

    // Register GAP callback and set security parameters
    ESP_ERROR_CHECK(esp_bt_gap_register_callback(gap_callback));

    // Set discoverability and connectability
    ESP_ERROR_CHECK(esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE));

    // Set pin type to fixed and pin code to "1234"
    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_FIXED;
    esp_bt_pin_code_t pin_code = {'1', '2', '3', '4'};
    ESP_ERROR_CHECK(esp_bt_gap_set_pin(pin_type, 4, pin_code));

    // Connect to the HC-05 device
    ESP_LOGI(SPP_SERVER_NAME, "Connecting to device...");
    ESP_ERROR_CHECK(esp_spp_start_discovery(peer_bd_addr));
}

void send_bluetooth_message(uint8_t *data, uint32_t len) {
    if (spp_handle) {
        ESP_ERROR_CHECK(esp_spp_write(spp_handle, len, data));
    } else {
        ESP_LOGE(SPP_SERVER_NAME, "No spp_handle");
    }
}