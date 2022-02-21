#include "Heater.hpp"

static const unsigned int tresholdTenthDegrees = 2;
void timer2Callback(void *pArg);

heater::heater(int relaisPin)
{
	this->relaisPin = relaisPin;
	this->isOn = false;
  this->timer = NULL;
	os_timer_setfn(&Timer2, timer2Callback, this);
	os_timer_arm(&Timer2, 1000, true);
}
		
void heater::On(unsigned int tenthDegrees, heaterTimer* timer)
{
	this->tenthDegreesShould = tenthDegrees;
	this->isOn = true;
  this->timer = timer;
}
		
void heater::Off (void)
{
	digitalWrite(this->relaisPin, LOW);
	this->isOn = false;
	this->isHeating = false;
  this->timer = NULL;
}
		
unsigned int heater::getTenthDegrees (void)
{
	/* TODO temperatur auslesen	*/
	return 200;
}

unsigned int heater::getTenthDegreesShould (void)
{
  return this->tenthDegreesShould;
}

void heater::timercb(void)
{
  if (NULL != this->timer)
  {
    if (0 >= this->timer->getTimer())
    {
      this->Off();
    }
  }
  
  if (!this->isOn)
  {
    return;
  }
	
	if (this->getTenthDegrees() > this->tenthDegreesShould)
	{
		digitalWrite(this->relaisPin, LOW);
		this->isHeating = false;
	}
	else if ((this->getTenthDegrees() <= (this->tenthDegreesShould - tresholdTenthDegrees)))
	{
		digitalWrite(this->relaisPin, HIGH);
		this->isHeating = true;
	}	
}

void timer2Callback(void *pArg)
{ 
  ((heaterTimer *) pArg)->timerCb();
} 
