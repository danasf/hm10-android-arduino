/*
Software Serial Bluetooth
Connect Bluetooth RX,TX to Arduino Pins 10,11

Requires NeoPixel Library
https://github.com/adafruit/Adafruit_NeoPixel
*/

#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
// RX, TX
SoftwareSerial mySerial(10, 11); 

int red,green,blue;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // initialize serial:
  mySerial.begin(9600);
  // set strip off
  colorSet(strip.Color(0, 0,0), 0); 

}

void loop() {
  // if there's any serial available, read it:
  while (mySerial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int red = mySerial.parseInt(); 
    // do it again:
    int green = mySerial.parseInt(); 
    // do it again:
    int blue = mySerial.parseInt(); 

    // look for the newline. That's the end of your statement
    if (mySerial.read() == '\n') {

      // constrain the values to 0 - 255
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);
      
      // fill strip
      colorSet(strip.Color(red, green, blue), 0);      
      
      // send some data back
      mySerial.println("received:"+String(red)+","+String(green)+","+String(blue));

   }
}
}

// Fill strip with a color
void colorSet(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
   strip.show();
   delay(wait);
}
