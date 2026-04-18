#define TRIG1 2
#define ECHO1 3

#define TRIG2 4
#define ECHO2 5

#define IR_PIN 6
#define MQ3_PIN A0   // Analog pin

#define BUZZER 8

long duration;
int distance1, distance2;

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void setup() {
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(IR_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  Serial.println("System Initialized...");
}

void loop() {

  distance1 = getDistance(TRIG1, ECHO1);
  distance2 = getDistance(TRIG2, ECHO2);

  int irState = digitalRead(IR_PIN);
  int alcoholValue = analogRead(MQ3_PIN);

  // 📊 Serial Output
  Serial.print("D1: ");
  Serial.print(distance1);
  Serial.print(" cm | D2: ");
  Serial.print(distance2);
  Serial.print(" cm | IR: ");
  Serial.print(irState);
  Serial.print(" | MQ3: ");
  Serial.println(alcoholValue);

  // 🔴 IR (Highest Priority)
  if (irState == LOW) {
    Serial.println("⚠️ IR Obstacle Detected!");
    for (int i = 0; i < 2; i++) {
      digitalWrite(BUZZER, HIGH);
      delay(150);
      digitalWrite(BUZZER, LOW);
      delay(150);
    }
    return;
  }

  // 🔴 Alcohol Detection (Threshold = 200)
  if (alcoholValue > 200) {
    Serial.println("⚠️ Alcohol Detected!");
    digitalWrite(BUZZER, HIGH);
    delay(800);
    digitalWrite(BUZZER, LOW);
    delay(200);
    return;
  }

  // 🔴 Parking
  if (distance2 > 0 && distance2 < 30) {
    Serial.println("🚗 Parking Object Detected!");
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(100);
    }
    return;
  }

  // 🔴 Level Warning
  if (distance1 < 10) {
    Serial.println("⚠️ Level Warning!");
    digitalWrite(BUZZER, HIGH);
    delay(1200);
    digitalWrite(BUZZER, LOW);
    delay(500);
    return;
  }

  // ✅ Normal
  Serial.println("✅ Normal Condition");
  digitalWrite(BUZZER, LOW);

  delay(500);
}