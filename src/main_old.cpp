/**
 * Author:     Lukas Haspel
 * Date  :     02.03.2021
 */

/**
 * LED Control
 *
 * Control LEDs via infrared (IR) sensor and WiFi
 */

/***************************************************
 * includes
 ***************************************************/
#include <Arduino.h>
#include <WiFi.h>

#include <Adafruit_NeoPixel.h>
#include <PubSubClient.h>

#include "Button.h"
#include "LedStripeModi.h"
#include "../lib/mqttData.h"

#define BUTTON_PIN 25 // Pin for Button

#define LEDS_PIN 12    // Pin for Led Stripe
#define NUMBER_LEDS 41 // Number of LEDs in Led Stripe

/***************************************************
 * Declaration of Methods
 ***************************************************/
void callback(char *topic, byte *payload, unsigned int length);
void publish(String payload, String topic);
void publishBytes(byte *bytes, String topic);
void setupWiFi();
void reconnect();
void handleButton();

/***************************************************
 * Implementation class objects
 ***************************************************/
Button button(BUTTON_PIN);
LedStripeModi ledStripe(NUMBER_LEDS, LEDS_PIN);
WiFiClient wifiClient;
PubSubClient mqttClient(MQTT_SERVER, MQTT_PORT, callback, wifiClient);

/***************************************************
 * Implementation of global variables
 ***************************************************/
bool turnedOff = false;
int now;
uint8_t halfRange = NUMBER_LEDS / 2;

/***************************************************
 * Implementation of static IP address
 ***************************************************/
/* IPAddress localIP(192, 168, 0, 158); // Set Static IP address
IPAddress gateway(192, 168, 0, 1);   // Set Gateway IP address
IPAddress subnet(255, 255, 255, 0);  // Set Subnet Mask */

/***************************************************
 * Implementation of MQTT topics
 ***************************************************/
const String topics[] =
    {
        TOPIC_BALKON_LEDS_STATE,
        TOPIC_BALKON_LEDS_BRIGHTNESS,
        TOPIC_BALKON_LEDS_COLOR,
        TOPIC_BALKON_LEDS_MODE,
        TOPIC_BALKON_LEDS_RANGE,
        TOPIC_BALKON_LEDS_SPEEDFACTOR,
        TOPIC_BALKON_LEDS_STATUS};

#define NUM_TOPICS (sizeof(topics) / sizeof(topics[0]))

/***************************************************
 * Setup + Loop
 ***************************************************/
void setup()
{
    Serial.begin(115200);

    // Wifi setup
    setupWiFi();

    // Inits
    //button.init();
    ledStripe.init();
}

void loop()
{
    // mqtt connection handle and loop call
    if (!mqttClient.connected())
    {
        reconnect();
    }
    mqttClient.loop();
    // Handles
    //handleButton();

    // Updates
    //button.update();
    ledStripe.update();
}

/***************************************************
 * MQTT Methods
 ***************************************************/
// Callback
void callback(char *topic, byte *payload, unsigned int length)
{
    // Print arrived Message with topic
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("]:\t");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // Buffer for payload
    char plBuffer[length + 1];
    strncpy(plBuffer, (char *)payload, length + 1);
    plBuffer[length] = '\0';

    // Control LED state
    if (strcmp(topic, TOPIC_BALKON_LEDS_STATE) == 0)
    {
        if (strcmp(plBuffer, "on") == 0)
        {
            ledStripe.on();
        }
        else
        {
            ledStripe.off();
        }
    }

    // Control LED brightness
    if (strcmp(topic, TOPIC_BALKON_LEDS_BRIGHTNESS) == 0)
    {
        int brightness = atoi(plBuffer);
        ledStripe.setBrightness(map(brightness, 0, 100, 0, 255));
    }

    // Control LED color
    if (strcmp(topic, TOPIC_BALKON_LEDS_COLOR) == 0)
    {
        char hexBuffer[length + 3];

        for (int i = 0; i < length + 3; i++)
        {
            hexBuffer[i + 2] = plBuffer[i];
        }
        hexBuffer[0] = '0';
        hexBuffer[1] = 'x';
        hexBuffer[length + 2] = '\0';
        uint32_t intBuffer = (uint32_t)strtol(hexBuffer, NULL, 16);
        ledStripe.setColor(intBuffer);
    }

    // Control LED modi
    if (strcmp(topic, TOPIC_BALKON_LEDS_MODE) == 0)
    {
        int mode = atoi(plBuffer);
        ledStripe.setMode(mode);
    }

    // Control LED range
    if (strcmp(topic, TOPIC_BALKON_LEDS_RANGE) == 0)
    {
        int range = atoi(plBuffer);
        ledStripe.setLedRangeMin(halfRange - range);
        if (NUMBER_LEDS % 2 == 0)
        {
            ledStripe.setLedRangeMax(halfRange + range - 1);
        }
        else
        {
            ledStripe.setLedRangeMax(halfRange + range);
        }
    }

    // Control LED speedfactor
    if (strcmp(topic, TOPIC_BALKON_LEDS_SPEEDFACTOR) == 0)
    {
        int speedfactor = atoi(plBuffer);
        ledStripe.setSpeedfactor(speedfactor);
    }

    // check status
    if (strcmp(topic, TOPIC_BALKON_LEDS_STATUS) == 0)
    {
        // publish actual state of LEDs
        if (ledStripe.getState())
        {
            publish("on", TOPIC_BALKON_LEDS_STATE);
        }
        else
        {
            publish("off", TOPIC_BALKON_LEDS_STATE);
        }

        // publish actual brightness of LEDs
        uint8_t brightness = map(ledStripe.getBrightness(), 0, 255, 0, 100);
        publish((String)brightness, TOPIC_BALKON_LEDS_BRIGHTNESS);

        // publish actual color of LEDs
        publish(ledStripe.getColorHexString(), TOPIC_BALKON_LEDS_COLOR);

        // publish actual mode of LEDs
        publish(String(ledStripe.getMode()), TOPIC_BALKON_LEDS_MODE);

        // publish actual range of LEDs
        if (NUMBER_LEDS % 2 == 0)
        {
            publish((String)(ledStripe.getRangeMax() - halfRange + 1), TOPIC_BALKON_LEDS_RANGE);
        }
        else
        {
            publish((String)(ledStripe.getRangeMax() - halfRange), TOPIC_BALKON_LEDS_RANGE);
        }

        // publish actual speedfactor of LEDs
        publish((String)ledStripe.getSpeedfactor(), TOPIC_BALKON_LEDS_SPEEDFACTOR);
    }
}

void publish(String payload, String topic)
{
    if (mqttClient.publish(topic.c_str(), payload.c_str()))
    {
        Serial.print("Message published [");
        Serial.print(topic.c_str());
        Serial.print("]:\t");
        Serial.println(payload.c_str());
    }
    else
    {
        Serial.print("Publishing failed [");
        Serial.print(topic.c_str());
        Serial.println("]");
    }
}

void publishBytes(byte *bytes, String topic)
{
    if (mqttClient.publish(topic.c_str(), (const char *)bytes))
    {
        Serial.print("Message published [");
        Serial.print(topic.c_str());
        Serial.print("]:\t");
        Serial.println((char *)bytes);
    }
    else
    {
        Serial.print("Publishing failed [");
        Serial.print(topic.c_str());
        Serial.print("]");
    }
}

/***************************************************
 * WiFi
 ***************************************************/
void setupWiFi()
{
    delay(10);

    /* // Configures static IP address
    if (!WiFi.config(localIP, gateway, subnet))
    {
        Serial.println("STA Failed to configure");
    } */

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(WLAN_SSID, WLAN_PASSWORD);

    int n = 0;

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting.. status: " + String(WiFi.status()));

        if (n == 40)
        {
            ESP.restart();
        }

        n++;
    }

    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect()
{
    // Loop until we're reconnected
    while (!mqttClient.connected())
    {
        Serial.print("Attempting MQTT connection...");

        // Attempt to connect
        if (mqttClient.connect(clientId))
        {
            Serial.println("Client connected!");

            // resubscribe
            for (int i = 0; i < NUM_TOPICS; i++)
            {
                mqttClient.subscribe(topics[i].c_str());
            }
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");

            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

/***************************************************
 * Methods
 ***************************************************/
void handleButton()
{
    if (button.getPosEdge())
    {
        now = millis();
    }

    if (button.getState())
    {
        if (!turnedOff)
        {
            if ((millis() - now) > 2000)
            {
                ledStripe.off();
                publish("off", TOPIC_BALKON_LEDS_STATE);
                turnedOff = true;
            }
        }
    }

    if (button.getNegEdge())
    {
        if (ledStripe.getState())
        {
            ledStripe.nextMode();
            publish(String(ledStripe.getMode()), TOPIC_BALKON_LEDS_MODE);
        }
        if (!turnedOff)
        {
            ledStripe.on();
            publish("on", TOPIC_BALKON_LEDS_STATE);
        }
        turnedOff = false;
    }
}