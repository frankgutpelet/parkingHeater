#include <ESP8266WebServer.h>
#include <Arduino.h>
#include "heaterTimer.hpp"

#pragma once

class heater
{
	public:
		heater(int relaisPin);
		
		void On(unsigned int tenthDegrees, heaterTimer* timer);
		void Off (void);
		
		unsigned int getTenthDegrees (void);
    unsigned int getTenthDegreesShould (void);
		
		void timercb(void);
		
	private:
		unsigned int tenthDegrees;
		unsigned int tenthDegreesShould;
		int relaisPin;
		bool isOn;
		bool isHeating;
   heaterTimer* timer;
   os_timer_t Timer2; 
};
