#include "motorcontrol.h"
#include <Arduino.h>

Motor::Motor(int ena, int enb, int in1, int in2, int in3, int in4) {
    ENA = ena; ENB = enb;
    IN1 = in1; IN2 = in2; IN3 = in3; IN4 = in4;
    leftSpeed = 150;
    rightSpeed = 150;
}

void Motor::motorSetup() {
    pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
}

void Motor::setSpeed(int left, int right) {
    leftSpeed = constrain(left, 0, 255);
    rightSpeed = constrain(right, 0, 255);
}

void Motor::forward() {
    analogWrite(ENA, leftSpeed); analogWrite(ENB, rightSpeed);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void Motor::backward() {
    analogWrite(ENA, leftSpeed); analogWrite(ENB, rightSpeed);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void Motor::turnLeft() {
    analogWrite(ENA, leftSpeed); analogWrite(ENB, rightSpeed);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void Motor::turnRight() {
    analogWrite(ENA, leftSpeed); analogWrite(ENB, rightSpeed);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void Motor::stop() {
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// variable turn: positive = right, negative = left
void Motor::turn(float speed) {
    speed = constrain(speed, -255, 255);
    if(speed > 0){
        analogWrite(ENA, speed); analogWrite(ENB, speed);
        digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    } else if(speed < 0){
        analogWrite(ENA, -speed); analogWrite(ENB, -speed);
        digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    } else stop();
}
