#pragma once

#include <Arduino.h>

class Shift8LCD {
public:
  Shift8LCD(int data, int clock, int latch, int mode, int enable);

  void begin(bool twoLines, bool fontHeight, bool cursor, bool blink);
  void print(const char *text);
  void clear();
  void setCursor(int col, int row);

private:
  int _dataPin, _clockPin, _latchPin, _modePin, _enablePin;
  void sendToRegister(byte data);
  void write(byte value, bool isData);
};
