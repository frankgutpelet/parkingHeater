#include <ESP8266WebServer.h>
#include <Arduino.h>

#pragma once

class heaterTimer
{
  public:
    heaterTimer ();
    void setTimer (unsigned int minutes);
    unsigned int getTimer(void);
    bool isOn (void);
    void timerCb ();

  private:
    int timerMinutes;
    os_timer_t Timer1; 
};
