#include "heaterTimer.hpp"

void timerCallback(void *pArg);


heaterTimer::heaterTimer(void)
{
  this->timerMinutes = 0;
  os_timer_setfn(&Timer1, timerCallback, this);
  os_timer_arm(&Timer1, 60000, true);
}

void heaterTimer::setTimer(unsigned int minutes)
{
  this->timerMinutes = minutes;
}

void heaterTimer::timerCb(void)
{
  if ((0 < this->timerMinutes)&& (60 >= timerMinutes)) // 61: infinity
  {
    this->timerMinutes--;
  }
}

bool heaterTimer::isOn (void)
{
  if (0 < this->timerMinutes)
  {
    return true;
  }
  return false;
}

unsigned int heaterTimer::getTimer(void)
{
  return this->timerMinutes;
}

void timerCallback(void *pArg)
{ 
  ((heaterTimer *) pArg)->timerCb();
} 
