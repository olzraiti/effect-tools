#include <Arduino.h>

void setup();
void led();
void test();
void resetPacketListen();
void throw_error_and_reset_pl(String error);
void loop();
void api_call(String method);
#line 1 "src/sketch.ino"
#define LED_PIN 13

void setup()
{
	Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}


String content = "";
char SOP = '{';
char EOP = '}';
String packet = "";
boolean sop_met = false;
boolean eop_met = false;
int NULL_CHAR = 10;

void led()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}
void test()
{
	Serial.println("TESTIS");
}

void resetPacketListen()
{
	content = "";
	eop_met = false;
	sop_met = false;
}

void throw_error_and_reset_pl(String error)
{
	Serial.println(error);
	resetPacketListen();
}

void loop()
{
	while(Serial.available()) {
		char character = Serial.read();

		if (character == NULL_CHAR)
			continue;
		else if (character == SOP)
			sop_met = true;
		else if (character == EOP) {
			eop_met = true;
			if (!sop_met)
				throw_error_and_reset_pl(String("ERROR: ") + EOP + "  met before " + SOP);
		} else if (character !=  SOP && character != SOP) {
			content.concat(character);
			if (!sop_met)
				throw_error_and_reset_pl(String("ERROR: content met before ") + SOP);
		}
	}

	if (eop_met) {
		Serial.println(content);
		api_call(content);
		resetPacketListen();
	}
}
void api_call(String method)
{
	if (method == "led")
		led();
	else if (method == "test")
		test();
}
