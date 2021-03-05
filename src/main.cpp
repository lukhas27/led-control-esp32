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

#include "MQTTSubscriber.h"
#include "MQTTPublisher.h"
#include "Button.h"
#include "Led.h"
#include "LedStripe.h"
#include "ModeHandler.h"


#define BUTTON_PIN  D0


/***************************************************
 * Implementation class objects
 ***************************************************/
Led builtInLed(LED_BUILTIN); 
MQTTSubscriber subscriber("sub_client", 1);
//MQTTPublisher publisher("pub_client", "test");
//Button button(BUTTON_PIN);
//ModeHandler led;


/***************************************************
 * Setup + Loop
 ***************************************************/
void setup()
{
    Serial.begin(115200);

    builtInLed.init();
    subscriber.init();
    //publisher.init();
    //button.init();
     
    //led.init();
}

void loop()
{
    subscriber.update();
    //publisher.update();
    //button.update();     
    //led.setWarmWhite();
    //led.update();

}
