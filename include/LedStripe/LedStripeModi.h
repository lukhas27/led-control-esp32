#ifndef LEDSTRIPEMODI_h
#define LEDSTRIPEMODI_h

#include <Adafruit_NeoPixel.h>

#define NUMMODI   5                       // adjust number of modi to enum

enum Mode
{
    WARM_WHITE = 0,
    MONOCHROME = 1,
    RAINBOW = 2,
    PULSE = 3,
    SINUS = 4
};

class LedStripeModi 
{
    private:
        uint32_t color;
        uint8_t brightness;
        uint8_t ledRangeMin;
        uint8_t ledRangeMax;
        uint8_t mode;
        uint8_t speedfactor;

        uint32_t colorOld;
        uint8_t ledRangeMinOld;
        uint8_t ledRangeMaxOld;
        uint8_t modeOld;

        Adafruit_NeoPixel ledStripe;

    public:
        LedStripeModi(Adafruit_NeoPixel ledStripe);
        
        void init();
        void update();

        void setColor(uint32_t color);
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        uint32_t getColor();
        void setBrightness(uint8_t brightness);
        uint8_t getBrightness();
        void setLedRangeMin(uint8_t ledRangeMin);
        uint8_t getLedRangeMin();
        void setLedRangeMax(uint8_t ledRangeMax);
        uint8_t getLedRangeMax();
        void setMode(uint8_t mode);
        uint8_t getMode();
        void setSpeedfactor(uint8_t mode);
        uint8_t getSpeedfactor();

        void on();
        void off();

        void handleModi();
        void nextMode();
        
        void setWarmWhite();
        void setMonochrome();
        void setRainbow();
        void setPulse();
        void setSinusCurve();

        bool colorChanged();
        bool brightnessChanged();
        bool rangeChanged();
        bool modeChanged();       
};
#endif