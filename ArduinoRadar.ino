
#include <Servo.h>  // Include the servo library

// Define pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Create a servo object
Servo myServo;

// Variables to hold distance values
int distance;

// Variables for radar sweep angles
int angle;

void setup() {
  // Initialize the serial monitor
  Serial.begin(9600);
  
  // Attach the servo to pin 11
  myServo.attach(11);
  
  // Set the pin modes for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Radar sweep from 0° to 180°
  for (angle = 0; angle <= 180; angle += 2) {
    myServo.write(angle);           // Move the servo to the angle
    distance = getDistance();       // Get distance reading
    Serial.print(angle);            // Send angle
    Serial.print(" ");
    Serial.println(distance);       // Send distance
    delay(30);                      // Wait for the next reading
  }
  
  // Radar sweep from 180° to 0°
  for (angle = 180; angle >= 0; angle -= 2) {
    myServo.write(angle);           // Move the servo to the angle
    distance = getDistance();       // Get distance reading
    Serial.print(angle);            // Send angle
    Serial.print(" ");
    Serial.println(distance);       // Send distance
    delay(30);                      // Wait for the next reading
  }
}

// Function to calculate distance from ultrasonic sensor
int getDistance() {
  // Send a 10us pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the time the echo takes to return
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance (duration/2 because of round trip of the signal)
  int distance = duration * 0.034 / 2;
  
  // Return the distance in cm
  return distance;
}
