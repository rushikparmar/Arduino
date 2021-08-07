#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int f, i, j;
char c ;

String readString;
SoftwareSerial mySerial(10, 11);//10-tx of BT 11-rx

void setup() 
{

  Serial.begin(9600);
  Serial.println("Hey !");

  mySerial.begin(9600);
  mySerial.println("Hello, world");
  
  lcd.begin(16, 2);
  
}

void loop() 
{
  
  while (mySerial.available())
  {
    if (mySerial.available()) 
    {
      delay(10);
  
      for (i = 0; i < 15; i++)
      {

        c = mySerial.read();
        readString += c;
        f = 1;
        if((c=='/0')||(c==-1))
        break;

      }

      if (i >= 15)
      { if((c=='/0')||(c==-1))
          f = -1;
      }
    
    }

    char s1 = readString.charAt(0);
    char s2 = readString.charAt(1);

   
    if (f == -1)
    { 
      Serial.println("invalid");
      lcd.print("invalid");
      delay(1000);
      readString="";
      break;
    }

    Serial.println(readString);
    lcd.print(readString);
    delay(2000);

    readString="";

    Serial.println(' ');
    lcd.clear();
    break;

  }


  if (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }

}
