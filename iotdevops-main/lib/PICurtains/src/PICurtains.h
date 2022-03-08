#ifndef PI_CURTAINS_H
#define PI_CURTAINS_H
#include <Arduino.h>
#include <ESP32Servo.h>

#include <PIMQTT.h>
class PICurtains : public PIMQTTHandler
{
private:
  int _waitTime = 500;
  int _pin;
  Servo *_servo;

public:
  PICurtains(int pin, int waitTime);

  void handle(String action);
};

#endif
