#define BLYNK_PRINT Serial
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_TEMPLATE_ID "TMPLMSowIS-n"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "PoOkI3hSyVomTf6QpOrvnxqZYJH8RZ77"
char auth[] = "PoOkI3hSyVomTf6QpOrvnxqZYJH8RZ77";
 
//char auth[] = "PoOkI3hSyVomTf6QpOrvnxqZYJH8RZ7";
 
char ssid[] = "pada";
char pass[] = "12345678";

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  Wire.begin(D2, D1);
  mlx.begin();
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  float ambientTemp = mlx.readAmbientTempC();
  float objectTemp = mlx.readObjectTempC();

  Blynk.virtualWrite(V0, ambientTemp); // send ambient temperature to virtual pin V0
  Blynk.virtualWrite(V1, objectTemp); // send object temperature to virtual pin V1

  Serial.print("Ambient temperature: ");
  Serial.print(ambientTemp);
  Serial.print(" C\tObject temperature: ");
  Serial.print(objectTemp);
  Serial.println(" C");

  Blynk.run();
  delay(1000);
}
