/**
 * Author:     lukhas
 * Date  :     02.03.2021
 */

/**
 * Led Stripe Modi
 *
 * -Led stripe /w diffrent modi:
 *
 *  1. Warm White (for relaxing Mood)
 *  2. All LEDs one choosable color
 *  3. Rainbow loop through Stripe (to be cool)
 *  4. Pulsing choosable color
 *  5. Sinus curve with choosable color
 */

/***************************************************
 * includes
 ***************************************************/
#include "LedStripeModi.h"

/***************************************************
 * Constructor
 ***************************************************/
LedStripeModi::LedStripeModi(uint16_t numberLeds, uint16_t pin)
{
    Adafruit_NeoPixel ledStripe(numberLeds, pin, NEO_GRBW + NEO_KHZ800);
    this->ledStripe = ledStripe;

    state = false;          // set Leds off
    setColor(0, 255, 0, 0); // set default color green
    brightness = 150;       // equals 80% brightness
    rangeMin = 0;           // default range:
    rangeMax = numberLeds;  // [0 ... (Number of LEDs)]
    mode = 0;               // set default mode to WARM_WHITE
    speedfactor = 20;       // set speedfactor
}

/***************************************************
 * Init + Update
 ***************************************************/
void LedStripeModi::init()
{
    ledStripe.begin(); // init LED stripe
    on();
    off();
}

void LedStripeModi::update()
{
    if (state)
    {
        // if (rangeChanged()){
        ledStripe.clear(); // clear LEDs if range changed
        //}

        ledStripe.setBrightness(brightness); // set Brightness if changed

        handleModi();
    }
    else
    {
        ledStripe.clear();
    }

    ledStripe.show(); // show updated LEDs
}

/***************************************************
 * On + Off
 ***************************************************/
void LedStripeModi::on()
{
    setState(true); // set state true -> LEDs on
}

void LedStripeModi::off()
{
    setState(false); // set state false -> LEDs off
}

/***************************************************
 * Modi functions
 ***************************************************/
void LedStripeModi::handleModi()
{
    switch (mode)
    {
    case WARM_WHITE:
        setWarmWhite();
        break;
    case MONOCHROME:
        setMonochrome();
        break;
    case RAINBOW:
        setRainbow();
        break;
        /* case PULSE:
            setPulse();
            break;
        case SINUS:
            setSinusCurve();
            break; */
    }
}

void LedStripeModi::nextMode()
{
    mode = (mode + 1) % NUMMODI;
}

void LedStripeModi::setWarmWhite()
{
    for (int i = rangeMin; i < (rangeMax + 1); i++)
    {
        ledStripe.setPixelColor(i, 0, 0, 0, 255);
    }
}

void LedStripeModi::setMonochrome()
{

    for (int i = rangeMin; i < (rangeMax + 1); i++)
    {
        ledStripe.setPixelColor(i, color);
    }
}

void LedStripeModi::setRainbow()
{
    for (int i = rangeMin; i < (rangeMax + 1); i++)
    {
        uint32_t color = ledStripe.ColorHSV(millis() * speedfactor + (65535 / (rangeMax - rangeMin)) * i, 255, 100);
        ledStripe.setPixelColor(i, color);
    }
}

/* void LedStripeModi::setPulse(){
    float sinValue = sin(millis() / 1000.0 * PI) * 255;
    uint8_t hsvValue = map(sinValue, -256, 256, 20, 255);

    uint32_t color = ledStripe.ColorHSV(map(this->color, 0, 4294967296, 0, 65536), 255, hsvValue);
    for (int i = rangeMin; i < rangeMax; i++){
        ledStripe.setPixelColor(i, color);
    }
}

void LedStripeModi::setSinusCurve(){
    for (int i = rangeMin; i < rangeMax; i++){
        float sinValue = sin((millis() / 1000.0 * PI) - PI / -2 * i) * 255;
        uint8_t hsvValue = map(sinValue, -256, 256, 20, 255);
        uint32_t color = ledStripe.ColorHSV(map(this->color, 0, 4294967296, 0, 65536), 255, hsvValue);
        ledStripe.setPixelColor(i, color);
    }
} */