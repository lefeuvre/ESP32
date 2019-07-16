#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

typedef enum LedColor {
  LED_NONE = 0x00,
  LED_RED = 0x01,
  LED_GREEN = 0x02,
  LED_YELLOW = 0x03,
  LED_BLUE = 0x04,
  LED_PURPLE = 0x05,
  LED_CYAN = 0x06,
  LED_WHITE = 0x07
};

const char* ssid = "OICore-ESP32-AP";
const char* password = "123456789";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);

LedColor led = LED_NONE;
bool stor[4] = {LOW, LOW, LOW, LOW};

String processor(const String& var){
  return String();
}

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/design.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  
  /*server.on("/", handle_OnConnect);
  server.on("/led/none", handle_led_none);
  server.on("/led/red", handle_led_red);
  server.on("/led/green", handle_led_green);
  server.on("/led/yellow", handle_led_yellow);
  server.on("/led/blue", handle_led_blue);
  server.on("/led/purple", handle_led_purple);
  server.on("/led/cyan", handle_led_cyan);
  server.on("/led/white", handle_led_white);
  server.on("/stor1/low", handle_stor1_low);
  server.on("/stor1/high", handle_stor1_high);
  server.on("/stor2/low", handle_stor2_low);
  server.on("/stor2/high", handle_stor2_high);
  server.on("/stor3/low", handle_stor3_low);
  server.on("/stor3/high", handle_stor3_high);
  server.on("/stor4/low", handle_stor4_low);
  server.on("/stor4/high", handle_stor4_high);
  server.onNotFound(handle_NotFound);*/
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  //server.handleClient();
}
/*
void handle_OnConnect() {
  Serial.println("Led color: NONE");
  server.send(200, "text/html", SendHTML()); 
}

void handle_led_none() {
  led = LED_NONE;
  Serial.println("Led color: NONE");
  server.send(200, "text/html", SendHTML()); 
}

void handle_led_red() {
  led = LED_RED;
  Serial.println("Led color: RED");
  server.send(200, "text/html", SendHTML()); 
}

void handle_led_green() {
  led = LED_GREEN;
  Serial.println("Led color: GREEN");
  server.send(200, "text/html", SendHTML()); 
}

void handle_led_yellow() {
  led = LED_YELLOW;
  Serial.println("Led color: YELLOW");
  server.send(200, "text/html", SendHTML()); 
}

void handle_led_blue() {
  led = LED_BLUE;
  Serial.println("Led color: BLUE");
  server.send(200, "text/html", SendHTML()); 
}

void handle_led_purple() {
  led = LED_PURPLE;
  Serial.println("Led color: PURPLE");
  server.send(200, "text/html", SendHTML()); 
}

void handle_led_cyan() {
  led = LED_CYAN;
  Serial.println("Led color: CYAN");
  server.send(200, "text/html", SendHTML()); 
}

void handle_led_white() {
  led = LED_WHITE;
  Serial.println("Led color: WHITE");
  server.send(200, "text/html", SendHTML()); 
}

void handle_stor1_low() {
  stor[0] = LOW;
  Serial.println("stor1 state: LOW");
  server.send(200, "text/html", SendHTML()); 
}

void handle_stor1_high() {
  stor[0] = HIGH;
  Serial.println("stor1 state: HIGH");
  server.send(200, "text/html", SendHTML()); 
}

void handle_stor2_low() {
  stor[1] = LOW;
  Serial.println("stor2 state: LOW");
  server.send(200, "text/html", SendHTML()); 
}

void handle_stor2_high() {
  stor[1] = HIGH;
  Serial.println("stor2 state: HIGH");
  server.send(200, "text/html", SendHTML()); 
}

void handle_stor3_low() {
  stor[2] = LOW;
  Serial.println("stor3 state: LOW");
  server.send(200, "text/html", SendHTML()); 
}

void handle_stor3_high() {
  stor[2] = HIGH;
  Serial.println("stor3 state: HIGH");
  server.send(200, "text/html", SendHTML()); 
}

void handle_stor4_low() {
  stor[3] = LOW;
  Serial.println("stor4 state: LOW");
  server.send(200, "text/html", SendHTML()); 
}

void handle_stor4_high() {
  stor[3] = HIGH;
  Serial.println("stor4 state: HIGH");
  server.send(200, "text/html", SendHTML()); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head>\n";
  ptr += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>OICore ESP32 Web Server</title>\n";
  
  ptr += "<style>\n";
  ptr += "html { font-family: Helvetica; display: inline-block; margin: 0px auto;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 30px auto 30px; text-align: center;}\n";
  ptr += "h3 {margin-left: 10px;}\n";
  ptr += "p {font-size: 14px;margin-bottom: 10px;}\n";
  ptr += "table {margin: auto;}\n";
  
  ptr += "</style>\n";
  ptr += "</head>\n";

  ptr += "<body>\n";
  ptr += "<h1>OICore ESP32 Web Server</h1>\n";

  ptr += "<h3>LED control :</h3>\n";

  ptr += "<table>\n";  
  ptr += "<tr><td><p>LED<p></td>\n";
  ptr += "<td><select onChange=\"window.document.location.href=this.options[this.selectedIndex].value;\">\n";
  if (led == LED_NONE) ptr += "<option value=\"/led/none\" selected>NONE</option>\n";
  else ptr += "<option value=\"/led/none\">NONE</option>\n";  
  if (led == LED_RED) ptr += "<option value=\"/led/red\" selected>RED</option>\n";
  else ptr += "<option value=\"/led/red\">RED</option>\n";  
  if (led == LED_GREEN) ptr += "<option value=\"/led/green\" selected>GREEN</option>\n";
  else ptr += "<option value=\"/led/green\">GREEN</option>\n";  
  if (led == LED_YELLOW) ptr += "<option value=\"/led/yellow\" selected>YELLOW</option>\n";
  else ptr += "<option value=\"/led/yellow\">YELLOW</option>\n";  
  if (led == LED_BLUE) ptr += "<option value=\"/led/blue\" selected>BLUE</option>\n";
  else ptr += "<option value=\"/led/blue\">BLUE</option>\n";  
  if (led == LED_PURPLE) ptr += "<option value=\"/led/purple\" selected>PURPLE</option>\n";
  else ptr += "<option value=\"/led/purple\">PURPLE</option>\n";  
  if (led == LED_CYAN) ptr += "<option value=\"/led/cyan\" selected>CYAN</option>\n";
  else ptr += "<option value=\"/led/cyan\">CYAN</option>\n";  
  if (led == LED_WHITE) ptr += "<option value=\"/led/white\" selected>WHITE</option>\n";
  else ptr += "<option value=\"/led/white\">WHITE</option>\n";
  ptr += "</select></td></tr>\n";
  ptr += "</table>\n";

  ptr += "<h3>Outputs control :</h3>\n";

  ptr += "<table>\n";
  ptr += "<tr><td><p>STOR 1<p></td>\n";
  ptr += "<td><select onChange=\"window.document.location.href=this.options[this.selectedIndex].value;\">\n";
  if (stor[0] == HIGH) ptr += "<option value=\"/stor1/high\" selected>HIGH</option>\n";
  else ptr += "<option value=\"/stor1/high\">HIGH</option>\n";
  if (stor[0] == LOW) ptr += "<option value=\"/stor1/low\" selected>LOW</option>\n";
  else ptr += "<option value=\"/stor1/low\">LOW</option>\n";
  ptr += "</select></td></tr>\n";  
  ptr += "<tr><td><p>STOR 2<p></td>\n";
  ptr += "<td><select onChange=\"window.document.location.href=this.options[this.selectedIndex].value;\">\n";
  if (stor[1] == HIGH) ptr += "<option value=\"/stor2/high\" selected>HIGH</option>\n";
  else ptr += "<option value=\"/stor2/high\">HIGH</option>\n";
  if (stor[1] == LOW) ptr += "<option value=\"/stor2/low\" selected>LOW</option>\n";
  else ptr += "<option value=\"/stor2/low\">LOW</option>\n";
  ptr += "</select></td></tr>\n";  
  ptr += "<tr><td><p>STOR 3<p></td>\n";
  ptr += "<td><select onChange=\"window.document.location.href=this.options[this.selectedIndex].value;\">\n"; 
  if (stor[2] == HIGH) ptr += "<option value=\"/stor3/high\" selected>HIGH</option>\n";
  else ptr += "<option value=\"/stor3/high\">HIGH</option>\n";
  if (stor[2] == LOW) ptr += "<option value=\"/stor3/low\" selected>LOW</option>\n";
  else ptr += "<option value=\"/stor3/low\">LOW</option>\n";
  ptr += "</select></td></tr>\n";  
  ptr += "<tr><td><p>STOR 4<p></td>\n";
  ptr += "<td><select onChange=\"window.document.location.href=this.options[this.selectedIndex].value;\">\n"; 
  if (stor[3] == HIGH) ptr += "<option value=\"/stor4/high\" selected>HIGH</option>\n";
  else ptr += "<option value=\"/stor4/high\">HIGH</option>\n";
  if (stor[3] == LOW) ptr += "<option value=\"/stor4/low\" selected>LOW</option>\n";
  else ptr += "<option value=\"/stor4/low\">LOW</option>\n";
  ptr += "</select></td></tr>\n";  
  ptr += "</table>\n";
    
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}*/
