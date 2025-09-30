#include <Wire.h>
#include "MPU.h"
#include "motorcontrol.h"


MPU mpu;


void setup() {
    Serial.begin(115200);
    if(mpu.check()) {
      mpu.begin();
      Serial.println("MPU connected");
    } else {
      Serial.println("MPU not connected");
    }
    
}

void loop() {
    if(mpu.check()) {
      mpu.update();
      Serial.println(mpu.getZ());
      delay(10);
    }
}
