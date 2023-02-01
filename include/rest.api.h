#ifndef RESTAPI
#define RESTAPI

#include <ArduinoJson.h>
#include <server.config.h>

DynamicJsonDocument doc(256);
char json_string[256];

int mq3_analog = 0;
int mq3_digital = 0;

bool isBegin = false;
int minute = 3;
unsigned long start = 0;
unsigned long duration = (1000 * 60) * minute;
unsigned long timer = 0;

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
        // Call API
        HttpPost("/write/realtime", "realtime");

        if(!isBegin)
        {
            isBegin = true;
            start = millis();
        }

        if(isBegin)
        {
            timer = millis();
            if(timer > start + duration)
            {
                // Call API
                HttpPost("/write", "record");
                isBegin = false;
            }
        }
    }

    static void HttpPost(String endpoint, String tag)
    {
        doc["analogValue"] = mq3_analog;
        doc["digitalValue"] = mq3_digital;

        serializeJson(doc, json_string);

        WiFiClient client;
        HTTPClient http;
        http.begin(client, serverName + endpoint);

        http.addHeader("Content-Type", "application/json");
        int httpCode = http.POST(json_string);
        String payload = http.getString();
        Serial.print("HttpCode: ");
        Serial.print(httpCode);
        Serial.print("\t");
        Serial.print(tag);
        Serial.print("\t");
        http.end();
    }
};

#endif