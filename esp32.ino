#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid = "OICore-ESP32-AP";
const char* password = "123456789";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);



String cmd_led = "LED_NONE";
String cmd_stor[4] = {"HIGH", "HIGH", "HIGH", "HIGH"};
String etor_state[6] = {"-", "-", "-", "-", "-", "-"};
String an_value[2] = {"-", "-"};



String processor(const String& var){
  if (var == "LED_NONE" && cmd_led == "LED_NONE")
    return "selected";
  else if (var == "LED_RED" && cmd_led == "LED_RED")
    return "selected";
  else if (var == "LED_GREEN" && cmd_led == "LED_GREEN")
    return "selected";
  else if (var == "LED_YELLOW" && cmd_led == "LED_YELLOW")
    return "selected";
  else if (var == "LED_BLUE" && cmd_led == "LED_BLUE")
    return "selected";
  else if (var == "LED_PURPLE" && cmd_led == "LED_PURPLE")
    return "selected";
  else if (var == "LED_CYAN" && cmd_led == "LED_CYAN")
    return "selected";
  else if (var == "LED_WHITE" && cmd_led == "LED_WHITE")
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
    uint8_t buf[12] = {0};
    size_t len = 12;
    uint16_t crc;
    
    if (request->hasParam("c")) {
      cmd = request->getParam("c")->value();
    }
    
    if (cmd == "LED_NONE") {
      cmd_led = "LED_NONE";
      buf[2] = 0x14;
      buf[6] = 0x00;
      buf[9] = 0x01;
    }
    else if (cmd == "LED_RED") {
      cmd_led = "LED_RED";
      buf[2] = 0x14;
      buf[6] = 0x01;
      buf[9] = 0x01;
    }
    else if (cmd == "LED_GREEN") {
      cmd_led = "LED_GREEN";
      buf[2] = 0x14;
      buf[6] = 0x02;
      buf[9] = 0x01;
    }
    else if (cmd == "LED_YELLOW") {
      cmd_led = "LED_YELLOW";
      buf[2] = 0x14;
      buf[6] = 0x03;
      buf[9] = 0x01;
    }
    else if (cmd == "LED_BLUE") {
      cmd_led = "LED_BLUE";
      buf[2] = 0x14;
      buf[6] = 0x04;
      buf[9] = 0x01;
    }
    else if (cmd == "LED_PURPLE") {
      cmd_led = "LED_PURPLE";
      buf[2] = 0x14;
      buf[6] = 0x05;
      buf[9] = 0x01;
    }
    else if (cmd == "LED_CYAN") {
      cmd_led = "LED_CYAN";
      buf[2] = 0x14;
      buf[6] = 0x06;
      buf[9] = 0x01;
    }
    else if (cmd == "LED_WHITE") {
      cmd_led = "LED_WHITE";
      buf[2] = 0x14;
      buf[6] = 0x07;
      buf[9] = 0x01;
    }
    else if (cmd == "STOR1_HIGH") {
      cmd_stor[0] = "STOR1_HIGH";
      buf[2] = 0x31;
      buf[5] = 0x00;
      buf[9] = 0x01;
    }
    else if (cmd == "STOR1_LOW") {
      cmd_stor[0] = "STOR1_LOW";
      buf[2] = 0x31;
      buf[5] = 0x00;
      buf[9] = 0x00;
    }
    else if (cmd == "STOR2_HIGH") {
      cmd_stor[1] = "STOR2_HIGH";
      buf[2] = 0x31;
      buf[5] = 0x01;
      buf[9] = 0x01;
    }
    else if (cmd == "STOR2_LOW") {
      cmd_stor[1] = "STOR2_LOW";
      buf[2] = 0x31;
      buf[5] = 0x01;
      buf[9] = 0x00;
    }
    else if (cmd == "STOR3_HIGH") {
      cmd_stor[2] = "STOR3_HIGH";
      buf[2] = 0x31;
      buf[5] = 0x02;
      buf[9] = 0x01;
    }
    else if (cmd == "STOR3_LOW") {
      cmd_stor[2] = "STOR3_LOW";
      buf[2] = 0x31;
      buf[5] = 0x02;
      buf[9] = 0x00;
    }
    else if (cmd == "STOR4_HIGH") {
      cmd_stor[3] = "STOR4_HIGH";
      buf[2] = 0x31;
      buf[5] = 0x03;
      buf[9] = 0x01;
    }
    else if (cmd == "STOR4_LOW") {
      cmd_stor[3] = "STOR4_LOW";
      buf[2] = 0x31;
      buf[5] = 0x03;
      buf[9] = 0x00;
    }
    else if (cmd == "SEND") {
      if (request->hasParam("v")) {
        val = request->getParam("v")->value();
      }
      if (val.length() == 16) {
        byte tmp[17] = {0};        
        val.getBytes(tmp, 17);

        // Convert String to uint8_t array
        for (int i=0; i<8; i++) {
          if (tmp[i*2] >= 48 && tmp[i*2] <= 57) {
            buf[i+2] |= (uint8_t)((tmp[i*2] - 48) << 4);
          }
          else if (tmp[i*2] >= 65 && tmp[i*2] <= 70) {
            buf[i+2] |= (uint8_t)((tmp[i*2] - 55) << 4);
          }
          
          if (tmp[(i*2)+1] >= 48 && tmp[(i*2)+1] <= 57) {
            buf[i+2] |= (uint8_t)(tmp[(i*2)+1] - 48);
          }
          else if (tmp[(i*2)+1] >= 65 && tmp[(i*2)+1] <= 70) {
            buf[i+2] |= (uint8_t)(tmp[(i*2)+1] - 55);
          } 
        }
      }
    }

    request->send(SPIFFS, "/index.html", String(), false, processor);

    // Add checksum and heading
    crc = calculChecksum(buf, len);
    buf[10] = (uint8_t)((crc & 0xFF00) >> 8);
    buf[11] = (uint8_t)(crc & 0x00FF);
    buf[0] = 0x4F;
    buf[1] = 0x49;
    
    Serial.write(buf, len);
  });
  
  server.begin();
}



void loop(){
  uint8_t tmp[8] = {0};
  
  while (Serial.available()) {
    if (Serial.read() == 0x4F) {
      if (Serial.read() == 0x49) {
        for (int i=0; i<8; i++) {
          tmp[i] = Serial.read();
        }
        if (calculChecksum(tmp, 8) == ((Serial.read() << 8) | Serial.read())) {
          // PROCESS_SEND_DATA  
          if (tmp[0] == 0x36) {          
            if (tmp[3] == 0x00 && tmp[7] == 0x00) {
              etor_state[0] = "LOW";
            }
            else if (tmp[3] == 0x00 && tmp[7] == 0x01) {
              etor_state[0] = "HIGH";
            }
            else if (tmp[3] == 0x01 && tmp[7] == 0x00) {
              etor_state[1] = "LOW";
            }
            else if (tmp[3] == 0x01 && tmp[7] == 0x01) {
              etor_state[1] = "HIGH";
            }
            else if (tmp[3] == 0x02 && tmp[7] == 0x00) {
              etor_state[2] = "LOW";
            }
            else if (tmp[3] == 0x02 && tmp[7] == 0x01) {
              etor_state[2] = "HIGH";
            }
            else if (tmp[3] == 0x03 && tmp[7] == 0x00) {
              etor_state[3] = "LOW";
            }
            else if (tmp[3] == 0x03 && tmp[7] == 0x01) {
              etor_state[3] = "HIGH";
            }
            else if (tmp[3] == 0x04 && tmp[7] == 0x00) {
              etor_state[4] = "LOW";
            }
            else if (tmp[3] == 0x04 && tmp[7] == 0x01) {
              etor_state[4] = "HIGH";
            }
            else if (tmp[3] == 0x05 && tmp[7] == 0x00) {
              etor_state[5] = "LOW";
            }
            else if (tmp[3] == 0x05 && tmp[7] == 0x01) {
              etor_state[5] = "HIGH";
            }
            else if (tmp[3] == 0x06) {
              an_value[0] = String((tmp[4] << 24) | (tmp[5] << 16) | (tmp[6] << 8) | tmp[7]);
            }
            else if (tmp[3] == 0x07) {
              an_value[1] = String((tmp[4] << 24) | (tmp[5] << 16) | (tmp[6] << 8) | tmp[7]);
            }
          }
        }
      }
    }
  }
}
