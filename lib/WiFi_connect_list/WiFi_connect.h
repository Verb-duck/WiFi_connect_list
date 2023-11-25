#ifndef WiFi_connect_h
#define WiFi_connect_h
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
public:
	static WiFiClient wificlient;
	static PubSubClient mqttClient;
  static char* mqttClientId;
  static char* mqttTopicDeviceStatus;
  static char* mqttTopicOta;

  static void name_device(const char* name); 
	static bool mqtt_connected();
};


bool WiFi_connected();				//подключение к ВиФи
void begin_OTA_WiFi_to_IP();  // обновление по IP
void WiFi_scan();							//поиск сетей
bool WiFi_loop();
//void mqtt_callback(char *topic, byte *payload, unsigned int length);
#endif