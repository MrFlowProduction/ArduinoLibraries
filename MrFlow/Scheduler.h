#ifndef Scheduler_h
#define Scheduler_h

/*

	Scheduler Module
	
	developed by Florian Szekely 
	Copyright (c) 2017
	
	
*/

#include <Arduino.h> // for byte data type



struct Schedule{
	Schedule(void (*f)(void *) = 0, char* _name = "", bool _enable = 1, uint16_t _interval = 0, unsigned long _timer = 0)
        : callback(f), name(_name), enable(_enable), interval(_interval), timer(_timer) {}
	char* name;
	bool enable;
	uint16_t interval;
	unsigned long timer;
	void (*callback)(); 
};




class Scheduler{
	public:	
	
	// Init Scheduler
	// count of schedule
	void init(byte count);
	
	// Add Schedule
	void add(void (*function)(), uint16_t interval, char* name, bool enable = true);
	
	// Run Scheduler
	// Need to call at loop
	void run(void);
	
	// Enable schedule by name
	void enableSchedule(char* name);
	
	
	// Disable schedule by name
	void disableSchedule(char* name);

	// Set Schedule Interval by name
	void setScheduleInterval(char* name, uint16_t newInterval);

	// Enable Scheduler
	void enable(void);

	// Disable Scheduler
	void disable(void);

	// Disable Scheduler
	void runAll(void);
	
	private:
	
	
	
};


#endif