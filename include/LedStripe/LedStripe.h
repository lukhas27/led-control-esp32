#ifndef LEDSTRIPE_h
#define LEDSTRIPE_h

#include <Adafruit_NeoPixel.h>

class LedStripe 
{
    private:
        uint32_t color;
        uint32_t colorOld;
        uint8_t brightness;
        uint8_t ledRangeMin;
        uint8_t ledRangeMax;

        Adafruit_NeoPixel ledStripe;

        void updateColor();

    public:
        LedStripe(Adafruit_NeoPixel ledStripe);
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

        void on();
        void off();

        bool colorChanged();
        bool brightnessChanged();
        bool rangeChanged();
        bool modeChanged();
};
#endif