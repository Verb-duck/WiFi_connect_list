#ifndef WiFi_connect_h
#define WiFi_connect_h

#define DEBUGING 1

#include <Arduino.h>
#include <ESP8266WiFi.h>        //wifi
#include <ESP8266mDNS.h>        //wifi
#include <ArduinoOTA.h>         //ota
#include <ESP8266httpUpdate.h>  //ota http
#include <PubSubClient.h>       //mqtt
#include "mqtt_constant.h"      //топики, команды 
#define ssid "5G OBLUCHATEL"
#define passwordW "00000000"
//#define ssid "хуета"
//#define passwordW "20192020"

//функции обратного вызова при подключении, при разрыве соединения
//WiFiEventHandler gotIpEventHandler, disconnectedEventHandler; 


  
class mqttObject {
private:
	static WiFiClient wificlient;
	static PubSubClient mqttClient;
  static char* mqttClientId;
  static char* mqttTopicDeviceStatus;
  static char* mqttTopicOta;
  static char* mqttLocationDevice;
	static bool mqtt_connected();

public:
  mqttObject (const char* name_device,const char* location_device); 
  static void mqtt_loop();
  static void setTopicOta (const char* topic_ota);
};


bool WiFi_connected();				//подключение к ВиФи
void begin_OTA_WiFi_to_IP();  // обновление по IP
void WiFi_scan();							//поиск сетей
bool WiFi_loop();
//void mqtt_callback(char *topic, byte *payload, unsigned int length);
#endif