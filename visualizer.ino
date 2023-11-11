#include "FastLED.h"

#define NUM_LEDS 300        // How many leds in your strip?
#define updateLEDS 8        // How many do you want to update every millisecond?
#define COLOR_SHIFT 180000  // Time for colours to shift to a new spectrum (in ms)
CRGB leds[NUM_LEDS];        // Define the array of leds

#define DATA_PIN 6          // led data transfer
#define PITCH_PIN 0         // pitch input from frequency to voltage converter
#define BRIGHT_PIN 4        // brightness input from amplified audio signal

unsigned long setTime = COLOR_SHIFT;
int shiftC = 0;
int mulC = 2;

// color structure for rgb
struct color {
  int r;
  int g;
  int b;
};
typedef struct color Color;

void setup() { 
    Serial.begin(9600);
  	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    pinMode(A0, INPUT);
    pinMode(A4, INPUT);

    for(int i = 0; i < NUM_LEDS ; i++) {
      leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
}

void loop() { 
  unsigned long time = millis();
  // Shift the color spectrum by 200
  if(time / (double)setTime >= 1) {
    setTime = time + COLOR_SHIFT;
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

  // Shift all LEDs to the right ime
  for(int i = NUM_LEDS - 1; i >= updateLEDS; i--) {
    leds[i] = leds[i - updateLEDS];
  }

  // Get the pitch and brightness to compute the new color
  int newPitch = (analogRead(PITCH_PIN)*2) + shiftC;
  Color nc = pitchConv(newPitch, analogRead(BRIGHT_PIN));

  // Set the left most updateLEDs 
  for(int i = 0; i < updateLEDS; i++) {
    leds[i] = CRGB(nc.r, nc.g, nc.b);
  }
  FastLED.show();
  delay(1);
}

/**
 * Converts the analog brightness reading into a percentage
 */
double convBrightness(int b) {
  double c = b / 614.0000;
  if( c < 0.2 ) {
    c = 0;
  }
  else if(c > 1) {
    c = 1.00;
  }
  return c;
}

/**
 * Creates a new color from pitch and brightness readings
 */
Color pitchConv(int p, int b) {
  Color c;
  double bright = convBrightness(b);

  if(p < 40) {
    setColor(&c, 255, 0, 0);
  }
  else if(p >= 40 && p <= 77) {
    int b = (p - 40) * (255/37.0000);
    setColor(&c, 255, 0, b);
  }
  else if(p > 77 && p <= 205) {
    int r = 255 - ((p - 78) * 2);
    setColor(&c, r, 0, 255);
  }
  else if(p >= 206 && p <= 238) {
    int g = (p - 206) * (255/32.0000);
    setColor(&c, 0, g, 255);
  }
  else if(p <= 239 && p <= 250) {
    int r = (p - 239) * (255/11.0000);
    setColor(&c, r, 255, 255);
  }
  else if(p >= 251 && p <= 270) {
    setColor(&c, 255, 255, 255);
  }
  else if(p >= 271 && p <= 398) {
    int rb = 255-((p-271)*2);
    setColor(&c, rb, 255, rb);
  }
  else if(p >= 398 && p <= 653) {
    setColor(&c, 0, 255-(p-398), (p-398));
  }
  else {
    setColor(&c, 255, 0, 0);
  }
  setColor(&c, c.r * bright, c.g * bright, c.b * bright);
  return c;
}

void setColor(Color *c, int r, int g, int b) {
  c->r = r;
  c->g = g;
  c->b = b;
}

// Prints color structure data
void printColor(Color c) {
  Serial.print("( ");
  Serial.print(c.r);
  Serial.print(", ");
  Serial.print(c.g);
  Serial.print(", ");
  Serial.print(c.b);
  Serial.println(" )");
}
