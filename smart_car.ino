#include <NewPing.h>   // Ultrasonic sensor library
#include <Servo.h>     // Servo motor library
#include <AFMotor.h>   // Motor driver library

// Ultrasonic sensor pins
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define max_distance 50

// IR sensor pins
#define irLeft A0
#define irRight A1

// Motor speed
#define MAX_SPEED 200
#define MAX_SPEED_OFFSET 20

// Servo object
Servo servo;

// Ultrasonic sensor object
NewPing sonar(TRIGGER_PIN, ECHO_PIN, max_distance);

// DC motor objects
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

// Variables
int distance = 0;
int leftDistance;
int rightDistance;
boolean object;

void setup() {

  // Start serial monitor
  Serial.begin(9600);

  // Set IR sensors as input
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);

  // Attach servo to pin 10
  servo.attach(10);

  // Set servo to center position
  servo.write(90);

  // Set motor speeds
  motor1.setSpeed(120);
  motor2.setSpeed(120);
  motor3.setSpeed(120);
  motor4.setSpeed(120);
}

void loop() {

  // Move forward
  if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 0 ) {
    objectAvoid();
  }

  // Turn left
  else if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 1 ) {
    objectAvoid();

    Serial.println("TL");
    moveLeft();
  }

  // Turn right
  else if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 0 ) {
    objectAvoid();

    Serial.println("TR");
    moveRight();
  }

  // Stop robot
  else if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 1 ) {
    Stop();
  }
}

// Obstacle avoidance function
void objectAvoid() {
  distance = getDistance();

  // Obstacle detected
  if (distance <= 15) {
    Stop();

    Serial.println("Stop");

    // Check left and right side
    lookLeft();
    lookRight();

    delay(100);

    // Compare distances
    if (rightDistance <= leftDistance) {
      object = true;
      turn();

      Serial.println("moveLeft");
    }

    else {
      object = false;
      turn();

      Serial.println("moveRight");
    }
    delay(100);
  }

  // No obstacle
  else {
    Serial.println("moveForward");
    moveForward();
  }
}

// Measure distance
int getDistance() {
  delay(50);

  int cm = sonar.ping_cm();

  // If no object detected
  if (cm == 0) {
    cm = 100;
  }

  return cm;
}

// Look left side
int lookLeft () {
  servo.write(150);
  delay(500);

  leftDistance = getDistance();
  delay(100);

  servo.write(90);

  Serial.print("Left:");
  Serial.print(leftDistance);

  return leftDistance;

  delay(100);
}

// Look right side
int lookRight() {
  servo.write(30);
  delay(500);

  rightDistance = getDistance();
  delay(100);

  servo.write(90);

  Serial.print("   ");
  Serial.print("Right:");
  Serial.println(rightDistance);

  return rightDistance;

  delay(100);
}

// Stop motors
void Stop() {

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

// Move forward
void moveForward() {

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// Move backward
void moveBackward() {

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// Turning logic
void turn() {

  // Turn right path
  if (object == false) {
    Serial.println("turn Right");

    moveLeft();
    delay(700);

    moveForward();
    delay(800);

    moveRight();
    delay(900);

    if (digitalRead(irRight) == 1) {
      loop();
    }

    else {
      moveForward();
    }
  }

  // Turn left path
  else {
    Serial.println("turn left");

    moveRight();
    delay(700);

    moveForward();
    delay(800);

    moveLeft();
    delay(900);

    if (digitalRead(irLeft) == 1) {
      loop();
    }

    else {
      moveForward();
    }
  }
}

// Move right
void moveRight() {

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);

  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// Move left
void moveLeft() {

  motor1.run(FORWARD);
  motor2.run(FORWARD);

  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
