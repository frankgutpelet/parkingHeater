#include <ESP8266WebServer.h>
#include <Arduino.h>
#include "heaterTimer.hpp"
#include "Logger.hpp"

#pragma once
#define MAX_VALUES 10

class heater
{
	public:
		heater(int relais1Pin, int relais2Pin);
		
		void On(heaterTimer* timer);
    void SetTemp(unsigned int tenthDegrees);
		void Off (void);
    void TurboOn(void){this->turbo = true;}   
    void TurboOff(void){this->turbo = false;}
    bool TurboActive(void){return this->turbo;}

    void setSpeeds(int silent, int turbo){this->speedSilent = silent; this->speedTurbo = turbo;}
		
		unsigned int getTenthDegrees (void);
    unsigned int getTenthDegreesShould (void);
		
		void timercb(void);

    bool IsOn(){return this->isOn;}
    bool IsHeating(){return this->isHeating;}
		
	private:
    void getTmpValue(void);
		unsigned int tenthDegreesShould;
		int relais1Pin;
    int relais2Pin;
    heaterTimer* timer;
    os_timer_t Timer2; 
    Logger* logger;
    bool isOn;
    bool turbo;
    bool isHeating;
    unsigned int tmpValuesNo = 0;
    unsigned int tmpValues[MAX_VALUES];
    int speedSilent = 100;
    int speedTurbo = 200;
};
