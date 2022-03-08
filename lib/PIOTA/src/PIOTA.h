#ifndef PI_OTA_H
#define PI_OTA_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

class PIOTA
{
private:
  boolean _isUpdating = false;
  boolean _isUpdated = false;

  WiFiClientSecure _wifiClient;

  String getDownloadUrl();
  bool downloadUpdate(String url);

public:
  PIOTA(){
    _wifiClient.setInsecure();
  };

  void loop();
};

#endif
