#ifndef PI_KEYBOARD_H
#define PI_KEYBOARD_H
#include <Arduino.h>
#include <Keypad.h>
#include <PubSubClient.h>


class PIKeyboard
{
private:
  int _waitTime = 500;
  PubSubClient *client;


public:
  PIKeyboard(int waitTime, PubSubClient *_client);


  void loop();
  void handler(String action);
};

#endif
