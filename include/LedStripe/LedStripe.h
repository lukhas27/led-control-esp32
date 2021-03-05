#ifndef LEDSTRIPE_h
#define LEDSTRIPE_h

#include <Adafruit_NeoPixel.h>
#include "ledStripeData.h"
#include "ModeHandler.h"

class LedStripe 
{
    private:
        uint32_t color;
        bool mode;

    public:
        LedStripe();
        LedStripe(bool mode);
        
        void init();
        void update();

        void setColor(uint32_t color);
        void setColor(uint8_t r, uint8_t g, uint8_t b);

        uint32_t getColor();

        void on();
        void off();
        
};
#endif