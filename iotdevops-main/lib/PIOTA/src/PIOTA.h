#ifndef PI_OTA_H
#define PI_OTA_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <Update.h>
#include <WiFi.h>

class PIOTA
{
private:
  boolean _isUpdating = false;
  boolean _isUpdated = false;

  WiFiClient client;

  String getDownloadUrl();
  bool downloadUpdate(String url);

public:
  PIOTA(){};

  void loop();
};

#endif
