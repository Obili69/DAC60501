#include "Arduino.h"
#include <Wire.h>

#define DAC_ADRESS 0x49

#define REGISTER_NOOP 0x00
#define REGISTER_DEVID 0x01
#define REGISTER_SYNC 0x02
#define REGISTER_CONFIG 0x03
#define REGISTER_GAIN 0x04
#define REGISTER_TRIGGER 0x05
#define REGISTER_STATUS 0x07
#define REGISTER_DATA 0x08

uint16_t DACdata = 0;
uint8_t RESOLUTION = 0b010;
#define RSTSEL 0
#define NOOP 0
#define DAC_SYNC 0
#define REF_PWDWN 0 
#define DAC_PWDWN 0
#define REF_DIV 0
#define BUFF_GAIN 0
#define LDAC 0
#define SOFT_RST 0

void setNOOP(){
  Wire.beginTransmission(DAC_ADRESS);
  Wire.write(REGISTER_NOOP);
  Wire.write(0x00);
  Wire.write(0x01);
  Wire.endTransmission();
}

void setDACtype(uint8_t type){
  Wire.beginTransmission(DAC_ADRESS);
  switch(type){
    case 0:
      RESOLUTION = 0b010;
    break;
    case 1:
      RESOLUTION = 0b001;
    break;
    case 2:
      RESOLUTION = 0b000;
    break;
  }
  Wire.write(REGISTER_DEVID);
  Wire.write(0x00 | (RESOLUTION << 4) & 0x70);
  Wire.write(0x00 | (RSTSEL << 7) & 0x80);
  Wire.endTransmission();
}
void setLDAC(bool enable){
  Wire.beginTransmission(DAC_ADRESS);
  Wire.write(REGISTER_SYNC);
  Wire.write(0x00);
  Wire.write(0x00 | (enable & 0x01));
  Wire.endTransmission();
}
void setConfig(bool REF, bool shtdwn){
  Wire.beginTransmission(DAC_ADRESS);
  Wire.write(REGISTER_CONFIG);
  Wire.write(0x00 | (REF & 0x01));
  Wire.write(0x00 | (shtdwn & 0x01));
  Wire.endTransmission();
}
void setGAIN(bool REF, bool GAIN){
  Wire.beginTransmission(DAC_ADRESS);
  Wire.write(REGISTER_GAIN);
  Wire.write(0x00 |(REF & 0x01));
  Wire.write(0x00 |(GAIN & 0x01));
  Wire.endTransmission();
}
void writeDAC(int value){
  Wire.write(REGISTER_DATA);
  value &= 0x0FFF;
  Wire.write((value >> 8) & 0x0F);
  Wire.write(value & 0xFF);
  Wire.endTransmission();
}

void initDAC(){
  Wire.beginTransmission(DAC_ADRESS);
  Wire.write(REGISTER_NOOP);
  Wire.write(0x00);
  Wire.write(0x00 | (NOOP & 0x01));
  Wire.endTransmission();

  Wire.beginTransmission(DAC_ADRESS);
  Wire.write(REGISTER_SYNC);
  Wire.write(0x00);
  Wire.write(0x00 | (DAC_SYNC & 0x01));
  Wire.endTransmission();

  Wire.beginTransmission(DAC_ADRESS);
  Wire.write(REGISTER_CONFIG);
  Wire.write(0x00 | (REF_PWDWN & 0x01));
  Wire.write(0x00 | (DAC_PWDWN & 0x01));
  Wire.endTransmission();

  Wire.beginTransmission(DAC_ADRESS);
  Wire.write(REGISTER_GAIN);
  Wire.write(0x00 |(REF_DIV & 0x01));
  Wire.write(0x00 |(BUFF_GAIN & 0x01));
  Wire.endTransmission();
}
