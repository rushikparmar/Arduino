#include "BluetoothSerial.h"
String readString;
BluetoothSerial SerialBT;

const int freq = 5000;
const int pwmChannel1 = 0;
const int resolution = 10;

int dutyCycle = 200;
const int MAX_DUTY_CYCLE = (int)(pow(2, resolution) - 1);

int enable1Pin = 32;

int Motor1P1=18;
int Motor1P2=19;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started");

  pinMode(Motor1P1,OUTPUT);
  pinMode(Motor1P2,OUTPUT);

  pinMode(enable1Pin, OUTPUT);
  
  ledcSetup(pwmChannel1, freq, resolution);
  
  ledcAttachPin(enable1Pin, pwmChannel1);

}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  char temp =0;
  
  while (SerialBT.available()) {
    
    char x=SerialBT.read();
    readString += x;
  }

  if (readString.length() >0) {

    Serial.println("-------------");
    Serial.println(readString);
    Serial.println("------_------");
    
    
    char temp=readString.charAt(0);
    
    Serial.print("temp=");
    Serial.println(temp);
    Serial.println("---------------");
    
    int speed=(readString.substring(1)).toInt();
    Serial.print("speed=");
    Serial.println(speed);
    Serial.println("---------------");

    ledcWrite(pwmChannel1, speed);

    if(temp=='1')
    {
      digitalWrite(Motor1P1, HIGH);
      digitalWrite(Motor1P2, LOW);
      Serial.println("Clockwise"+speed);
    }
    else
    {
      if(temp=='2')
      {
        digitalWrite(Motor1P1, LOW);
        digitalWrite(Motor1P2, HIGH);
        Serial.println("Anticlockwise"+speed);
      }
      else
      {
        digitalWrite(Motor1P1, LOW);
        digitalWrite(Motor1P2, LOW);
      }
    }
    
  
  }
  
  readString="";
  delay(100);
}
