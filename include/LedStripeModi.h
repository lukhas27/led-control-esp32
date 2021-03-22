#ifndef LEDSTRIPEMODI_h
#define LEDSTRIPEMODI_h

#include <Adafruit_NeoPixel.h>

#define NUMMODI 3 // adjust number of modi to enum

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
    bool state;
    uint32_t color;
    uint8_t brightness;
    uint8_t rangeMin;
    uint8_t rangeMax;
    uint8_t mode;
    uint8_t speedfactor;

    uint32_t stateOld;
    uint32_t colorOld;
    uint8_t ledRangeMinOld;
    uint8_t ledRangeMaxOld;
    uint8_t modeOld;

    Adafruit_NeoPixel ledStripe;

    bool turnedOn();
    bool turnedOff();
    bool colorChanged();
    bool brightnessChanged();
    bool rangeChanged();
    bool modeChanged();

public:
    LedStripeModi(uint16_t numberLeds, uint16_t pin);

    void init();
    void update();

    void setState(bool state)
    {
        this->stateOld = this->state;
        this->state = state;
    };
    bool getState() { return state; };
    void setColor(uint32_t color)
    {
        this->colorOld = this->color;
        this->color = color;
    };
    void setColor(uint8_t r, uint8_t g, uint8_t b)
    {
        this->colorOld = this->color;
        this->color = ledStripe.Color(r, g, b);
    };
    uint32_t getColor() { return color; };
    void setBrightness(uint8_t brightness) { this->brightness = brightness; };
    uint8_t getBrightness() { return brightness; };
    void setLedRangeMin(uint8_t rangeMin)
    {
        this->ledRangeMinOld = this->rangeMin;
        this->rangeMin = rangeMin;
    };
    uint8_t getRangeMin() { return rangeMin; };
    void setLedRangeMax(uint8_t rangeMax)
    {
        this->ledRangeMaxOld = this->rangeMax;
        this->rangeMax = rangeMax;
    };
    uint8_t getRangeMax() { return rangeMax; };
    void setMode(uint8_t mode)
    {
        this->modeOld = this->mode;
        this->mode = mode;
    };
    uint8_t getMode() { return mode; };
    void setSpeedfactor(uint8_t speedfactor) { this->speedfactor = speedfactor; };
    uint8_t getSpeedfactor() { return speedfactor; };

    void on();
    void off();

    void handleModi();
    void nextMode();

    void setWarmWhite();
    void setMonochrome();
    void setRainbow();
    void setPulse();
    void setSinusCurve();
};
#endif