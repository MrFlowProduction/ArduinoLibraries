#ifndef GsmM95_h
#define GsmM95_h

/*

	Quectel M95 GSM Module Library
	
	Working with Espressif ESP32 module
	
	developed by Florian Szekely 
	Copyright (c) 2017
	
	
*/

#include <Arduino.h> // for byte data type
#include "HardwareSerial.h"

#define NO			0
#define YES			1	
#define NORESULT	2	// Module is not response
#define FAIL 		3	// Reading FAIL/GSM modul is powered down
#define ERROR		4	// ERROR enum

#define CTRLZ		0x1A

#define GSM_TX_PIN 16

struct GsmTime{
	uint16_t year;
	byte month;
	byte day;
	byte hour;
	byte minute;
	byte second;
	bool valid;
};


class GsmM95{
	public:	
	
	
	// Init GSM Module with parameters
	void init(byte power_pin, byte ring_pin, byte wake_pin);
	
	// return GSM ring pin status
	bool isRing(void);
	
	// Return GSM Module power status (ON/OFF)
	bool powerStat(void);
	
	// Auto PowerOn or PowerOff GSM module
	bool power(void);
	
	// Power ON GSM module
	// return it was success or not
	bool powerOn(void);
	
	// PowerDown GSM module
	// Input parameter: 
	// TRUE if you would like to power down via AT Command
	// FALSE if you would like to power down with virtual button
	// return it was success or not
	bool powerDown(bool softDown);
	
	// Sending AT command to GSM module
	void sendCmd(char* command);
	
	// Sending String based command to GSM module
	void sendStringCmd(String command);
	
	// Return Sim Card insert status
	byte isSimCardInserted(void);
	
	// Get GSM Supply voltage/Battery Voltage
	float supplyVoltage(void);
	
	// Get GSM module serial number
	String serialNum(void);
	
	// Get Network Operator
	String networkOperator(void);
	
	// GSM module is Registrated on network
	byte isRegistrated(void);
	
	// GSM signal quality, return 255 if function couldn't read
	byte signalQuality(void);
	
	// Set Registration enabling on GSM module
	byte setRegistration(bool enable);
	
	// Get GPRS attached status
	byte isGprsAlive(void);
	
	// Get GPRS APN settings
	byte getGprsSettings(String &apn, String &username, String &password);
	
	// Set GPRS APN Settings
	bool setGprsSettings(String apn, String username, String password);
	
	// Attach GPRS registration
	bool attachGPRS(void);
	
	// Detach GPRS registration
	bool detachGPRS(void);
		
	// Get Local IP
	String getIP(void);
	
	// Set Transmission (step 1)
	// Input parameter: Transparent or Non-Transparent mode
	bool setTransmission(void);
	
	// Activate DPD context (step 2)
	bool activateDPD(void);
	
	// Connect To TCP Server / Opening Session
	// IP - Destination IP Address
	// port - Server service port
	bool openSession(String IP, uint16_t port);
	
	// Close TCP/IP Session
	bool closeSession(void);
	
	// Send data via TCP/IP connection
	bool sendViaTCP(String msg);
		
	// Waiting for GPRS connection
	bool waitForGprs();
	
	// HTTP Post action
	bool httpPost(String url, String body);
	
	// Closing Serial Connection
	void getSerial(void);
	
	// Set SSL config
	bool setSSL(void);
	
	// Connect TLS Server (SSL)
	// host - Server host address (URL or IP)
	// port - Server service port
	bool openSslSession(String host, uint16_t port);
	
	// Colse TLS Connection
	bool closeSslSession(void);
	
	// Send data via TLS
	bool sendDataSSL(String data);
	
	// Set GSM automatic time sync
	// (ENABLE or DISABLE)
	bool setTimeSync(bool enable);
	
	// Set default settings on module
	bool setDefaults(void);
	
	// Get Hardware clock time (RTC)
	GsmTime getHwdTime(void);
	
	
	private:
	
	byte GSM_POWER_PIN = 0; 
	byte GSM_RING_PIN = 0;
	byte GSM_WAKE_PIN = 0;
	//uint16_t BAUDRATE = 115200;
	char gsmbuf[128];
	byte gsmMsgSize;
	
	// Erease message buffer
	void erease_buf(void);
	
	// Add new char to GSM Message Buffer
	// Return true if the current char is the line end
	bool add_to_buffer(char c);

	// Flush Serial Bus buffer
	void flush_uart(void);
	
	// Get parameter from msg buffer
	String get_parameter_from_buffer(byte index);
	
	// Get Full response message
	String get_response_msg(void);
	
	// Waiting for response message
	// return true if the module is answered
	// return false if the function is timered out
	bool waiting_for_response(void);
	
	// Skip echo message from serial reading
	bool skip_echo_msg(void);
	
	// Saving to buffer response message
	bool save_response_msg(void);
	
	// Full Response Message collector
	bool collect_response_msg(void);
	
	// Check response message (is OK or NOT OK)
	bool check_result(void);
	
	// Recieve message from module with timeout (in millisecond)
	// Return received message
	String message_provider(long timeout);
	
	// CTRL+Z combination (SUB)
	void ctrlz(void);
	
	// Check String
	// return is number or not
	bool isValidNumber(String str);
	
};


#endif