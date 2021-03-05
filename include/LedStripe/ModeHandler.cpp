/**
 * Author:     lukhas
 * Date  :     02.03.2021
 */

/**
 * Mode Handler
 * 
 * -switching between diffrent modes:
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
#include "ModeHandler.h"


/***************************************************
 * Constructor
 ***************************************************/
ModeHandler::ModeHandler(Adafruit_NeoPixel ledStripe){
    this->ledStripe = ledStripe;
    warmWhite = ledStripe.Color(90, 87, 85);
    color = warmWhite;
    mode = 0;
}


/***************************************************
 * Init + Update
 ***************************************************/
void ModeHandler::init(){ 
    ledStripe.begin();
}

void ModeHandler::update(){
    ledStripe.show();
}


/***************************************************
 * On + Off
 ***************************************************/
void ModeHandler::on(){
    handleMode();
}

void ModeHandler::off(){
    setMonochrome();
}


/***************************************************
 * mode handling
 ***************************************************/
void ModeHandler::setMode(int mode){
    this->mode = mode;
}

void ModeHandler::nextMode(){
    mode = (mode + 1) % NUM_MODES;
}

void ModeHandler::handleMode(){
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

        case PULSE: 
            setPulse();
            break;
        
        case SINUS: 
            setSinusCurve();
            break;

    }
}


/***************************************************
 * Setters
 ***************************************************/
void ModeHandler::setColor(uint32_t color){
    for(int i = 0; i<NUMLEDS; i++){
        ledStripe.setPixelColor(i, color);
    }
}

void ModeHandler::setColor(uint8_t r, uint8_t g, uint8_t b){
    color = ledStripe.Color(r, g, b);
    for(int i = 0; i<NUMLEDS; i++){
        ledStripe.setPixelColor(i, color);
    }
}

uint32_t ModeHandler::getColor(){ 
    return color; 
}


void ModeHandler::setWarmWhite(){
    setColor(warmWhite);
}

void ModeHandler::setMonochrome(){
    setColor(color);
}

void ModeHandler::setRainbow(){
    
}

void ModeHandler::setPulse(){

}

void ModeHandler::setSinusCurve(){

}