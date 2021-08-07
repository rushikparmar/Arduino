
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // RX, TX

void setup() {  
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("iot");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() 
{
  int i=0;
  String s;
  
  mySerial.flush();
  
  while(!mySerial.available()); 
  
  if(mySerial.available()) 
  {
    s=mySerial.readStringUntil('\r');
    char ch[s.length()];
    s.toCharArray(ch,s.length());
    Serial.println(ch);
    
    if(ch[1]=='0')
    digitalWrite(3,LOW);
    if(ch[1]=='1')
    digitalWrite(3,1);
    if(ch[2]=='0')
    digitalWrite(4,LOW);
    if(ch[2]=='1')
    digitalWrite(4,1);
    if(ch[3]=='0')
    digitalWrite(5,LOW);
    if(ch[3]=='1')
    digitalWrite(5,1);
    if(ch[4]=='0')
    digitalWrite(6,LOW);
    if(ch[4]=='1')
    digitalWrite(6,1);
  }
}
