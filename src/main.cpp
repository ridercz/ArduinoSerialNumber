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
