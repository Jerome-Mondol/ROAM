#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// pin mapping
const int ENA = 10; // PWM for motor A (left)
const int IN1 = 9;
const int IN2 = 8;
const int IN3 = 7;
const int IN4 = 6;
const int ENB = 5; // PWM for motor B (right)

inline void stopMotors();

inline void motorInit() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  stopMotors();
}

inline void setMotorRaw(int pinEN, int pinFwd, int pinRev, int pwm) {
  pwm = constrain(pwm, -255, 255);
  if (pwm > 0) {
    digitalWrite(pinFwd, HIGH);
    digitalWrite(pinRev, LOW);
    analogWrite(pinEN, pwm);
  } else if (pwm < 0) {
    digitalWrite(pinFwd, LOW);
    digitalWrite(pinRev, HIGH);
    analogWrite(pinEN, -pwm);
  } else {
    digitalWrite(pinFwd, LOW);
    digitalWrite(pinRev, LOW);
    analogWrite(pinEN, 0);
  }
}

inline void setMotors(int leftPWM, int rightPWM) {
  setMotorRaw(ENA, IN1, IN2, leftPWM);
  setMotorRaw(ENB, IN3, IN4, rightPWM);
}

inline void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

#endif
