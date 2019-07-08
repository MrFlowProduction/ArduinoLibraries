#ifndef SerialMaster_h
#define SerialMaster_h

/*

	Mr Flow Framework
	
	developed by Florian Szekely 
	Copyright (c) 2017
	
	
*/

#include <Arduino.h> // for byte data type


struct SerialEvent{

	SerialEvent(void (*f)(void *) = 0, char* _command = "", bool _enable = 1, char* _echo = "")
        : callback(f), command(_command), enable(_enable), echo(_echo) {}
	char* command;
	char* echo;
	bool enable;
	void (*callback)(); 

};


class SerialMaster{
	public:	
	
	void begin(byte eventCount);
	
	bool waitToSerial(int timeout = 0);

	String readLine(void);

	bool Add(void (*function)(), char* name, char* echo = "", bool enable = true);
	
	void InitSerialHandler(byte eventCount);
	
	void RunSerialHandler(void);
	
	
	private:
	
	
	
};


#endif