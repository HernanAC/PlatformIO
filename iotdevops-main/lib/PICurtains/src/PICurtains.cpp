#include "PICurtains.h"

PICurtains::PICurtains(int pin, int waitTime)
{
  _pin = pin;
  _waitTime = waitTime;
  _servo = new Servo();

  _servo->setPeriodHertz(50);
  _servo->attach(_pin, 1000, 2000);
}

void PICurtains::handle(String action)
{
  if (action == "open")
  {
    _servo->write(180);
    delay(_waitTime);
    _servo->write(90);
  }

  if (action == "close")
  {

    _servo->write(0);
    delay(_waitTime);
    _servo->write(90);
  }
}
