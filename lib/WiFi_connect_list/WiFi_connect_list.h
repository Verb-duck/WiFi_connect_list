#ifndef WiFi_connect_list_h
#define WiFi_connect_list_h
#include <Arduino.h>
#include <ESP8266WiFi.h>        //wifi
#include <ESP8266mDNS.h>        //wifi
#include <ArduinoOTA.h>         //ota
#include <ESP8266httpUpdate.h>  //ota http
#include <PubSubClient.h>       //mqtt

#define ssid "5G OBLUCHATEL"
#define passwordW "00000000"
//#define ssid "хуета"
//#define passwordW "20192020"

class WiFi_connect_list {
	private:
		bool WiFi_connecting();				//подключение к ВиФи
		void begin_OTA_WiFi_to_IP();  // обновление по IP
	public:
		WiFi_connect_list() {}
		void begin() 
		{
			if(WiFi_connecting()) 
			{
				begin_OTA_WiFi_to_IP();
			}
		}
		bool loop ()       
		{
			if(WiFi_connecting())			//если есть подкоючение
			{
				ArduinoOTA.handle(); 		//проверим обновление по IP
				return true;
			}
			return false;
		}
};


#endif