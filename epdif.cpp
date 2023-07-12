/*
Original by EastRising Technology Co.,LTD
Web: http://www.buydisplay.com

2023-07-11 edp - Modified to use MCP23X17 IO expander
*/

#include "epdif.h"
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;

EpdIf::EpdIf() {
};

EpdIf::~EpdIf() {
};

void EpdIf::DigitalWrite(int pin, int value) {
  mcp.digitalWrite(pin, value);
}

int EpdIf::DigitalRead(int pin) {
  return mcp.digitalRead(pin);
}

void EpdIf::DelayMs(unsigned int delaytime) {
  delay(delaytime);
}

void EpdIf::SpiTransfer(unsigned char data) {
  mcp.digitalWrite(MCP_DEBUG_LED, HIGH);
  mcp.digitalWrite(CS_PIN, LOW);
  // shift out a byte
  for(int i = 0; i < 8; i += 1) {
    // set data
    mcp.digitalWrite(SPI_DATA, data & 0x80);
    data = data << 1;
    // clock high then low
    mcp.digitalWrite(SPI_CLK, HIGH);
    // possible delay here, but things are probably so slow coming out of the IO expander we don't need it
    mcp.digitalWrite(SPI_CLK, LOW);
  }
  mcp.digitalWrite(CS_PIN, HIGH);
  mcp.digitalWrite(MCP_DEBUG_LED, LOW);
}

int EpdIf::IfInit(void) {
  if (!mcp.begin_I2C()) {
    return -1; // could not init I2C comms to IO expander
  }
  mcp.pinMode(CS_PIN, OUTPUT);
  mcp.pinMode(RST_PIN, OUTPUT);
  mcp.pinMode(DC_PIN, OUTPUT);
  mcp.pinMode(BUSY_PIN, INPUT);
  mcp.pinMode(SPI_DATA, OUTPUT);
  mcp.pinMode(SPI_CLK, OUTPUT);

  mcp.pinMode(MCP_DEBUG_LED, OUTPUT);
  return 0;
}

