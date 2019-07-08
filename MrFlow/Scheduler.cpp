#include <Arduino.h>
#include "Scheduler.h"


Schedule* schedules;

byte count = 0;
byte maxCount = 0;
bool isEnabled = true;

// Init Scheduler
void Scheduler::init(byte _count){

	maxCount = _count;
	schedules = new Schedule[maxCount];
	
}


// Add Schedule
void Scheduler::add(void (*function)(), uint16_t interval, char* name, bool enable){

	if(count >= maxCount || function == NULL || name == ""){  
	
	// DEBUG
	Serial.print("\"");
	Serial.print(name);
	Serial.println(F("\" schedule doesn't added"));
	
	return; }

	schedules[count] = Schedule(function, name, enable, interval);
	
	count++;
	
	// DEBUG
	Serial.print("\"");
	Serial.print(name);
	Serial.println(F("\" schedule added"));
}


// Run Scheduler
// Need to call at loop
void Scheduler::run(void){
	
	if(count == 0 || !isEnabled){ return; }
	
	for(byte i = 0; i < count; i++){
		
		// if Schedule is disabled then skip this task
		if(!schedules[i].enable){ continue; }
		
		// Check Timer
		if(schedules[i].timer <= millis()){
			
			// DEBUG
			Serial.print(F("Scheduler Callback: "));
			Serial.println(schedules[i].name);
			
			// Callback function
			schedules[i].callback();
			
			// Set Timer
			schedules[i].timer = schedules[i].timer + schedules[i].interval;
			
			
		}
	}	
}



// Enable schedule by name
void Scheduler::enableSchedule(char* name){

	for(byte i = 0; i < count; i++){
		
		if(schedules[i].name == name){
			schedules[i].enable = true;
			return;
		}
	}
		
}



// Disable schedule by name
void Scheduler::disableSchedule(char* name){

	for(byte i = 0; i < count; i++){
		
		if(schedules[i].name == name){
			schedules[i].enable = false;
			return;
		}
	}
		
}


// Set Schedule Interval by name
void Scheduler::setScheduleInterval(char* name, uint16_t newInterval){

	for(byte i = 0; i < count; i++){
		
		if(schedules[i].name == name){
			
			schedules[i].interval = newInterval;
			schedules[i].timer = schedules[i].timer + schedules[i].interval;
			
			return;
		}
	}
		
}


// Enable Scheduler
void Scheduler::enable(void){

	isEnabled = true;
}


// Disable Scheduler
void Scheduler::disable(void){
	
	isEnabled = false;
}


// Disable Scheduler
void Scheduler::runAll(void){
	
	for(byte i = 0; i < count; i++){
		
		// if Schedule is disabled then skip this task
		if(!schedules[i].enable){ continue; }
		
		// DEBUG
		Serial.print(F("Scheduler Callback: "));
		Serial.println(schedules[i].name);
		
		// Callback function
		schedules[i].callback();
			
		// Set Timer
		schedules[i].timer = schedules[i].timer + schedules[i].interval;
			
		
	}
	
}



