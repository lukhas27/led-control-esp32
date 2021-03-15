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
#include <ESP8266WiFi.h>

#include <Adafruit_NeoPixel.h>
#include <PubSubClient.h>

#include "Button.h"
#include "Led.h"
#include "LedStripeModi.h"
#include "mqttData.h"


#define BUTTON_PIN          D6                  // Pin for Button

#define LEDS_PIN            D4                  // Pin for Led Stripe
#define NUMBER_LEDS         30                  // Number of LEDs in Led Stripe

/***************************************************
 * Declaration of Methods
 ***************************************************/
void callback(char* topic, byte* payload, unsigned int length);
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


/***************************************************
 * Implementation of MQTT topics
 ***************************************************/
const String topics[] = 
{
    TOPIC_BALKON_LEDS_STATE,
    TOPIC_BALKON_LEDS_BRIGHTNESS,
    TOPIC_BALKON_LEDS_COLOR,
    TOPIC_BALKON_LEDS_RANGE_MIN,
    TOPIC_BALKON_LEDS_RANGE_MAX
};

#define NUM_TOPICS       (sizeof(topics) / sizeof(topics[0]))


/***************************************************
 * Setup + Loop
 ***************************************************/
void setup()
{
    Serial.begin(115200);

    // Wifi setup
    setupWiFi();

    /* button.init();
    ledStripe.init(); */
}

void loop()
{
    // mqtt connection handle and loop call
    if (!mqttClient.connected()) {
      reconnect();
    }
    mqttClient.loop();


    /* // Handles
    handleButton();

    
    // Updates
    button.update();
    ledStripe.update(); */
}

/***************************************************
 * MQTT Methods
 ***************************************************/
// Callback
void callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("]:\t");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}


/***************************************************
 * WiFi
 ***************************************************/
void setupWiFi(){
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WLAN_SSID, WLAN_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect(){
    // Loop until we're reconnected
    while (!mqttClient.connected()) {
      Serial.print("Attempting MQTT connection...");
    
      // Attempt to connect
      if (mqttClient.connect(clientId)) {
        Serial.println("Client connected!");

        // resubscribe
        for (int i = 0; i<NUM_TOPICS; i++){
            mqttClient.subscribe(topics[i].c_str());
        }
      } 
      else {
        Serial.print("failed, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" try again in 5 seconds");

        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
}


/***************************************************
 * Button Methods
 ***************************************************/
void handleButton(){
    if (button.getPosEdge()){
        now = millis();
    }

    if (button.getState()){
        if ((millis() - now) > 2000){
            ledStripe.off();
            turnedOff = true;
        }
    }

    if (button.getNegEdge()){
        if (ledStripe.getState()){
            ledStripe.nextMode();
        }
        if (!turnedOff){
            ledStripe.on();
        }
        turnedOff = false;
    }
}

