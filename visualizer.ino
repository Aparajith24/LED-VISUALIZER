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
  delay(1);
}

//brightness reading to a percentage (100% = 614) that is 3 volts
//It will be multipled to the RGB values to get voltage.
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

//creating new colours from the pitch and brightness
Color pitchConv(int p, int b) {
  Color c;
  double bright = convBrightness(b);

  if(p < 40) {
    setColour(&c, 255, 0, 0);
  }
  else if(p >= 40 && p <= 77) {
    int b = (p - 40) * (255/37.0000);
    setColour(&c, 255, 0, b);
  }
  else if(p > 77 && p <= 205) {
    int r = 255 - ((p - 78) * 2);
    setColour(&c, r, 0, 255);
  }
  else if(p >= 206 && p <= 238) {
    int g = (p - 206) * (255/32.0000);
    setColour(&c, 0, g, 255);
  }
  else if(p <= 239 && p <= 250) {
    int r = (p - 239) * (255/11.0000);
    setColour(&c, r, 255, 255);
  }
  else if(p >= 251 && p <= 270) {
    setColour(&c, 255, 255, 255);
  }
  else if(p >= 271 && p <= 398) {
    int rb = 255-((p-271)*2);
    setColour(&c, rb, 255, rb);
  }
  else if(p >= 398 && p <= 653) {
    setColour(&c, 0, 255-(p-398), (p-398));
  }
  else {
    setColour(&c, 255, 0, 0);
  }
  setColour(&c, c.r * bright, c.g * bright, c.b * bright);
  return c;
}

void setColour(Color *c, int r, int g, int b) {
  c->r = r;
  c->g = g;
  c->b = b;
}

// Prints color structure data
void printColour(Color c) {
  Serial.print("( ");
  Serial.print(c.r);
  Serial.print(", ");
  Serial.print(c.g);
  Serial.print(", ");
  Serial.print(c.b);
  Serial.println(" )");
}

