#include "WiFi_connect.h"

// подключение в ВиФи
bool WiFi_connected()
{
  if (WiFi.status() == WL_CONNECTED)
  {     
    return true;
  }
  else     //переподключение к ВиФи
  {
    Serial.println();
    Serial.print("Connecting to WiFi ");
    // wifi connect
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passwordW);
    byte count_attempt = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
      count_attempt++;
      Serial.print("*");
      delay(500);
      if (count_attempt > 20)
      {
        Serial.println();
        Serial.println("WiFi connection failed");
        return false;
      }
    }
    Serial.println();
    Serial.print("WiFi connected. IP address: ");
    Serial.println(WiFi.localIP());

    begin_OTA_WiFi_to_IP();         //инициализация обновления прошшивки по IP
    return true;
  }
}
// обновление по IP
void begin_OTA_WiFi_to_IP()
{
  ArduinoOTA.onStart([]()
                     {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type); });
  ArduinoOTA.onEnd([]()
                   { Serial.println("\nEnd"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
  ArduinoOTA.onError([](ota_error_t error)
                     {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    } });
  ArduinoOTA.begin();
  ArduinoOTA.setPassword(passwordW);
  Serial.println("OTA update WiFi connected");
}

bool WiFi_loop()
{
  if (WiFi_connected()) // если есть подкоючение
  {
    ArduinoOTA.handle(); // проверим обновление по IP
    if (mqttObject::mqtt_connected())  // проверяем подключение к брокеру
    {
      mqttObject::mqttClient.loop(); // и отправляем сообщение
    }
    return true;
  }
  return false;
}
//поиск сетей асинхронный
void WiFi_scan() 
{
  WiFi.mode(WIFI_STA);
  // Disconnect from an AP if it was previously connected
  if (WiFi.status() == WL_CONNECTED)
  {     
    WiFi.disconnect();
  }
  static uint32_t timer_scan; 
  // WiFi.scanNetworks will return the number of networks found.
  if(millis() - timer_scan >= 5000)
  {
    timer_scan = millis();
	  Serial.println("Scan start");
    WiFi.scanNetworks(true);        //async scan
  }
  int n = WiFi.scanComplete();
  // n = 0 no networks found
  // n = -1 scan in progress
  // n = -2 scan not triggered
  if (n > 0) {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      Serial.print(WiFi.SSID(i));     //название
      Serial.print("\t");
      Serial.println(WiFi.RSSI(i));     //уровень сигнала, меньше лучше
    }
    WiFi.scanDelete();
  }
}
//************************************
//----class mqttObject---
WiFiClient mqttObject::wificlient;
PubSubClient mqttObject::mqttClient(mqttServer, mqttPort,wificlient);
//подключение к mqtt брокеру
bool mqttObject::mqtt_connected()
{
	if (!mqttClient.connected())
  {
    Serial.print("Connecting to MQTT ... ");
    //отправка LWT сообщения
    if (mqttClient.connect(mqttClientId, mqttUser, mqttPass,
      mqttTopicDeviceStatus, mqttDeviceStatusQos , mqttDeviceStatusRetained, mqttDeviceStatusOff))      
    {      
      Serial.println("connected MQTT Ok.");
      //отправим сообщение я в сети, online
      mqttClient.publish(mqttTopicDeviceStatus, mqttDeviceStatusOn,mqttDeviceStatusRetained);
    } 
    else
    {
      Serial.print("failed, error code: ");
      Serial.print(mqttClient.state());
      Serial.println("");
    }
    return mqttClient.connected();
  }
  return true;
}


