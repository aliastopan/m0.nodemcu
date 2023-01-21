#include <Arduino.h>
#include <DNSServer.h>
#include <server.config.h>

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);

    Config::Setup();
}

void loop()
{
	// digitalWrite(LED_BUILTIN, LOW);
	// Serial.println("LOW");
	// delay(100);

	// digitalWrite(LED_BUILTIN, HIGH);
	// Serial.println("HIGH");
	// delay(100);
}