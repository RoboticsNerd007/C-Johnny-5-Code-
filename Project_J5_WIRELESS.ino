//This is the Project J-5 Prototype code. FINAL REVISION!!

//WIRELESS CONTROLLED!!


#include <IRremote.h>
#include <Servo.h>

//Startup Button
#define START_UP_CODE 0xFFA25D //IR code for power button

//Buttons to drive
#define FORWARD_BUTTON_CODE  0xFFC23D// IR code for fast forward button
#define BACKWARD_BUTTON_CODE 0xFF22DD // IR code for fast back
#define STOP_BUTTON_CODE  0xFFB04F //IR code for stop button

//Buttons for Head movement
#define TURN_HEAD_LEFT_CODE 0xFF629D //IR code for down button button
#define TURN_HEAD_RIGHT_CODE 0xFFA857 //IR code for up button
#define LOOK_FORWARD_CODE 0xFF02FD // IR code for pause button


//Buttons for Left Arm
#define ARM_MOTOR_UP1  0xFF7A85 //IR code for 3
#define ARM_MOTOR_DOWN1  0xFF30CF //IR code for 1
#define ARM_MOTOR_LEFT1 0xFF9867 //IR code or EQ
#define ARM_MOTOR_RIGHT1 0xFF18E7 //IR code for 2

//Buttons for Right Arm
#define ARM_MOTOR_UP2 0xFF52AD //IR code for 9
#define ARM_MOTOR_DOWN2 0xFF42BD //IR code for 7
#define ARM_MOTOR_LEFT2 0xFF38C7 //IR code for 5
#define ARM_MOTOR_RIGHT2 0xFF4AB5 //IR code for 8


#define SERVO_PIN1 8 // Pin1 for motor connected to servo
#define SERVO_PIN2 9 // Pin2 for motor connected to servo
#define LEFT_MOTOR1 5 //Both motor pins for Left Arm
#define LEFT_MOTOR2 4
#define RIGHT_MOTOR1 6 //Both motor pins for Right Arm
#define RIGHT_MOTOR2 7

int IRreceiver = 10;
int val;

const int signalLight = 3;

IRrecv irrecv(IRreceiver);
decode_results results;

Servo servoMotor1;
Servo servoMotor2;
Servo leftServoMotor1;
Servo leftServoMotor2;
Servo rightServoMotor1;
Servo rightServoMotor2;

bool r1Rotation, r2Rotation, r3Rotation;

unsigned long irCode;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  servoMotor1.attach(SERVO_PIN1);
  servoMotor2.attach(SERVO_PIN2);
 
  pinMode(signalLight, OUTPUT);

  servoMotor2.write(0);
}

void loop() {

  if (irrecv.decode(&results)) {

    Serial.println(irCode, HEX);
   
  irCode = results.value;

    driveFunction();
      headRotationFunction();
       
   
   irrecv.resume(); // Receive the next value
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
      r1Rotation = !r1Rotation; //Rotate in this Fashion if pressed
      r2Rotation = false;
      r3Rotation = false;
    }
    if(irCode == TURN_HEAD_LEFT_CODE){                                            //This section determins the position.
      r2Rotation = !r2Rotation; //Rotate in this Fashion if pressed
      r1Rotation = false;
      r3Rotation = false;
    }
    if(irCode == TURN_HEAD_RIGHT_CODE){
      r3Rotation = !r3Rotation; //Rotate in this Fashion if pressed
      r2Rotation = false;
      r1Rotation = false;
     }
if(r1Rotation && (val != 0)){
  val--;
}                                               //This section runs the rotation of the head position.
 if(r2Rotation && (val != 90)){
  val++;
 }

 if(r3Rotation && (val != 180)){
  val--;
 }

 servoMotor2.write(val);
}


