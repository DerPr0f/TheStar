#include <Adafruit_NeoPixel.h>

#define PIN 4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

int brightness = 50;

void setup() {
  Serial.begin(9600);
  Serial.println("Funzt");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  int Randoof = random(0, 8);

  if (Randoof == 0) {
    for (int D = 0; D <= 5; D++)  {
      rainbowCycle(20, brightness);
    }
  }
  if (Randoof == 1) {
    for (int D = 0; D <= 5; D++)  {
      rainbow(20, brightness);
    }
  }
  if (Randoof == 2) {
    for (int D = 0; D <= 10; D++)  {
      colorWipe(strip.Color(random(0, brightness), random(0, brightness), random(0, brightness)), 50);
    }
  }
  if (Randoof == 3) {
    for (int D = 0; D <= 10; D++)  {
      theaterChase(strip.Color(random(0, brightness), random(0, brightness), random(0, brightness)), 50);
    }
  }
  if (Randoof == 4) {
      theaterChaseRainbow(30, brightness);
  }
  if (Randoof == 5) {
    for (int D = 0; D <= 5; D++)  {
      FadeInOut(random(0, brightness), random(0, brightness), random(0, brightness), 150);
    }
  }
  if (Randoof == 6) {
    for (int D = 0; D <= 5; D++)  {
      singleScan(random(0, brightness), random(0, brightness), random(0, brightness), 25);
    }
  }
  if (Randoof == 7) {
    for (int D = 0; D <= 5; D++)  {
      dualScan(random(0, brightness), random(0, brightness), random(0, brightness), 5);
    }
  }
  if (Randoof == 8) {
    for (int D = 0; D <= 10; D++)  {
      twinkle(random(0, brightness), random(0, brightness), random(0, brightness), 15);
    }
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait, int bright) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255, bright));
    }
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait, int bright) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255, bright));
    }
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait, int bright) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255, bright)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

void FadeInOut(int red, int green, int blue, int wait) {
  for (int k = 0; k < 256; k = k + 1) {
    int r = (k / 256.0) * red;
    int g = (k / 256.0) * green;
    int b = (k / 256.0) * blue;
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
    delay(wait / 50);
  }
  for (int k = 255; k >= 0; k = k - 1) {
    int r = (k / 256.0) * red;
    int g = (k / 256.0) * green;
    int b = (k / 256.0) * blue;
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
    delay(wait / 50);
  }
}

void singleScan(int r, int g, int b, int Delay) {
  int x;
  for (int i = 0; i < strip.numPixels() * 2; i++) {
    if (x > (strip.numPixels() * 2) - 2) {
      x = 0;
    }
    x++;
    int j = x - (strip.numPixels() - 1);
    j = abs(j);
    strip.clear();
    strip.setPixelColor(abs(j), r, g, b);
    strip.show();
    delay(Delay);
  }
}

void dualScan(int r, int g, int b, int Delay) {
  int x;
  for (int i = 0; i < strip.numPixels(); i++) {
    if (x > (strip.numPixels() * 2) - 2) {
      x = 0;
    }
    x++;
    int j = x - (strip.numPixels() - 1);
    j = abs(j);
    strip.clear();
    strip.setPixelColor(abs(j), r, g, b);
    strip.setPixelColor(strip.numPixels() - (j + 1), r, g, b);
    strip.show();
    delay(Delay * 10);
  }
}

void twinkle(int r, int g, int b, int Delay) {
  strip.clear();
  for (int i = random(strip.numPixels() / 5, strip.numPixels() / 2); i > 1; i--) {
    strip.setPixelColor(random(strip.numPixels()), r, g, b);
    strip.show();
    delay(Delay * 10);
  }
}

uint32_t Wheel(byte WheelPos, int bright) {
  int light = 255 / bright;
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(round((255 - WheelPos * 3) / light), 0, round((WheelPos * 3) / light));
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, round((WheelPos * 3) / light), round((255 - WheelPos * 3) / light));
  }
  WheelPos -= 170;
  return strip.Color(round((WheelPos * 3) / light), round((255 - WheelPos * 3) / light), 0);
}
