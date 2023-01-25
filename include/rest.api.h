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
        doc["analogValue"] = mq3_analog;
        doc["digitalValue"] = mq3_digital;

        serializeJson(doc, json_string);

        WiFiClient client;
        HTTPClient http;
        http.begin(client, serverName);

        int httpResponseCode = http.GET();
        String payload = "{}";

        if(httpResponseCode > 0)
        {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            payload = http.getString();
            Serial.print("Payload: ");
            Serial.println(payload);
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        // Free resources
        http.end();

        // http.addHeader("Content-Type", "application/json");
        // int httpCode = http.POST(json_string);
        // String payload = http.getString();

        // Serial.print("json: ");
        // Serial.println(json_string);
        // Serial.print("HttpCode: ");
        // Serial.println(httpCode);
        // Serial.print("Payload: ");
        // Serial.println(payload);
    }
};

#endif