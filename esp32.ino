#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

#define LOW                 (uint8_t)0x00
#define HIGH                (uint8_t)0x01
/*#define ACT_BLINK_LED       (uint8_t)0X14
#define PROCESS_SET_VALUE   (uint8_t)0x31
#define PROCESS_GET_DATA    (uint8_t)0x35*/

typedef enum
{
  LED_NONE    = (uint8_t)0,
  LED_RED     = (uint8_t)1,
  LED_GREEN   = (uint8_t)2,
  LED_YELLOW  = (uint8_t)3,
  LED_BLUE    = (uint8_t)4,
  LED_PURPLE  = (uint8_t)5,
  LED_CYAN    = (uint8_t)6,
  LED_WHITE   = (uint8_t)7,
} LedColor;

const char* ssid = "OICore-ESP32-AP";
const char* password = "123456789";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);

String cmd_led = "LED_COLOR_NONE";
String cmd_stor[4] = {"HIGH", "HIGH", "HIGH", "HIGH"};
String etor_state[6] = {"-", "-", "-", "-", "-", "-"};
String an_value[2] = {"-", "-"};

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
  else if (var == "STOR1_HIGH" && cmd_stor[0] == "STOR1_HIGH")
    return "selected";
  else if (var == "STOR1_LOW" && cmd_stor[0] == "STOR1_LOW")
    return "selected";
  else if (var == "STOR2_HIGH" && cmd_stor[1] == "STOR2_HIGH")
    return "selected";
  else if (var == "STOR2_LOW" && cmd_stor[1] == "STOR2_LOW")
    return "selected";
  else if (var == "STOR3_HIGH" && cmd_stor[2] == "STOR3_HIGH")
    return "selected";
  else if (var == "STOR3_LOW" && cmd_stor[2] == "STOR3_LOW")
    return "selected";
  else if (var == "STOR4_HIGH" && cmd_stor[3] == "STOR4_HIGH")
    return "selected";
  else if (var == "STOR4_LOW" && cmd_stor[3] == "STOR4_LOW")
    return "selected";
  else if (var == "ETOR1_STATE")
    return etor_state[0];
  else if (var == "ETOR2_STATE")
    return etor_state[1];
  else if (var == "ETOR3_STATE")
    return etor_state[2];
  else if (var == "ETOR4_STATE")
    return etor_state[3];
  else if (var == "ETOR5_STATE")
    return etor_state[4];
  else if (var == "ETOR6_STATE")
    return etor_state[5];
  else if (var == "AN1_VALUE")
    return an_value[0];
  else if (var == "AN2_VALUE")
    return an_value[1];
  else
    return String();
}

uint16_t calculChecksum(uint8_t* buf, uint8_t len) {
  uint16_t checksum = 0;
  if (buf != NULL) {
    for (int i=0; i<len; i++) {
      checksum += buf[i];
    }
  }
  return checksum;
}

uint8_t* encodeCmd(uint8_t* buf) {
  uint8_t tmp[12] = {0};
  size_t len = 8;
  tmp[0] = 0x4F; // Heading
  tmp[1] = 0x49; // Heading
  for (int i=0; i<len; i++) {
    tmp[i+2] = buf[i]; // data
  }
  tmp[11] = calculChecksum (buf, len); // CRC
  return tmp;
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
    String cmd, val;
    uint8_t buf[8] = {0};
    
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
      cmd_stor[0] = "STOR1_HIGH";
      buf[0] = 0x31;
      buf[3] = 0x00;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR1_LOW") {
      cmd_stor[0] = "STOR1_LOW";
      buf[0] = 0x31;
      buf[3] = 0x00;
      buf[7] = 0x00;
    }
    else if (cmd == "STOR2_HIGH") {
      cmd_stor[1] = "STOR2_HIGH";
      buf[0] = 0x31;
      buf[3] = 0x01;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR2_LOW") {
      cmd_stor[1] = "STOR2_LOW";
      buf[0] = 0x31;
      buf[3] = 0x01;
      buf[7] = 0x00;
    }
    else if (cmd == "STOR3_HIGH") {
      cmd_stor[2] = "STOR3_HIGH";
      buf[0] = 0x31;
      buf[3] = 0x02;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR3_LOW") {
      cmd_stor[2] = "STOR3_LOW";
      buf[0] = 0x31;
      buf[3] = 0x02;
      buf[7] = 0x00;
    }
    else if (cmd == "STOR4_HIGH") {
      cmd_stor[3] = "STOR4_HIGH";
      buf[0] = 0x31;
      buf[3] = 0x03;
      buf[7] = 0x01;
    }
    else if (cmd == "STOR4_LOW") {
      cmd_stor[3] = "STOR4_LOW";
      buf[0] = 0x31;
      buf[3] = 0x03;
      buf[7] = 0x00;
    }
    else if (cmd == "SEND") {
      if (request->hasParam("v")) {
        val = request->getParam("v")->value();
      }
      if (val.length() == 16) {
        // Convert string to uint8_t array        
      }
    }

    request->send(SPIFFS, "/index.html", String(), false, processor);

    Serial.write(encodeCmd(buf), 12);
  });
  
  server.begin();
}

void loop(){
  uint8_t tmp[8];
  
  while (Serial.available()) {
    if (Serial.read() == 0x4F) {
      if (Serial.read() == 0x49) {
        for (int i=0; i<8; i++) {
          tmp[i] = Serial.read();
        }
        if (calculChecksum(tmp, 8) == ((Serial.read() << 8) + Serial.read())) {
          if (tmp[0] == 0x35) { // PROCESS_GET_DATA
            if (tmp[3] == 0x00 && tmp[7] == LOW) {
              etor_state[0] = "LOW";
            }
            else if (tmp[3] == 0x00 && tmp[7] == HIGH) {
              etor_state[0] = "HIGH";
            }
            else if (tmp[3] == 0x01 && tmp[7] == LOW) {
              etor_state[1] = "LOW";
            }
            else if (tmp[3] == 0x01 && tmp[7] == HIGH) {
              etor_state[1] = "HIGH";
            }
            else if (tmp[3] == 0x02 && tmp[7] == LOW) {
              etor_state[2] = "LOW";
            }
            else if (tmp[3] == 0x02 && tmp[7] == HIGH) {
              etor_state[2] = "HIGH";
            }
            else if (tmp[3] == 0x03 && tmp[7] == LOW) {
              etor_state[3] = "LOW";
            }
            else if (tmp[3] == 0x03 && tmp[7] == HIGH) {
              etor_state[3] = "HIGH";
            }
            else if (tmp[3] == 0x04 && tmp[7] == LOW) {
              etor_state[4] = "LOW";
            }
            else if (tmp[3] == 0x04 && tmp[7] == HIGH) {
              etor_state[4] = "HIGH";
            }
            else if (tmp[3] == 0x05 && tmp[7] == LOW) {
              etor_state[5] = "LOW";
            }
            else if (tmp[3] == 0x05 && tmp[7] == HIGH) {
              etor_state[5] = "HIGH";
            }
          }
        }
      }
    }
  }
}
