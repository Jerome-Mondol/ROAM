#include "motorcontrol.h"

Motor motors(10, 5, 9, 8, 7, 6); // ENA, ENB, IN1, IN2, IN3, IN4

void setup() {
  motors.motorSetup();
  motors.setSpeed(200, 180);
  motors.testMotors();
}

void loop() {
  
}
