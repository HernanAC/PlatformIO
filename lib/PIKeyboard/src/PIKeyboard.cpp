#include "PIKeyboard.h"
#include <Keypad.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE  (200)

PIKeyboard::PIKeyboard(int waitTime, PubSubClient *_client)
{
  _waitTime = waitTime;
  client = _client;
  pinMode(BUILTIN_LED, OUTPUT);
}

void PIKeyboard::handler(String action)
{
  if (action == "on")
  {
    digitalWrite(BUILTIN_LED, LOW);
  }

  if (action == "off")
  {
    digitalWrite(BUILTIN_LED, HIGH);
  }


  
}
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;
char customKey; 
char password2[5];
char* key_password = "1234";
byte indice = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
byte rowPins[ROWS] = {D1, D2, D3, D4}; 
byte colPins[COLS] = {D5, D6, D7, D8}; 
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};  
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


void PIKeyboard::loop()
{
  customKey = customKeypad.getKey();
  if(customKey){
    password2[indice]=customKey;
    indice++;
    Serial.print(customKey);  
  }
  if(indice==4){

    unsigned long now = millis();
    if (now - lastMsg > 2000) {
      lastMsg = now;
      ++value;
      snprintf (msg, MSG_BUFFER_SIZE, password2 , value);
      client->publish("estudiantesUdeAsot1", msg);
    }

    
    if(!strcmp(password2, key_password)){
      Serial.println("");
      Serial.println("Contraseña correcta");
      client->publish("gym/main/courtains","open");
      client->publish("gym/main/lights","on");
      indice = 0;
    }
    else{
      Serial.println("");
      Serial.println("Contraseña incorrecta");
      indice = 0;
      
    }
    delay(100);
  }
  
}
