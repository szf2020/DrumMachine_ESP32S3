/*
 * WebInterface.h
 * RED808 Web Interface Header
 */

#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#define UDP_PORT 8888  // Puerto para recibir comandos UDP

class WebInterface {
public:
  WebInterface();
  ~WebInterface();
  
  bool begin(const char* ssid, const char* password);
  void update();
  void handleUdp();  // Nueva función para procesar paquetes UDP
  
  void broadcastSequencerState();
  void sendSequencerStateToClient(AsyncWebSocketClient* client);
  void broadcastPadTrigger(int pad);
  void broadcastStep(int step);
  void broadcastVisualizationData();
  
  String getIP();
  
private:
  AsyncWebServer* server;
  AsyncWebSocket* ws;
  WiFiUDP udp;  // Servidor UDP
  bool initialized;
  
  void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, 
                       AwsEventType type, void *arg, uint8_t *data, size_t len);
  void processCommand(const JsonDocument& doc);  // Función común para procesar comandos
};

#endif
