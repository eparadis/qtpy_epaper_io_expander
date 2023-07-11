/*
Original by EastRising Technology Co.,LTD
Web: http://www.buydisplay.com


*/

#ifndef EPDIF_H
#define EPDIF_H

#include <arduino.h>

// Pin definition
#define RST_PIN         2
#define DC_PIN          1
#define CS_PIN          0
#define BUSY_PIN        3

class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);
};

#endif
