#include "ER-EPM027-1B.h"
#include "imagedata.h"
#include "epdpaint.h"

// blink the system LED on and off forever to signal failure state.
void errorBlinkForever() {
  pinMode(LED_BUILTIN, OUTPUT);
  while(1) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

// Demonstration test of using the display's SRAM from buydisplay / EastRising demo
#define COLORED     0
#define UNCOLORED   1
void epdSramTest(Epd epd) {
  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */
  unsigned char image[1024];
  Paint paint(image, 176, 24);    //width should be the multiple of 8 

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "e-Paper Demo", &Font16, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 16, 32, paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawStringAt(2, 2, "buydisplay.com", &Font16, UNCOLORED);
  epd.TransmitPartialData(paint.GetImage(), 0, 64, paint.GetWidth(), paint.GetHeight());
  
  paint.SetWidth(64);
  paint.SetHeight(64);

  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 0, 40, 50, COLORED);
  paint.DrawLine(0, 0, 40, 50, COLORED);
  paint.DrawLine(40, 0, 0, 50, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 10, 130, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawCircle(32, 32, 30, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 90, 120, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 10, 200, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledCircle(32, 32, 30, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 90, 190, paint.GetWidth(), paint.GetHeight());

  /* This displays the data from the SRAM in e-Paper module */
  epd.DisplayFrame();
}

void setup() {
  Epd epd;
  if (epd.Init() != 0) {
    errorBlinkForever();
  }
  epd.ClearFrame();

  epdSramTest(epd);
  delay(2000);
  epd.DisplayFrame(IMAGE_DATA);
  delay(2000);
  epd.DisplayFrame(IMAGE_DATA1);
  delay(15000);
  epd.ClearFrame();   // clears the SRAM
  epd.DisplayFrame(); // displays the now-empty SRAM
  epd.Sleep();        // "deep sleep"
}

void loop() {
  // nop
}
