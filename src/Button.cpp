/**
 * Author:     lukhas
 * Date  :     02.03.2021
 */

/**
 * Button Class
 * 
 * Create an Button
 */


/***************************************************
 * includes
 ***************************************************/
#include "button.h"


/***************************************************
 * Constructor
 ***************************************************/
Button::Button(uint16_t pin)
{
    this->pin = pin;
    oldState = false;
    posEdge = false;
    negEdge = false;
}

/***************************************************
 * Init + Update
 ***************************************************/
void Button::init()
{
    pinMode(pin, INPUT);
}

void Button::update()
{
    bool newState = digitalRead(pin); //  read Pin
    // ask if new and old value are equal
    if (oldState == newState)
    {
        return;
    }
    // ask for positive edge
    else if (oldState == false && newState == true)
    {
        posEdge = true;
    }
    // ask for negative edge
    else if (oldState == true && newState == false)
    {
        negEdge = true;
    }
    oldState = newState;
}

/***************************************************
 * Getters
 ***************************************************/
bool Button::getState()
{
    return oldState;
}

bool Button::getPosEdge()
{
    if (posEdge == true)
    {
        posEdge = false;
        return true;
    }
    return false;
}

bool Button::getNegEdge()
{
    if (negEdge == true)
    {
        negEdge = false;
        return true;
    }
    return false;
}