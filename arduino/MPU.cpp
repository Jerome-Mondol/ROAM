#include "MPU.h"



bool MPU::check() {
    return mpu.testConnection();
}

void MPU::begin() {
  mpu.initialize();
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
  MPU::calibrate();
}

void MPU::update() {
   int16_t ax, ay, az, gx, gy, gz;
   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   gyroZ = (float)gz / 65.5;
   yawRate = gyroZ - calibrationOffset;
   filteredGyro = ALPHA * filteredGyro + (1 - ALPHA) * yawRate; 
}

float MPU::getZ() {
  return filteredGyro;
}

void MPU::calibrate(int samples) {
  float sum = 0.0;
  for(int i = 0; i < samples; i++) {
     int16_t ax, ay, az, gx, gy, gz;
     mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
     sum += (float)gz / 65.5;
     delay(1);
  }
  calibrationOffset = sum / samples;
}
