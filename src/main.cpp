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

#include "C:/Workspaces/Workspace_VSC_MQTT_Control/mqtt-control/include/Button"
#include "MQTTPublisher.h"
#include "Button.h"
#include "Led.h"
#include "LedStripeModi.h"


#define BUTTON_PIN  D0


/***************************************************
 * Implementation class objects
 ***************************************************/
Led builtInLed(LED_BUILTIN);


/***************************************************
 * Setup + Loop
 ***************************************************/
void setup()
{
    
}

void loop()
{
   
}
