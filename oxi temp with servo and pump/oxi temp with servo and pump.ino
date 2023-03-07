#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Servo.h>
#include "MAX30100_PulseOximeter.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo servo;
int motorPin = D5; // Servo motor control pin
int pumpPin = D6; // Water pump control pin

MAX30100_PulseOximeter pox;
const uint8_t RATE_SIZE = 4; // Increase this for more averaging. 4 is good.
int rates[RATE_SIZE]; // Array of heart rates
uint8_t rateSpot = 0;
long lastBeat = 0; // Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

void setup() {
  Serial.begin(9600);
  Wire.begin(D4, D8); // Initialize I2C communication with SDA on D8 and SCL on D4
  mlx.begin();
  servo.attach(motorPin);
  pinMode(pumpPin, OUTPUT);

  if (!pox.begin()) {
    Serial.println("MAX30100 was not found. Please check wiring/power.");
    while (1);
  }

  pox.setup();
  pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);
}

void loop() {
  float objTemp = mlx.readObjectTempC(); // Read the object temperature in Celsius
  Serial.print("Object Temperature: ");
  Serial.print(objTemp);
  Serial.println(" C");

  // Read heart rate
  pox.check();
  if (millis() - lastBeat > 10000UL) {
    beatsPerMinute = 0;
  }

  if (pox.getHeartRate() > 0) {
    rates[rateSpot++] = pox.getHeartRate();
    rateSpot %= RATE_SIZE;
    beatAvg = 0;
    for (int i = 0; i < RATE_SIZE; i++) {
      beatAvg += rates[i];
    }
    beatAvg /= RATE_SIZE;
    lastBeat = millis();
    beatsPerMinute = beatAvg;
  }

  Serial.print("Heart rate: ");
  Serial.print(beatsPerMinute);
  Serial.println(" bpm");

  if (objTemp >= 50 && beatsPerMinute >= 70) { // If object temperature is greater than or equal to 50 degrees Celsius and heart rate is greater than or equal to 70 bpm
    servo.write(360); // Rotate servo motor 360 degrees
    delay(5000); // Delay for 5 seconds
    digitalWrite(pumpPin, HIGH); // Turn on water pump
    delay(5000); // Delay for 5 seconds
    digitalWrite(pumpPin, LOW); // Turn off water pump
  }

  delay(500); // Delay for 0.5 seconds
}
