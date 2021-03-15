#ifndef MQTTCLIENT_h
#define MQTTCLIENT_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "mqttData.h"

class MQTTClient 
{
    private:
        String clientId;
        uint8_t qos;

    public:
        MQTTClient(String clientId, uint8_t qos);
        
        void init();
        void update();

        void setupWiFi();
        void reconnect(); 
};
#endif