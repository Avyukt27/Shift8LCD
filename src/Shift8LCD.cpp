#include "Shift8LCD.h"

Shift8LCD::Shift8LCD(int data, int clock, int latch, int mode, int enable) {
  _dataPin = data;
  _clockPin = clock;
  _latchPin = latch;
  _modePin = mode;
  _enablePin = enable;
}

void Shift8LCD::begin(bool twoLines, bool fontHeight, bool cursor, bool blink) {
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  pinMode(_modePin, OUTPUT);
  pinMode(_enablePin, OUTPUT);

  byte functionSetFlags = 3 << 4 | twoLines | fontHeight;
  byte displayControlFlags = 3 << 2 | cursor | blink;

  delay(5);
  write(functionSetFlags, false);    // Function set
  write(displayControlFlags, false); // Display control - 0b1DCB
  clear();
  write(0x06, false); // Entry mode set
}

void Shift8LCD::write(byte value, bool isData) {
  digitalWrite(_modePin, isData);

  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, MSBFIRST, value);
  digitalWrite(_latchPin, HIGH);

  digitalWrite(_enablePin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_enablePin, LOW);

  delay(2);
}

void Shift8LCD::clear() { write(0x01, false); }

void Shift8LCD::setCursor(int col, int row) {
  byte address = (row == 0) ? col : (0x40 + col);
  write(0x80 | address, false);
}

void Shift8LCD::print(const char *text) {
  while (*text) {
    write(*text++, true);
  }
}
