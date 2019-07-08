#include <Arduino.h>
#include "SerialMaster.h"


SerialEvent * serial_events;
byte serial_events_count;
byte serial_max_events_count;


void SerialMaster::begin(byte eventCount){

	serial_events = new SerialEvent[eventCount];
	serial_max_events_count = eventCount;
	
}



bool SerialMaster::waitToSerial(int timeout){
	
	unsigned long timer = 0;
	
	if(timer > 0){
	
		timeout = millis() + timer;
	}	
	
	
	while(Serial.available() == 0){
		if(timeout > 0){
			if(timer < millis()){
				return false;
			}
		}
		delay(1);
	}
	
	return true;
	
}



String SerialMaster::readLine(void){
	
  //waitToSerial();

  String line = "";
  char c;

  while(Serial.available() > 0){
    
	c = (char)Serial.read();
    if(c == '\r'){ continue; }
    if(c == '\n'){ return line; }

    line += c;
    
    delay(1);
  }
  
  

  return line;
}



void SerialMaster::InitSerialHandler(byte eventCount){
	serial_events = new SerialEvent[eventCount];
	serial_max_events_count = eventCount;
}


// Add new Event
bool SerialMaster::Add(void (*function)(), char* command, char* echo, bool enable){

	serial_events_count++;
	
	if(serial_events_count > serial_max_events_count){ return false; }
	
	serial_events[serial_events_count - 1] = SerialEvent(function, command, enable, echo);
	
}

// Event/Command handler
void SerialMaster::RunSerialHandler(void){
	
	if(Serial.available() > 0){
	
		String command = readLine();
		
		// DEBUG
		//Serial.println(command);
		
		for(byte i=0; i < serial_events_count; i++){
			
			if(String(serial_events[i].command) == command){
				
				Serial.println(serial_events[i].echo);
				
				if(serial_events[i].enable) { serial_events[i].callback(); 
					
				}
				return;
			}
		}
	}
}



