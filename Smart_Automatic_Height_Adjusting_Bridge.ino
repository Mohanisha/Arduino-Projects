#include <Servo.h>

// ----- Pin Definitions -----
const int waterSensor = A0;
const int redLED = 7;
const int buzzer = 8;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Threshold for high water level (adjust after testing)
int waterThreshold = 400;

void setup() {
  Serial.begin(9600);

  pinMode(waterSensor, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Attach servos to pins
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);

  // Initial positions (bridge normal)
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);

  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  int waterValue = analogRead(waterSensor);
  Serial.print("Water Level: ");
  Serial.println(waterValue);

  if (waterValue > waterThreshold) {
    // High water level detected
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);

    // Rotate all 4 servos to activate safety mode
    servo1.write(0);
    servo2.write(0);
    servo3.write(0);
    servo4.write(0);

    Serial.println("Flood Detected! Bridge Activated.");
  } 
  else {
    // Water level normal
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);

    // Reset servos to normal operation
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
  }

  delay(300); // small delay
}
