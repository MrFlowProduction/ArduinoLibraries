#include <MrFlow.h>
#include <Scheduler.h>


Scheduler scheduler;


void function1(){
  Serial.println("Function 1 is runned\n");
}

void function2(){
  Serial.println("Function 2 is runned\n");
}

void function3(){
  Serial.println("Function 3 is runned\n");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  scheduler.init(3);
  
  scheduler.add(function1, 3000, "Function1"); 
  scheduler.add(function2, 5000, "Function2");
  scheduler.add(function3, 1000, "Function3");
}

void loop() {
  // put your main code here, to run repeatedly:

  scheduler.run();
}
