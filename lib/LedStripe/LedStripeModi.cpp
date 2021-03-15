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


const uint32_t warmWhite = 0x5a5755;                        // rgb value (90, 87, 85)


/***************************************************
 * Constructor
 ***************************************************/
LedStripeModi::LedStripeModi(uint16_t numberLeds, uint16_t pin){
    Adafruit_NeoPixel ledStripe(numberLeds, pin, NEO_GRB + NEO_KHZ800);
    this->ledStripe = ledStripe;
    
    state = false;                                          // set Leds off

    setColor(0, 0, 255);                                    // set default color green
    
    brightness = 204;                                       // equals 80% brightness
    
    ledRangeMin = 0;                                        // default range:                               
    ledRangeMax = numberLeds;                               // [0 ... (Number of LEDs)]

    mode = 0;                                               // set default mode to WARM_WHITE

    speedfactor = 20;                                       // set speedfactor 
    
    // initialize old values same as current values
    stateOld = state;
    colorOld = color;
    ledRangeMinOld = ledRangeMin;
    ledRangeMaxOld = ledRangeMaxOld;
    modeOld = mode;
}

/***************************************************
 * Init + Update
 ***************************************************/
void LedStripeModi::init(){
    ledStripe.begin();                                      // init LED stripe
    ledStripe.clear();
}

void LedStripeModi::update(){
    if (state){
        if (rangeChanged()){
            ledStripe.clear();                              // clear LEDs if range changed
        }
        if (brightnessChanged()){
            ledStripe.setBrightness(brightness);            // set Brightness if changed
        }
        handleModi();
    }
    if (turnedOff()){
        ledStripe.clear();
    }
    
    ledStripe.show();                                       // show updated LEDs
}



/***************************************************
 * On + Off
 ***************************************************/
void LedStripeModi::on(){
    setState(true);                                         // set state true -> LEDs on
}

void LedStripeModi::off(){
    setState(false);                                         // set state false -> LEDs off
}


/***************************************************
 * Modi functions
 ***************************************************/
void LedStripeModi::handleModi(){
    switch(mode){
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

void LedStripeModi::nextMode(){
    mode = (mode + 1) % NUMMODI;
}


void LedStripeModi::setWarmWhite(){
    if (turnedOn() || modeChanged()){
        ledStripe.fill(warmWhite, ledRangeMin, ledRangeMax);
    }
}

void LedStripeModi::setMonochrome(){
    if (turnedOn() || modeChanged() || colorChanged()){
        ledStripe.fill(color, ledRangeMin, ledRangeMax);
    }
}

void LedStripeModi::setRainbow(){
    for (int i = ledRangeMin; i < ledRangeMax; i++){
        uint32_t color = ledStripe.ColorHSV(millis() * speedfactor + (65535 / (ledRangeMax + ledRangeMin)) * i, 255, 100);
        ledStripe.setPixelColor(i, color);
    }

}

void LedStripeModi::setPulse(){
    float sinValue = sin(millis() / 1000.0 * PI) * 255;
    uint8_t hsvValue = map(sinValue, -256, 256, 20, 255);
    
    uint32_t color = ledStripe.ColorHSV(map(this->color, 0, 4294967296, 0, 2^16), 255, hsvValue);
    for (int i = ledRangeMin; i < ledRangeMax; i++){
        ledStripe.setPixelColor(i, color);
    }
}

void LedStripeModi::setSinusCurve(){
    for (int i = ledRangeMin; i < ledRangeMax; i++){
        float sinValue = sin((millis() / 1000.0 * PI) - PI / -2 * i) * 255;
        uint8_t hsvValue = map(sinValue, -256, 256, 20, 255);
        uint32_t color = ledStripe.ColorHSV(map(this->color, 0, 4294967296, 0, 2^16), 255, hsvValue);
        ledStripe.setPixelColor(i, color);
    }
}


/***************************************************
 * Private Functions
 ***************************************************/
bool LedStripeModi::turnedOn(){
    if (!stateOld && state){
        stateOld = state;
        return true;
    }
    return false;
}

bool LedStripeModi::turnedOff(){
    if (stateOld && !state){
        stateOld = state;
        return true;
    }
    return false;
}

bool LedStripeModi::colorChanged(){
    if(colorOld != color){
        this->colorOld = this->color;
        return true;
    }
    return false;
}

bool LedStripeModi::brightnessChanged(){
    if(ledStripe.getBrightness() != brightness){
        return true;
    }
    return false;
}

bool LedStripeModi::rangeChanged(){
    if(ledRangeMin != ledRangeMinOld || ledRangeMin != ledRangeMinOld){
        this->ledRangeMinOld = this->ledRangeMin;
        this->ledRangeMaxOld = this->ledRangeMax;
        return true;
    }
    return false;
}

bool LedStripeModi::modeChanged(){
    if (modeOld != mode){
        modeOld = mode;
        return true;
    }
    return false;
}