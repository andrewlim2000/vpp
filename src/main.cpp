 /**
 * VPP Code
 * 
 * 
 * 
 */
#include "Arduino.h"

// Hall Effect Pins
#define HALLEFFECT_PIN 2

// Motor Pins
#define MOTOR_PWM_PIN 5
#define IN1 6
#define IN2 7

// States
double RPM;
// We need a map of RPM to angle (or use a function to model it)

// Variables to calculate RPM from HES data
#define SIZE 2 // define size of array
unsigned long ms_array[SIZE]; // stores an array of microseconds (each "slot" is 1 rev)
volatile unsigned int index;
unsigned long mean;
unsigned long ms_start;

void interrupt() { // one rotation has happened
    // Serial.println();
    // Serial.println("Interrupted!");
    // Serial.println();
    ms_start = millis();
    if(index == SIZE - 1) {
        index = 0;
    } else {
        index++;
    }
}

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