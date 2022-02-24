#include "Heater.hpp"

#define TURBO_PWM_VALUE 150
#define SILENT_PWM_VALUE 100
static const unsigned int tresholdTenthDegrees = 2;
void timer2Callback(void *pArg);

heater::heater(int relais1Pin, int relais2Pin)
{
	this->relais1Pin = relais1Pin;
  this->relais2Pin = relais2Pin;
	this->isOn = false;
  this->timer = NULL;
	os_timer_setfn(&Timer2, timer2Callback, this);
	os_timer_arm(&Timer2, 1000, true);
  logger = Logger::instance();
  logger->Debug("Initialized Heater");

  for (int i=0;i<MAX_VALUES;i++)
  {
    this->getTmpValue();
  }
}
		
void heater::On(heaterTimer* timer)
{
	this->isOn = true;
  this->timer = timer;
  logger->Debug("Heater Switched On");
}
void heater::SetTemp(unsigned int tenthDegrees)
{
  this->tenthDegreesShould = tenthDegrees;
}
		
void heater::Off (void)
{
	digitalWrite(this->relais1Pin, LOW);
 digitalWrite(this->relais2Pin, LOW);
	this->isOn = false;
	this->isHeating = false;
  this->timer = NULL;
  logger->Debug("Heater Switched Off");
}
		
unsigned int heater::getTenthDegrees (void)
{
  unsigned long sum = 0;
  for(int i=0;i<MAX_VALUES;i++)
  {
    sum += this->tmpValues[i];
  }
  return (unsigned int) sum / MAX_VALUES;
}

unsigned int heater::getTenthDegreesShould (void)
{
  return this->tenthDegreesShould;
}

void heater::timercb(void)
{
  unsigned int tenthdegrees = this->getTenthDegrees();
  this->getTmpValue();
  
  if (NULL != this->timer)
  {
    if (0 >= this->timer->getTimer())
    {
      this->Off();
      logger->Debug("Timer expired");
    }
  }
  
  if (!this->isOn)
  {
    return;
  }
	
	if (tenthdegrees > this->tenthDegreesShould)
	{
		digitalWrite(this->relais1Pin, LOW);
    digitalWrite(this->relais2Pin, LOW);
		this->isHeating = false;
    logger->Debug("heating Off");
	}
	else if ((tenthdegrees <= (this->tenthDegreesShould - tresholdTenthDegrees)))
	{
		digitalWrite(this->relais1Pin, HIGH);
    analogWrite(this->relais2Pin, SILENT_PWM_VALUE);
    if (this->turbo)
    {
      digitalWrite(this->relais2Pin, TURBO_PWM_VALUE);
    }
		this->isHeating = true;
    logger->Debug("heating ON");
	}	
}

void heater::getTmpValue (void)
{
  this->tmpValues[tmpValuesNo] = (analogRead(A0) * 1024.0 /450);
  tmpValuesNo++;

  if (MAX_VALUES <= tmpValuesNo)
  {
    tmpValuesNo = 0;
  }
}

void timer2Callback(void *pArg)
{ 
  ((heater *) pArg)->timercb();
} 
