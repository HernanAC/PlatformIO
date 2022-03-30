#include <PIOTA.h>
#include <ESP8266httpUpdate.h>
#define VARIANT "esp8266"
#define CURRENT_VERSION VERSION
#define FIRWARE_URL "https://us-central1-iotdevops.cloudfunctions.net/getDownloadUrl"


String PIOTA::getDownloadUrl()
{
  HTTPClient http;
  String downloadUrl;

  Serial.println("[HTTP] begin...");

  String url = FIRWARE_URL;
  url += String("?version=") + CURRENT_VERSION + String("&variant=") + VARIANT;

  http.begin(_wifiClient, url);

  Serial.println("[HTTP] GET...");

  int httpCode = http.GET();

  if (httpCode == 0)
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return downloadUrl;
  }

  Serial.printf("[HTTP] GET... code: %d\n", httpCode);

  if (httpCode != HTTP_CODE_OK)
  {
    Serial.println("Device is up to date!");
    http.end();
    return downloadUrl;
  }

  String payload = http.getString();

  Serial.println(payload);
  downloadUrl = payload;

  http.end();

  return downloadUrl;
}

bool PIOTA::downloadUpdate(String url)
{
  Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");
  t_httpUpdate_return ret = ESPhttpUpdate.update(_wifiClient, url);

  switch(ret) {
    case HTTP_UPDATE_FAILED:
        Serial.println("[update] Update failed.");
        return false;
    case HTTP_UE_TOO_LESS_SPACE:
        Serial.println("[update] Update failed too less space.");
        return false;
    case HTTP_UE_SERVER_FILE_NOT_FOUND:
        Serial.println("[update] Update failed server file not found.");
        return false;
    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("[update] Update no Update.");
        return true;
    case HTTP_UPDATE_OK:
        Serial.println("[update] Update ok."); // may not be called since we reboot the ESP
        return true;
  }
  
  return true;
}

void PIOTA::loop()
{
  if (_isUpdated || _isUpdating || WiFi.status() != WL_CONNECTED)
  {
    return;
  }

  _isUpdating = true;

  String downloadUrl = getDownloadUrl();

  if (downloadUrl.length() > 0)
  {
    bool success = downloadUpdate(downloadUrl);
    if (success)
    {
      _isUpdated = true;
    }
    else
    {
      Serial.println("Error updating device");
    }
  }
  else
  {
    _isUpdated = true;
  }

  _isUpdating = false;
}
