int ENB = 9, POT_PIN = A0; // we define pin variables here
void setup()
{
pinMode(ENB, OUTPUT); 
pinMode(POT_PIN,INPUT); // defining the pot pin as input pin
}
void loop()
{
int inp = analogRead(POT_PIN); // read the value of pot pin
int motor_speed = map(inp,0,1023,0,255); // map the value from [0,1023] to [0,255]
analogWrite(ENB,motor_speed); // set the speed to motor_speed
}
