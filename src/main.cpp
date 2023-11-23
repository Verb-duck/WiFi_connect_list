#include <Arduino.h>
#include "WiFi_connect.h"

#define MQTT_TOPIC_OTA "device/ota/esp1"
/*  --wemos d1 pin--
	d1, d2 - calm pin, the others make high step
	d1, d2 - sda, scl
	d0 - no pwm, no attachInterrupt
	d3 - high
	d4 - high
	d9 - low
	*/


void setup()
{	
	Serial.begin(115200);
}

void loop()
{
	WiFi_loop();
}

