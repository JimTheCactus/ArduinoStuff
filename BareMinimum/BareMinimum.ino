#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly: 
  for(i=0;i<strip.numPixels();i++) {
    strip.setPixelColor(i,strip.Color(255,0,0));
  }
  delay(1000)
  for(i=0;i<strip.numPixels();i++) {
    strip.setPixelColor(i,strip.Color(0,0,255));
  }
}
