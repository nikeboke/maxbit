#include <Sipeed_ST7789.h>

SPIClass spi_(SPI0); // MUST be SPI0 for Maix series on board LCD
Sipeed_ST7789 tft(320, 240, spi_);

float p = 3.1415926;
  uint16_t time = millis();
  
void setup(void) {
  Serial.begin(115200);
  delay(150);
  Serial.println(F("Hello! ST7789 TFT Test"));
  tft.begin(15000000, COLOR_RED);    


  Serial.println(F("Initialized"));

}

void loop() {


  time = millis() - time;

  Serial.println(time, DEC);
  
  // large block of text
  tft.fillScreen(COLOR_BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", COLOR_WHITE);
  delay(1000);

  // tft print function!
    Serial.println("tftPrintTest");

  tftPrintTest();
  delay(2000);

  // a single pixel
  Serial.println("tft.drawPixel");
  tft.drawPixel(tft.width()/2, tft.height()/2, COLOR_GREEN);
  delay(500);

  // line draw test
//  Serial.println("yellow lines");
//  testlines(COLOR_YELLOW);
//  delay(500);

  // optimized lines
  Serial.println("testfastlines");
  testfastlines(COLOR_RED, COLOR_BLUE);
  delay(500);

  testdrawrects(COLOR_GREEN);
  delay(500);

  testfillrects(COLOR_YELLOW, COLOR_MAGENTA);
  delay(500);

  Serial.println("circles");
  tft.fillScreen(COLOR_BLACK);
  testfillcircles(10, COLOR_BLUE);
  testdrawcircles(10, COLOR_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  mediabuttons();
  delay(500);

  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
  mediabuttons();
  delay(500);

  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
  mediabuttons();
  delay(500);

  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);

  Serial.println("done");
 
} // end loop

void testlines(uint16_t color) {
  tft.fillScreen(COLOR_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(COLOR_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(COLOR_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(COLOR_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(COLOR_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(COLOR_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(COLOR_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(COLOR_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(COLOR_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(COLOR_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(COLOR_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(COLOR_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(COLOR_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(COLOR_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(COLOR_BLACK);
  tft.setTextColor(COLOR_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(COLOR_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(COLOR_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(COLOR_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(COLOR_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(COLOR_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, COLOR_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, COLOR_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, COLOR_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, COLOR_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, COLOR_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, COLOR_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, COLOR_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, COLOR_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, COLOR_GREEN);
}
