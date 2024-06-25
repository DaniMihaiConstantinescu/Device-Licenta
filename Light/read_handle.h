#ifndef READ_HANDLE_H
#define READ_HANDLE_H
#include <Arduino.h>
#include <BLECharacteristic.h>
#include <string.h>
#include "led_functions.h"

void handleInput(BLECharacteristic* pCharacteristicWrite, BLECharacteristic* pCharacteristic);
void handleNotify(std::string message, BLECharacteristic* pCharacteristic);

#endif
