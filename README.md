# Altairis Arduino Serial Number Library

Wouldn't it be good if Arduino project would have unique serial numbers? But they don't. I need unique device identification for one project, so I created a library which will store serial numbers in EEPROM.

The serial number (which can have variable length, but by default is 8 bytes long) is stored at the end of EEPROM, so the beginning is free to use with custom configuration data. To detect that the serial number was initialized, the value is prefixed with configured fixed prefix, which is by default two bytes `0x53 0x4E` (`SN` in ASCII).

## API

### Constructor SerialNumber()

Initializes the class with default values

### Constructor SerialNumber(int length = 8, char *prefix = (char*)"SN", int prefix_length = 2)

Initializes the class with custom serial number length and prefix

### bool hasSerialNumber()

Returns `true` if there is serial number defined in EEPROM (correct prefix is stored), `false` otherwise.

### void getSerialNumber(char* sn)

Gets serial number (last `length` bytes of EEPROM).

### void setSerialNumber(char* sn)

Saves serial number to EEPROM, including the configured prefix.

### void clearSerialNumber()

Clears first byte of prefix from EEPROM, effectively reseting serial number.

## Example

The following code shows all the features of the library.

* First it checks if there is serial number stored.
* If it isn't, it will display `SN?` on serial port and then read `SN_LENGTH` (8 by default) bytes from serial port in raw and use them as a serial number.
* If there is serial number defined (or was just set in the previous step), it will display it in hex form on serial port.

```cpp
#include <Arduino.h>
#include <SerialNumber.h>

#define SN_LENGTH 8

void setup() {
  // Enable serial port
  Serial.begin(115200);

  // Prepare the Serial Number class
  SerialNumber snUtil = SerialNumber(SN_LENGTH);

  // Prepare array to hold the serial number
  char sn[SN_LENGTH];

  // Uncomment the following line to reset serial number
  // snUtil.clearSerialNumber();

  if (!snUtil.hasSerialNumber()) {
    // No serial number - read it from serial port
    Serial.print("SN?");
    while (Serial.available() < SN_LENGTH);
    Serial.readBytes(sn, SN_LENGTH);

    // Save the values as serial number
    snUtil.setSerialNumber(sn);
    Serial.println();
  }

  // Print serial number in hex
  Serial.print("SN=");
  snUtil.getSerialNumber(sn);
  for (int i = 0; i < SN_LENGTH; i++) {
    if (sn[i] < 0x10) Serial.print("0");
    Serial.print(sn[i], HEX);
    if (i < SN_LENGTH - 1) Serial.print("-");
  }
  Serial.println();
}

void loop() {
  // Nothing in loop
}

```

### Notes about random generation

It seems logical that the library should automatically generate serial number by random if none is defined. Sadly, random numbers aren't easy to come by on Arduino. The commonly available methods will not be random enough for this purpose. And no, reading seed value from unconnected analog input port would not help. More about it later.

## License

Copyright (c) Michal Altair Valasek, 2018

Licensed under terms of the MIT license.

## Contributor Code of Conduct

This project adheres to No Code of Conduct. We are all adults. We accept anyone's contributions. Nothing else matters.

For more information please visit the [No Code of Conduct](https://github.com/domgetter/NCoC) homepage.