
#include <PIWiFiHandler.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

void PIWIFI_IDLE_HANDLER(PIWiFiState *wifiState)
{
  if (wifiState->_isConnecting)
  {
    return;
  }

  Serial.print("Connecting to ");
  Serial.println(wifiState->_ssid);

  wifiState->_isConnecting = true;
  WiFi.begin(wifiState->_ssid, wifiState->_password);
}
