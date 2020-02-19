 /**
 * Motor Unit Testing
 * 
 * TODO: Change to unit test format 
 * https://docs.platformio.org/en/latest/tutorials/core/unit_testing_blink.html#tutorial-unit-testing-blink
 * 
 */
#include "Arduino.h"
#include <SparkFun_TB6612.h>
#include <unity.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define STBY 8
#define AIN1 9
#define AIN2 10
#define PWMA 11

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguments you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
    
    motor1.drive(-255,1000);
    motor1.brake();
    
    // To make sure code is even running
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second

    //Use of the drive function which takes as arguements the speed
    //and optional duration.  A negative speed will cause it to go
    //backwards.  Speed can be from -255 to 255.  Also use of the 
    //brake function which takes no arguements.
    motor1.drive(255,1000);
    motor1.brake();
}