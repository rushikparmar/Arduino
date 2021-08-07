
#include "BluetoothSerial.h"

String readString;

BluetoothSerial SerialBT;

#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 18;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started!");

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000);
  
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
  while (SerialBT.available()) {
    
    char x=SerialBT.read();
    readString += x;
  }

  if (readString.length() >0) {
    Serial.println(readString.toInt());
    myservo.write(readString.toInt());
  }
  
  readString="";
  delay(100);
}
