#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Servo.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo servo;
int motorPin = D5; // Servo motor control pin
int pumpPin = D6; // Water pump control pin

void setup() {
  Serial.begin(9600);
  Wire.begin(D2, D1); // Initialize I2C communication with SDA on D2 and SCL on D1
  mlx.begin();
  servo.attach(motorPin);
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  float objTemp = mlx.readObjectTempC(); // Read the object temperature in Celsius
  Serial.print("Object Temperature: ");
  Serial.print(objTemp);
  Serial.println(" C");

  if (objTemp >= 30) { // If object temperature is greater than or equal to 50 degrees Celsius
    
    digitalWrite(pumpPin, HIGH); // Turn on water pump
    delay(5000); // Delay for 5 seconds
    digitalWrite(pumpPin, LOW); // Turn off water pump
    servo.write(360); // Rotate servo motor 360 degrees
    delay(5000); // Delay for 5 seconds
  }

  delay(500); // Delay for 0.5 seconds
}
