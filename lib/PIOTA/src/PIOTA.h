#ifndef PI_OTA_H
#define PI_OTA_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

class PIOTA
{
private:
  boolean _isUpdating = false;
  boolean _isUpdated = false;

  WiFiClient _wifiClient;

  String getDownloadUrl();
  bool downloadUpdate(String url);

public:
  PIOTA(){};

  void loop();
};

#endif
