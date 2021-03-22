#ifndef BUTTON_h
#define BUTTON_h

#include <Arduino.h>

class Button
{
private:
    uint16_t pin;
    bool oldState;
    bool posEdge;
    bool negEdge;

public:
    Button(uint16_t pin);

    void init();
    void update();
    
    bool getState();
    bool getPosEdge();
    bool getNegEdge();
};
#endif