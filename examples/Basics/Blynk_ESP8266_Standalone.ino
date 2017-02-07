/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * Note: This requires ESP8266 support package:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
// MCL: token for esptest with ESP8266
char auth[] = "d3664a568faa4f90bdfae9684519919a";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CEREBRO_GUEST";
char pass[] = "17flyonWater";

void setup()
{
//  delay(1000);
  Serial.begin(9600);
//  Serial.println("before blynk.begin");
  Blynk.begin(auth, ssid, pass);
//  Serial.println("after blynk.begin");
}

void loop()
{
  Blynk.run();
}

