#include <Wire.h>
#include "motorcontrol.h"

#define SLAVE_ADDR 0x08

Motor motors(10, 5, 9, 8, 7, 6); // ENA, ENB, IN1, IN2, IN3, IN4

void setup() {
  motors.motorSetup();
  Wire.begin(SLAVE_ADDR);          // Arduino = I2C slave
  Wire.onReceive(receiveEvent);    // callback when master sends data
  Serial.begin(115200);
  Serial.println("Arduino I2C slave ready");
}

void loop() {
  // Nothing needed here; I2C handled in receiveEvent
}

// I2C callback
void receiveEvent(int bytes) {
  String cmd = "";
  while (Wire.available()) {
    char c = Wire.read();
    cmd += c;
  }
  cmd.trim();  // remove whitespace

  // Print received command
  Serial.print("Received via I2C (");
  Serial.print(cmd.length());
  Serial.print(" chars): ");
  Serial.println(cmd);

  // Execute motor commands
  if (cmd == "FORWARD") motors.forward();
  else if (cmd == "BACKWARD") motors.backward();
  else if (cmd == "LEFT") motors.turnLeft();
  else if (cmd == "RIGHT") motors.turnRight();
  else if (cmd == "STOP") motors.stop();

  delay(10); // tiny delay to prevent overlapping I2C events
}
