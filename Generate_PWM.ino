#define LED 13
void setup()
{
// set pin 13 as ouptput pin
pinMode(LED, OUTPUT);
}

void loop()
{
//brightness of LED increases with the increment of i
// as ton and hence duty cycle increases
for(int i=0; i<=512; i++)
{
digitalWrite(LED,HIGH);
delayMicroseconds(i);
digitalWrite(LED,LOW);
delayMicroseconds(512-i);
}
  for(int i=512; i>=0; i--)
{
digitalWrite(LED,HIGH);
delayMicroseconds(i);
digitalWrite(LED,LOW);
delayMicroseconds(512-i);
}
}
