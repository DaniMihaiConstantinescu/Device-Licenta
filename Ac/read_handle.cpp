#include <string>
#include "read_handle.h"

float globalTemperature = 24.0;

bool extractInfo(const std::string& input, std::string& info, std::string& messType) {
    // Check if the string starts and ends with '{' and '}'
    if (input.front() == '{' && input.back() == '}') {
        // Find the position of '=' character
        size_t pos = input.find('=');
        if (pos != std::string::npos) {
            // Extract the information after '=' (message type)
            messType = input.substr(1, pos-1);
            // Extract the information after '='
            info = input.substr(pos + 1, input.length() - pos - 2);
            return true; // Return true if extraction is successful
        }
    }
    return false; // Return false if the format is incorrect or extraction fails
}

float getNewTemp(const std::string& str, float defaultValue = -1.0f) {
    std::istringstream iss(str);
    float value;
    iss >> std::noskipws >> value; 

    if (iss.eof() && !iss.fail()) {
        return value;
    } else {
        return defaultValue; 
    }
}

int getCase(std::string mess) {
    std::string messType = "";
    std::string info = "";

    extractInfo(mess, info, messType);
    Serial.println("Info:");
    Serial.println(info.c_str());

    float newTemp = getNewTemp(info);

    /*
      0 - get device type
      1 - modify temperature
    */

    if (mess == "0") {
        return 0;
    } else if (extractInfo(mess, info, messType)) {
        if (messType == "ac" && newTemp != -1 ){
          for ( int i=0; i< abs(globalTemperature-newTemp) ; i++ ) {
            powerOnLed(2);
            delay(300);
            powerOffLed(2);
            delay(300);
          }
          globalTemperature = newTemp;
          return 1;
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
      handleNotify("{type:shutter}", pCharacteristic);
      break;
    case 1:
      Serial.println("case 1");
      break;
    default:
      Serial.println("Default case");

  }

  pCharacteristicWrite->setValue("");
}

