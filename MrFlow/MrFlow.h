#ifndef MrFlow_h
#define MrFlow_h

/*

	Mr Flow Framework
	
	developed by Florian Szekely 
	Copyright (c) 2017
	
	
*/

#include <Arduino.h> // for byte data type

#define NO			0
#define YES			1
#define OFF			0
#define ON			1	
#define UNLOCKED	0
#define LOCKED		1	
#define NOEVENT	3

#define CTRLZ		0x1A







class MrFlow{
	public:	
	
	void blink(byte pin, byte count, int _delay);
	
	
	
	private:
	
	
	
};


#endif