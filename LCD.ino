
#include <LiquidCrystal.h>

int seconds = 0;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.
	lcd_1.setCursor(2, 0);
  // Print a message to the LCD.
  lcd_1.print("hello world!");
  delay(1000);
}

void loop()
{
    
  lcd_1.setCursor(0, 0);

  // print from 0 to 9:

  lcd_1.print("XXX NAME XXX");
  

  // set the cursor to (16,1):

  lcd_1.setCursor(16, 1);

  // set the display to automatically scroll:

  lcd_1.autoscroll();

  String roll=String("171717231");
  for (int i = 0; i < 10; i++) {

    lcd_1.print(roll.charAt(i));

    delay(500);

  }

  // turn off automatic scrolling

  lcd_1.noAutoscroll();

  // clear screen for the next loop:

  lcd_1.clear();
}
