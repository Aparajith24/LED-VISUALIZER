#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN  7
#define SOUNDSENSOR 3
#define FADESPEED 5     // make this higher to slow down

void setup() {
  pinMode(REDPIN, OUTPUT);   //define R color of LED strip as output
  pinMode(GREENPIN, OUTPUT); // defie G color of LED strip as output
  pinMode(BLUEPIN, OUTPUT);  // define B color of LED stripas output
  pinMode(SOUNDSENSOR , INPUT); // define the sound sensor as input
}


void loop() {
  int statusSensor = analogRead(SOUNDSENSOR);
  int r, g, b;

 if(statusSensor == 1){ // when sensor detects a signal
   // fade from blue to violet
   for (r = 0; r < 256; r++) {
     analogWrite(REDPIN, r);
     delay(FADESPEED);
   }
   // fade from violet to red
   for (b = 255; b > 0; b--) {
     analogWrite(BLUEPIN, b);
     delay(FADESPEED);
   }
   // fade from red to yellow
   for (g = 0; g < 256; g++) {
     analogWrite(GREENPIN, g);
     delay(FADESPEED);
   }
   // fade from yellow to green
   for (r = 255; r > 0; r--) {
     analogWrite(REDPIN, r);
     delay(FADESPEED);``````5 66
   }
   // fade from green to teal
   for (b = 0; b < 256; b++) {
     analogWrite(BLUEPIN, b);
     delay(FADESPEED);
   }
   // fade from teal to blue
   for (g = 255; g > 0; g--) {
     analogWrite(GREENPIN, g);
     delay(FADESPEED);
   }
   /**The following loops will be used to produce white
   *first loop will fade up red and fade down blue
   the last loop will fade up green and blue to produce white
   */
   for (r = 0; r < 256; r++) {
     analogWrite(REDPIN, r);
     analogWrite(BLUEPIN, 255 - r);
     delay(FADESPEED);
   }
   for (r = 0; r < 256; r++) {
     analogWrite(GREENPIN, 255 r);
     analogWrite(BLUEPIN, 255 r);
     delay(FADESPEED);
   }
  }
}
