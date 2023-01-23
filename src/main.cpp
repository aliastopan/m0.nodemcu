#include <Arduino.h>
#include <rest.api.h>

const int MQ3 = A0;
int value = 0;

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(MQ3, INPUT);
	pinMode(D5, INPUT);

    // API::Setup();
    // API::Start();
}

unsigned long start = 0;
unsigned long timer = 0;
unsigned long duration = 1000 * 10;
bool checking = false;

void loop()
{
	delay(1000);

	if(!checking)
	{
		value = analogRead(MQ3);
		Serial.print(value);
		Serial.print("\t");
		Serial.println(digitalRead(D5));
	}

	if(digitalRead(D5) == 0 && !checking)
	{
		start = millis();
		checking = true;
	}

	if(checking)
	{
		int second = start + duration - timer;
		Serial.print("Checking: ");
		Serial.print(second/1000);
		Serial.println(" second(s)");

		if(digitalRead(D5) == 1)

		timer = millis();
		if(timer >= start + duration)
		{
			checking = false;
		}
	}

		// unsigned long = start + duration - timer;

	// digitalWrite(LED_BUILTIN, LOW);
	// Serial.println("LOW");
	// delay(100);

	// digitalWrite(LED_BUILTIN, HIGH);
	// Serial.println("HIGH");
	// delay(100);
}