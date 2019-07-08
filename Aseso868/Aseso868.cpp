// Aseso868 Library for Node-Base-ControlPoint communication
// Created by Florian Szekely (florian.szekely@aseso.hu)
// Owner Agro Services & Solutions Kft.
// All right reserved (c) Copyright 2016
//
// Library contain all drive code for Hope Microelectronics HM-TRP-868S module
// Working with SoftwareSerial interface and/or Serial
// Tested Chips: ATMEGA328p-PU, ATMEGA2560-AU


#include "Aseso868.h"


Aseso868::Aseso868(void){
	
}


void Aseso868::Initial(uint8_t rxPin, uint8_t txPin, uint8_t enable_pin, uint8_t config_pin, uint8_t mode, uint8_t Addr){

	
	_rft = SoftwareSerial(rxPin,txPin);
	pinMode(rxPin, INPUT);
	pinMode(txPin, OUTPUT);
	
	currentMode = SLEEP_MODE;
	enablePin = enable_pin;
	configPin = config_pin;
	NewPackage = 0;
	
	
	OwnAddress = Addr;
	
	
	pinMode(enablePin,OUTPUT);
	pinMode(configPin,OUTPUT);
	
	SetLibMode(mode);
	
	SetMode(NORMAL_MODE);
	SetMode(SLEEP_MODE);
	
}



// Set Library Work Mode
void Aseso868::SetLibMode(uint8_t mode){
	
	libMode = mode;
	
	if(libMode == BASE){ 			sleepEnable = false; 	OwnAddress = BaseAddress = DEFAULT_SERVER_ADDR; }
	if(libMode == NODE){ 			sleepEnable = true; 	BaseAddress = DEFAULT_SERVER_ADDR; }
	if(libMode == CONTROL_POINT) { 	sleepEnable = false; 	BaseAddress = BROADCAST; }
	if(libMode == LISTENER) { 		sleepEnable = false; 	BaseAddress = 255; }
}


// Set Modul Mode (NORMAL/SLEEP/CONFIG)
void Aseso868::SetMode(uint8_t mode){
	
	if(mode == SLEEP_MODE && !sleepEnable){return;}
	
	currentMode = mode;
	
	
	if(mode == NORMAL_MODE){
		digitalWrite(enablePin,0);
		digitalWrite(configPin,1);
		delay(10);
		_rft.begin(DEF_BAUDRATE);
		return;
	}
	
	
	if(mode == SLEEP_MODE){
		digitalWrite(enablePin,1);
		digitalWrite(configPin,1);
		return;
	}
	
	
	if(mode == CONFIG_MODE){
		digitalWrite(enablePin,0);
		digitalWrite(configPin,0);
		delay(10);
		_rft.begin(DEF_BAUDRATE);
		return;
	}
}


void Aseso868::WaitFreeSpace(){
	while(_rft.available() > 0){
		_rft.flush();
		delay(random(5,30));
	}
}


// Send Datas
void Aseso868::SendData(uint8_t reciever, byte* datas, byte msgType){
	
	uint8_t datasize = sizeof(datas);
	uint8_t vectorsize = datasize + 6;
	
	byte package[vectorsize];
	
	package[0] = START;
	package[1] = vectorsize - 2;
	package[2] = reciever;
	package[3] = OwnAddress;
	package[4] = msgType;
	package[vectorsize - 1] = STOP;
	
	for(int i=0; i<datasize;i++){
		package[i + 5] = datas[i];
	}
	
	WaitFreeSpace();
	
	for(int i=0; i < vectorsize; i++){
		_rft.write(package[i]);
	}

}


// Send One Data
void Aseso868::SendOneData(uint8_t reciever, byte data, byte msgType){

	byte package[7];
	
	package[0] = START;
	package[1] = 5;
	package[2] = reciever;
	package[3] = OwnAddress;
	package[4] = msgType;
	package[5] = data;
	package[6] = STOP;
	
	WaitFreeSpace();
	
	for(int i=0; i < 7; i++){
		_rft.write(package[i]);
	}
}


// Sending ACK to reciever
void Aseso868::SendAck(){
	
	SendOneData(LastSender, 0, ACK);
	
}


// Clear Full Buffer
void Aseso868::ClearBuff(){
	for(int i = 0; i < BUFFER_SIZE; i++){
		buff[i] = 0;
	}
}


// Check Package Type
uint8_t Aseso868::CheckPackage(){
	
	if(NewPackage > 4){
		if(buff[NewPackage - 1] != STOP ||
		   buff[0] != OwnAddress){ ClearBuff(); return NOM; }
		   LastSender = buff[1];
		   
		return buff[2];   
	}
	
	ClearBuff(); 
	return NOM;
}



// Check Serial buffer for message
uint8_t Aseso868::CheckInbox(){
	
	if(_rft.available() > 0){
		
		// Search Package Start Point
		while(_rft.read() != START){
		
		// If no StartPoint return No Message
		if(_rft.available() == 0){ return NOM; }
		delay(10); }
		
		// Check Serial buffer
		if(_rft.available() == 0){ return NOM; }
		
		// Set Package Length
		LastLenght = _rft.read();
		
		// Read Full Package
		for(NewPackage = 0; NewPackage < LastLenght; NewPackage++){
			if(_rft.available() == 0){ return NOM; }
			buff[NewPackage] = _rft.read();
			delay(10);
		}
		
		_rft.flush();
		
		return CheckPackage();
	}
	
	return NOM;
}


// Get Data from package
byte* Aseso868::GetMessage(){
	
	byte data[LastLenght - 4];
	
	if(NewPackage > 4){
		for(int i = 3; i < LastLenght - 1; i++){
			data[i-3] = buff[i];
		}
	}
	
	SendAck();

	ClearBuff();
	
	return data;
}


// Can ask LastSender Address
byte Aseso868::GetSender(){
	return LastSender;
}


// Wait ACK with timout
bool Aseso868::WaitACK(){
	AckTimeout = millis() + ACK_TIMOUT;
	
	while(AckTimeout > millis()){
		if(CheckInbox() == ACK){ return true; }
		delay(10);
	}
	
	return false;
}


// Send Simple Text Message
bool Aseso868::SendMsg(char* text){
	
	SetMode(NORMAL_MODE);
	
	byte dat[sizeof(text)];
	
	for(int i = 0; i< sizeof(text); i++){
		dat[i] = (byte)text[i];
	}
	
	_rft.flush();
	
	for(int i = 0; i < MAX_REPEAT; i++){
		SendData(BaseAddress, dat, MSG);
		delay(100);
		if(WaitACK()){ SetMode(SLEEP_MODE); return true; }
	}
	
	SetMode(SLEEP_MODE);	
	
	return false;
	
}