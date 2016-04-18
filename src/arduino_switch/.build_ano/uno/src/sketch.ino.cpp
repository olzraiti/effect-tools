#include <Arduino.h>
#include <avr/sleep.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include <avr/sleep.h>
#define LED_PIN 13
#define INPUT_PIN 2

boolean pushed = false;
unsigned long time;
const long WAIT = 500;

void setup()
{
	Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(INPUT_PIN, INPUT);
    digitalWrite(LED_PIN, HIGH);
	sleep_enable(); 
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
}


void loop()
{
	int connected = digitalRead(INPUT_PIN);
	
	if (millis() - time <= WAIT) return;
	if (connected && !pushed) {
		pushed = true;
		time = millis();
		Serial.println("button pushed");
	}
	if (!connected) {
		time = millis() - WAIT + 10;
		pushed = false;
	}
}
