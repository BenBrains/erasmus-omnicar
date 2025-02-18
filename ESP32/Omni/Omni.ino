#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

// Motor 1 (Front Right)
const int motor1_in1 = 25;  // White
const int motor1_in2 = 33;  // Gray
const int motor1_ena = 26;  // Purple

// Motor 2 (Front Left)
const int motor2_in1 = 21;  // Green
const int motor2_in2 = 19;  // Blue
const int motor2_ena = 18;  // White

// Motor 3 (Back Left)
const int motor3_in1 = 27;  // Violet
const int motor3_in2 = 14;  // Gray
const int motor3_ena = 12;  // Purple

// Motor 4 (Back Right)
const int motor4_in1 = 13;  // Blue
const int motor4_in2 = 4;   // Purple
const int motor4_ena = 2;   // White

// Speed (0-255)
int currentSpeed = 254;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("IntentionalDisaster");

  int motor_pins[] = {
    motor1_in1, motor1_in2, motor1_ena,
    motor2_in1, motor2_in2, motor2_ena,
    motor3_in1, motor3_in2, motor3_ena,
    motor4_in1, motor4_in2, motor4_ena
  };

  for (int i = 0; i < 12; i++) {
    pinMode(motor_pins[i], OUTPUT);
  }

  Serial.println("Disaster ready");
}

// Function to control a motor
void controlMotor(int in1, int in2, int ena, int speed, bool forward) {
  digitalWrite(in1, forward);
  digitalWrite(in2, !forward);
  analogWrite(ena, speed);
}

// Move forward (adjusted for reversed motor)
void moveForward(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, true);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, true);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, true);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, true);
}

// Move backward
void moveBackward(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, false);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, false);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, false);
}

// Move left
void moveLeft(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, true);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, false);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, true);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, false);
}

// Move right
void moveRight(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, false);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, true);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, true);
}

// Move Diagonal Right
void moveDiagonalRight(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, 0, false);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, true);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, 0, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, true);
}

// Move Diagonal Left
void moveDiagonalLeft(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, true);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, 0, false);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, true);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, 0, false);
}

// Move Diagonal Right Reverse
void moveDiagonalRightReverse(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, false);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, 0, false);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, 0, false);
}

// Move Diagonal Left Reverse
void moveDiagonalLeftReverse(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, 0, false);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, false);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, 0, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, false);
}

// Spin Right
void spinRight(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, false);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, true);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, true);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, false);
}

// Spin Left
void spinLeft(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, true);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, false);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, true);
}

// Turn Right
void turnRight(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, 0, false);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, true);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, speed, true);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, 0, false);
}

// Turn Left
void turnLeft(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, true);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, 0, false);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, 0, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, speed, true);
}

// Rotate Right
void rotateRight(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, false);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, true);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, 0, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, 0, false);
}

// Rotate Left
void rotateLeft(int speed) {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, speed, true);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, speed, false);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, 0, false);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, 0, false);
}




// Stop all motors
void stopMotors() {
  controlMotor(motor1_in1, motor1_in2, motor1_ena, 0, true);
  controlMotor(motor2_in1, motor2_in2, motor2_ena, 0, true);
  controlMotor(motor3_in1, motor3_in2, motor3_ena, 0, true);
  controlMotor(motor4_in1, motor4_in2, motor4_ena, 0, true);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    String action = SerialBT.readStringUntil('~');

    if (action.equals("minus")) {
      if (currentSpeed - 10 >= 80) currentSpeed -= 10;
      SerialBT.print("SUGON SUCKER THE SPEED CHANGED TO ");
      SerialBT.println(currentSpeed);
    } else if (action.equals("plus") || action.equals("equal")) {
      if (currentSpeed + 10 >= 255) currentSpeed += 10;
      SerialBT.print("SUGON SUCKER THE SPEED CHANGED TO ");
      SerialBT.println(currentSpeed);
    }

    // Default
    if (action.equals("w")) moveForward(currentSpeed);
    else if (action.equals("a")) moveLeft(currentSpeed);
    else if (action.equals("s")) moveBackward(currentSpeed);
    else if (action.equals("d")) moveRight(currentSpeed);

    // Diagonal
    else if (action.equals("aw")) moveDiagonalLeft(currentSpeed);
    else if (action.equals("dw")) moveDiagonalRight(currentSpeed);
    else if (action.equals("as")) moveDiagonalLeftReverse(currentSpeed);
    else if (action.equals("ds")) moveDiagonalRightReverse(currentSpeed);

    // Spain without the a
    else if (action.equals("e")) spinRight(currentSpeed);
    else if (action.equals("q")) spinLeft(currentSpeed);

    // Turn (soft)
    else if (action.equals("ew")) turnRight(currentSpeed);
    else if (action.equals("qw")) turnLeft(currentSpeed);

    // Rotate (hard)
    else if (action.equals("de")) rotateRight(currentSpeed);
    else if (action.equals("aq")) rotateLeft(currentSpeed);

    // Else
    else if (action.equals("0")) {
      stopMotors();
      SerialBT.println("Yes boss I have stopped the motors");
    } else {
      stopMotors();
      SerialBT.println("Hmmmm, oh dear, oh no no no, or fiddlesticks, it seems like we are not getting any input now");
    }
  }
  delay(20);
}
