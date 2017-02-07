/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  Control a color gradient on NeoPixel strip using a slider!

  For this example you need NeoPixel library:
    https://github.com/adafruit/Adafruit_NeoPixel

  App project setup:
    Slider widget (0...500) on V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
// MCL: token for esptest with ESP8266
char auth[] = "d3664a568faa4f90bdfae9684519919a";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CEREBRO_GUEST";
char pass[] = "17flyonWater";

// NeoPixel stick DIN pin
#define DIN_PIN D2

// How many NeoPixels on the stick?
#define NUM_PIXELS 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, DIN_PIN, NEO_GRB + NEO_KHZ800);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

BLYNK_WRITE(V1)
{
  int shift = param.asInt();
  for (int i = 0; i < strip.numPixels(); i++)
  {
    Serial.print("Color is ");
    Serial.println(shift & 255);
    strip.setPixelColor(i, Wheel(shift & 255));
    //strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + shift) & 255));
  }
  strip.show();
}

BLYNK_WRITE(V2)
{
  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();

  Serial.print("Got RGB values: R=");
  Serial.print(R);
  Serial.print(" G=");
  Serial.print(G);
  Serial.print(" B=");
  Serial.println(B);
  
  for (int i = 0; i < strip.numPixels(); i++)
  {
    Serial.print("Color is ");
    strip.setPixelColor(i, strip.Color(R, G, B));
    // OR: strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + shift) & 255));
  }
  strip.show();
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  strip.setBrightness(15);
  strip.begin();
}

void loop()
{
  Blynk.run();
}

