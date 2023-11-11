#include "WiFi_connect.h"

// подключение в ВиФи
bool WiFi_Connected()
{
  if (WiFi.isConnected())
  {
    return true;
  }
  else
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
      if (count_attempt > 100)
      {
        Serial.println();
        Serial.println("WiFi connection failed");
        return false;
      }
    }
    Serial.println();
    Serial.print("WiFi connected. IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
}
// обновление прошивки по ВиФи по IP
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
}

// обновление прошивки
void OTA_begin(const char *mqtt_ota_update)
{
  begin_OTA_WiFi_to_IP(); // обновление по ВиФи
}
void OTA_update() 
{ 
  ArduinoOTA.handle(); 
} // обновление по ВиФи по IP
