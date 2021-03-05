#ifndef MQTTCLIENT_h
#define MQTTCLIENT_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "mqttData.h"

class MQTTSubscriber 
{
    private:
        String clientId;
        uint8_t qos;

    public:
        MQTTSubscriber(String clientId, uint8_t qos);
        
        void init();
        void update();

        void setupWiFi();
        void reconnect(); 
};
#endif