#include "EEPROMM95P32.h"

EEPROMM95P32::EEPROMM95P32(int csPin)
{
  _csPin = csPin;
}

void EEPROMM95P32::begin()
{
  pinMode(_csPin, OUTPUT);
  SPI.begin();
}

void EEPROMM95P32::writeByte(uint32_t address, byte data)
{
  writeEnable();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_csPin, LOW);
  SPI.transfer(0x02); // WRITE command
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);
  SPI.transfer(data);
  digitalWrite(_csPin, HIGH);
  SPI.endTransaction();
  waitForWriteComplete();
}

byte EEPROMM95P32::readByte(uint32_t address)
{
  byte result;
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_csPin, LOW);
  SPI.transfer(0x03); // READ command
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);
  result = SPI.transfer(0); // Dummy transfer to read data
  digitalWrite(_csPin, HIGH);
  SPI.endTransaction();
  return result;
}

void EEPROMM95P32::writeFloat(uint32_t address, float data)
{
  union
  {
    float a;
    byte bytes[4];
  } thing;

  thing.a = data;

  for (int i = 0; i < 4; i++)
  {
    writeByte(address + i, thing.bytes[i]);
  }
}

float EEPROMM95P32::readFloat(uint32_t address)
{
  union
  {
    float a;
    byte bytes[4];
  } thing;

  for (int i = 0; i < 4; i++)
  {
    thing.bytes[i] = readByte(address + i);
  }

  return thing.a;
}

void EEPROMM95P32::writeUnsignedLong(uint32_t address, unsigned long data)
{
  union
  {
    unsigned long a;
    byte bytes[4];
  } thing;

  thing.a = data;

  for (int i = 0; i < 4; i++)
  {
    writeByte(address + i, thing.bytes[i]);
  }
}

unsigned long EEPROMM95P32::readUnsignedLong(uint32_t address)
{
  union
  {
    unsigned long a;
    byte bytes[4];
  } thing;

  for (int i = 0; i < 4; i++)
  {
    thing.bytes[i] = readByte(address + i);
  }

  return thing.a;
}

void EEPROMM95P32::readuniqueid(uint32_t address, byte *data)
{
  for (int i = 0; i < 12; i++)
  {
    data[i] = readByte(address + i);
  }
}

void EEPROMM95P32::writeEnable()
{
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_csPin, LOW);
  SPI.transfer(0x06); // WRITE ENABLE command
  digitalWrite(_csPin, HIGH);
  SPI.endTransaction();
}

void EEPROMM95P32::waitForWriteComplete()
{
  byte status;
  do
  {
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_csPin, LOW);
    SPI.transfer(0x05);       // READ STATUS REGISTER command
    status = SPI.transfer(0); // Dummy transfer to read the status register
    digitalWrite(_csPin, HIGH);
    SPI.endTransaction();
  } while (status & 0x01); // Wait until write in progress bit is cleared
}
