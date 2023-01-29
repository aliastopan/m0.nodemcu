#include <Arduino.h>
#include <sensor.config.h>
#include <rest.api.h>

const int MQ3_ANALOG = A0;
const int MQ3_DIGITAL = D1;
const int WARNING_PIN = D5;

int invert(int value)
{
	bool toInvert = value;
	return !toInvert;
}

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(MQ3_ANALOG, INPUT);
	pinMode(MQ3_DIGITAL, INPUT);
	pinMode(WARNING_PIN, OUTPUT);

	MQ::Calibrate();
    API::Setup();
    API::Start();
}

void loop()
{
	mq3_analog = analogRead(MQ3_ANALOG);
	mq3_digital = invert(digitalRead(MQ3_DIGITAL));

	if(mq3_digital == 1)
		digitalWrite(WARNING_PIN, HIGH);
	else
		digitalWrite(WARNING_PIN, LOW);

	// Serial.print(mq3_analog);
	// Serial.print("\t");
	// Serial.println(mq3_digital);
	MQ::Loop();


	// API::Loop();
	delay(250);
}

