#define DEBUGING 1

#include <Arduino.h>
#include "WiFi_connect.h"
//#include <EEPROM_memory.h>


/*  --wemos d1 pin--
  d4 - pin_led
	d1, d2 - calm pin, the others make high step
	d1, d2 - sda, scl
	d0 - no pwm, no attachInterrupt
	d3 - high
	d4 - high
	d9 - low
	*/

//создадим всего один объект mqtt клиента 
  mqttObject& mqttDevice = mqttObject::generate("esp_head/" ,"bedroom/" );
void setup()
{	
	Serial.begin(115200);
  Serial.println();
}

void loop()
{
	WiFi_loop();
}

