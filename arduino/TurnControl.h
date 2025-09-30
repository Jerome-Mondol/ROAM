#ifndef TURNCONTROL_H
#define TURNCONTROL_H

#include <Arduino.h>
#include "MPU.h"
#include "PID.h"
#include "Motor.h"

// Configuration
const float ANGLE_TOLERANCE = 1.0; // degrees
const int STABLE_COUNT_REQUIRED = 5;
const int CONTROL_PERIOD_MS = 10;
const int TIMEOUT_MS = 20000; // 20s safety timeout

class TurnControl {
public:
  TurnControl(mpu &imu, PID &pid)
    : imu(imu), pid(pid), angleEstimate(0.0) {}

  // turn by deltaDegrees (positive = clockwise/right), will overshoot and correct
  void turnBy(float deltaDegrees) {
    // use persistent angleEstimate and call turnToAngle for relative turns
    float targetAbs = angleEstimate + deltaDegrees;
    turnToAngle(targetAbs);
  }

  // turn to an absolute angle (degrees) relative to the angleEstimate origin (0 at startup)
  void turnToAngle(float absoluteDegrees) {
    pid.reset();

    unsigned long startTime = millis();
    unsigned long lastTime = startTime;
    int stableCount = 0;

    while (millis() - startTime < TIMEOUT_MS) {
      unsigned long now = millis();
      unsigned long dt = now - lastTime;
      if (dt < CONTROL_PERIOD_MS) {
        delay(CONTROL_PERIOD_MS - dt);
        continue;
      }
      lastTime = now;

      // update IMU and integrate yaw rate
      if (imu.check()) {
        imu.update();
      }
      float yawrate = imu.getz();
      angleEstimate += yawrate * (dt / 1000.0);

      // compute remaining error using shortest path logic
      float error = shortestAngle(absoluteDegrees, angleEstimate);

      // PID compute (input=current angle, target=absoluteDegrees)
      float control = pid.compute(angleEstimate, absoluteDegrees);

      // deadband to overcome static friction
      const int MIN_DRIVE = 40; // tweak if necessary
      if (fabs(control) > 0 && fabs(control) < MIN_DRIVE) {
        control = (control > 0) ? MIN_DRIVE : -MIN_DRIVE;
      }

      int pwm = (int)constrain(control, -255, 255);
      setMotors(-pwm, pwm);

      if (fabs(error) < ANGLE_TOLERANCE) {
        stableCount++;
        if (stableCount >= STABLE_COUNT_REQUIRED) break;
      } else {
        stableCount = 0;
      }
    }

    stopMotors();
  }

  // optional: allow external reset of the internal angle estimate (e.g., after absolute sensor update)
  void resetAngleEstimate(float to = 0.0) {
    angleEstimate = to;
  }

private:
  mpu &imu;
  PID &pid;
  float angleEstimate; // integrated yaw (degrees) since startup or last reset

  float shortestAngle(float target, float current) {
    float diff = target - current;
    while (diff > 180.0) diff -= 360.0;
    while (diff <= -180.0) diff += 360.0;
    return diff;
  }
};

#endif
