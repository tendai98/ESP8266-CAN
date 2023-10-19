#include <ESP8266WiFi.h>

void startWiFiAP(char * ssid, char * password){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
}
