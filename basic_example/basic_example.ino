#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

#define NUM_LEDS 8

#define DATA_PIN_1 3
#define DATA_PIN_2 4
#define DATA_PIN_3 5
#define DATA_PIN_4 6
#define DATA_PIN_5 7
#define DATA_PIN_6 8
#define DATA_PIN_7 9
#define DATA_PIN_8 10

#define MINTEMP 18
#define MAXTEMP 32

// Define the array of leds
CRGB leds[8][NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN_1, RGB>(leds[0], NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN_2, RGB>(leds[1], NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN_3, RGB>(leds[2], NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN_4, RGB>(leds[3], NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN_5, RGB>(leds[4], NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN_6, RGB>(leds[5], NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN_7, RGB>(leds[6], NUM_LEDS);
  FastLED.addLeds<WS2812B, DATA_PIN_8, RGB>(leds[7], NUM_LEDS);

  bool status;

  // default settings
  status = amg.begin();
  if (!status) {
    //Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
    while (1);
  }
}

void loop() {
  amg.readPixels(pixels);

  //more blue for cold, more red for hot
  //no green

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      uint8_t scaled = map((pixels[i * 8 + j]), MINTEMP, MAXTEMP, 0, 255);
      scaled = constrain(scaled, 0, 255);
      
      leds[j][i].green = scaled;
      //leds[j][i].blue = 1;
      leds[j][i].blue = 255 - scaled;
    }
  }
  FastLED.show();

}
