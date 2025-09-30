#ifndef PID_H
#define PID_H

class PID {
public:
  float kp, kd, ki;
  float error, derivative, integral, previouserror;
  float integralMax = 100.0; // anti-windup clamp

  PID(float p, float i, float d) {
    setconstant(p, i, d);
    reset();
  }

  void setconstant(float p, float i, float d) {
    if (p < 0 || i < 0 || d < 0) {
      kp = kd = ki = 1.0;
      return;
    }
    kp = p;
    kd = d;
    ki = i;
  }

  // compute using time delta in seconds
  float compute(float input, float target, float dt) {
    if (dt <= 0.0) dt = 0.001; // avoid divide by zero
    error = target - input;

    // integral with dt
    integral += error * dt;
    // clamp integrator to avoid windup
    if (integral > integralMax) integral = integralMax;
    if (integral < -integralMax) integral = -integralMax;

    // derivative based on error change over dt
    derivative = (error - previouserror) / dt;
    previouserror = error;

    return kp * error + ki * integral + kd * derivative;
  }

  void reset() {
    error = derivative = integral = previouserror = 0;
  }

private:
};

#endif
