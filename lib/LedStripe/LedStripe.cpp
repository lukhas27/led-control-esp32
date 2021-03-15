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
LedStripe::LedStripe(uint16_t numberLeds, uint16_t pin){
    Adafruit_NeoPixel ledStripe(numberLeds, pin, NEO_GRB + NEO_KHZ800);
    this->ledStripe = ledStripe;

    state = false;                                          // set Leds off

    color = warmWhite;                                      // set default color warmwhite
    
    brightness = 204;                                       // equals 80% brightness
    
    ledRangeMin = 0;                                        // default range:                               
    ledRangeMax = numberLeds;                               // [0 ... (Number of LEDs)]
    
    // initialize old values same as current values
    stateOld = state;
    colorOld = color;
    ledRangeMinOld = ledRangeMin;
    ledRangeMaxOld = ledRangeMaxOld;
}

/***************************************************
 * Init + Update
 ***************************************************/
void LedStripe::init(){
    ledStripe.begin();
    ledStripe.clear();   
}

void LedStripe::update(){
    if (state){
        if (rangeChanged()){
            ledStripe.clear();
            ledStripe.fill(color, ledRangeMin, ledRangeMax-ledRangeMin);    
        }
        if (colorChanged() || turnedOn()){
            ledStripe.fill(color, ledRangeMin, ledRangeMax-ledRangeMin);    // assign all LEDs in range to current color if color changed
        }
        if (brightnessChanged()){
            ledStripe.setBrightness(brightness);                // set Brightness if changed
        }
    }
    if (turnedOff()){
        ledStripe.clear();
    }
    
    ledStripe.show();                                       // show updated LEDs
}


/***************************************************
 * On + Off
 ***************************************************/
void LedStripe::on(){
    setState(true);                                         // set state true -> LEDs on
}

void LedStripe::off(){
    setState(false);                                         // set state false -> LEDs off
}


/***************************************************
 * Private Functions
 ***************************************************/
bool LedStripe::turnedOn(){
    if (!stateOld && state){
        stateOld = state;
        return true;
    }
    return false;
}

bool LedStripe::turnedOff(){
    if (stateOld && !state){
        stateOld = state;
        return true;
    }
    return false;
}

bool LedStripe::colorChanged(){
    if(colorOld != color){
        this->colorOld = this->color;
        return true;
    }
    return false;
}

bool LedStripe::brightnessChanged(){
    if(ledStripe.getBrightness() != brightness){
        return true;
    }
    return false;
}

bool LedStripe::rangeChanged(){
    if(ledRangeMin != ledRangeMinOld || ledRangeMin != ledRangeMinOld){
        this->ledRangeMinOld = this->ledRangeMin;
        this->ledRangeMaxOld = this->ledRangeMax;
        return true;
    }
    return false;
}
