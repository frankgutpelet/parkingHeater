#include "Heater.hpp"

#define TURBO_PWM_VALUE 255
#define SILENT_PWM_VALUE 100
static const unsigned int tresholdTenthDegrees = 2;
void timer2Callback(void *pArg);

heater::heater(int relais1Pin, int relais2Pin, int relaisFanPin, base* viewer)
{
	this->relais1Pin = relais1Pin;
  this->relais2Pin = relais2Pin;
  this->relaisFanPin = relaisFanPin;
  this->viewer = viewer;
	this->isOn = false;
  this->timer = NULL;
	os_timer_setfn(&Timer2, timer2Callback, this);
	os_timer_arm(&Timer2, 1000, true);
  logger = Logger::instance();
  logger->Debug("Initialized Heater");

  pinMode(this->relais1Pin, OUTPUT);
  pinMode(this->relais2Pin, OUTPUT);
  
  for (int i=0;i<MAX_VALUES;i++)
  {
    this->getTmpValue();
  }
}
		
void heater::On(heaterTimer* timer)
{
	this->isOn = true;
  this->timer = timer;
  this->viewer->Set_state("ON");
  logger->Debug("Heater Switched On");
  this->fanDelay = false;
}
void heater::SetTemp(unsigned int tenthDegrees)
{
  this->tenthDegreesShould = tenthDegrees;
}
		
void heater::Off (void)
{
	digitalWrite(this->relais1Pin, LOW);
  digitalWrite(this->relais2Pin, LOW);
  this->viewer->Set_state("OFF");
  this->viewer->Set_heating("OFF");
	this->isOn = false;
	this->isHeating = false;
  logger->Debug("Heater Switched Off");
  this->fanDelay = true;
  logger->Debug("set Timer");
  this->viewer->Set_state("cooldown");
  this->timer->setTimer(5);
}
		
unsigned int heater::getTenthDegrees (void)
{
  unsigned long sum = 0;
  char temp[5];
  this->getTmpValue();
  for(int i=0;i<MAX_VALUES;i++)
  {
    sum += this->tmpValues[i];
  }

  sprintf(temp, "%.1f", ((float)sum / (MAX_VALUES * 10.0)));
  this->viewer->Set_tempIst(temp);

  return (unsigned int) sum / MAX_VALUES;
}

unsigned int heater::getTenthDegreesShould (void)
{
  return this->tenthDegreesShould;
}

void heater::timercb(void)
{
  unsigned int tenthdegrees = this->getTenthDegrees();
  unsigned int timer;
  if (NULL == this->timer)
  {
    return;
  }
  timer = this->timer->getTimer();
  this->viewer->Set_timer(String(timer));

  logger->Debug("timer" + String(timer));
  
  if ((this->fanDelay) && (0 >= this->timer->getTimer()))
  {
    logger->Debug("delay timer finished");
    analogWrite(this->relaisFanPin, 0);
    this->viewer->Set_state("OFF");
    return;
  }
    
  if (0 >= timer)
  {
    this->Off();
    this->fanDelay = true;
    logger->Debug("set Timer");
    this->viewer->Set_state("cooldown");
    this->timer->setTimer(5);
    logger->Debug("Timer set"); 
    return;
  }
 
  if (!this->isOn)
  {
    return;
  }
	if (tenthdegrees > this->tenthDegreesShould)
	{
		digitalWrite(this->relais1Pin, LOW);
    digitalWrite(this->relais2Pin, LOW);
    analogWrite(this->relaisFanPin, SILENT_PWM_VALUE);
		this->isHeating = false;
    logger->Debug("heating Off");
    this->viewer->Set_heating("OFF");
	}
	else if ((tenthdegrees <= (this->tenthDegreesShould - tresholdTenthDegrees)))
	{
		digitalWrite(this->relais1Pin, HIGH);
    digitalWrite(this->relais2Pin, HIGH);
    analogWrite(this->relaisFanPin, SILENT_PWM_VALUE);
    this->viewer->Set_heating("ON");
    if (this->turbo)
    {
      digitalWrite(this->relaisFanPin, TURBO_PWM_VALUE);
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
