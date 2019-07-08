#ifndef Aseso868_h
#define Aseso868_h

#define LIBVERSION "1.0.0"

#include <SoftwareSerial.h>
#include <Arduino.h> // for byte data type, gpio handling


// Package Types
#define NOM 	0x00	// No Message
#define ACK 	0x63	// ACK
#define ENB 	0x62	// Enable Communication
#define MSG 	0x01	// Text Message
#define DAT		0x02	// Data
#define POST 	0x03	// Question 
#define WHOAMI	0x04	// Ask from base own address
#define SERVER	0x05	// Request from server


// Modes
#define NORMAL_MODE 0	// Normal mode
#define SLEEP_MODE	1	// Chip Sleep mode 1uA Power
#define CONFIG_MODE	2	// Chip Configuration Mode


// Work Modes
#define BASE			0	// This library will be working as Base Point. Important: ONE wireless network ONE base point!!!
#define NODE			1	// This library will be working as Node/Energy save mode. No listening, only send package or ask information
#define CONTROL_POINT	2	// This library will be working as Control Point Centre. Only listening in the network and it can ask from the base.
#define LISTENER		3	// This library will be working as Phantom Listener. It can listening but can't ask or sending.


// START/STOP Bytes
#define START 	0xFF		// Package Start Byte
#define STOP	0xFF		// Package Stop Byte

// Defaults
#define DEFAULT_SERVER_ADDR	0x01	// Default Server Address
#define BROADCAST 			0x00	// Broadcast Address
#define BUFFER_SIZE			100		// Buffer Size
#define DEF_BAUDRATE		9600	// Default Baudrate
#define ACK_TIMOUT			1000	// ACK timout
#define MAX_REPEAT			3		// Repeat count for failed sending

class Aseso868{
	public:
	
		Aseso868(void);
	
		SoftwareSerial _rft = SoftwareSerial(11,10);
		
		// Initial Device and UART Port
		void Initial(uint8_t rxPin, uint8_t txPin, uint8_t enable_pin, uint8_t config_pin, uint8_t mode, uint8_t Addr);
		
		uint8_t CheckInbox(void);
		
		byte* GetMessage(void);
		
		byte GetSender(void);
		
		bool SendMsg(char* text);
		
		
	private:
	
		// Functions
		void SendAck(void);
	
		void WaitFreeSpace(void);
		
		void SendData(uint8_t reciever, byte* datas, byte msgType);
		
		void SendOneData(uint8_t reciever, byte data, byte msgType);
	
		void SetLibMode(uint8_t mode);
		
		void SetMode(uint8_t mode);
		
		uint8_t CheckPackage(void);
		
		bool WaitACK(void);
		
		void ClearBuff(void);
		
		
		// Variables:
		
		uint8_t LastLenght;
		
		uint8_t OwnAddress;
		
		uint8_t BaseAddress;
	
		uint8_t enablePin;
		
		uint8_t configPin;
		
		uint8_t currentMode;
		
		uint8_t libMode;
		
		bool sleepEnable;
		
		unsigned long AckTimeout;
		
		byte buff[100];
		
		uint8_t NewPackage;
		
		uint8_t LastSender;
		
};

#endif