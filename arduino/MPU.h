#ifndef MPU_H
#define MPU_H

#include <MPU6050.h>

class MPU {
  public: 
  bool check();
  void begin();
  void update();
  void calibrate(int samples = 2000);
  float getZ();


  
  private:
  MPU6050 mpu;
  float gyroZ = 0;
  float filteredGyro = 0;
  const float ALPHA = 0.9;
  float calibrationOffset = 0;
  float yawRate = 0;
};

#endif
