#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid = "OICore-ESP32-AP";
const char* password = "123456789";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);

String cmd_led = "LED_COLOR_NONE";
String cmd_stor1 = "HIGH";
String cmd_stor2 = "HIGH";
String cmd_stor3 = "HIGH";
String cmd_stor4 = "HIGH";

String processor(const String& var){
  if (var == "LED_COLOR_NONE" && cmd_led == "LED_COLOR_NONE")
    return "selected";
  else if (var == "LED_COLOR_RED" && cmd_led == "LED_COLOR_RED")
    return "selected";
  else if (var == "LED_COLOR_GREEN" && cmd_led == "LED_COLOR_GREEN")
    return "selected";
  else if (var == "LED_COLOR_YELLOW" && cmd_led == "LED_COLOR_YELLOW")
    return "selected";
  else if (var == "LED_COLOR_BLUE" && cmd_led == "LED_COLOR_BLUE")
    return "selected";
  else if (var == "LED_COLOR_PURPLE" && cmd_led == "LED_COLOR_PURPLE")
    return "selected";
  else if (var == "LED_COLOR_CYAN" && cmd_led == "LED_COLOR_CYAN")
    return "selected";
  else if (var == "LED_COLOR_WHITE" && cmd_led == "LED_COLOR_WHITE")
    return "selected";
  else if (var == "STOR1_HIGH" && cmd_stor1 == "STOR1_HIGH")
    return "selected";
  else if (var == "STOR1_LOW" && cmd_stor1 == "STOR1_LOW")
    return "selected";
  else if (var == "STOR2_HIGH" && cmd_stor2 == "STOR2_HIGH")
    return "selected";
  else if (var == "STOR2_LOW" && cmd_stor2 == "STOR2_LOW")
    return "selected";
  else if (var == "STOR3_HIGH" && cmd_stor3 == "STOR3_HIGH")
    return "selected";
  else if (var == "STOR3_LOW" && cmd_stor3 == "STOR3_LOW")
    return "selected";
  else if (var == "STOR4_HIGH" && cmd_stor4 == "STOR4_HIGH")
    return "selected";
  else if (var == "STOR4_LOW" && cmd_stor4 == "STOR4_LOW")
    return "selected";
  else
    return String();
}

void setup() {
  Serial.begin(115200);

  SPIFFS.begin(true);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/act", HTTP_GET, [](AsyncWebServerRequest *request){
    String cmd;
    uint8_t buf[8] {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    size_t len = 8;
    
    if (request->hasParam("c")) {
      cmd = request->getParam("c")->value();
    }
    if (cmd == "LED_COLOR_NONE") {
      cmd_led = "LED_COLOR_NONE";
      buf[0] = 0x14;
      buf[4] = 0x00;
      buf[7] = 0x01;
    }
    else if (cmd == "LED_COLOR_RED") {
      cmd_led = "LED_COLOR_RED";
      buf[0] = 0x14;
      buf[4] = 0x01;
      buf[7] = 0x01;
    }
    else if (cmd == "LED_COLOR_GREEN") {
      cmd_led = "LED_COLOR_GREEN";
      buf[0] = 0x14;
      buf[4] = 0x02;
      buf[7] = 0x01;
    }
    else if (cmd == "LED_COLOR_YELLOW") {
      cmd_led = "LED_COLOR_YELLOW";
      buf[0] = 0x14;
      buf[4] = 0x03;
      buf[7] = 0x01;
    }
    else if (cmd == "LED_COLOR_BLUE") {
      cmd_led = "LED_COLOR_BLUE";
      buf[0] = 0x14;
      buf[4] = 0x04;
      buf[7] = 0x01;
    }
    else if (cmd == "LED_COLOR_PURPLE") {
      cmd_led = "LED_COLOR_PURPLE";
      buf[0] = 0x14;
      buf[4] = 0x05;
      buf[7] = 0x01;
    }
    else if (cmd == "LED_COLOR_CYAN") {
      cmd_led = "LED_COLOR_CYAN";
      buf[0] = 0x14;
      buf[4] = 0x06;
      buf[7] = 0x01;
    }
    else if (cmd == "LED_COLOR_WHITE") {
      cmd_led = "LED_COLOR_WHITE";
      buf[0] = 0x14;
      buf[4] = 0x07;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR1_HIGH") {
      cmd_stor1 = "STOR1_HIGH";
      buf[0] = 0x31;
      buf[3] = 0x00;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR1_LOW") {
      cmd_stor1 = "STOR1_LOW";
      buf[0] = 0x31;
      buf[3] = 0x00;
      buf[7] = 0x00;
    }
    else if (cmd == "STOR2_HIGH") {
      cmd_stor2 = "STOR2_HIGH";
      buf[0] = 0x31;
      buf[3] = 0x01;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR2_LOW") {
      cmd_stor2 = "STOR2_LOW";
      buf[0] = 0x31;
      buf[3] = 0x01;
      buf[7] = 0x00;
    }
    else if (cmd == "STOR3_HIGH") {
      cmd_stor3 = "STOR3_HIGH";
      buf[0] = 0x31;
      buf[3] = 0x02;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR3_LOW") {
      cmd_stor3 = "STOR3_LOW";
      buf[0] = 0x31;
      buf[3] = 0x02;
      buf[7] = 0x00;
    }
    else if (cmd == "STOR4_HIGH") {
      cmd_stor4 = "STOR4_HIGH";
      buf[0] = 0x31;
      buf[3] = 0x03;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR4_LOW") {
      cmd_stor4 = "STOR4_LOW";
      buf[0] = 0x31;
      buf[3] = 0x03;
      buf[7] = 0x00;
    }

    request->send(SPIFFS, "/index.html", String(), false, processor);

    Serial.write(buf, len);
  });
  
  server.begin();
}

void loop() {}
