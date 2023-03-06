#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <MAX30100_PulseOximeter.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLMSowIS-n"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "PoOkI3hSyVomTf6QpOrvnxqZYJH8RZ77"
char auth[] = "PoOkI3hSyVomTf6QpOrvnxqZYJH8RZ7";
 
char ssid[] = "Yusuf";
char pass[] = "12345678";

// Initialize the pulse oximeter and temperature sensor objects
PulseOximeter pox;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Variables to store pulse oximeter and temperature sensor data
float bpm = 0;
float spo2 = 0;
float temp = 0;
// Blynk virtual pins
#define VIRTUAL_PIN_BPM V0
#define VIRTUAL_PIN_SPO2 V1
#define VIRTUAL_PIN_TEMP V2
void setup() {
  Serial.begin(9600);
  // Initialize the pulse oximeter
  if (!pox.begin()) {
    Serial.println("Failed to initialize pulse oximeter!");  
  }
  // Initialize the temperature sensor
  mlx.begin();
  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Update the pulse oximeter
  pox.update();
  // Get the heart rate and SpO2 values
  bpm = pox.getHeartRate();
  spo2 = pox.getSpO2();
  // Get the temperature value
  temp = mlx.readObjectTempC();
  // Print the values to the serial monitor
  Serial.print("Heart rate: ");
  Serial.print(bpm);
  Serial.print(" bpm, SpO2: ");
  Serial.print(spo2);
  Serial.print("%, Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  // Send the values to Blynk
  Blynk.virtualWrite(VIRTUAL_PIN_BPM, bpm);
  Blynk.virtualWrite(VIRTUAL_PIN_SPO2, spo2);
  Blynk.virtualWrite(VIRTUAL_PIN_TEMP, temp);
  // Wait for 1 second
  delay(1000);
}
