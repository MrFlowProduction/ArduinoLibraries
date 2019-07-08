/*
>>>>> HIH71XX Library V1.0 <<<<<<

Created by Florian Szekely, May 24, 2015.
Company: Agro Services & Solutions Ltd.

Library for HIH71XX Humidity and Temperature Sensors.
*/

#include "Arduino.h"
#include "Wire.h"
#include "HIH71XX.h"

HIH71XX::HIH71XX()
{
	Wire.begin();	
}

byte HIH71XX::GetHihDatas(float *Hum, float *Temp){
	unsigned int H_dat, T_dat;
	byte _status;
	
	_status = fetchHumidityTemperature(&H_dat,&T_dat);
	
	if(_status == 0){
		*Hum = (float)H_dat * 6.10e-3;
		*Temp = (float)T_dat * 1.007e-2 - 40.0;
	}
	else{ *Hum = 0; *Temp = 0;}
	
	return _status;	
}

byte HIH71XX::fetchHumidityTemperature(unsigned int *p_H_dat, unsigned int *p_T_dat){
	byte address, Hum_H, Hum_L, Temp_H, Temp_L, _status;
      unsigned int H_dat, T_dat;
      address = 0x27;;
      Wire.beginTransmission(address); 
      Wire.endTransmission();
      delay(100);
      
      Wire.requestFrom((int)address, (int) 4);
      Hum_H = Wire.read();
      Hum_L = Wire.read();
      Temp_H = Wire.read();
      Temp_L = Wire.read();
      Wire.endTransmission();
      
      _status = (Hum_H >> 6) & 0x03;
      Hum_H = Hum_H & 0x3f;
      H_dat = (((unsigned int)Hum_H) << 8) | Hum_L;
      T_dat = (((unsigned int)Temp_H) << 8) | Temp_L;
      T_dat = T_dat / 4;
      *p_H_dat = H_dat;
      *p_T_dat = T_dat;
      return(_status);
}


String HIH71XX::FloatToString(float f, int num_digits){
	int f_int;
    int pows_of_ten[4] = {1, 10, 100, 1000};
    int multiplier, whole, fract, d, n;

	String outputText;
	
    multiplier = pows_of_ten[num_digits];
    if (f < 0.0)
    {
        f = -f;
        Serial.print("-");
    }
    whole = (int) f;
    fract = (int) (multiplier * (f - (float)whole));
	
	outputText = (String)whole;
	outputText += '.';
	
    for (n=num_digits-1; n>=0; n--) // print each digit with no leading zero suppression
    {
         d = fract / pows_of_ten[n];
         outputText += (String)d;
         fract = fract % pows_of_ten[n];
    }
	
	return outputText;
}