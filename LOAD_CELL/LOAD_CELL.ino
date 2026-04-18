#include "HX711.h"

#define DT 4
#define SCK 5

HX711 scale;

// 🔴 Put your calculated value here
float calibration_factor = 214.0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  scale.begin(DT, SCK);

  Serial.println("Remove weight...");
  scale.tare();

  Serial.println("Ready!");
}

void loop() {
  float weight = scale.get_units(10) / calibration_factor;

  Serial.print("Weight: ");
  Serial.print(weight, 2);
  Serial.println(" g");

  delay(500);
}