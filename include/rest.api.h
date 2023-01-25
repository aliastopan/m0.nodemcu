#ifndef RESTAPI
#define RESTAPI

#include <ArduinoJson.h>
#include <server.config.h>

DynamicJsonDocument doc(256);
char json_string[256];

int mq3_analog = 0;
int mq3_digital = 0;

class API
{
    private:
    static void NotFound(AsyncWebServerRequest *request)
    {
        request->send(404, "text/plain", "not found");
    }

    public:
    static void Setup()
    {
        Config::Setup();
    }

    static void Start()
    {

        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(200, "application/json", "ready");
        });

        server.on("/mq3", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(200, "application/json", json_string);
        });

        server.onNotFound(NotFound);
        server.begin();
    }

    static void Loop()
    {
        doc["analog"] = 0;
        doc["digital"] = 0;

        serializeJson(doc, json_string);
    }
};

#endif