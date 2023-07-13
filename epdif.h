/*
Original by EastRising Technology Co.,LTD
Web: http://www.buydisplay.com


*/

#ifndef EPDIF_H
#define EPDIF_H

#include <arduino.h>
#include <Adafruit_MCP23X17.h>


// Pin definitions. These are on the MCP23017
// 0..7  = PA0..7
// 8..15 = PB0..7
#define RST_PIN         2
#define DC_PIN          1
#define CS_PIN          0
#define BUSY_PIN        3
// 4..6 currently unused
#define MCP_DEBUG_LED   7

// Pin definitions. These are on the device itself
#define SPI_DATA        2
#define SPI_CLK         3



class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);

private:

};

#endif
