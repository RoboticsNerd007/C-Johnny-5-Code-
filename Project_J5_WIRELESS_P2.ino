#include <Wire.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>


unsigned long irCode;

//Startup Button
#define START_UP_CODE 0xFFA25D //IR code for power button

//Buttons to drive
#define FORWARD_BUTTON_CODE  0xFFC23D// IR code for fast forward button
#define BACKWARD_BUTTON_CODE 0xFF22DD // IR code for fast back
#define STOP_BUTTON_CODE  0xFFB04F //IR code for stop button

//Buttons for Head movement
#define TURN_HEAD_LEFT_CODE 0xFFA857 //IR code for up button button
#define TURN_HEAD_RIGHT_CODE 0xFF629D //IR code for down button
#define LOOK_FORWARD_CODE 0xFF02FD // IR code for pause button

//Buttons for Left Arm
#define ARM_MOTOR_UP1  0xFF7A85 //IR code for 3
#define ARM_MOTOR_DOWN1  0xFF30CF //IR code for 1
#define ARM_MOTOR_LEFT1 0xFF9867 //IR code or EQ
#define ARM_MOTOR_RIGHT1 0xFF18E7 //IR code for 2
#define ARM_MOTOR_RESET1 0xFF5AA5 //IR code for 6

//Buttons for Right Arm
#define ARM_MOTOR_UP2 0xFF52AD //IR code for 9
#define ARM_MOTOR_DOWN2 0xFF42BD //IR code for 7
#define ARM_MOTOR_LEFT2 0xFF38C7 //IR code for 5
#define ARM_MOTOR_RIGHT2 0xFF4AB5 //IR code for 8
#define ARM_MOTOR_RESET2 0xFF10EF //IR code for 4

//Servo Pin Connections
#define SERVO_PIN1 8 // Pin1 for motor connected to servo
#define SERVO_PIN2 9 // Pin2 for motor connected to servo
#define LEFT_MOTOR1 5 //Both motor pins for Left Arm
#define LEFT_MOTOR2 4
#define RIGHT_MOTOR1 6 //Both motor pins for Right Arm
#define RIGHT_MOTOR2 7

const int signalLight = 3;
int IRreceiver = 10;
int val;
int initialPosition = 90;   // Variable to store initial position of the motor
int currentPosition = 90;   // Variable to store current position of the motor

IRrecv irrecv(IRreceiver);
decode_results results;

Servo servoMotor1;
Servo servoMotor2;
Servo leftServoMotor1;
Servo leftServoMotor2;
Servo rightServoMotor1;
Servo rightServoMotor2;




void setup() {
 Serial.begin(9600);
  
  // Start the receiver
  irrecv.enableIRIn(); 
  
  //assign all pins to given motors
  servoMotor1.attach(SERVO_PIN1);
  servoMotor2.attach(SERVO_PIN2);
  leftServoMotor1.attach(LEFT_MOTOR1);
  leftServoMotor2.attach(LEFT_MOTOR2);
  rightServoMotor1.attach(RIGHT_MOTOR1);
  rightServoMotor2.attach(RIGHT_MOTOR2);

//assign the output of signal light
  pinMode(signalLight, OUTPUT);

  digitalWrite(signalLight, HIGH);

  
}

void loop() {
 if (irrecv.decode(&results)) {

    Serial.println(irCode, HEX);
   
  irCode = results.value;


   driveFunction();
      headRotationFunction();
       leftArmMovement();
         rightArmMovement();
           resetMotorPosition1();
            resetMotorPosition2();
   
   irrecv.resume(); // Receive the next 
   }

 

}





void driveFunction(){
  if (irCode == FORWARD_BUTTON_CODE) {
      // Drive servo forward
      servoMotor1.writeMicroseconds(1000);

      delay(1000);

    } 
    if (irCode == BACKWARD_BUTTON_CODE) {
      //Drive servo backward
      servoMotor1.writeMicroseconds(3000);

      delay(1000);
    }
    
    if (irCode == STOP_BUTTON_CODE){
      //Stop servo motor
      servoMotor1.writeMicroseconds(1500);
    }
}

void headRotationFunction(){
  if(irCode == LOOK_FORWARD_CODE){
    servoMotor2.write(90);

    delay(1000);
  }
  if(irCode == TURN_HEAD_LEFT_CODE){
    servoMotor2.writeMicroseconds(1000);
    
    delay(1000);
  }
  if(irCode == TURN_HEAD_RIGHT_CODE){
    servoMotor2.writeMicroseconds(3000);
  }
}

void leftArmMovement(){
  if(irCode == ARM_MOTOR_UP1){
    leftServoMotor1.writeMicroseconds(1000);
  }
  if(irCode == ARM_MOTOR_DOWN1){
    leftServoMotor1.write(3000);
  }
  if(irCode == ARM_MOTOR_LEFT1){
    leftServoMotor2.writeMicroseconds(1000);
  }
  if(irCode == ARM_MOTOR_RIGHT1){
    leftServoMotor2.writeMicroseconds(3000);
  }
}

void rightArmMovement(){
  if(irCode == ARM_MOTOR_UP2){
    rightServoMotor1.writeMicroseconds(3000);
  }
  if(irCode == ARM_MOTOR_DOWN2){
    rightServoMotor1.write(1000);
  }
  if(irCode == ARM_MOTOR_LEFT2){
    rightServoMotor2.writeMicroseconds(1000);
  }
  if(irCode == ARM_MOTOR_RIGHT2){
    rightServoMotor2.writeMicroseconds(3000);
  }
}

void resetMotorPosition1(){
  if(irCode == ARM_MOTOR_RESET1){
    leftServoMotor2.write(initialPosition);

    currentPosition = initialPosition;
  }
}

void resetMotorPosition2(){
  if(irCode == ARM_MOTOR_RESET2){
    rightServoMotor2.write(initialPosition);

    currentPosition = initialPosition;
  }
}