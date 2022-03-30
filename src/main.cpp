#include <PIWiFi.h>
#include <PIMQTT.h>
#include <PIOTA.h>
#include <PIKeyboard.h>


char* wifiSSID = "MARTHA CRUZ";  
char* wifiPassword = "19640910"; 
char *mqttServerIP = "broker.emqx.io";
int mqttPort = 1883;
char *mqttClientID = "KeyboardClient";

PIWiFi *wiFiController;
PIMQTT *mqttController;
PIOTA *otaManager;
PIKeyboard *keyboardManager;


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("Message arrived [" + String(topic) + "]");

  String message;

  for (int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }

  Serial.println(message);

  String stringTopic = String(topic);

  if (stringTopic == "gym/main/keyboard")
  {
    keyboardManager->handler(message);
  }

}

void setup()
{
  Serial.begin(115200);


  
  wiFiController = new PIWiFi(wifiSSID, wifiPassword, 500);
  mqttController = new PIMQTT(mqttServerIP, mqttClientID, mqttPort);
  mqttController->_mqttClient->setCallback(callback);

  otaManager = new PIOTA();
  keyboardManager = new PIKeyboard(500,mqttController->_mqttClient);

  
}

void loop()
{
  wiFiController->loop();
  mqttController->loop();
  otaManager->loop();
  keyboardManager->loop();
}
