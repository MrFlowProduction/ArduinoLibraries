#include <Arduino.h>
#include "IntList.h"


int *items;

int items_count = 0;



void IntList::Add(int element){

	items_count++;
	
	if(items_count == 1){
		items = new int[items_count + 1];
		items[0] = element;
		return;
	}
	
	int* tempList = items;

	items = new int[items_count + 1];
	
	for(int i = 0; i < items_count - 1; i++){
		items[i] = tempList[i];
	}
	
	items[items_count - 1] = element;
	
}


bool IntList::Any(void){
	
	if(items_count == 0){ return false; }
	
	return true;
}


// return list items count
int IntList::Count(void){

	return items_count;
}


// Search index of element
int IntList::IndexOf(int element){

	if(items_count == 0){ return -1; }
	
	for(int i = 0; i < items_count; i++){
		
		if(items[i] == element){
			return i;
		}
	}
	
	return -1;
}


// Remove element from list by index
bool IntList::Remove(int index){
	
	if(index < 0 || index > items_count - 1){ return false; }
	
	items_count--;
	
	if(items_count == 0){ items = new int[0]; return true; }
	
	int* tempList = items;
	
	items = new int[items_count + 1];
	
	bool pointerModifi = false;
	
	for(int i = 0; i < items_count + 1; i++){
		
		if(i == index){ pointerModifi = true; continue; }
		
		if(pointerModifi) items[i - 1] = tempList[i];
		else items[i] = tempList[i];
	}
	
	return true;
	
}


void IntList::PrintList(void){
	
	if(items_count == 0){ Serial.println(F("List is empty")); return; }
	
	for(int i = 0; i < items_count; i++){
		
		Serial.print(i);
		Serial.print(".\t");
		Serial.println(items[i], DEC);
	}
	
}


void IntList::Clear(void){
	
	if(items_count == 0){ return; }
	
	items = new int[0];
	
	items_count = 0;
}



int IntList::Sum(void){
	
	if(items_count == 0){ return 0; }
	
	int summ = 0;
	
	for(int i = 0; i < items_count; i++){
		
		summ += items[i];
	}
	
	return summ;
	
}


float IntList::Avg(void){
	
	float _avg = 0;
	
	for(int i = 0; i < items_count; i++){
		
		_avg += items[i];
	}
	
	return _avg / (float)items_count;
}


int IntList::Max(void){
	
	int max = 0;
	
	for(int i = 0; i < items_count; i++){
		
		if(max < items[i]){ max = items[i]; }
	}
	
	return max;
	
}


int IntList::Min(void){
	
	int min = Max();
	
	for(int i = 0; i < items_count; i++){
		
		if(min > items[i]){ min = items[i]; }
	}
	
	return min;
	
}

