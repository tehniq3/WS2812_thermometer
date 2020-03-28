#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>
 
// numar pin OneWire DS18B20
#define ONE_WIRE_BUS 4
 
// Setari neopixel
#define PIN 5
#define LED_COUNT 31
 
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Create an instance of the Adafruit_NeoPixel class called "leds". That'll be what we refer to from here on...
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

int te0 = 10;
int te1 = 15;
int te2 = 20;
int te3 = 25;
int te4 = 30;
int te5 = 35;
int te6 = 40;

int r, r1, r2;
int g, g1, g2;
int b, b1, b2;
 
void setup(void)
{
  Serial.begin(9600); // start serial port
 
  // ds18b20
  sensors.begin(); // Start up the library
  // More on resolution: https://homautomation.org/2015/11/17/ds18b20-how-to-change-resolution-9-10-11-12-bits/
  sensors.setResolution(9);    
            
  // neopixel
  leds.begin();
  leds.show(); // Initialize all pixels to 'off'
}
 
 
void loop(void)
{
  float temp;
  int i, numar_led;
 
//  ds18b20
  sensors.requestTemperatures(); // Send the command to get temperatures. request to all devices on the bus
  temp = sensors.getTempCByIndex(0);
 
  Serial.print("Temperature: ");
  Serial.println(temp); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
 delay(2000);
  // neopixel
 
  // nejak si zkusine zpocitat teplotu, treba..
  numar_led = temp - te0;

/*
  // vsechno zhasneme
  for(i=0; i<leds.numPixels(); i++) {
    leds.setPixelColor(i, 0x000000);
    //leds.show();
  }
*/

 if ((temp >= te0) and (temp < te1))
 {
  r1 = 0;
  g1 = 0;
  b1 = 255;
  r2 = 255;
  g2 = 255;
  b2 = 255;
  r = (r2-r1)/(te1-te0)*(temp-te0)+r1;
  g = (b2-b1)/(te1-te0)*(temp-te0)+g1;
  b = (b2-b1)/(te1-te0)*(temp-te0)+b1;
 }

 if ((temp >= te1) and (temp < te2))
 {
  r1 = 255;
  g1 = 255;
  b1 = 255;
  r2 = 0;
  g2 = 255;
  b2 = 255;
  r = (r2-r1)/(te1-te0)*(temp-te0)+r1;
  g = (b2-b1)/(te1-te0)*(temp-te0)+g1;
  b = (b2-b1)/(te1-te0)*(temp-te0)+b1;
 }

 if ((temp >= te2) and (temp < te3))
 {
  r1 = 0;
  g1 = 255;
  b1 = 255;
  r2 = 0;
  g2 = 255;
  b2 = 0;
  r = (r2-r1)/(te1-te0)*(temp-te0)+r1;
  g = (b2-b1)/(te1-te0)*(temp-te0)+g1;
  b = (b2-b1)/(te1-te0)*(temp-te0)+b1;
 }

 if ((temp >= te3) and (temp < te4))
 {
  r1 = 0;
  g1 = 255;
  b1 = 0;
  r2 = 255;
  g2 = 255;
  b2 = 0;
  r = (r2-r1)/(te1-te0)*(temp-te0)+r1;
  g = (b2-b1)/(te1-te0)*(temp-te0)+g1;
  b = (b2-b1)/(te1-te0)*(temp-te0)+b1;
 }

 if ((temp >= te4) and (temp < te5))
 {
  r1 = 255;
  g1 = 255;
  b1 = 0;
  r2 = 255;
  g2 = 0;
  b2 = 0;
  r = (r2-r1)/(te1-te0)*(temp-te0)+r1;
  g = (b2-b1)/(te1-te0)*(temp-te0)+g1;
  b = (b2-b1)/(te1-te0)*(temp-te0)+b1;
 }

 if ((temp >= te5) and (temp <= te6))
 {
  r1 = 255;
  g1 = 0;
  b1 = 0;
  r2 = 255;
  g2 = 0;
  b2 = 255;
  r = (r2-r1)/(te1-te0)*(temp-te0)+r1;
  g = (b2-b1)/(te1-te0)*(temp-te0)+g1;
  b = (b2-b1)/(te1-te0)*(temp-te0)+b1;
 }

   //se aprinde doar numărul de diode, care arata temperatura - 20, așa că, de exemplu, 25 ° ar trebui să aprindă 5 diode
  for(i=0; i<numar_led; i++) {
  //  leds.setPixelColor(i, 0x0100000);
   leds.setPixelColor(i, leds.Color(r, g, b));
   // leds.show();
  }
   for(i=numar_led; i<LED_COUNT; i++) {
  //  leds.setPixelColor(i, 0x0100000);
   leds.setPixelColor(i, leds.Color(0, 0, 0));
   // leds.show();
  }
  leds.show();
}
