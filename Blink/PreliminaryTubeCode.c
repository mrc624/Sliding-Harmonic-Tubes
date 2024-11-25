#include <TMCStepper.h>  // TMCstepper library

#define DIR_PIN          18  // Direction - WHITE
#define STEP_PIN         19  // Step - ORANGE
#define SW_TX            17  // Hardware Serial TX pin
#define SW_RX            16  // Hardware Serial RX pin

#define R_SENSE 0.11f         // Sense resistor value
#define DRIVER_ADDRESS 0b00   // Driver address for MS1/MS2 configuration

HardwareSerial TMCSerial(1);  // Use Serial1 for UART communication
TMC2209Stepper TMCdriver(&TMCSerial, R_SENSE, DRIVER_ADDRESS);

bool dir = true;               // Current motor direction
const int stepsPerCycle = 10000; // Number of steps to move in one direction
const int stepDelay = 75;      // Adjusted delay in microseconds for smoother motion

void setup() {
  Serial.begin(115200);               // Initialize serial for debugging
  TMCSerial.begin(115200, SERIAL_8N1, SW_RX, SW_TX);  // Start UART for TMC2209
  TMCdriver.begin();                  // Initialize TMC2209 driver

  // Configure pins
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  // TMC2209 settings
  TMCdriver.toff(5);                  // Enable driver in software
  TMCdriver.rms_current(900);         // Increase RMS current for more torque (adjust as needed)
  TMCdriver.microsteps(16);           // Set microsteps (16 is a good starting point)
  TMCdriver.en_spreadCycle(false);    // Enable StealthChop mode
  TMCdriver.pwm_autoscale(true);      // Enable automatic PWM scaling

  // Set initial direction
  digitalWrite(DIR_PIN, dir);
  TMCdriver.shaft(dir);
}

void loop() {
  // Move stepsPerCycle steps in the current direction
  for (int i = 0; i < stepsPerCycle; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(stepDelay);
  }

  // Change direction
  dir = !dir;                         // Toggle direction
  digitalWrite(DIR_PIN, dir);         // Update direction pin
  TMCdriver.shaft(dir);               // Update driver direction
  Serial.print("Direction: ");
  Serial.println(dir ? "HIGH" : "LOW");  // Debug: print direction to serial monitor

  delay(1000);                        // Delay to allow motor to settle before reversing
}
