#ifndef LEDSTRIPE_h
#define LEDSTRIPE_h

#include <Adafruit_NeoPixel.h>

class LedStripe 
{
    private:
        bool state;
        uint32_t color;
        uint8_t brightness;
        uint8_t ledRangeMin;
        uint8_t ledRangeMax;

        uint32_t stateOld;
        uint32_t colorOld;
        uint8_t ledRangeMinOld;
        uint8_t ledRangeMaxOld;

        Adafruit_NeoPixel ledStripe;

        bool turnedOn();
        bool turnedOff();
        bool colorChanged();
        bool brightnessChanged();
        bool rangeChanged();

    public:
        LedStripe(uint16_t numberLeds, uint16_t pin);
        void init();
        void update();

        void setState(bool state) { 
            this->stateOld = this->state;
            this->state = state; 
        };
        bool getState(){ return state; };
        void setColor(uint32_t color) { 
            this->colorOld = this->color;
            this->color = color;
        };
        void setColor(uint8_t r, uint8_t g, uint8_t b) { 
            this->colorOld = this->color;
            this->color = ledStripe.Color(r, g, b); 
        };
        uint32_t getColor() { return color; };
        void setBrightness(uint8_t brightness) { this->brightness = brightness; };
        uint8_t getBrightness() { return brightness; };
        void setLedRangeMin(uint8_t ledRangeMin) { 
            this->ledRangeMinOld = this->ledRangeMin;
            this->ledRangeMin = ledRangeMin; 
        };
        uint8_t getLedRangeMin() { return ledRangeMin; };
        void setLedRangeMax(uint8_t ledRangeMax) { 
            this->ledRangeMaxOld = this->ledRangeMax;
            this->ledRangeMax = ledRangeMax; 
        };
        uint8_t getLedRangeMax() { return ledRangeMax; };

        void on();
        void off();
};
#endif