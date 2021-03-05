#ifndef BUTTON_h
#define BUTTON_h

#include <Arduino.h>

class Button
{
private:
    int pin;
    bool oldState;
    bool posEdge;
    bool negEdge;

public:
    Button(int pin);

    void init();
    void update();
    
    bool getState();
    bool getPosEdge();
    bool getNegEdge();
};
#endif