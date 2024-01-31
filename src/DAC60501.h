#ifndef DAC60501_h
#define DAC60501_h

#include "Arduino.h"
#include <Wire.h>



void initDAC();
void writeDAC(int value);
void setGAIN(bool REF, bool GAIN);
void setConfig(bool REF, bool shtdwn);
void setLDAC(bool enable);
void setDACtype(uint8_t type);
void setNOOP();
#endif
