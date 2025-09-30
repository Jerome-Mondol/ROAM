#include <Wire.h>

#define SLAVE_ADDR 0x08  // I2C address of Arduino

void setup() {
  Wire.begin(SLAVE_ADDR); // Join I2C bus as slave
  Wire.onRequest(sendData); // Callback when master requests data
  Wire.onReceive(receiveData); // Callback when master sends data
  Serial.begin(9600);
}

void loop() { 
  // You can do sensor/motor stuff here 
  delay(100);
}

void sendData() {
  Wire.write("hello from arduino"); // Send message to ESP
}

void receiveData(int byteCount) {
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c); // Print received chars
  }
  Serial.println();
}
