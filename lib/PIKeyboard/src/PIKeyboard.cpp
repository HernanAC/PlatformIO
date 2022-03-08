#include "PIKeyboard.h"

PIKeyboard::PIKeyboard(int pin, int waitTime)
{
  _waitTime = waitTime;

}

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
      client.publish("estudiantesUdeAsot1", msg);
    }

    
    if(!strcmp(password2, key_password)){
      Serial.println("");
      Serial.println("Contraseña correcta");
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
