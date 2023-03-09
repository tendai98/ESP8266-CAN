#include "const.h"
#include "wifi.h"
#include "server.h"

byte state = 0;

int blinkLED(int d){
  digitalWrite(D4, HIGH);
  delay(d);
  digitalWrite(D4, LOW);
  delay(d);
  return 0;
}

void setup(){
  pinMode(D4, OUTPUT);
  startWiFiAP(AP_SSID, AP_PASS);
  initServer();
}

void loop(){
  handleClients();
  state = configured == true ? false : blinkLED(100);
}
