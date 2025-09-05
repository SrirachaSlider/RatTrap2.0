#include <Arduino.h>

// Declare our variables
long duration;
int distance;

const int trigPin = 7;
const int echoPin = 6;

void setup()
{
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 29) / 2; // cm

  Serial.print("Distance: ");
  Serial.println(distance);
}
