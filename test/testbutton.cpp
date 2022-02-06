#include <Arduino.h>
#include "Button.h"

#define BUTTON_PIN 34 // Pin for Button

Button button(BUTTON_PIN);

void handleButton();

void setup()
{
	Serial.begin(115200);

	// Inits
	button.init();
}

void loop()
{
	// Handles
	handleButton();
}

void handleButton()
{
	if (button.getPosEdge())
	{
		Serial.print("pos Edge");
	}

	if (button.getState())
	{
		Serial.print("true");
	}
	else
	{
		Serial.print("false");
	}

	if (button.getNegEdge())
	{
		Serial.print("neg Edge");
	}
}