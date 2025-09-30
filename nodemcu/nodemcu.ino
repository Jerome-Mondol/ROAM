#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define SLAVE_ADDR 0x08

const char* ssid = "ROAM_WIFI";
const char* password = "12345678";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1); // SDA=D2, SCL=D1 on ESP8266
  WiFi.softAP(ssid, password);
  Serial.println("Web server started!");

  server.on("/", handleRoot);
  server.on("/forward", [](){ sendCommand("FORWARD"); });
  server.on("/backward", [](){ sendCommand("BACKWARD"); });
  server.on("/left", [](){ sendCommand("LEFT"); });
  server.on("/right", [](){ sendCommand("RIGHT"); });
  server.on("/stop", [](){ sendCommand("STOP"); });

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<h1>ROAM Control</h1>"
                "<button onclick=\"fetch('/forward')\">Forward</button>"
                "<button onclick=\"fetch('/backward')\">Backward</button>"
                "<button onclick=\"fetch('/left')\">Left</button>"
                "<button onclick=\"fetch('/right')\">Right</button>"
                "<button onclick=\"fetch('/stop')\">Stop</button>";
  server.send(200, "text/html", html);
}

void sendCommand(String cmd) {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(cmd.c_str(), cmd.length()); // send exact chars
  Wire.endTransmission();

  Serial.println("Sent: " + cmd);
  server.send(200, "text/plain", "Command sent: " + cmd);
}
