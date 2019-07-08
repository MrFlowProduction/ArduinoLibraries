#include <Arduino.h>
#include "StateEvent.h"


bool boolState = false;
bool _isChanged = false;

void StateEvent::newState(bool state){

	boolState = state;
	_isChanged = true;
	
}


void StateEvent::changeState(void){

	newState(!boolState);

}


bool StateEvent::isChanged(void){
	return _isChanged;
}


bool StateEvent::getValue(void){
	_isChanged = false;
	return boolState;
}


