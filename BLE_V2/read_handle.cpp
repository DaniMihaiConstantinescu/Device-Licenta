#include <string>
#include "read_handle.h"

int getCase(std::string mess){

  /*
    0 - get device type
    1 - led on
    2 - led of
  */

  if(mess == "0")
    return 0;
  if(mess == "1")
    return 1;
  if(mess == "2")
  return 2;

  return -1;
}

void handleNotify(std::string message, BLECharacteristic* pCharacteristic) {
  pCharacteristic->setValue(message.c_str());
  pCharacteristic->notify();
}

void handleInput(BLECharacteristic* pCharacteristicWrite, BLECharacteristic* pCharacteristic) {
  Serial.print("Received message: ");

  std::string input = pCharacteristicWrite->getValue().c_str();
  Serial.println(input.c_str());

  int type = getCase(input);
  Serial.println(type);

  switch(type){
    case 0:
      Serial.println("0 case");
      handleNotify("{type:light}", pCharacteristic);
      break;
    case 1:
      Serial.println("1 case");
      powerOnLed(2);
      break;
    case 2:
      Serial.println("2 case");
      powerOffLed(2);
      break;
    default:
      Serial.println("Default case");

  }

  pCharacteristicWrite->setValue("");
}

