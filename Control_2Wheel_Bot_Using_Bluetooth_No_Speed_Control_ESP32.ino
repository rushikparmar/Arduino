
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started");

  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);

}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  char temp =0;
  
  if (SerialBT.available()) {
    
    int x=SerialBT.read();

    temp=(char)x;
    
    Serial.println("-----");
    Serial.print(x);
    Serial.print("-----");
    Serial.println(temp);
    Serial.println("-----");
  }

  switch (temp) 
  {
    case '8':
            digitalWrite(18, HIGH);
            digitalWrite(19, LOW);
            digitalWrite(22, HIGH);
            digitalWrite(23, LOW);
            Serial.print("8 - 1010 - FWD");
            break;
    case '4':
            digitalWrite(18, HIGH);
            digitalWrite(19, LOW);
            digitalWrite(22, LOW);
            digitalWrite(23, HIGH);
            Serial.print("4 - 1001 - ANT CLK");
            break;
    case '2':
            digitalWrite(18, LOW);
            digitalWrite(19, HIGH);
            digitalWrite(22, LOW);
            digitalWrite(23, HIGH);
            Serial.print("2 - 0101 - BCK");
            break;
    case '6':
            digitalWrite(18, LOW);
            digitalWrite(19, HIGH);
            digitalWrite(22, HIGH);
            digitalWrite(23, LOW);
            Serial.print("6 - 0110 - CLK");
            break;
    default:
            digitalWrite(18, LOW);
            digitalWrite(19, LOW);
            digitalWrite(22, LOW);
            digitalWrite(23, LOW);
//            Serial.print("0 - 0000 - STOP");
            break;
  }
  delay(100);
}
