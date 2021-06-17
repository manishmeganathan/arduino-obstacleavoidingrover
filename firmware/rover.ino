// Define Dependancies
#include <Servo.h>
#include <NewPing.h>

//Define L298N Motor Pins
#define LeftMotorForward = 6;
#define LeftMotorBackward = 7;
#define RightMotorForward = 5;
#define RightMotorBackward = 4;

// Define Ultrasonic Sensor Pins
#define trig_pin A1
#define echo_pin A2 

// Define Max Distance
#define maximum_distance 200

// Construct a Servo Object
Servo servo_motor; 

// Construct an Ultrasonic Sensor Object
NewPing Sonar(trig_pin, echo_pin, maximum_distance); 

bool goesForward = false;

// Declare a global variable to 
// hold the obstacle distance
int distance = 100;


// Arduino Initialization Runtime
void setup() {
    // Set Motor Pins to Output
    pinMode(RightMotorForward, OUTPUT);
    pinMode(LeftMotorForward, OUTPUT);
    pinMode(LeftMotorBackward, OUTPUT);
    pinMode(RightMotorBackward, OUTPUT);

    // Attach the Servo to Pin 9
    servo_motor.attach(9);
    // Set the initial angle of the Servo
    servo_motor.write(115);
    delay(2000);

    // Find the distance of the nearest obstacle    
    distance = read_distance();
    delay(100);
}

// Arduino Loop Runtime
void loop() {
    // Declare the distance to the left and right as zero
    int distanceRight = 0;
    int distanceLeft = 0;
    delay(50);

    // Find the distance to the nearest obstacle
    distance = read_distance();

    // Check if the distance is less than 20cm
    if (distance <= 20){
        // Stop Moving
        moveStop();
        delay(300);

        // Move Backwards
        moveBackward();
        delay(400);

        // Stop Moving
        moveStop();
        delay(300);

        // Check distance to obstacles on the right
        distanceRight = lookRight();
        delay(300);

        // Check distance to obstacles on the left
        distanceLeft = lookLeft();
        delay(300);

        // Check if distance of obstacle to left is less than 20cm
        if (distanceLeft > 20) {
            // Turn Right
            turnRight();
            moveStop();

        } else if (distanceRight > 20) {
            // Turn Left
            turnLeft();
            moveStop();
        } else {
            // Move Backward
            moveBackward();
            delay(400);
            moveStop();
        }

    } else {
        // Move Forward
        moveForward(); 
    }
}

// A function to turn the Servo to the
// right and measure distance to obstacle
int lookRight(){ 
    // Turn the Servo to the Right
    servo_motor.write(50);
    delay(500);

    // Read the distance
    int distance = read_distance();
    delay(100);

    // Turn the Servo to the Centre
    servo_motor.write(115);
    delay(100);

    // Return the distance
    return distance;
}

// A function to turn the Servo to the
// left and measure distance to obstacle
int lookLeft(){
    // Turn the Servo to the Left
    servo_motor.write(170);
    delay(500);

    // Read the distance
    int distance = read_distance();
    delay(100);

    // Turn the Sevo to the Centre
    servo_motor.write(115);
    delay(100);

    // Return the distance
    return distance;
}

// A function that reads the distance of the 
// nearest obstacle in cms and returns it
int read_distance(){
    // Read the distance in cms
    int cm = Sonar.ping_cm();

    // Check if value is 0 (no detected obstacle)
    if (cm==0){
        // Assume distance is 250 cms
        cm=250;
    }

    // Return the distance
    return cm;
}

// A function that stops the rover movement
void moveStop(){
    // Stop all Motors
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

    if(!goesForward){

        goesForward=true;

        digitalWrite(LeftMotorForward, HIGH);
        digitalWrite(RightMotorForward, HIGH);

        digitalWrite(LeftMotorBackward, LOW);
        digitalWrite(RightMotorBackward, LOW); 
    }
}

void moveBackward(){

    goesForward=false;

    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorBackward, HIGH);

    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorForward, LOW);

}

void turnRight(){

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorBackward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorForward, LOW);

    delay(500);

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
}

void turnLeft(){
    digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);

    delay(500);

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
}