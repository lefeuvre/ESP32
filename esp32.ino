#include <WiFi.h>
#include <WebServer.h>
#include "OIMessage.h"
#include "OIDefinition.h"
#include "OIProtocol.h"

/* Put your SSID & Password */
const char* ssid = "OICore-ESP32-AP";
const char* password = "123456789";

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

OIMessage msg;
LedColor led = LED_NONE;

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/led/none", handle_led_none);
  server.on("/led/red", handle_led_red);
  server.on("/led/green", handle_led_green);
  server.on("/led/yellow", handle_led_yellow);
  server.on("/led/blue", handle_led_blue);
  server.on("/led/purple", handle_led_purple);
  server.on("/led/cyan", handle_led_cyan);
  server.on("/led/white", handle_led_white);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  Serial.println("Led color: NONE");
  server.send(200, "text/html", SendHTML(LED_NONE)); 
}

void handle_led_none() {
  led = LED_NONE;
  Serial.println("Led color: NONE");
  server.send(200, "text/html", SendHTML(LED_NONE)); 
}

void handle_led_red() {
  led = LED_RED;
  Serial.println("Led color: RED");
  server.send(200, "text/html", SendHTML(LED_RED)); 
}

void handle_led_green() {
  led = LED_GREEN;
  Serial.println("Led color: GREEN");
  server.send(200, "text/html", SendHTML(LED_GREEN)); 
}

void handle_led_yellow() {
  led = LED_YELLOW;
  Serial.println("Led color: YELLOW");
  server.send(200, "text/html", SendHTML(LED_YELLOW)); 
}

void handle_led_blue() {
  led = LED_BLUE;
  Serial.println("Led color: BLUE");
  server.send(200, "text/html", SendHTML(LED_BLUE)); 
}

void handle_led_purple() {
  led = LED_PURPLE;
  Serial.println("Led color: PURPLE");
  server.send(200, "text/html", SendHTML(LED_PURPLE)); 
}

void handle_led_cyan() {
  led = LED_CYAN;
  Serial.println("Led color: CYAN");
  server.send(200, "text/html", SendHTML(LED_CYAN)); 
}

void handle_led_white() {
  led = LED_WHITE;
  Serial.println("Led color: WHITE");
  server.send(200, "text/html", SendHTML(LED_WHITE)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(LedColor ledColor){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>OICore ESP32 Web Server</h1>\n";

  ptr += "<table>\n";
  ptr += "<tr><td>LED</td>\n";
  ptr += "<td><select onChange=\"window.document.location.href=this.options[this.selectedIndex].value;\">\n";
  if (ledColor == LED_NONE) ptr += "<option value=\"/led/none\" selected>NONE</option>\n";
  else ptr += "<option value=\"/led/none\">NONE</option>\n";  
  if (ledColor == LED_RED) ptr += "<option value=\"/led/red\" selected>RED</option>\n";
  else ptr += "<option value=\"/led/red\">RED</option>\n";  
  if (ledColor == LED_GREEN) ptr += "<option value=\"/led/green\" selected>GREEN</option>\n";
  else ptr += "<option value=\"/led/green\">GREEN</option>\n";  
  if (ledColor == LED_YELLOW) ptr += "<option value=\"/led/yellow\" selected>YELLOW</option>\n";
  else ptr += "<option value=\"/led/yellow\">YELLOW</option>\n";  
  if (ledColor == LED_BLUE) ptr += "<option value=\"/led/blue\" selected>BLUE</option>\n";
  else ptr += "<option value=\"/led/blue\">BLUE</option>\n";  
  if (ledColor == LED_PURPLE) ptr += "<option value=\"/led/purple\" selected>PURPLE</option>\n";
  else ptr += "<option value=\"/led/purple\">PURPLE</option>\n";  
  if (ledColor == LED_CYAN) ptr += "<option value=\"/led/cyan\" selected>CYAN</option>\n";
  else ptr += "<option value=\"/led/cyan\">CYAN</option>\n";  
  if (ledColor == LED_WHITE) ptr += "<option value=\"/led/white\" selected>WHITE</option>\n";
  else ptr += "<option value=\"/led/white\">WHITE</option>\n";
  ptr += "</select></td></tr>\n";
  ptr += "</table>\n";
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
