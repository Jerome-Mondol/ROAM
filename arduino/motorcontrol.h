#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

class Motor {
  public:
    Motor(int ena, int enb, int in1, int in2, int in3, int in4);

    void forward();
    void backward();
    void turnLeft();
    void turnRight();
    void stop();
    void motorSetup();
    void testMotors();

    void setSpeed(int leftSpeed, int rightSpeed); // NEW

  private: 
    int ENA, ENB;     // PWM speed pins
    int IN1, IN2, IN3, IN4; // direction pins
    int leftSpeed, rightSpeed; // store current speeds
};

#endif // MOTORCONTROL_H
