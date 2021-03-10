/**
 * Author:     lukhas
 * Date  :     02.03.2021
 */

/**
 * Led Stripe
 * 
 * Control a LED stripe with any number of LEDs with diffrent modes
 *  
 */

/***************************************************
 * includes
 ***************************************************/ 
#include "LedStripe.h"


const uint32_t warmWhite = 0x5a5755;                        // rgb value (90, 87, 85)


/***************************************************
 * Constructor
 ***************************************************/
LedStripe::LedStripe(Adafruit_NeoPixel ledStripe){
    this->ledStripe = ledStripe;

    color = warmWhite;                                      // set default color warmwhite
    colorOld = color;

    brightness = 204;                                       // equals 80% brightness
    
    ledRangeMin = 0;                                        // default range:                               
    ledRangeMax = NUMLEDS;                                  // [0 ... (Number of LEDs)]
}

/***************************************************
 * Init + Update
 ***************************************************/
void LedStripe::init(){
    ledStripe.begin();                                      // init LED stripe
}

void LedStripe::update(){
    if (colorChanged()){
        ledStripe.fill(color, ledRangeMin, ledRangeMax);    // assign all LEDs in range to current color if color changed
    }
    if (brightnessChanged()){
        ledStripe.setBrightness(brightness);                // set Brightness if changed
    }
    ledStripe.show();                                       // show updated LEDs
}


/***************************************************
 * Setters + Getters
 ***************************************************/
void LedStripe::setColor(uint32_t color){
    this->color = color;
}

void LedStripe::setColor(uint8_t r, uint8_t g, uint8_t b){
    this->color = ledStripe.Color(r, g, b);
}

uint32_t LedStripe::getColor(){ 
    return color; 
}

void LedStripe::setBrightness(uint8_t brightness){
    this->brightness = brightness;
}

uint8_t LedStripe::getBrightness(){
    return brightness;
}

void LedStripe::setLedRangeMin(uint8_t ledRangeMin){
    this->ledRangeMin = ledRangeMin;
}

uint8_t LedStripe::getLedRangeMin(){
    return ledRangeMin;
}

void LedStripe::setLedRangeMax(uint8_t ledRangeMax){
    this->ledRangeMax = ledRangeMax;
}

uint8_t LedStripe::getLedRangeMax(){
    return ledRangeMax;
}


/***************************************************
 * On + Off
 ***************************************************/
void LedStripe::on(){
    setColor(colorOld);                                     // turn LEDs on with saved color (Default: warmWhite)
}

void LedStripe::off(){
    this->colorOld = color;                                 // save color value berfore turn off
    this->color = 0;                                        // set color to black (LEDs off)
}


/***************************************************
 * Value has changed check
 ***************************************************/
bool LedStripe::colorChanged(){
    if(ledStripe.getPixelColor((ledRangeMin + ledRangeMax) / 2) != color){
        return true;
    }
    else{
        return false;
    }
}

bool LedStripe::brightnessChanged(){
    if(ledStripe.getBrightness() != brightness){
        return true;
    }
    else{
        return false;
    }
}