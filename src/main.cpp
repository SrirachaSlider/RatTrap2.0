#include <Arduino.h>

// Declare our variables

// Pin definitions
const int IR_SENSOR_PIN = 2;
const int ACTUATOR_FORWARD_PIN = 8;
const int ACTUATOR_BACKWARD_PIN = 7;
const int ACTUATOR_SPEED_PIN = 9;
const int trigPin = 7;
const int echoPin = 6;

// Constants
const int ACTUATION_TIME = 2000;
const int DEBOUNCE_DELAY = 50;

void setup()
{
  // pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(ACTUATOR_FORWARD_PIN, OUTPUT);
  pinMode(ACTUATOR_BACKWARD_PIN, OUTPUT);
  pinMode(ACTUATOR_SPEED_PIN, OUTPUT);

  Serial.begin(9600); // For debugging
  Serial.println("Rat Trap System ready to kill, ah safely trap a rat");
}

void loop()
{
  digitalWrite(ACTUATOR_FORWARD_PIN, HIGH);
  digitalWrite(ACTUATOR_BACKWARD_PIN, LOW);
  analogWrite(ACTUATOR_SPEED_PIN, 255); // Full speed; adjust 0-255
  delay(2000);
}
