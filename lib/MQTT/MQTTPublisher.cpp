/**
 * Author:     lukhas
 * Date  :     02.03.2021
 */

/**
 * MQTT Publisher Class
 * 
 * creates MQTT publishing Client
 */

/***************************************************
 * includes
 ***************************************************/ 
#include "MQTTPublisher.h"


/***************************************************
 * Implementation class objects
 ***************************************************/
WiFiClient wifiPubClient;
PubSubClient pubClient(wifiPubClient);
Led builtInLed(LED_BUILTIN);


/***************************************************
 * Constructor
 ***************************************************/
MQTTPublisher::MQTTPublisher(String clientId){
    this->clientId = clientId;
}


/***************************************************
 * Init + Update
 ***************************************************/
void MQTTPublisher::init(){
    Serial.begin(115200);
    builtInLed.init();
    setupWiFi();
    pubClient.setServer(MQTT_SERVER, 1883);
}

void MQTTPublisher::update(){
    if (!pubClient.connected()) {
      reconnect();
    }
    pubClient.loop();
}


/***************************************************
 * Wifi 
 ***************************************************/
void MQTTPublisher::setupWiFi(){
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

void MQTTPublisher::reconnect(){
    // Loop until we're reconnected
  while (!pubClient.connected()) {
    Serial.print("Attempting MQTT Publish connection...");
   
    // Attempt to connect
    if (pubClient.connect(clientId.c_str())) {
        Serial.println("Publisher connected!");      
    } else {
        Serial.print("failed, rc=");
        Serial.print(pubClient.state());
        Serial.println(" try again in 5 seconds");

        // Wait 5 seconds before retrying
        delay(5000);
    }
  }
}


/***************************************************
 * publish
 ***************************************************/
void MQTTPublisher::publish(String payload, String topic){
    boolean success = pubClient.publish(topic.c_str(), payload.c_str());

    if (success){
        Serial.print("Message published [");
        Serial.print(topic.c_str());
        Serial.print("]:\t");
        Serial.println(payload.c_str());
        builtInLed.on();
    } else {
        Serial.print("Publishing failed [");
        Serial.print(topic.c_str());
        Serial.println("]");
    }
    builtInLed.off();
}

void MQTTPublisher::publishBytes(byte *bytes, String topic){
    if (pubClient.publish(topic.c_str(), (const char *)bytes)){
        Serial.print("Message published [");
        Serial.print(topic.c_str());
        Serial.print("]:\t");
        Serial.println((char *)bytes);
    } else {
        Serial.print("Publishing failed [");
        Serial.print(topic.c_str());
        Serial.print("]");
    }
}
