#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2c361cc388594f3e8088c65a1d3222b3";

SimpleTimer timer;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CEREBRO_GUEST";
char pass[] = "17flyonWater.1";

int state;
int count=0;
int flag=1;

WidgetLED LED1 (V1);
WidgetLED motionLED(V2);

void myTimerEvent()
{
  count = count+1;
  
  if(count==5)
  {
    motionLED.off();
    count=0;
    flag = 1;
  }

  int movementDectected = digitalRead(D7);
  if (movementDectected) // You can write any condition to trigger e-mail sending
  {
    if (flag == 1)
    {
        Serial.println("Movement Dectected"); // This can be seen in the Serial Monitor
        Blynk.email("Subject: PIR Sensor", "Movement detected at home!");
        Blynk.notify("WARNING: Movement detected at home!");
        digitalWrite(D4, LOW);
        LED1.on();
        // Or, if you want to use the email specified in the App (like for App Export):
        //Blynk.email("Subject: Button Logger", "You just pushed the button...");
        motionLED.on();
        flag=2;
      
    }
  }
}




void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(D4, OUTPUT);
  timer.setInterval(1000L, myTimerEvent);
}

BLYNK_WRITE(V0)
{
  state = param.asInt();
  if (state == 1){
    digitalWrite(D4, LOW);
    LED1.on();
  }
  else {
    digitalWrite(D4, HIGH);
    LED1.off();
  }
}


void loop()
{
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
}
