 /**
 * Test Rig
 * 
 * 
 * 
 */
#include <Arduino.h> // Core Arduino Library
#include <PID_v1.h> // PID Library 
// #include <PID_AutoTune_v0> // PID Autotuner Library

#define IN1 6 // pin for LOW (Logic 1/IN1 on L298N Motor Controller)
#define IN2 7 // pin for HIGH (Logic 2/IN2 on L298N)

#define PWM 3 // pin for PWM (to vary the motor rpm)
#define HALL 2 // pin for Hall Effect Sensor data (interrupt pin 0 but pin 2 of arduino)

// PID Variables
double Input; // actual RPM - we get this from converting HES data ()
double Output; // the PWM that Arduino will adjust ()
double Setpoint; // the RPM we want (fixed by user)
PID myPID(&Input, &Output, &Setpoint, 0.1, 1, 1, DIRECT);

// Variables to calculate RPM from HES data
#define SIZE 2 // define size of array
unsigned long ms_array[SIZE]; // stores an array of microseconds (each "slot" is 1 rev)
volatile unsigned int index;
unsigned long mean;
unsigned long ms_start;

// Printing
unsigned long ms_print = 0;

// Function to check RPM
void checkRotation() 
{
	mean = ((mean * (double) SIZE) - ms_array[index]) / SIZE; // prepare average calculation for later
	ms_array[index] = (millis() - ms_start); // record ms passed to array
	mean = ((mean * (double) SIZE) + ms_array[index]) / SIZE; // get new average
	
	// get RPM based on average microseconds
	Input = 1.0 / ((mean / (60.0 * 1000)) / SIZE); // revolutions per minute, "fairly" accurate
}

// Function to update time(s) array everytime 1 rotation has happened
void interrupt() { // one rotation has happened
    Serial.println();
//    Serial.println("Interrupted!");
    Serial.println();
    ms_start = millis();
    if(index == SIZE - 1) {
        index = 0;
    } else {
        index++;
    }
}

void setup() 
{
	Serial.begin(9600);
	// Makes the PWM, IN1, and IN2 pins output
	pinMode(PWM, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	// Next 2 digital writes will configure clockwise/anti-clockwise of motor
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, HIGH); 

	// Initialize Hall Effect Sensor (HES) stuff
    pinMode(HALL, INPUT_PULLUP);
    attachInterrupt(0, interrupt, RISING);
	mean = 0; 
	index = 0; // start recording at index 0
	ms_start = micros();
   
	// Initialize PID stuff
	Input = 0;
	Serial.println("What RPM do you want?"); // Prompts user for desired RPM
   	while(!Serial.available()); // Waits for user input
	Setpoint = Serial.parseFloat();
	Serial.print("Your Input: "); // Echoes back user input for debugging
   	Serial.println(Setpoint);
	Serial.println();
	myPID.SetOutputLimits(0, 255); // PID will not go below 0 or above 255 (PWM limit)
	myPID.SetMode(AUTOMATIC); // Sets PID Controller to automatic calculations
}

void loop() {
	checkRotation();
	myPID.Compute();
	digitalWrite(PWM, Output);
	// Print stats every second
    if((millis() - ms_print) > 1000) {
        Serial.print("Actual: ");
        Serial.println(Input);
        Serial.print("Desired: ");
        Serial.println(Setpoint);
        Serial.print("Adjusted PWM: ");
        Serial.println(Output);
        Serial.print("Array:");
        for(long ms : ms_array) {
            Serial.print(" ");
            Serial.print(ms);
        }
        Serial.println();
        Serial.print("Average: ");
        Serial.println(mean);
        Serial.println();
        ms_print = millis();
    }
}