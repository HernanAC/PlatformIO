
#include <PIWiFiHandler.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

void PIWIFI_CONNECTED_HANDLER(PIWiFiState *wifiState)
{
  if (!wifiState->_isConnecting)
  {
    return;
  }

  wifiState->_isConnecting = false;

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
