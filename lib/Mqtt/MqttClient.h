#ifndef MQTTCLIENT_H_
#define MQTTCLIENT_H_

#include "MqttClient.h"
#include <WiFi.h>
#include <Wire.h>
#include "PubSubClient.h"
#include <Arduino.h>
#include "LedStripeModi.h"

class MqttClient
{
public:
  /**
   * Default Constructor of Driver.
   * @param info Reference to Position Info to share Infos between tasks.
   */
  MqttClient(LedStripeModi &ledStripe);

  /**
   * Has to be called frequently, then the callback-
   * function is able to interupt when receiving a message.
   */
  void update();

  /**
   * Public a Message on a given Topic
   */
  void publish(const char topic[], const char msg[]);

  /**
   * Checks if MQTT is connected
   */
  bool is_connected();

private:
  WiFiClient espClient; // Used to establish the WiFi connection
  PubSubClient client;  // Used to send MQTT Commands

  LedStripeModi &ledStripe; // Reference for inter-Task-Communication

  /**
   * Callback-function is called when a Message arrives.
   * The function can be seen as a Interrupt Handler for receiving Messages.
   */
  void callback(char *topic, byte *message, unsigned int length);

  /**
   * This Function reconects the MqttClient. It retries ever 5 sec.
   * @warning contains a while(!connected) loop. Therefore it may delay.
   */
  void reconnect();

  /**
   * Subscribes to all Topics given in the mqtt topic Config in config.h.
   */
  void subscribe();

  /**
   * Connects the ESP to the Wifi network. Settings can be found in config.h
   */
  void setup_wifi();
};
#endif