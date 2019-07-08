#ifndef StateEvent_h
#define StateEvent_h

/*

	Mr Flow Framework
	
	developed by Florian Szekely 
	Copyright (c) 2017
	
	
*/

#include <Arduino.h> // for byte data type


class StateEvent{
	public:	
	
	void newState(bool state);


	void changeState(void);


	bool isChanged(void);


	bool getValue(void);
	
	
	
	private:
	
	
	
};


#endif