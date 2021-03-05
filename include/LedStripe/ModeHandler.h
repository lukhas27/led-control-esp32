#ifndef MODEHANDLER_h
#define MODEHANDLER_h

#include <Adafruit_NeoPixel.h>
#include "ledStripeData.h"

#define NUM_MODES   5

enum Mode
{
    WARM_WHITE = 0,
    MONOCHROME = 1,
    RAINBOW = 2,
    PULSE = 3,
    SINUS = 4
};

class ModeHandler 
{
    private:
        uint32_t warmWhite;
        uint32_t color;
        uint8_t valInOut;
        int mode;
        Adafruit_NeoPixel ledStripe;

    public:
        ModeHandler(Adafruit_NeoPixel ledStripe);
        
        void init();
        void update();
        
        void on();
        void off();
        
        void setMode(int mode);
        void nextMode();
        void handleMode();

        void setColor(uint32_t color);
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        uint32_t getColor();

        void setWarmWhite();
        void setMonochrome();
        void setRainbow();
        void setPulse();
        void setSinusCurve();

        
};
#endif