#include <string>
#include "read_handle.h"

bool extractInfo(const std::string& input, std::string& info) {
    // Check if the string starts and ends with '{' and '}'
    if (input.front() == '{' && input.back() == '}') {
        // Find the position of '=' character
        size_t pos = input.find('=');
        if (pos != std::string::npos) {
            // Extract the information after '='
            info = input.substr(pos + 1, input.length() - pos - 2);
            return true; // Return true if extraction is successful
        }
    }
    return false; // Return false if the format is incorrect or extraction fails
}

int getCase(std::string mess) {
    std::string info = "";

    extractInfo(mess, info);
    Serial.println("Info:");
    Serial.println(info.c_str());

    /*
      0 - get device type
      1 - led on
      2 - led off
    */

    if (mess == "0") {
        return 0;
    } else if (extractInfo(mess, info)) {
        if (info == "on") {
            return 1;
        } else if (info == "off") {
            return 2;
        }
    }

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
      Serial.println("case 1");
      powerOnLed(2);
      break;
    case 2:
      Serial.println("case 2");
      powerOffLed(2);
      break;
    default:
      Serial.println("Default case");

  }

  pCharacteristicWrite->setValue("");
}

