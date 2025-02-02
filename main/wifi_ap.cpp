/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_mac.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <nvs_flash.h>

#include <string_view>
#include <algorithm>

#include <lwip/err.h>
#include <lwip/sys.h>

/* The examples use WiFi configuration that you can set via project configuration menu.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
constexpr std::string_view EXAMPLE_ESP_WIFI_SSID =  "wifi-esp32";
// #define EXAMPLE_ESP_WIFI_PASS    "" // "wifi-esp32"
constexpr std::string_view EXAMPLE_ESP_WIFI_PASS = "wifi-esp32\0";
#define EXAMPLE_ESP_WIFI_CHANNEL  0
#define EXAMPLE_MAX_STA_CONN      10

static const char *TAG = "wifi softAP";

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        const char * mac = (char*)event->mac;
        ESP_LOGI(TAG, "AP Client connected %s, AID=%d", mac, event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        // ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d, reason=%d",
        //          MAC2STR(event->mac), event->aid, event->reason);
    }
}

void wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    auto wifi_config = wifi_config_t{};
    auto & ap = wifi_config.ap;
    std::copy(std::begin(EXAMPLE_ESP_WIFI_SSID), std::end(EXAMPLE_ESP_WIFI_SSID), std::begin(ap.ssid));
    ap.ssid_len = EXAMPLE_ESP_WIFI_SSID.size();
    ap.channel = EXAMPLE_ESP_WIFI_CHANNEL;
    ap.max_connection = EXAMPLE_MAX_STA_CONN;
    ap.authmode = WIFI_AUTH_WPA2_PSK,
    ap.pmf_cfg = {
            .required = false,
    };
    if (EXAMPLE_ESP_WIFI_PASS.size() == 0) {
        ap.authmode = WIFI_AUTH_OPEN;
    }
    else
    {
        ap.authmode = WIFI_AUTH_WPA2_PSK;
        std::copy(std::begin(EXAMPLE_ESP_WIFI_PASS), std::end(EXAMPLE_ESP_WIFI_PASS), std::begin(ap.password));
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             EXAMPLE_ESP_WIFI_SSID.data(), EXAMPLE_ESP_WIFI_PASS.data(), EXAMPLE_ESP_WIFI_CHANNEL);
}

extern "C" void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();

    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();
}
