#include <ByteList.h>


ByteList byteList;


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  Serial.println(F("______________________\nAdd elements\n"));
  
  byteList.Add(1);
  byteList.Add(2);
  byteList.Add(234);
  byteList.Add(23);
  byteList.Add(44);
  byteList.Add(127);
  
  byteList.PrintList();

  Serial.print(F("List Items count: "));
  Serial.println(byteList.Count(), DEC);

  Serial.println(F("\n______________________\nRemove element of 44\n"));

  byteList.Remove(byteList.IndexOf(44));

  Serial.print(F("\nList Items count: "));
  Serial.println(byteList.Count(), DEC);

  byteList.PrintList();

  Serial.println(F("\n______________________\nRemove all elements with remove command\n"));

  byteList.Remove(byteList.IndexOf(1));
  byteList.Remove(byteList.IndexOf(2));
  byteList.Remove(byteList.IndexOf(234));
  byteList.Remove(byteList.IndexOf(23));
  byteList.Remove(byteList.IndexOf(127));

  Serial.print(F("\nList Items count: "));
  Serial.println(byteList.Count(), DEC);

  Serial.println(F("\n"));

  byteList.PrintList();

  Serial.println(F("\n______________________\nAdd elements"));

  byteList.Add(1);
  byteList.Add(2);
  byteList.Add(234);
  byteList.Add(23);
  byteList.Add(44);
  byteList.Add(127);

  Serial.print(F("\nList Items count: "));
  Serial.println(byteList.Count(), DEC);


  Serial.print(F("\nSUM:"));
  Serial.println(byteList.Sum());

  Serial.print(F("\nAvg:"));
  Serial.println(byteList.Avg());

  Serial.print(F("\nMax:"));
  Serial.println(byteList.Max());

  Serial.print(F("\nMin:"));
  Serial.println(byteList.Min());

  Serial.println(F("\n______________________\nClear List: "));

  byteList.Clear();

  Serial.print(F("\nList Items count: "));
  Serial.println(byteList.Count(), DEC);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
}
