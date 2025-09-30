
#ifndef MPU_H
#define MPU_H

#include <MPU6050.h>

class mpu {
public:

  bool begin() {
    mpu.initialize();
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
    return mpu.testConnection();
  }

  void update() {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    gyroz = (float)gz / 65.5;
    yawrate = gyroz - calibrateoffset;
  }

  float getz() {
    return yawrate;
  }

  bool check() {
    if (mpu.testConnection()) {
      return true;
    } else {
      return false;
    }
  }

  void calibrate() {
    float sum = 0.0;
    for (int i = 0; i < sample; i++) {
      int16_t gx, gy, gz;
      mpu.getRotation(&gx, &gy, &gz);
      sum += (float)gz / 65.5;  // deg/s for Z axis
      delay(1);
    }
    calibrateoffset = sum/sample;
  }

private:
  MPU6050 mpu;
  float gyroz;
  float calibrateoffset = 0.0;
  int sample = 2000;
  float yawrate = 0.0;
};

#endif
