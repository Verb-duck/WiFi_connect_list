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
	protected:
		bool WiFi_connecting();				//подключение к ВиФи
		void begin_OTA_WiFi_to_IP();  // обновление по IP
		//mqtt
			WiFiClient wificlient;
			PubSubClient mqttClient;
			const char *mqttServer = "192.168.3.44";
			const int mqttPort = 1883;
			const char *mqttUser = "esp";
			const char *mqttPass = "8266";
			const char *mqttClientId;
			char *mqttTopicDeviceStatus;
			const char *mqttDeviceStatusOn 		= "online";
			const char *mqttDeviceStatusOff		= "offline";
			const bool mqttDeviceStatusRetained = true;
			const int mqttDeviceStatusQos = 1;
			void mqtt_callback(char *topic, byte *payload, unsigned int length);
			bool mqtt_connecting();

		public:
			WiFi_connect_list(const char *mqttClientId)
				:mqttClientId(mqttClientId) 
			{
				mqttTopicDeviceStatus = new char[16 + strlen(mqttClientId)];
				strcat(mqttTopicDeviceStatus, "device/");
				strcat(mqttTopicDeviceStatus, mqttClientId);
				strcat(mqttTopicDeviceStatus, "/status");
			}
			bool loop();       	
		
};


#endif