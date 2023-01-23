#ifndef RESTAPI
#define RESTAPI

#include <server.config.h>

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

        server.onNotFound(NotFound);
        server.begin();
    }
};

#endif