#include <AFMotor.h>          // Motor control library
#include <NewPing.h>          // Ultrasonic sensor library
#include <SoftwareSerial.h>   // Bluetooth communication
#include <Servo.h>            // Servo control
#include <EEPROM.h>           // For storing paths in memory

// Motor definitions
AF_DCMotor motor1(1, MOTOR12_1KHZ);  // Front-left motor
AF_DCMotor motor2(2, MOTOR12_1KHZ);  // Front-right motor
AF_DCMotor motor3(3, MOTOR34_1KHZ);  // Rear-left motor
AF_DCMotor motor4(4, MOTOR34_1KHZ);  // Rear-right motor

// Ultrasonic sensor configuration
#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Bluetooth setup
SoftwareSerial BT(0, 1);  // RX, TX pins

// Servo configuration
Servo myServo;
int servoPosition = 90;  // Center position

// Global variables
int motorSpeed = 200;     // Base motor speed (0-255)
int turnDelay = 300;      // Time for turning adjustments
int turnAdjustment = 0;   // Calibration value for turns
int currentAddress = 0;   // EEPROM address pointer

// Operational modes
bool autonomousMode = false;
bool recordingMode = false;
char currentCommand = '9';  // Default command

// Distance measurements
int frontDistance = 100;
int leftDistance = 0;
int rightDistance = 0;

void setup() {
  BT.begin(9600);
  myServo.attach(10);
  myServo.write(servoPosition);
  delay(2000);  // Initialization delay
  
  // Load turn calibration from EEPROM
  turnAdjustment = EEPROM.read(200);
}

// Main program loop
void loop() {
  checkBluetoothCommands();
  if (autonomousMode) {
    avoidObstacles();
  }
}

//###########################
//## Movement Functions ##
//###########################

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward() {
  setMotorDirections(FORWARD, FORWARD);
  setMotorSpeeds(motorSpeed, motorSpeed-25);
  delay(1000);
  stopMotors();
  if (recordingMode) saveCommand('f');
}

void moveBackward() {
  setMotorDirections(BACKWARD, BACKWARD);
  setMotorSpeeds(motorSpeed+3, motorSpeed-27);
  delay(400);
  stopMotors();
  if (recordingMode) saveCommand('b');
}

void rotateRight() {
  setMotorDirections(FORWARD, BACKWARD);
  setMotorSpeeds(255, 255);
  delay(turnDelay);
  stopMotors();
  if (recordingMode) saveCommand('r');
}

void rotateLeft() {
  setMotorDirections(BACKWARD, FORWARD);
  setMotorSpeeds(255, 255);
  delay(turnDelay);
  stopMotors();
  if (recordingMode) saveCommand('l');
}

//##########################
//## Sensor Functions ##
//##########################

int getDistance() {
  int distance = sonar.ping_cm();
  delay(50);
  return (distance == 0) ? MAX_DISTANCE : distance;
}

int lookLeft() {
  myServo.write(180);
  delay(400);
  int dist = getDistance();
  myServo.write(90);
  return dist;
}

int lookRight() {
  myServo.write(0);
  delay(400);
  int dist = getDistance();
  myServo.write(90);
  return dist;
}

//###########################
//## Autonomous Navigation ##
//###########################

void avoidObstacles() {
  while (autonomousMode) {
    frontDistance = getDistance();
    if (frontDistance < MAX_DISTANCE-50) {
      stopMotors();
      autonomousMode = false;
      moveBackward();
      makeTurnDecision();
      break;
    }
    moveForward();
  }
}

void makeTurnDecision() {
  rightDistance = lookRight();
  leftDistance = lookLeft();
  
  if (rightDistance >= leftDistance) {
    while (getDistance() < MAX_DISTANCE) {
      rotateRight();
      if (getDistance() == MAX_DISTANCE) {
        autonomousMode = true;
        avoidObstacles();
        break;
      }
    }
  } else {
    while (getDistance() < MAX_DISTANCE) {
      rotateLeft();
      if (getDistance() == MAX_DISTANCE) {
        autonomousMode = true;
        avoidObstacles();
        break;
      }
    }
  }
}

//#######################
//## Memory Functions ##
//#######################

void saveCommand(char cmd) {
  EEPROM.update(currentAddress, cmd);
  currentAddress++;
}

void executePath(int startAddr, int endAddr) {
  for (int addr = startAddr; addr <= endAddr; addr++) {
    char command = EEPROM.read(addr);
    executeCommand(command);
    delay(50);
  }
}

//##########################
//## Bluetooth Handling ##
//##########################

void checkBluetoothCommands() {
  if (BT.available()) {
    char received = BT.read();
    switch(received) {
      case '1': setupRecording(1); break;
      case '2': setupRecording(2); break;
      case '3': setupRecording(3); break;
      case '4': executePath(1, 50); break;
      case '5': executePath(51, 100); break;
      case '6': executePath(101, 150); break;
      case 'f': moveForward(); break;
      case 'b': moveBackward(); break;
      case 'r': rotateRight(); break;
      case 'l': rotateLeft(); break;
      case 's': autonomousMode = true; break;
      case 'z': recordingMode = false; break;
    }
  }
}

//########################
//## Utility Functions ##
//########################

void setMotorDirections(uint8_t frontDir, uint8_t rearDir) {
  motor1.run(frontDir);
  motor2.run(frontDir);
  motor3.run(rearDir);
  motor4.run(rearDir);
}

void setMotorSpeeds(int frontSpeed, int rearSpeed) {
  motor1.setSpeed(frontSpeed);
  motor2.setSpeed(frontSpeed);
  motor3.setSpeed(rearSpeed);
  motor4.setSpeed(rearSpeed);
}

void setupRecording(int pathNumber) {
  recordingMode = true;
  currentAddress = (pathNumber-1)*50;
  BT.print("Recording Path ");
  BT.println(pathNumber);
}

void executeCommand(char command) {
  switch(command) {
    case 'f': moveForward(); break;
    case 'b': moveBackward(); break;
    case 'r': rotateRight(); break;
    case 'l': rotateLeft(); break;
  }
}
