#ifndef WiFi_connect_h
#define WiFi_connect_h
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

//функции обратного вызова при подключении, при разрыве соединения
//WiFiEventHandler gotIpEventHandler, disconnectedEventHandler; 

#define mqttServer  "192.168.3.44"
#define mqttPort 1883
#define mqttUser "esp"
#define mqttPass "8266"
#define mqttClientId "wemos_1"
#define mqttTopicDeviceStatus "device/ota/esp1"
#define mqttDeviceStatusOn "online"
#define mqttDeviceStatusOff "offline"
#define mqttDeviceStatusRetained true
#define mqttDeviceStatusQos 1

class mqttObject {
private:
public:
	static WiFiClient wificlient;
	static PubSubClient mqttClient;
	static bool mqtt_connected();
};

bool WiFi_connected();				//подключение к ВиФи
void begin_OTA_WiFi_to_IP();  // обновление по IP
void WiFi_scan();							//поиск сетей
bool WiFi_loop();
//void mqtt_callback(char *topic, byte *payload, unsigned int length);
#endif