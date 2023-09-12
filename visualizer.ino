#include "FastLED.h"

#define NUM_LEDS 60 //Change this to the number of LEDs in your strip
#define updateLED 4 //Change to how many LEDs you want every ms
#define COLOUR_SHIFT 180000 //Time for colour to shift
CRGB led[NUM_LEDS]; 

#define DATA_PIN 6
#define PITCH_PIN 0
#define BRIGHTNESS_PIN 4

unsigned long setTime = COLOUR_SHIFT;
int shiftC = 0;
int mulC = 2;

//Colour structure for the LEDs
struct Colour {
  int r;
  int g;
  int b;
};
typedef struct Colour Colour;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(led, NUM_LEDS);
  FastLED.setBrightness(255);
  pinMode(PITCH_PIN, INPUT);
  pinMode(BRIGHTNESS_PIN, INPUT);
  for (int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void loop(){
    unsigned long time = millis();

  // Shift colour (change the value accordingly)
  if(time / (double)setTime >= 1) {
    setTime = time + COLOUR_SHIFT;
    Serial.println(setTime);
    shiftC += 200;
    mulC++;
    if(shiftC >= 600) {
      shiftC = 0;
    }
    if(mulC > 3) {
      mulC = 2;
    }
  }

  // Shift all LEDs to the right by updateLEDS
  for(int i = NUM_LEDS - 1; i >= updateLED; i--) {
    leds[i] = leds[i - updateLED];
  }
  // Get the pitch and brightness to compute the next colour
  int newPitch = (analogRead(PITCH_PIN)*2) + shiftC;
  Color nc = pitchConv(newPitch, analogRead(BRIGHT_PIN));

  // Set the left most updateLEDs 
  for(int i = 0; i < updateLEDS; i++) {
    leds[i] = CRGB(nc.r, nc.g, nc.b);
  }
  FastLED.show();
}
