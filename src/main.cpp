 /**
 * VPP Code
 * 
 * 
 * 
 */
#include "Arduino.h"
#include <SparkFun_TB6612.h>
#include <Encoder.h>

// Pins based off of https://easyeda.com/editor#id=815d6710d64740d7be23ae165a4ac48c|9e069235e92947119db9ace52b95412e
#define HALLEFFECT 2

// Motor stuff
#define STBY 8
#define AIN1 9
#define AIN2 10
#define PWMA 11
// Allow you to make your motor configuration line up with function names like forward (to make it actually go forward rather than backward).  Value can be 1 or -1
const int offsetA = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY); // Initialize motor

// Encoder Stuff
// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
#define CA 3
#define CB 4
#define INDEX 5
Encoder enc(CA, CB);

// States
double RPM;
// We need a map of RPM to angle (or use a function to model it)

// Variables to calculate RPM from HES data
#define SIZE 2 // define size of array
unsigned long ms_array[SIZE]; // stores an array of microseconds (each "slot" is 1 rev)
volatile unsigned int index;
unsigned long mean;
unsigned long ms_start;


void setup() {
    // Zero the motor to "home" (the angle that the motor SHOULD be at such that the propellor angle is 0 degrees)
    // Use index pin for this
}

void loop() {
    // Receive data from hall effect sensor to know current RPM (this is saved in a state)

    // Everytime we interrupt, we want to check the RPM to see if it has changed significantly
    
    // If RPM has changed enough that it warrants an angle change, then proceed to spin the motor until desired angle (based on encoder)

    // Have some code to deal with motor jamming (some time limiter)
}