# ePaper Display with an I2C IO Expander

## The display in question:
[East Rising ER-EPM027-1B](https://www.buydisplay.com/black-2-7-inch-e-paper-display-module-for-arduino-raspberry-pi)

## The IO expander
[Adafruit i2c / SPI LCD backpack ](https://www.adafruit.com/product/292)

You can also use a bare [MCP23008](https://www.adafruit.com/product/593) or [MCP23017](https://www.adafruit.com/product/732). The concept is the same.

## Notes

The "Arduino example" provided by EastRising is well factored so that the hardware interface is defined seperately in `epdif.cpp` and `epdif.h`. The provided implementation simply uses standard Arduino `digitalWrite()` and `SPI` libraries to drive the control and data lines directly.

This implementation makes use of that physical interface abstraction to use IO pins on the IO expander. Unfortunately SPI is bit-banged over the expander, making for some pretty slow updates. The trade-off is that only two pins for standard I2C are required, allowing very pin-restricted devices like the [ESP8211 ESP01 modules](https://www.sparkfun.com/products/17146) to use the ePaper display.


