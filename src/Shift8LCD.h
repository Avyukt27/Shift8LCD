#pragma once

#include "Print.h"
#include <Arduino.h>

#define LCD_ONELINE false
#define LCD_TWOLINES true
#define LCD_FONTHEIGHT8 false
#define LCD_FONTHEIGHT11 true
#define LCD_CURSORFF false
#define LCD_CURSORON true
#define LCD_BLINKOFF false
#define LCD_BLINKON true

#define IS_DATA true
#define IS_INSTRUCTION true

class Shift8LCD : public Print {
public:
  Shift8LCD(uint8_t data, uint8_t clock, uint8_t latch, uint8_t mode,
            uint8_t enable);

  void begin(bool twoLines = LCD_TWOLINES, bool fontHeight = LCD_FONTHEIGHT11,
             bool cursor = LCD_CURSORFF, bool blink = LCD_BLINKOFF);
  void clear();
  void setCursor(uint8_t col, uint8_t row);
  virtual size_t write(uint8_t character) override;

private:
  int _dataPin, _clockPin, _latchPin, _modePin, _enablePin;
  void sendToRegister(byte data);
  void send(byte value, bool isData = IS_DATA);
};
