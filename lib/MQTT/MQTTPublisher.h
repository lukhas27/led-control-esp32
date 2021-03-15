#ifndef MQTTPUBLISHER_h
#define MQTTPUBLISHER_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "Led.h"
#include "mqttData.h"

#define MSG_BUFFER_SIZE 50

class MQTTPublisher 
{  
    private:
        String clientId;

    public:
        MQTTPublisher(String clientId);

        void init();
        void update();
        
        void setupWiFi();
        void reconnect();

        void publish(String payload, String topic);
        void publishBytes(byte *bytes, String topic);  
};
#endif