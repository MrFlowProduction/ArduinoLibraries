#include "HardwareSerial.h"     // ESP32 other UART port
#include "GsmM95.h"


HardwareSerial gsm_uart(2);


void GsmM95::init(byte power_pin, byte ring_pin, byte wake_pin){
	
	GSM_POWER_PIN = power_pin;
	GSM_RING_PIN = ring_pin;
	GSM_WAKE_PIN = wake_pin;
	//BAUDRATE = baudrate;
	
	pinMode(GSM_POWER_PIN, OUTPUT);
	pinMode(GSM_RING_PIN, INPUT);
	pinMode(GSM_WAKE_PIN, OUTPUT);
	gsm_uart.begin(115200);
}


// GSM Ring Status
bool GsmM95::isRing(void){

	return digitalRead(GSM_RING_PIN);
	
}


// Return GSM Power Status (ON/OFF)
bool GsmM95::powerStat(void){

	return digitalRead(GSM_TX_PIN);
	
}


//_________________________________________________________________ Private Functions ____________________________


// Erease GSM Message Buffer
void GsmM95::erease_buf(void){
  for(byte i = 0; i < 128; i++){
    gsmbuf[i] = 0;
  }
  gsmMsgSize = 0;
}


// Add new char to GSM Message Buffer
// Return true if it is the message endpoint
bool GsmM95::add_to_buffer(char c){

  if(c == '\n'){ return true; }

  if(c != '\r' && c != '"'){
  
    gsmbuf[gsmMsgSize] = c;
    
    gsmMsgSize++;
    
    if(gsmMsgSize == 255){
      gsmMsgSize = 0;
    }

  }

  return false;

}


// Flush GSM Serial bus buffer
void GsmM95::flush_uart(void){
  
  while(gsm_uart.available() > 0){
    gsm_uart.read();
    delay(2);
  }
  
  //gsm_uart.flush();
}



// Return Selected index of splitted values from response message
String GsmM95::get_parameter_from_buffer(byte index){

  if(gsmMsgSize == 0) { return ""; }

  byte count = 1;

  // DEBUG
  //Serial.print(F("MSG Size: "));
  //Serial.println(gsmMsgSize, DEC);

  

  for(byte i = 0; i < gsmMsgSize; i++){
    if(gsmbuf[i] == ','){ count++; }
  }

  // DEBUG
  //Serial.print(F("Count: "));
  //Serial.println(count, DEC);

  if(index > count) { return ""; }

  byte indexer = 1;
  String value = "";

  for(byte i = 0; i < gsmMsgSize; i++){
    
    if(gsmbuf[i] == ','){ indexer++; continue; }

    if(indexer == index){
      value += gsmbuf[i];
	  
	  // DEBUG
      //Serial.print(gsmbuf[i]);
    }
    
  }

  return value;
  
}


// Get Full response message
String GsmM95::get_response_msg(void){

  if(gsmMsgSize == 0) { return ""; }

  String value = "";

  for(byte i = 0; i < gsmMsgSize; i++){

    value += gsmbuf[i];
    
  }

  return value;
  
}




// Waiting for uart reaction
// return FALSE if the task is timed out
bool GsmM95::waiting_for_response(void){

  if(gsm_uart.available() > 0){ return true; }

  // DEBUG
  //Serial.println(F("[TASK] Waiting from incoming datas from GSM"));

  unsigned long gsmTimeout = millis() + 1000;

  while(gsm_uart.available() == 0){ 
    
    if(gsmTimeout <= millis()){ 

      // DEBUG
      //Serial.println(F("[FAIL] Timeout GSM response waiting"));
      
      return false; } 
      
    delay(1); 
  }

  // DEBUG
  //Serial.println(F("[DONE] Datas is coming from GSM..."));

  return true;
  
}



// Skip echo message from response text
// return FALSE if the task is timed out
bool GsmM95::skip_echo_msg(void){

  // DEBUG
  //Serial.println(F("[TASK] Skip echo message"));

  unsigned long gsmTimeout = millis() + 1000;

  while(true){
	  
	// Detect Timeout 
    if(gsmTimeout <= millis()){ 

      // DEBUG
      //Serial.println(F("[FAIL] Timeout GSM echo skip"));
      
      return false; } 
    
	// Read Serial if it is available
    while(gsm_uart.available() > 0){
	
		// Detecting end of the echo message
		if(gsm_uart.read() == ':'){ 
			// delete first white space from buffer
			if(gsm_uart.available() > 0){ gsm_uart.read(); }
			return true; }
	    delay(1);
    }
    
    delay(1);
  }
  
}




// GSM read Uart message
// Waiting for message with timout
// return got new message or not
bool GsmM95::save_response_msg(void){

  // DEBUG
  //Serial.println(F("[TASK] Collecting incoming datas"));

  unsigned long timeout = millis() + 2000;

  // Eresase Buffer
  erease_buf();

  while(true){   

    while(gsm_uart.available() > 0){
      
	  // saving char to message, and detecting response message end
      if(add_to_buffer((char)gsm_uart.read())){
        
        flush_uart();

        // DEBUG
        //Serial.println(F("[DONE] Response message collected!"));
		//Serial.println(gsmbuf);
        
        return true;
      }

      delay(1);
    }

    // Detect Timout
    if(timeout < millis()){ 

      // DEBUG
      //Serial.println(F("[FAIL] Timeout response waiting"));
      
      return false; }

    delay(1);
  }
  
}


// Waiting for module message
String GsmM95::message_provider(long timeout){

  unsigned long gsmTimeout = millis() + timeout;

  while(gsm_uart.available() == 0){ 
    
    if(gsmTimeout <= millis()){ 
      
      return "timeout"; } 
      
    delay(1); 
  }

  // Eresase Buffer
  erease_buf();

  while(gsm_uart.available() > 0){
      
	  add_to_buffer((char)gsm_uart.read());

      delay(1);
  }

  
  return get_response_msg();
  
}




// Waiting and Collect GSM response message
bool GsmM95::collect_response_msg(void){
  
  if(!waiting_for_response()){ return false; }

  if(!skip_echo_msg()){ return false; }

  if(!save_response_msg()){ return false; }

  return true;
}


//content.indexOf("Teststring") > 0
// Check result
// if response message is OK return true
// if response message not Ok or ran out of timeout return false
bool GsmM95::check_result(void){
  
  if(!save_response_msg()){ return false; }
  
  String result = get_response_msg();
  
  if(result.indexOf("OK") == 0){ return false; }

  return true;
}


// Send CTRL+Z combination to GSM module
void GsmM95::ctrlz(void){
	gsm_uart.println((char)0x1A); // Sending CTRL + Z combination
}


// Check String
// return is number or not
bool GsmM95::isValidNumber(String str){

	bool isNum=false;
	if( str.charAt(0) != '+' && str.charAt(0) != '-' && !isDigit(str.charAt(0)) ) return false;

	for(byte i=1;i<str.length();i++)
	{
		if(!(isDigit(str.charAt(i)) || str.charAt(i) == '.')) return false;
	}
	
	return true;
}


//_________________________________________________________________ Public Functions ____________________________



// Send AT command to GSM
// Return it was succeeded?
void GsmM95::sendCmd(char* command){

  //Debug
  //Serial.print(F("[TASK] GSM Execute: "));
  //Serial.println(command);

  erease_buf();
  flush_uart();

  gsm_uart.println(command);

}


// Closing Serial Connection
void GsmM95::getSerial(void){
	
	Serial.print("GSM <-> USB");

  if(!powerStat()){ powerOn(); }
    

  String temp = "";
  char c;

  while(true){
    
    if(Serial.available() > 0){
      
      delay(1);
      
      while(Serial.available() > 0){
        
        c = Serial.read();
        if(c == '\r'){ continue; }
        if(c == '#'){ c = 0x1A; }
        temp += c;
        
        delay(1);
      }

      gsm_uart.println(temp);
      temp = "";
      delay(1);
    }


    if(gsm_uart.available() > 0){
      
      delay(1);
      
      while(gsm_uart.available() > 0){
        
        c = gsm_uart.read();
        if(c == '\r'){ continue; }
        temp += c;

        delay(1);
      }

     Serial.println(temp);
     temp = ""; 
     delay(1);     
    }
    
  }

}


// Send AT command to GSM
// Return it was succeeded?
void GsmM95::sendStringCmd(String command){

  //Debug
  //Serial.print(F("[TASK] GSM Execute: "));
  //Serial.println(command);

  erease_buf();
  flush_uart();

  gsm_uart.println(command);

}





bool GsmM95::powerOn(void){
	
	if(powerStat()){ return true; }

	unsigned long timeout = millis() + 2000;
  
	//Serial.println("[TASK] - Try power on GSM");
    digitalWrite(GSM_POWER_PIN, HIGH);

    while(!powerStat()){
       
      if(timeout <= millis()){
        digitalWrite(GSM_POWER_PIN, LOW);
        //Serial.println(F("[TIMEOUT ERROR] - GSM module not working"));
        return false; }
        delay(10);
    }

    delay(1000);
    
    digitalWrite(GSM_POWER_PIN, LOW);

    //Serial.println(F("[DONE] - GSM is powered ON"));

    return true;
	
}


// Power Down GSM module
bool GsmM95::powerDown(bool softDown){
  
  if(!powerStat()){ return true; }
  //Serial.println("[TASK] - Try power down GSM");

  if(softDown){
	  
    sendCmd("AT+QPOWD = 1");
    
    unsigned long timeout = millis() + 4000;
    
    while(powerStat()){
       
      if(timeout <= millis()){
        //Serial.println(F("[TIMEOUT ERROR] - GSM not powered down"));
        return false; }
        delay(10);
      }
  }
  else{
    digitalWrite(GSM_POWER_PIN, HIGH);

    delay(1000);
    
    digitalWrite(GSM_POWER_PIN, LOW);

    delay(1000);
  }
  
    
  // Check GSM module, Is powered Down or not
    if(!powerStat()){
      //Serial.println(F("[DONE] - GSM is powered OFF"));
      return true;
    }
    
    //Serial.println(F("[FAIL] - GSM is keep power ON"));
    return false;
}


// GSM module auto PowerOn or OFF
bool GsmM95::power(void){

  if(!powerStat()){
    powerOn();
  }
  else{
    powerDown(false);
  }
  
  return powerStat();
	
}




// Ask GSM module from SIM Card Status
byte GsmM95::isSimCardInserted(void){
	
  if(!powerStat()){ return FAIL; }

  sendCmd("AT+QSIMSTAT?");

  if(collect_response_msg()){

    String result = get_parameter_from_buffer(2);

    if(result != ""){
      if(result == "1"){ return YES; }

      return NO;
    }
	
	return NORESULT;
  }

  return ERROR;
  
}




// Get GSM Supply Voltage (in volts)
float GsmM95::supplyVoltage(void){
	
  if(!powerStat()){ return FAIL; }
  
  sendCmd("AT+CBC");

  if(collect_response_msg()){

    String result = get_parameter_from_buffer(3);

    if(result != ""){
      float value = (float)result.toInt();
      value /= 1000.0;
      return value;
    }
  }

  return -99999;
}




// Get GSM Serial Number
String GsmM95::serialNum(void){

  sendCmd("AT+CGSN?");

  if(collect_response_msg()){
    return get_response_msg();
  }

  return "null";
}



// Get GSM Operator
String GsmM95::networkOperator(void){
	
  if(!powerStat()){ return "null"; }

  sendCmd("AT+COPS?");

  if(collect_response_msg()){
    return get_parameter_from_buffer(3);
  }

  return "null";
}


// GSM module registrated on the network or not
byte GsmM95::isRegistrated(void){
	
  if(!powerStat()){ return FAIL; }

  sendCmd("AT+CREG?");

  if(collect_response_msg()){

    String result = get_parameter_from_buffer(2);

    if(result != ""){
      if(result == "1"){ return YES; }

      return NO;
    }
	
	return NORESULT;
  }

  return ERROR;
  
}



// Return GSM Signal Quality (0-33)
byte GsmM95::signalQuality(void){
	
  if(!powerStat()){ return 255; }
	
  sendCmd("AT+CSQ");

  if(collect_response_msg()){

    String result = get_parameter_from_buffer(1);
	
	if(result == ""){ return 255; }

    return (byte)result.toInt();
  }

  return 255;
  
}



// Set GSM Module network registration
byte GsmM95::setRegistration(bool enable){
	
  if(!powerStat()){ return 255; }

  if(enable){ sendCmd("AT+CREG=1"); }
  else{ sendCmd("AT+CREG=0"); }

  if(collect_response_msg()){

    return YES;
    
  }

  return NO;
  
}



// Get GPRS attached status
byte GsmM95::isGprsAlive(void){
	
  if(!powerStat()){ return FAIL; }

  sendCmd("AT+CGATT?");

  if(collect_response_msg()){

    String result = get_parameter_from_buffer(1);
	
	if(result == ""){ return NORESULT; }
	
    if(result == "1"){ return YES; }
	
	return NO;
  }

  return ERROR;
  
}



// Get GPRS settings
byte GsmM95::getGprsSettings(String &apn, String &username, String &password){
	
  if(!powerStat()){ return FAIL; }

  sendCmd("AT+QIREGAPP?");

  if(collect_response_msg()){
  
    apn 		= get_parameter_from_buffer(1);
	username 	= get_parameter_from_buffer(2);
	password 	= get_parameter_from_buffer(3);
	
	return YES;
	
  }

  return ERROR;
  
}



// Get GPRS settings
bool GsmM95::setGprsSettings(String apn, String username, String password){
	
  if(!powerStat()){ return FAIL; }

  sendStringCmd(String("AT+QIREGAPP=\"" + apn + "\",\"" + username + "\",\"" + password + "\""));

  if(collect_response_msg()){
	
	return YES;
	
  }

  return NO;
  
}



// Attach GPRS registration
bool GsmM95::attachGPRS(void){
	
  if(!powerStat()){ return false; }

  sendCmd("AT+QIACT");

  return check_result();
  
}



// Detach GPRS registration
bool GsmM95::detachGPRS(void){
	
  if(!powerStat()){ return false; }

  sendCmd("AT+QIDEACT");

  return check_result();
  
}

// Get Local IP address
String GsmM95::getIP(void){
	
  if(!powerStat()){ return "null"; }

  sendCmd("AT+QILOCIP");

  if(collect_response_msg()){
	
	String ip = get_response_msg();
	
	if(ip == ""){ return "null"; }

	return ip;
	
  }
  
  return "no response";
  
}


// Set Transmission (Step 1)
bool GsmM95::setTransmission(void){
	
  if(!powerStat()){ return false; }
  
	sendCmd("AT+QIFGCNT=0");	// Set the context 0 as FGCNT
	if(!check_result()){
	Serial.println("[FAIL] - set FGCNT context");
	return false; }
	
	sendCmd("AT+QIMUX=0");		// Disable MUXIP function
	if(!check_result()){ 
	Serial.println("[FAIL] - disable MUXIP");
	return false; }
	
	sendCmd("AT+QIMODE=0");		// Set the session mode as non-transparent
	if(!check_result()){ 
	Serial.println("[FAIL] - set non-tranparent mode");
	return false; }
	
	sendCmd("AT+QIDNSIP=0");	// Use IP address to establish TCP/UDP session
	if(!check_result()){ 
	Serial.println("[FAIL] - use ip address");
	return false; }
 
	
  return true;
  
}


// Waiting for GPRS connection
bool GsmM95::waitForGprs(){

	unsigned long timeout = millis() + 10000;
  
	while(true){
		if(isGprsAlive()){ return true; }
		if(timeout <= millis()){ return false; }
		delay(500);
	}
}



// Activate DPD context (Step 2)
bool GsmM95::activateDPD(void){
	
  if(!powerStat()){ return false; }
  
	sendCmd("AT+QIREGAPP");	// Register the TCP/IP stack
	if(!check_result()){ 
	Serial.println("[FAIL] - register tcpip stack");
	return false; }
	
	attachGPRS(); // Activate FGCNT
	
	return waitForGprs();
}


// Connect To TCP Server
// IP - Destination IP Address
// port - Server service port
bool GsmM95::openSession(String IP, uint16_t port){
	
  if(!powerStat()){ return false; }
  
	String connectionString = "AT+QIOPEN=\"TCP\",\"";
	connectionString += IP;
	connectionString += "\",";
	connectionString += String(port, DEC);
	
  
	sendStringCmd(connectionString);		// Connect command to remote server
	if(!check_result()){ return false; }	// result of command syntax
	
	String msg = message_provider(30000);
	
	if(msg.indexOf("OK") > 0){ return true; }
	
	return false;
}


// Close TCP/IP Session
bool GsmM95::closeSession(void){
	
  if(!powerStat()){ return false; }
  
	
	sendCmd("AT+QICLOSE");					// Connect command to remote server
	return check_result();					// result of command syntax

}


// Send data via TCP/IP connection
bool GsmM95::sendViaTCP(String msg){
	
	if(msg.length() > 1460){ return false; }
	
	flush_uart();

	sendCmd("AT+QISEND");
	
	waiting_for_response();
	delay(5);
	flush_uart();
	
	sendStringCmd(msg);
	
	waiting_for_response();
	delay(5);
	flush_uart();
	
	ctrlz();
	
	delay(500);
	
	msg = message_provider(30000);
	
	if(msg.indexOf("OK") > 0){ return true; }
	
	return false;

}




// Set Transmission (Step 1)
bool GsmM95::setSSL(void){
	
  if(!powerStat()){ return false; }
  
	sendCmd("AT+QSSLCFG=\"sslversion\",0,2");			// Set SSL version
	if(!check_result()){
	Serial.println("[FAIL] - set ssl version");
	return false; }
	
	sendCmd("AT+QSSLCFG=\"seclevel\",0,0");				// Disable MUXIP function
	if(!check_result()){ 
	Serial.println("[FAIL] - disable MUXIP");
	return false; }
	
	sendCmd("AT+QSSLCFG=\"ciphersuite\",0,\"0XFFFF\"");	// Set the session mode as non-transparent
	if(!check_result()){ 
	Serial.println("[FAIL] - set non-tranparent mode");
	return false; }
 
	
  return true;
  
}



// Connect To TCP Server (SSL)
// host - Server host address (URL or IP)
// port - Server service port
bool GsmM95::openSslSession(String host, uint16_t port){
	
  if(!powerStat()){ return false; }
  
	String connectionString = "AT+QSSLOPEN=3,0,\"";
	connectionString += host;
	connectionString += "\",";
	connectionString += String(port, DEC);
	connectionString += ",0";
  
	sendStringCmd(connectionString);		// Connect command to remote server
	if(!check_result()){ return false; }	// result of command syntax
	
	String msg = message_provider(30000);
	
	// DEBUG
	Serial.println(msg);
	
	if(msg.indexOf("QSSLOPEN: 3") > 0){ return true; }
	
	return false;
}


// Colse TCP SSL Connection
bool GsmM95::closeSslSession(void){
	
  if(!powerStat()){ return false; }
  
	sendCmd("AT+QSSLCLOSE=3");
	
	String msg = message_provider(30000);
	
	if(msg.indexOf("OK") > 0){ return true; }
	
	return false;
}


// Colse TCP SSL Connection
bool GsmM95::sendDataSSL(String data){
	
 if(data.length() > 1460){ return false; }
	
	flush_uart();

	sendCmd("AT+QSSLSEND=3");
	
	waiting_for_response();
	delay(5);
	flush_uart();
	
	sendStringCmd(data);
	
	delay(100);
	
	while(waiting_for_response()){
		delay(1);
		flush_uart();
	}
	
	
	ctrlz();
	
	delay(20);
	
	data = "";
	
	data = message_provider(30000);

	// DEBUG
	Serial.println(data);
	
	if(data.indexOf("OK") > 0){ return true; }
	
	return false;
}




// Set GSM automatic time sync
// (ENABLE or DISABLE)
bool GsmM95::setTimeSync(bool enable){
	
	if(!powerStat()){ return false; }

	// Enable Auto Sync
	if(enable){ 
		sendCmd("AT+CTZU=3"); // Update localized time and time zone rtc
		if(!check_result()){ return false; }
		sendCmd("AT+QNITZ=1"); // Enable GSM Time sync
		if(!check_result()){ return false; }
	} 
	
	// Disable Auto Sync
	else{	
		sendCmd("AT+CTZU=0"); // Update localized time and time zone rtc
		if(!check_result()){ return false; }
		sendCmd("AT+QNITZ=0"); // Enable GSM Time sync
		if(!check_result()){ return false; }
	}
	
	
	return true;
 
}




// Set idle settings and modes
bool GsmM95::setDefaults(void){
	
	if(!powerStat()){ return false; }
	
	if(!setTimeSync(true)){ return false; }
	
	setGprsSettings("internet", "", "");
	
	setTransmission();
	
	return true;
 
}



// Set idle settings and modes
GsmTime GsmM95::getHwdTime(void){
	
	GsmTime datetime;
	
	if(!powerStat()){ return datetime; }
	
	sendCmd("AT+CCLK?");

	if(collect_response_msg()){
	
		String timeStr = get_response_msg();
		
		Serial.println(timeStr);
	
		if(timeStr == "" || timeStr.length() < 18){ 
		 Serial.println("X"); return datetime; }

		datetime.valid = true;
		String temp = "";	
		
		// YEAR
		temp += timeStr.charAt(0);
		temp += timeStr.charAt(1);
		
		
		if(isValidNumber(temp)){ datetime.year = (uint16_t)(temp.toInt() + 2000); }
		else{ datetime.valid = false; }
		
		temp = "";
		
		
		// MONTH
		temp += timeStr.charAt(3);
		temp += timeStr.charAt(4);
		
		if(isValidNumber(temp)){ datetime.month = (byte)temp.toInt(); }
		else{ datetime.valid = false; }
		
		temp = "";
		
		
		// DAY
		temp += timeStr.charAt(6);
		temp += timeStr.charAt(7);
		
		if(isValidNumber(temp)){ datetime.day = (byte)temp.toInt(); }
		else{ datetime.valid = false; }
		
		temp = "";
		
		
		// HOUR
		temp += timeStr.charAt(9);
		temp += timeStr.charAt(10);
		
		if(isValidNumber(temp)){ datetime.hour = (byte)temp.toInt(); }
		else{ datetime.valid = false; }
		
		temp = "";
		
		
		// MINUTE
		temp += timeStr.charAt(12);
		temp += timeStr.charAt(13);
		
		if(isValidNumber(temp)){ datetime.minute = (byte)temp.toInt(); }
		else{ datetime.valid = false; }
		
		temp = "";
		
		
		// SECOND
		temp += timeStr.charAt(15);
		temp += timeStr.charAt(16);
		
		if(isValidNumber(temp)){ datetime.second = (byte)temp.toInt(); }
		else{ datetime.valid = false; }
	
	}
	
	return datetime;
 
}




// HTTP Post
bool GsmM95::httpPost(String url, String body){
	
	if(!powerStat()){ return false; }
  
	String temp = "AT+QHTTPURL=";
	temp += String(url.length(), DEC);
	temp += ",30";
  
	sendStringCmd(temp);	// Set the context 0 as FGCNT
	
	waiting_for_response();
	delay(1);
	flush_uart();
	
	sendStringCmd(url);
	
	String msg = message_provider(5000);
	
	if(msg.indexOf("OK") == 0){ return false; }
	
	temp = "AT+GHTTPPOST=";
	temp += String(body.length(), DEC);
	temp += ",50,10";
	
	waiting_for_response();
	delay(5);
	flush_uart();
	
	sendStringCmd(body);
	
	msg = message_provider(5000);
	
	if(msg.indexOf("OK") > 0){ return true; }
 
	
  return false;

}