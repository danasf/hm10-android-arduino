/*
Connect Bluetooth RX,TX to Arduino RX,TX

Requires NeoPixel Library
https://github.com/adafruit/Adafruit_NeoPixel

If you want to view via Serial Monitor and have your Arduino connect to BT module 
simultaneously use Software Serial to open a second port.

#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 4); // RX, TX
*/



#include <Adafruit_NeoPixel.h>

int red,green,blue;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // initialize serial:
  Serial.begin(9600);
  // mySerial.begin(9600);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int red = Serial.parseInt(); 
    // do it again:
    int green = Serial.parseInt(); 
    // do it again:
    int blue = Serial.parseInt(); 

    // look for the newline. That's the end of your
    // sentence:
    // if (mySerial.read() == '\n') {
    if (Serial.read() == '\n') {
      // sends confirmation
      Serial.println("received");
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

