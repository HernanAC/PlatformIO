#ifndef PI_KEYBOARD_H
#define PI_KEYBOARD_H
#include <Arduino.h>
#include <Keypad.h>


class PIKeyboard
{
private:
  int _waitTime = 500;
  

public:
  PIKeyboard(int pin, int waitTime);


  void loop();
};

#endif
