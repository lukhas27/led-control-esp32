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
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
    {
        this->colorOld = this->color;
        this->color = ledStripe.Color(r, g, b, w);
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

    String getColorHexString()
    {
        // hex Format: FFFFFF  String: FFFFFF\0
        char hexBuffer[8];

        String hexString = String(this->color, HEX);
        Serial.println(color);

        switch (hexString.length())
        {
        case 1:
            for (int i = 0; i < 5; i++)
            {
                hexBuffer[i] = 0;
            }
            hexBuffer[5] = hexString[0];
            break;

        case 2:
            for (int i = 0; i < 4; i++)
            {
                hexBuffer[i] = 0;
            }
            for (int i = 4; i < 4 + hexString.length(); i++)
            {
                hexBuffer[i] = hexString[i - 4];
            }
            break;

        case 3:
            for (int i = 0; i < 3; i++)
            {
                hexBuffer[i] = 0;
            }
            for (int i = 3; i < 3 + hexString.length(); i++)
            {
                hexBuffer[i] = hexString[i - 3];
            }
            break;

        case 4:
            for (int i = 0; i < 2; i++)
            {
                hexBuffer[i] = 0;
            }
            for (int i = 2; i < 2 + hexString.length(); i++)
            {
                hexBuffer[i] = hexString[i - 2];
            }
            break;

        case 5:
            hexBuffer[0] = 0;
            for (int i = 1; i < 1 + hexString.length(); i++)
            {
                hexBuffer[i] = hexString[i - 1];
                break;
            }

        case 6:
            for (int i = 0; i < 1 + hexString.length(); i++)
            {
                hexBuffer[i] = hexString[i];
            }
            break;
        }

        hexBuffer[7] = '\0';
        return hexBuffer;
    };

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