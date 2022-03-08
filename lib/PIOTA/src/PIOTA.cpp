#include <PIOTA.h>

#define VARIANT "esp32"
#define CURRENT_VERSION VERSION
#define FIRWARE_URL "http://us-central1-iotdevops.cloudfunctions.net/getDownloadUrl"


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
  HTTPClient http;
  Serial.print("[HTTP] Download begin...\n");

  http.begin(_wifiClient, url);

  Serial.print("[HTTP] GET...\n");

  int httpCode = http.GET();

  if (httpCode == 0)
  {
    return false;
  }

  Serial.printf("[HTTP] GET... code: %d\n", httpCode);

  if (httpCode != HTTP_CODE_OK)
  {
    return false;
  }

  int contentLength = http.getSize();
  Serial.println("contentLength : " + String(contentLength));

  if (contentLength <= 0)
  {
    Serial.println("There was no content in the response");
    _wifiClient.flush();
    return false;
  }

  bool canBegin = Update.begin(contentLength);

  if (!canBegin)
  {
    Serial.println("Not enough space to begin OTA");
    return false;
  }

  WiFiClient stream = http.getStream();
  Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");

  size_t written = Update.writeStream(stream);

  if (written == contentLength)
  {
    Serial.println("Written : " + String(written) + " successfully");
  }
  else
  {
    Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?");
  }

  if (!Update.end())
  {
    Serial.println("Error Occurred. Error #: " + String(Update.getError()));
    return false;
  }

  Serial.println("OTA done!");

  if (!Update.isFinished())
  {
    Serial.println("Update not finished? Something went wrong!");
    return false;
  }

  Serial.println("Update successfully completed. Rebooting.");
  ESP.restart();
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
