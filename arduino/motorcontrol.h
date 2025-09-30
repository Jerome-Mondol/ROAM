#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

class Motor {
public:
    Motor(int ena, int enb, int in1, int in2, int in3, int in4);
    void motorSetup();
    void setSpeed(int left, int right);
    void forward();
    void backward();
    void turnLeft();
    void turnRight();
    void stop();
    void turn(float speed);  // new: variable turning

private:
    int ENA, ENB, IN1, IN2, IN3, IN4;
    int leftSpeed, rightSpeed;
};

#endif
