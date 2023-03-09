#include <ESP8266WebServer.h>
#include "can.h"
#include "base64.hpp"

#define HTTP_OK 200
#define HTTP_NOT_FOUND 404
#define MIME_TYPE "text/plain"
#define ERROR_MESSAGE "Invalid-Operation"

ESP8266WebServer server(80);

char ingressBuffer[MAX_FRAME_LEN];
char egressBuffer[MAX_FRAME_LEN];
bool configured = false;
int len = 0;

void canLoopbackMode(){
  if(!configured){
    configured = true;
    initLoopbackCAN();
    server.send(HTTP_OK, MIME_TYPE, "CAN LOOPBACK MODE");
  }else{
    server.send(HTTP_OK, MIME_TYPE, "Configured");    
  }
}

void canHardwareMode(){
  if(!configured){
    configured = true;
    initNormalCAN();
    server.send(HTTP_OK, MIME_TYPE, "CAN HARDWARE MODE");  
  }else{
    server.send(HTTP_OK, MIME_TYPE, "Configured");    
  }
}

void canWrite(){
  if(configured){
    len = server.arg(0).toInt();
    server.arg(1).toCharArray(ingressBuffer, len);
    uint8_t frameData[BASE64::decodeLength(ingressBuffer)];
    BASE64::decode(ingressBuffer, frameData);
    
    canSend(frameData);
    server.send(HTTP_OK, MIME_TYPE, "CAN FRAME SENT"); 
  }else{
    server.send(HTTP_OK, MIME_TYPE, "Configure");    
  }
}

void canRead(){
  if(configured){
    if(canRecv()){
      char b64[BASE64::encodeLength(MAX_FRAME_LEN)];
      BASE64::encode((const uint8_t*) &canMsg, MAX_FRAME_LEN, b64);
      server.send(HTTP_OK, MIME_TYPE, b64);
    }else{
      server.send(HTTP_OK, MIME_TYPE, "NO CAN DATA");         
    }
  }else{
    server.send(HTTP_OK, MIME_TYPE, "Configure");    
  }
}

void resetSystem(){
  server.send(HTTP_NOT_FOUND, MIME_TYPE, "Resetting...");
  delay(5000);
  ESP.reset();
}

void nothing(){
  server.send(HTTP_NOT_FOUND, MIME_TYPE, ERROR_MESSAGE);
}

void initServer(){
  
  server.on("/write", canWrite);
  server.on("/read", canRead);
  server.on("/loopback", canLoopbackMode);
  server.on("/hardware", canHardwareMode);
  server.on("/reset", resetSystem);
  server.onNotFound(nothing);
  server.begin();
}

void handleClients(){
  server.handleClient();
}
