#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "base.hpp"
#include "heaterTimer.hpp"
#include "Logger.hpp"
#include "Heater.hpp"

const char* ssid = "WMOSKITO";
const char* password = ".ubX54bVSt#vxW11m.";
const char* myhostname = "Standheizung";
const char* curVersion = "0.0.1"; 
const int relaisPin = 5;

ESP8266WebServer server(80);
base indexPage(&server);
heaterTimer hTimer;
Logger* logger = Logger::instance();
heater myHeater(relaisPin);

void handleRoot() 
{
  logger->Debug(String("Timer: " + indexPage.Get_timer()));
  if (0 < indexPage.Get_timer().toInt())
  {
    hTimer.setTimer(indexPage.Get_timer().toInt());
  }
  else
  {
    indexPage.Set_timer(String(hTimer.getTimer()));
  }

  int tempSoll = (int) (10.0 * indexPage.Get_tempSoll().toFloat());
  if (0 < tempSoll)
  {
    myHeater.On(tempSoll, &hTimer);
  }

  indexPage.Set_tempSoll(String((((double) myHeater.getTenthDegreesShould()) / 10)));
  indexPage.Set_tempIst(String((((double) myHeater.getTenthDegrees()) / 10)));
  indexPage.Set_version(curVersion);
  indexPage.Render();
  indexPage.Set_timer(String(0));
}

void callback() 
{ 
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(myhostname);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
    server.send(200, "text/plain", "this works as well");
  indexPage.SetCallback_submit(callback); 
  

  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
