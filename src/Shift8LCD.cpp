#include "Shift8LCD.h"

Shift8LCD::Shift8LCD(uint8_t data, uint8_t clock, uint8_t latch, uint8_t mode,
                     uint8_t enable) {
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

  delay(50);
  send(functionSetFlags, IS_INSTRUCTION);    // Function set
  send(displayControlFlags, IS_INSTRUCTION); // Display control - 0b1DCB
  clear();
  send(0x06, IS_INSTRUCTION); // Entry mode set
}

void Shift8LCD::send(byte value, bool isData) {
  digitalWrite(_modePin, isData);

  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, MSBFIRST, value);
  digitalWrite(_latchPin, HIGH);

  digitalWrite(_enablePin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_enablePin, LOW);

  delay(2);
}

void Shift8LCD::clear() { send(0x01, IS_INSTRUCTION); }

void Shift8LCD::setCursor(uint8_t col, uint8_t row) {
  byte address = (row == 0) ? col : (0x40 + col);
  send(0x80 | address, IS_INSTRUCTION);
}

size_t Shift8LCD::write(uint8_t character) {
  send(character);
  return 1;
}
