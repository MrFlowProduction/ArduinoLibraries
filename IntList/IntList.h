#ifndef IntList_h
#define IntList_h

/*

	IntList type
	
	developed by Florian Szekely 
	Copyright (c) 2017
	
	
*/

#include <Arduino.h> // for int data type

class IntList{
	public:	
	

	
	// Add new element
	void 	Add(int element);
	
	// Print list elements to Serial
	void 	PrintList(void);
	
	// Remove element by index
	bool 	Remove(int index);
	
	// Index of element, return -1 if the list doesn't contain it
	int 	IndexOf(int element);

	// Count of elements
	int 	Count(void);
	
	// Return true if list has items and return false if it doesn't cointain element
	bool 	Any(void);
	
	// Clear List
	void 	Clear(void);
	
	// Return list sum
	int 	Sum(void);
	
	// Avarage of items
	float 	Avg(void);
	
	// Return max
	int 	Max(void);
	
	// Return min
	int 	Min(void);
	
	
	private:
	
	
	
};


#endif