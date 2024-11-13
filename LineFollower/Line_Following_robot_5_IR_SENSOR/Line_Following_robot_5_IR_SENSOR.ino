// Pin definitions
const int leftMostSensor = 2;
const int leftSensor = 3;
const int centerSensor = 4;
const int rightSensor = 5;
const int rightMostSensor = 6;

const int motorLeftForward = 7;  // Change to an available output pin
const int motorLeftBackward = 8; // Change to an available output pin
const int motorRightForward = 9; // Change to an available output pin
const int motorRightBackward = 12; // Change to an available output pin
const int EN1 = 10; // PWM pin for left motor speed
const int EN2 = 11; // PWM pin for right motor speed

void setup() {
  pinMode(leftMostSensor, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(rightMostSensor, INPUT);

  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);
  
  pinMode(EN1, OUTPUT); // PWM for left motor
  pinMode(EN2, OUTPUT); // PWM for right motor
}

void loop() {
  int leftMost = digitalRead(leftMostSensor);
  int left = digitalRead(leftSensor);
  int center = digitalRead(centerSensor);
  int right = digitalRead(rightSensor);
  int rightMost = digitalRead(rightMostSensor);

  if (center == LOW) {
    moveForward();
  } else if (left == LOW) {
    turnLeft();
  } else if (right == LOW) {
    turnRight();
  } else if (leftMost == LOW) {
    hardTurnLeft();
  } else if (rightMost == LOW) {
    hardTurnRight();
  } else {
    stopMotors();
  }
}

void moveForward() {
  analogWrite(EN1, 255); // Full speed for left motor
  analogWrite(EN2, 255); // Full speed for right motor
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

void turnLeft() {
  analogWrite(EN1, 200); // Slow down left motor
  analogWrite(EN2, 255); // Full speed for right motor
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

void turnRight() {
  analogWrite(EN1, 255); // Full speed for left motor
  analogWrite(EN2, 200); // Slow down right motor
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
}

void hardTurnLeft() {
  analogWrite(EN1, 0);   // Stop left motor
  analogWrite(EN2, 255); // Full speed for right motor
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
  delay(200); // Adjust this delay for a sharper turn
}

void hardTurnRight() {
  analogWrite(EN1, 255); // Full speed for left motor
  analogWrite(EN2, 0);   // Stop right motor
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
  delay(200); // Adjust this delay for a sharper turn
}

void stopMotors() {
  analogWrite(EN1, 0); // Stop left motor
  analogWrite(EN2, 0); // Stop right motor
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightBackward, LOW);
}
