// The library "Adafruit NeoPixel by Adafruit" needs to be installed.
#include <Adafruit_NeoPixel.h>

// The LED strip is wired to PIN 1.
#define LED 1

// The sensor is wired to the 0 digital pin.
#define SENSOR 0

// Initialising the the NeoPixel strip library with the model we have
// installed.
Adafruit_NeoPixel  strip = Adafruit_NeoPixel(24, LED, NEO_RGBW + NEO_KHZ800);

// The parameter holds the time of the last sensor reading.
// We use this and the sensorReadingThreshold to define how often take readings
// of the sensor.
uint32_t lastSensorReading = millis();

// The minimum time to pass in milliseconds before taking another reading 
// on the proximty sensor.
uint32_t sensorReadingThreshold = 1000;

void setup() {
  // Init Touch Sensor PIN
  pinMode(SENSOR, INPUT);
  
  // Init Strip
  strip.begin();
  
  // Setting the brightness of the LED strip to the highest level.
  strip.setBrightness(255);
}

void loop() {

  uint32_t currentTime = millis();
  uint32_t delta = currentTime - lastSensorReading;

  // Dismiss the reading if last reading was within the treshold.
  if (delta < sensorReadingThreshold) {
    return;
  }

  // The digital sensor reading
  int reading = digitalRead(SENSOR);

  if (reading == 1) {
    lightUp();
  } else {
    turnOff(); 
  }

  delay(50);

}


// Called to turn on the strip. 
// We only address the WHITE pixel.
void lightUp() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 255));
    strip.show();
  }
}

// Called to turn off the strip.
void turnOff() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
    strip.show();
  }
}