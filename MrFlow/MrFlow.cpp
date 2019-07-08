#include <Arduino.h>
#include "MrFlow.h"



void MrFlow::blink(byte pin, byte count, int _delay){

	for(byte i = 0; i < count; i++){
		digitalWrite(pin, ON);
		delay(_delay);
		digitalWrite(pin, OFF);
		delay(_delay);
	}
}