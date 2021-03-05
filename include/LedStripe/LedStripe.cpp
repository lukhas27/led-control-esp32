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


/***************************************************
 * Implementation class objects
 ***************************************************/
Adafruit_NeoPixel ledStripe(NUMLEDS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
ModeHandler modeHandler();

/***************************************************
 * Constructor
 ***************************************************/
LedStripe::LedStripe(bool mode){
    color = ledStripe.Color(90, 87, 85);         // set default color to warm white
    this->mode = mode;
}

/***************************************************
 * Init + Update
 ***************************************************/
void LedStripe::init(){
    ledStripe.begin();
}

void LedStripe::update(){
    if (!mode){
        ledStripe.show();
    }
    else{
        
    }
}


/***************************************************
 * Setters + Getters
 ***************************************************/
void LedStripe::setColor(uint32_t color){
    for(int i = 0; i<NUMLEDS; i++){
        ledStripe.setPixelColor(i, color);
    }
}

void LedStripe::setColor(uint8_t r, uint8_t g, uint8_t b){
    color = ledStripe.Color(r, g, b);
    for(int i = 0; i<NUMLEDS; i++){
        ledStripe.setPixelColor(i, color);
    }
}

uint32_t LedStripe::getColor(){ 
    return color; 
}

/***************************************************
 * On + Off
 ***************************************************/
void LedStripe::on(){
    setColor(color);
}

void LedStripe::off(){
    setColor(NULL);
}