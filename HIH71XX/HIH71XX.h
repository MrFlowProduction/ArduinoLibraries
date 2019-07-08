/*
>>>>> HIH71XX Library V1.0 <<<<<<

Created by Florian Szekely, May 24, 2015.
Company: Agro Services & Solutions Ltd.

Library for HIH71XX Humidity and Temperature Sensors.
*/
#ifndef HIH71XX_h
#define HIH71XX_h

#include <Arduino.h>
#include <Wire.h>

class HIH71XX{
  public:
    
	HIH71XX();
    
	byte GetHihDatas(float *Hum, float *Temp);
	
	String FloatToString(float f, int num_digits);
  
  private:	
	
	byte fetchHumidityTemperature(unsigned int *p_H_dat, unsigned int *p_T_dat);
    
};

#endif