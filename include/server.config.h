#ifndef CONFIG
#define CONFIG

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <DNSServer.h>

const int port = 80;
AsyncWebServer server(port);
DNSServer dns;
String serverName = "http://mthrowaway488-001-site1.dtempurl.com/api";

class Config
{
    public:
    static void Setup()
    {
        Serial.println("Waiting for Access Point.");
        AsyncWiFiManager wifiManager(&server,&dns);
        wifiManager.autoConnect("NodeMCU");

        Serial.print("Stand By: ");
        Serial.println(WiFi.localIP());

        server.begin();
    }
};

#endif