#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX

char character;
boolean flag=false;

int Red=9,Blue=10,Green=11;

String s1 = "1", s2 = "2", s3 = "3";

void setup()  
{
  mySerial.begin(9600);
  Serial.begin(9600);
  
  pinMode(Red,OUTPUT);
  pinMode(Blue,OUTPUT);
  pinMode(Green,OUTPUT);
  
  mySerial.print("Press 1:Red, 2:Yellow,3:White ");
  digitalWrite(13,0);

}

void loop() 
{
   String Data = "";
   flag=false;
   while(mySerial.available()) 
   {
      character = mySerial.read();
      Data.concat(character);
      flag=true;
      //digitalWrite(13,1);
      //Serial.print("Received : ");
      delay(100);
      //Serial.println("foo");
   }
   if(flag)
   {
      Data.trim();
      Serial.println(Data);
      if(Data.equals(s1))
      {
        digitalWrite(Red,1);
        digitalWrite(Blue,0);
        digitalWrite(Green,0);
        Serial.println("Red ON");
      }
      else if(Data.equals(s2))
      {
        digitalWrite(Red,0);
        digitalWrite(Blue,1);
        digitalWrite(Green,0);
        Serial.println("Blue ON");
      }
      else if(Data.equals(s3))
      {
        digitalWrite(Red,0);
        digitalWrite(Blue,0);
        digitalWrite(Green,1);
        Serial.println("Green ON");
      }
   }
}
