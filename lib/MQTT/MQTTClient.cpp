/**
 * Author:     lukhas
 * Date  :     02.03.2021
 */

/**
 * MQTT Client Class
 * 
 * creates MQTT Client for publishing and subscribing
 */

/***************************************************
 * includes
 ***************************************************/
#include "MQTTClient.h"


/***************************************************
 * Implementation class objects
 ***************************************************/
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);


/***************************************************
 * topics Array
 * 
 * -add all Topics you wanna subscribe to
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
 * Callback
 ***************************************************/
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
 * Constructor
 ***************************************************/
MQTTClient::MQTTClient(String clientId, uint8_t qos){
    this->clientId = clientId;
    this->qos = qos;
}

/***************************************************
 * Init + Update
 ***************************************************/
void MQTTClient::init(){
    Serial.begin(115200);
    setupWiFi();
    mqttClient.setServer(MQTT_SERVER, 1883);
    mqttClient.setCallback(callback);
}

void MQTTClient::update(){
    if (!mqttClient.connected()) {
      reconnect();
    }
    mqttClient.loop();
}


/***************************************************
 * Wifi
 ***************************************************/
void MQTTClient::setupWiFi(){
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

void MQTTClient::reconnect(){
    // Loop until we're reconnected
    while (!mqttClient.connected()) {
      Serial.print("Attempting MQTT Subscribe connection...");
    
      // Attempt to connect
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Subsrciber connected!");

        // resubscribe
        for (int i = 0; i<NUM_TOPICS; i++){
            mqttClient.subscribe(topics[i].c_str(), qos);
        }
        
      } else {
        Serial.print("failed, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" try again in 5 seconds");

        // Wait 5 seconds before retrying
        delay(5000);
      }
  }
}