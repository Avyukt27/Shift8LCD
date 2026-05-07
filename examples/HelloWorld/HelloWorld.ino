#include <Shift8LCD.h>

Shift8LCD lcd(11, 12, 8, 7, 9);

void setup() {
  lcd.begin();
}

void loop() {
  lcd.print("Hello World!");
  lcd.setCursor(0, 0);
}
