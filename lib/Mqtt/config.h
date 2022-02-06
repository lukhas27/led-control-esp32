// WiFi setup
#define WIFI_SSID "WG RiBuHa"
#define WIFI_PASSWORD "MaViSi92!"

// MQTT setup
#define MQTT_SERVER "192.168.0.169"
#define MQTT_PORT 1883

const char *clientId = "NodeMCU-PubSub";

// Topics
#define TOPIC_BALKON_LEDS_STATE "balkon/leds/state"
#define TOPIC_BALKON_LEDS_BRIGHTNESS "balkon/leds/brightness"
#define TOPIC_BALKON_LEDS_COLOR "balkon/leds/color"
#define TOPIC_BALKON_LEDS_MODE "balkon/leds/mode"
#define TOPIC_BALKON_LEDS_RANGE "balkon/leds/range"
#define TOPIC_BALKON_LEDS_SPEEDFACTOR "balkon/leds/speedfactor"
#define TOPIC_BALKON_LEDS_STATUS "balkon/leds/status"