/**
 * Author:     lukhas
 * Date  :     02.03.2021
 */

/**
 * MQTT Subscriber Class
 * 
 * creates MQTT subscribing Client
 */

/***************************************************
 * includes
 ***************************************************/
#include "MQTTSubscriber.h"


/***************************************************
 * Implementation class objects
 ***************************************************/
WiFiClient wifiSubClient;
PubSubClient subClient(wifiSubClient);


/***************************************************
 * topics Array
 * 
 * -add all Topics you wanna subscribe to
 ***************************************************/
const String topics[] = 
{
    TOPIC_BALKON_LED,
    TOPIC_BALKON_TEMP,
    TOPIC_BEDROOM_LED
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

    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
}


/***************************************************
 * Constructor
 ***************************************************/
MQTTSubscriber::MQTTSubscriber(String clientId, uint8_t qos){
    this->clientId = clientId;
    this->qos = qos;
}

/***************************************************
 * Init + Update
 ***************************************************/
void MQTTSubscriber::init(){
    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    Serial.begin(115200);
    setupWiFi();
    subClient.setServer(MQTT_SERVER, 1883);
    subClient.setCallback(callback);
}

void MQTTSubscriber::update(){
    if (!subClient.connected()) {
      reconnect();
    }
    subClient.loop();
}


/***************************************************
 * Wifi
 ***************************************************/
void MQTTSubscriber::setupWiFi(){
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

void MQTTSubscriber::reconnect(){
    // Loop until we're reconnected
  while (!subClient.connected()) {
    Serial.print("Attempting MQTT Subscribe connection...");
   
    // Attempt to connect
    if (subClient.connect(clientId.c_str())) {
      Serial.println("Subsrciber connected!");

      // resubscribe
      for (int i = 0; i<NUM_TOPICS; i++){
          subClient.subscribe(topics[i].c_str(), qos);
      }
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(subClient.state());
      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}