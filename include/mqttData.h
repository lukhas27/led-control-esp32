// WiFi setup
#define WLAN_SSID                   "WLAN Haspel"
#define WLAN_PASSWORD               "Haspel59alp0209"

// MQTT setup
#define MQTT_SERVER                 "192.168.0.169"         
#define MQTT_PORT                   1883

const char *clientId = "NodeMCU-PubSub";

// Topics
#define TOPIC_BALKON_LEDS_STATE             "balkon/leds/state"
#define TOPIC_BALKON_LEDS_BRIGHTNESS        "balkon/leds/brightness"
#define TOPIC_BALKON_LEDS_COLOR             "balkon/leds/color"
#define TOPIC_BALKON_LEDS_RANGE_MIN         "balkon/leds/range/min"
#define TOPIC_BALKON_LEDS_RANGE_MAX         "balkon/leds/range/max"