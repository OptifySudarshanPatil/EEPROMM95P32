#ifndef EEPROMM95P32_h
#define EEPROMM95P32_h

#include "Arduino.h"
#include <SPI.h>

class EEPROMM95P32 {
  public:
    EEPROMM95P32(int csPin);
    void begin();
    void writeByte(uint32_t address, byte data);
    byte readByte(uint32_t address);
    void writeFloat(uint32_t address, float data);
    float readFloat(uint32_t address);
    void writeUnsignedLong(uint32_t address, unsigned long data);
    unsigned long readUnsignedLong(uint32_t address);
    void readuniqueid(uint32_t address, byte *data);
    
    // Additional functions for block erase, write enable, etc., can be added here.
  private:
    int _csPin;
    void writeEnable();
    void waitForWriteComplete();
};

#endif