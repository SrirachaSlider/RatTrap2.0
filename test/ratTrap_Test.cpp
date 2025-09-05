#include <Arduino.h>

// Pin definitions
const int IR_SENSOR_PIN = 2;         // Digital pin for IR sensor
const int TRIG_PIN = 3;              // Ultrasonic sensor trigger pin
const int ECHO_PIN = 4;              // Ultrasonic sensor echo pin
const int ACTUATOR_FORWARD_PIN = 8;  // Actuator direction pin (extend)
const int ACTUATOR_BACKWARD_PIN = 7; // Actuator direction pin (retract)
const int ACTUATOR_SPEED_PIN = 9;    // PWM pin for actuator speed

// Constants
const int ACTUATION_TIME = 2000; // Time in ms to extend actuator
const int DEBOUNCE_DELAY = 50;   // Delay to debounce sensor readings
const float MAX_DISTANCE = 50.0; // Max distance in cm for ultrasonic detection (adjust based on trap size)

// Variables
bool trapActivated = false; // Flag to prevent multiple triggers

void setup()
{
  // Initialize pins
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ACTUATOR_FORWARD_PIN, OUTPUT);
  pinMode(ACTUATOR_BACKWARD_PIN, OUTPUT);
  pinMode(ACTUATOR_SPEED_PIN, OUTPUT);

  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Rat Trap System Initialized");

  // Ensure actuator is off at start
  digitalWrite(ACTUATOR_FORWARD_PIN, LOW);
  digitalWrite(ACTUATOR_BACKWARD_PIN, LOW);
  analogWrite(ACTUATOR_SPEED_PIN, 0);
}

void loop()
{
  // Skip actuation if trap already triggered
  if (trapActivated)
  {
    delay(DEBOUNCE_DELAY);
    return;
  }

  // Read IR sensor (assuming LOW means detection; adjust based on sensor)
  int irValue = digitalRead(IR_SENSOR_PIN);

  // Read ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // Convert to cm

  // Check if both sensors detect rat
  if (irValue == LOW && distance < MAX_DISTANCE)
  {
    Serial.println("Rat detected by both sensors!");
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    activateActuator();
    trapActivated = true; // Prevent re-triggering
  }

  delay(DEBOUNCE_DELAY); // Stabilize readings
}

void activateActuator()
{
  Serial.println("Activating actuator...");

  // Extend actuator
  digitalWrite(ACTUATOR_FORWARD_PIN, HIGH);
  digitalWrite(ACTUATOR_BACKWARD_PIN, LOW);
  analogWrite(ACTUATOR_SPEED_PIN, 255); // Full speed; adjust 0-255

  delay(ACTUATION_TIME); // Time to push

  // Stop actuator
  digitalWrite(ACTUATOR_FORWARD_PIN, LOW);
  digitalWrite(ACTUATOR_BACKWARD_PIN, LOW);
  analogWrite(ACTUATOR_SPEED_PIN, 0);

  Serial.println("Actuation complete.");
}