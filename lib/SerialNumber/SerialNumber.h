#include <EEPROM.h>

#ifndef _SerialNumber_h
#define _SerialNumber_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SerialNumber {
private:
  int _length;
  int _eepromIndex;
  char *_prefix;
  int _prefix_length;

public:
  SerialNumber(int length = 8, char *prefix = (char*)"SN", int prefix_length = 2);

  bool hasSerialNumber();
  void getSerialNumber(char *sn);
  void setSerialNumber(char *sn);
  void clearSerialNumber();
};

#endif
