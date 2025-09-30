#include "MPU.h"
#include <Wire.h>
#include "PID.h"
#include "Motor.h"
#include "TurnControl.h"

PID p(2.35, 0.025, 0.35);

mpu m;
TurnControl *turnCtrl;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  motorInit();

  if (m.begin()) {
    Serial.println("MPU CONNECTED");
    m.calibrate();
  } else {
    Serial.println("MPU NOT CONNECTED");
  }

  turnCtrl = new TurnControl(m, p);

  // give IMU a moment and prime a few updates before starting the automatic turn
  delay(100);
  for (int i = 0; i < 5; ++i) {
    if (m.check()) m.update();
    delay(10);
  }

  Serial.println("Auto-turn: rotating 90 deg on startup");
  turnCtrl->resetAngleEstimate(0.0); // ensure reference
  turnCtrl->turnBy(90.0);
  Serial.println("Auto-turn complete");
}

void loop() {
  // example usage: wait for serial command to turn
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "90") {
      Serial.println("Turning 90 deg");
      turnCtrl->turnBy(90.0);
      Serial.println("Done 90");
    } else if (cmd == "180") {
      Serial.println("Turning 180 deg");
      turnCtrl->turnBy(180.0);
      Serial.println("Done 180");
    } else if (cmd.startsWith("turn ")) {
      float a = cmd.substring(5).toFloat();
      Serial.print("Turning "); Serial.println(a);
      turnCtrl->turnBy(a);
      Serial.println("Done");
    }
  }

  // small idle loop to keep IMU updating
  if (m.check()) {
    m.update();
  }

  delay(10);
}
