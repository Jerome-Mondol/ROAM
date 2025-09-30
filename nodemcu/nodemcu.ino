#include <Wire.h>

#define SLAVE_ADDR 0x08

void setup() {
  Wire.begin(); // Master mode
  Serial.begin(115200);
}

void loop() {
  // Request data from Arduino
  Wire.requestFrom(SLAVE_ADDR, 20); // request up to 20 bytes
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();

  // Example: send a command to Arduino
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write("Hello from esp"); // e.g., Forward command
  Wire.endTransmission();

  delay(1000);
}
