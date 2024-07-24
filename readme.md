
# EEPROMM95P32 Library

This library provides an interface for working with the EEPROM M95P32 chip using SPI communication. It allows for reading and writing bytes and floats to and from the EEPROM.

## Features

- Initialize SPI communication with a specific chip select pin.
- Write a byte to a specific address.
- Read a byte from a specific address.
- Write a float to a specific address.
- Read a float from a specific address.

## Usage

To use this library, include `EEPROMM95P32.h` in your project and follow the steps below:

### Initialization

Create an instance of `EEPROMM95P32` by passing the chip select (CS) pin to the constructor. Then, call the `begin()` method to initialize the SPI communication.

```cpp
#include "EEPROMM95P32.h"

EEPROMM95P32 eeprom(10); // Example using pin 10 for CS

void setup() {
  eeprom.begin();
}
```

### Writing a Byte

To write a byte to the EEPROM, use the `writeByte` method with the desired address and the byte data.

```cpp
uint32_t address = 0x0001;
byte data = 0xFF;
eeprom.writeByte(address, data);
```

### Reading a Byte

To read a byte from the EEPROM, use the `readByte` method with the desired address. The method returns the byte read from the specified address.

```cpp
uint32_t address = 0x0001;
byte readData = eeprom.readByte(address);
```

### Writing a Float

To write a float to the EEPROM, use the `writeFloat` method. This method breaks the float into 4 bytes and writes them sequentially to the specified address.

```cpp
uint32_t address = 0x000A; // Example address
float data = 123.456;
eeprom.writeFloat(address, data);
```

### Reading a Float

To read a float from the EEPROM, use the `readFloat` method. This method reads 4 bytes from the specified address and combines them into a float.

```cpp
uint32_t address = 0x000A; // Example address
float readData = eeprom.readFloat(address);
```

## Dependencies

This library depends on the SPI library for communication with the EEPROM chip. Ensure that the SPI library is included in your project.

