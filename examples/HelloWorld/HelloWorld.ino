/*
*   Shift8LCD - HelloWorld.ino
*   A simple program to output "Hello World!" to an LCD through a shift register
*
*   Circuit
*   Connect the output pins of the shift register to the data pins of the lcd
*   Connect the DATA or SER pin of the shift register to Digital 12
*   Connect the SRCLK or SHCP pin of the shift register to Digital 11
*   Connect the RCLK or STCP pin of the shift register to Digital 10
*   Connect the RS pin of the LCD to Digital 9
*   Connect the E pin of the LCD to Digital 8
*
*   This example code is in the public domain
*/

#include <Shift8LCD.h>

Shift8LCD lcd(12, 11, 10, 9, 8);

void setup() {
  lcd.begin();
}

void loop() {
  lcd.print("Hello World!");
  lcd.setCursor(0, 0);
}
