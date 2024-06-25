#include "led_functions.h"

void setupLeds(){
  // built-in led
  pinMode(2, OUTPUT);
}

void powerOnLed(uint pin){
  digitalWrite(pin, HIGH);
}

void powerOffLed(uint pin){
  digitalWrite(pin, LOW);
}