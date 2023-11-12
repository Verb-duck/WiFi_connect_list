#ifndef WiFi_connect_list_h
#define WiFi_connect_list_h
#include <Arduino.h>
#include <ESP8266WiFi.h>        //wifi
#include <ESP8266mDNS.h>        //wifi
#include <ArduinoOTA.h>         //ota
#include <ESP8266httpUpdate.h>  //ota http
#include <PubSubClient.h>       //mqtt

#define ssid1 "5G OBLUCHATEL"
#define passwordW1 "00000000"
#define ssid "хуета"
#define passwordW "20192020"

bool WiFi_Connected();       // подключение в ВиФи    
void begin_OTA_WiFi_to_IP(); // обновление по ВиФи по IP
void OTA_begin(const char *mqtt_ota_update);// обновление прошивки, все в одном месте
void OTA_update();           // обновление по ВиФи по IP


#endif