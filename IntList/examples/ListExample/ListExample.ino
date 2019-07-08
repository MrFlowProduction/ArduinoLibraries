#include <IntList.h>

IntList intList;


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  Serial.println(F("______________________\nAdd elements\n"));
  
  intList.Add(1);
  intList.Add(2);
  intList.Add(234);
  intList.Add(23);
  intList.Add(44);
  intList.Add(127);
  
  intList.PrintList();

  Serial.print(F("List Items count: "));
  Serial.println(intList.Count(), DEC);

  Serial.println(F("\n______________________\nRemove element of 44\n"));

  intList.Remove(intList.IndexOf(44));

  Serial.print(F("\nList Items count: "));
  Serial.println(intList.Count(), DEC);

  intList.PrintList();

  Serial.println(F("\n______________________\nRemove all elements with remove command\n"));

  intList.Remove(intList.IndexOf(1));
  intList.Remove(intList.IndexOf(2));
  intList.Remove(intList.IndexOf(234));
  intList.Remove(intList.IndexOf(23));
  intList.Remove(intList.IndexOf(127));

  Serial.print(F("\nList Items count: "));
  Serial.println(intList.Count(), DEC);

  Serial.println(F("\n"));

  intList.PrintList();

  Serial.println(F("\n______________________\nAdd elements"));

  intList.Add(1);
  intList.Add(2);
  intList.Add(234);
  intList.Add(23);
  intList.Add(44);
  intList.Add(127);

  Serial.print(F("\nList Items count: "));
  Serial.println(intList.Count(), DEC);


  Serial.print(F("\nSUM:"));
  Serial.println(intList.Sum());

  Serial.print(F("\nAvg:"));
  Serial.println(intList.Avg());

  Serial.print(F("\nMax:"));
  Serial.println(intList.Max());

  Serial.print(F("\nMin:"));
  Serial.println(intList.Min());

  Serial.println(F("\n______________________\nClear List: "));

  intList.Clear();

  Serial.print(F("\nList Items count: "));
  Serial.println(intList.Count(), DEC);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
}
