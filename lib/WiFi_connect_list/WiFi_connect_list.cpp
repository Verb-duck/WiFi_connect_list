#include "WiFi_connect_list.h"

// подключение в ВиФи
bool WiFi_connect_list::WiFi_connecting()
{
  if (WiFi.isConnected())
  {     
    return true;
  }
  else     //переподключение к ВиФи
  {
    Serial.println();
    Serial.println("Connection failed! Fixing");
    // wifi connect
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passwordW);
    byte count_attempt = 0;
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      count_attempt++;
      Serial.print("*");
      if (count_attempt > 50)
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
// обновление прошивки по ВиФи по IP
void WiFi_connect_list::begin_OTA_WiFi_to_IP()
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
}
//обработчик сообше
void WiFi_connect_list::mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived ["); Serial.print(topic); Serial.print("] ");
  for (int i = 0; i < length; i++) Serial.print((char)payload[i]); Serial.println();

  if ((char)payload[0] == '1')
  {    
  }
  else
  {
  }
}
//подключение к mqtt брокеру
bool WiFi_connect_list::mqtt_connecting()
{
  if (!mqttClient.connected())
  {
    mqttClient.setClient(wificlient);
    mqttClient.setServer(mqttServer, mqttPort);
    Serial.print("Connecting to MQTT ... ");
    // Attempt to connect
    if (mqttClient.connect(mqttClientId, mqttUser, mqttPass,
      mqttTopicDeviceStatus, mqttDeviceStatusQos , mqttDeviceStatusRetained, mqttDeviceStatusOff))      
    {      
      Serial.println("connected MQTT Ok.");
      //отправим сообщение я в сети
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

bool WiFi_connect_list::loop()
{
  if (WiFi_connecting()) // если есть подкоючение
  {
    ArduinoOTA.handle(); // проверим обновление по IP
    if (mqtt_connecting())  // проверяем подключение к брокеру
    {
      mqttClient.loop(); // и отправляем сообщение
    }
    return true;
  }
  return false;
}

