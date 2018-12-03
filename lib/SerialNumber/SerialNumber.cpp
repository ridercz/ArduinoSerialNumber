#include "SerialNumber.h"

SerialNumber::SerialNumber(int length = 8, char *prefix = (char*)"SN", int prefix_length = 2) {
  _length = length;
  _prefix = prefix;
  _prefix_length = prefix_length;
  _eepromIndex = EEPROM.length() - length - prefix_length;
}

bool SerialNumber::hasSerialNumber() {
  for (int i = 0; i < _prefix_length; i++) {
    if (EEPROM.read(_eepromIndex + i) != _prefix[i]) return false;
  }
  return true;
}

void SerialNumber::getSerialNumber(char *sn) {
  for (int i = 0; i < _length; i++) {
    sn[i] = EEPROM.read(_eepromIndex + _prefix_length + i);
  }
}

void SerialNumber::setSerialNumber(char *sn) {
  // Set prefix
  for (int i = 0; i < _prefix_length; i++) {
    EEPROM.update(_eepromIndex + i, _prefix[i]);
  }

  // Set serial number
  for (int i = 0; i < _length; i++) {
    EEPROM.update(_eepromIndex + _prefix_length + i, sn[i]);
  }
}

void SerialNumber::clearSerialNumber(){
    EEPROM.update(_eepromIndex, 0);
}