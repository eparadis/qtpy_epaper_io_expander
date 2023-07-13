# ePaper Display with an I2C IO Expander

## The display in question:
[East Rising ER-EPM027-1B](https://www.buydisplay.com/black-2-7-inch-e-paper-display-module-for-arduino-raspberry-pi)

## The IO expander
[Adafruit i2c / SPI LCD backpack ](https://www.adafruit.com/product/292)

You can also use a bare [MCP23008](https://www.adafruit.com/product/593) or [MCP23017](https://www.adafruit.com/product/732). The concept is the same.

## Notes

The "Arduino example" provided by EastRising is well factored so that the hardware interface is defined seperately in `epdif.cpp` and `epdif.h`. The provided implementation simply uses standard Arduino `digitalWrite()` and `SPI` libraries to drive the control and data lines directly.

This implementation makes use of that physical interface abstraction to use IO pins on the IO expander.

The first implementation bit-banged the SPI over the expander, making for some pretty slow updates. The trade-off is that only two pins for standard I2C are required, allowing very pin-restricted devices like the [ESP8211 ESP01 modules](https://www.sparkfun.com/products/17146) to use the ePaper display easily.

The ESP-01/ESP-01S does have [two more pins available if you're willing to share the TX and RX pins](http://www.forward.com.au/pfod/ESP8266/GPIOpins/ESP8266_01_pin_magic.html). The performance improvement may be worth it.

## Performance
When bit banging the SPI CLK and DATA through the I2C IO expander, it takes about 70 seconds to transfer a full image to the display.

When bit banging the SPI CLK and DATA out normal GPIO pins, it takes 10-15 seconds.

Using the hardware SPI on the QTPy SAMD21, it's more or less instant.

Sending a static value (as when you clear the display by sending 0x00) is faster.

Only updating specific regions of the SRAM is a clear way to improve performance.
