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
LedStripeModi::LedStripeModi(Adafruit_NeoPixel ledStripe){
    this->ledStripe = ledStripe;

    color = warmWhite;                                      // set default color warmwhite
    colorOld = color;

    brightness = 204;                                       // equals 80% brightness
    
    ledRangeMin = 0;                                        // default range:                               
    ledRangeMax = NUMLEDS;                                  // [0 ... (Number of LEDs)]

    mode = 0;                                               // set default mode to WARM_WHITE

    speedfactor = 30;                                       // set speedfactor 
}

/***************************************************
 * Init + Update
 ***************************************************/
void LedStripeModi::init(){
    ledStripe.begin();                                      // init LED stripe
}

void LedStripeModi::update(){

    if (brightnessChanged()){
        ledStripe.setBrightness(brightness);                // set Brightness if changed
    } 
    ledStripe.show();                                       // show updated LEDs
}


/***************************************************
 * Setters + Getters
 ***************************************************/
void LedStripeModi::setColor(uint32_t color){
    this->color = color;
}

void LedStripeModi::setColor(uint8_t r, uint8_t g, uint8_t b){
    this->color = ledStripe.Color(r, g, b);
}

uint32_t LedStripeModi::getColor(){ 
    return color; 
}

void LedStripeModi::setBrightness(uint8_t brightness){
    this->brightness = brightness;
}

uint8_t LedStripeModi::getBrightness(){
    return brightness;
}

void LedStripeModi::setLedRangeMin(uint8_t ledRangeMin){
    this->ledRangeMin = ledRangeMin;
}

uint8_t LedStripeModi::getLedRangeMin(){
    return ledRangeMin;
}

void LedStripeModi::setLedRangeMax(uint8_t ledRangeMax){
    this->ledRangeMax = ledRangeMax;
}

uint8_t LedStripeModi::getLedRangeMax(){
    return ledRangeMax;
}

void LedStripeModi::setMode(uint8_t mode){
    this->mode = mode;
}

uint8_t LedStripeModi::getMode(){
    return mode;
}

void LedStripeModi::setSpeedfactor(uint8_t Speedfactor){
    this->speedfactor = speedfactor;
}

uint8_t LedStripeModi::getSpeedfactor(){
    return speedfactor;
}


/***************************************************
 * On + Off
 ***************************************************/
void LedStripeModi::on(){
    setColor(colorOld);                                     // turn LEDs on with saved color (Default: warmWhite)
}

void LedStripeModi::off(){
    this->colorOld = color;                                 // save color value berfore turn off
    this->color = 0;                                        // set color to black (LEDs off)
}


/***************************************************
 * Modi functions
 ***************************************************/
void LedStripeModi::handleModi(){
    if (rangeChanged()){
        ledStripe.clear();
    }
    switch(mode){
        case WARM_WHITE:
            if (colorChanged() || rangeChanged()){
                setWarmWhite();
            }
            break;
        case MONOCHROME:
            if (colorChanged() || rangeChanged()){
                setMonochrome();
            }
            break;
        case RAINBOW:
            setRainbow();
            break;
        case PULSE:
            setPulse();
            break;
        case SINUS:
            setSinusCurve();
            break;
    }
}

void LedStripeModi::nextMode(){
    if (modeChanged()){
        mode = (mode + 1) % NUMMODI;
    }
}


void LedStripeModi::setWarmWhite(){
    ledStripe.fill(warmWhite, ledRangeMin, ledRangeMax);
}

void LedStripeModi::setMonochrome(){
    ledStripe.fill(color, ledRangeMin, ledRangeMax);
}

void LedStripeModi::setRainbow(){
    for (int i = ledRangeMin; i < ledRangeMax; i++){
        uint32_t color = ledStripe.ColorHSV(millis() * speedfactor + (65535 / NUMLEDS) * i, 255, 100);
        ledStripe.setPixelColor(i, color);
    }

}

void LedStripeModi::setPulse(){
    float sinValue = sin(millis() / 1000.0 * PI) * 255;
    uint8_t hsvValue = map(sinValue, -256, 256, 20, 255);
    
    uint32_t color = ledStripe.ColorHSV(map(color, 0, 4294967296, 0, 65536), 255, hsvValue);
    for (int i = ledRangeMin; i < ledRangeMax; i++){
        ledStripe.setPixelColor(i, color);
    }
}

void LedStripeModi::setSinusCurve(){
    for (int i = ledRangeMin; i < ledRangeMax; i++){
        float sinValue = sin((millis() / 1000.0 * PI) - PI / -2 * i) * 255;
        uint8_t hsvValue = map(sinValue, -256, 256, 20, 255);
        uint32_t color = ledStripe.ColorHSV(map(color, 0, 4294967296, 0, 65536), 255, hsvValue);
        ledStripe.setPixelColor(i, color);
    }
}


/***************************************************
 * Value has changed check
 ***************************************************/
bool LedStripeModi::colorChanged(){
    if(ledStripe.getPixelColor((ledRangeMin + ledRangeMax) / 2) != color){
        return true;
    }
    else{
        return false;
    }
}

bool LedStripeModi::brightnessChanged(){
    if(ledStripe.getBrightness() != brightness){
        return true;
    }
    else{
        return false;
    }
}

bool LedStripeModi::rangeChanged(){
    if(ledRangeMin != ledRangeMinOld || ledRangeMin != ledRangeMinOld){
        return true;
    }
    else{
        return false;
    }
}

bool LedStripeModi::modeChanged(){
    if(mode != modeOld){
        return true;
    }
    else{
        return false;
    }
}