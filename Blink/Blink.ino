#include <math.h>

#include <TMCStepper.h>  // TMCstepper library

// CONFIGS
//#define SERIAL_MONITOR 1
#define LED_WHEN_STEP 1
//#define SPEAKER 1
//#define MANUAL_INPUT 1
// PIPE CONFIGS
#define CONFIG_PIPE1 1
//#define CONFIG_PIPE2 1 
//#define CONFIG_PIPE3 1
//#define CONFIG_PIPE_BASS 1

#define OUT_OF_RANGE_NOTE _C_2

#define MAX_STEP 14000
#define MIN_STEP 0

#ifdef CONFIG_PIPE1 // Pipe 1 Config

  #define MIN_NOTE 0 // NOT SET YET
  #define MAX_NOTE 120 // NOT SET YET

#elif CONFIG_PIPE_2 // Pipe 2 Config
  
#elif CONFIG_PIPE_3 // Pipe 3 Config

#elif CONFIG_PIPE_BASS // Bass Pipe Config

#endif

// Pin defines
#define DIR_PIN          18  // Direction
#define STEP_PIN         19  // Step
#define HOME_PIN         21  // Pin connected to homing DIP switch
#define SOLENOID_PIN     5   // Solenoid
#define SPEAKER_PIN      4   // Speaker
#define SW_TX            17  // Hardware Serial TX pin
#define SW_RX            16  // Hardware Serial RX pin

// TMC defines
#define R_SENSE 0.11f         // Sense resistor value
#define DRIVER_ADDRESS 0b00   // Driver address for MS1/MS2 configuration

#ifdef SPEAKER
  #define SPEAKER_OFF 0
  #define SPEAKER_ON 128
  #define DEFAULT_FREQUENCY 0
  #define SEMITONES_IN_OCTAVE 12
#endif

#define DIR_DOWN true
#define DIR_UP false

// Ramp
#define STEP_DELAY_RAMP_START 500
#define STEP_DELAY_RAMP 10
#define STEP_DELAY 100
#define STEPS_TO_DECELERATE ( (STEP_DELAY_RAMP_START - STEP_DELAY) / STEP_DELAY_RAMP )

#define STEP_DELAY_HOME 500
#define STEPS_MOVE_WHEN_HOME 1000
#define STEP_OFFSET 100 // The amount of steps above the homing
#define HOMED LOW // GPIO reads low when homed
#define NOT_HOMED HIGH // GPIO reads high when note homed
#define DEBOUNCE_THRESHOLD 10

#define SOLENOID_TRIGGER C_0
#define HOME_TRIGGER C_s_0

enum Receiving_Data
{
  NOTHING_EXPECTED,
  NOTE,
  VELOCITY,
  NUM_RECEIVING_DATA
};

enum MidiNote {
    _C_2 = 0,
    _C_s_2 = 1,
    _D_b_2 = 1,
    _D_2 = 2,
    _D_s_2 = 3,
    _E_b_2 = 3,
    _E_2 = 4,
    _F_2 = 5,
    _F_s_2 = 6,
    _G_b_2 = 6,
    _G_2 = 7,
    _G_s_2 = 8,
    _A_b_2 = 8,
    _A_2 = 9,
    _A_s_2 = 10,
    _B_b_2 = 10,
    _B_2 = 11,
    _C_1 = 12,
    _C_s_1 = 13,
    _D_b_1 = 13,
    _D_1 = 14,
    _D_s_1 = 15,
    _E_b_1 = 15,
    _E_1 = 16,
    _F_1 = 17,
    _F_s_1 = 18,
    _G_b_1 = 18,
    _G_1 = 19,
    _G_s_1 = 20,
    _A_b_1 = 20,
    _A_1 = 21,
    _A_s_1 = 22,
    _B_b_1 = 22,
    _B_1 = 23,
    C_0 = 24,
    C_s_0 = 25,
    D_b_0 = 25,
    D_0 = 26,
    D_s_0 = 27,
    E_b_0 = 27,
    E_0 = 28,
    F_0 = 29,
    F_s_0 = 30,
    G_b_0 = 30,
    G_0 = 31,
    G_s_0 = 32,
    A_b_0 = 32,
    A_0 = 33,
    A_s_0 = 34,
    B_b_0 = 34,
    B_0 = 35,
    C_1 = 36,
    C_s_1 = 37,
    D_b_1 = 37,
    D_1 = 38,
    D_s_1 = 39,
    E_b_1 = 39,
    E_1 = 40,
    F_1 = 41,
    F_s_1 = 42,
    G_b_1 = 42,
    G_1 = 43,
    G_s_1 = 44,
    A_b_1 = 44,
    A_1 = 45,
    A_s_1 = 46,
    B_b_1 = 46,
    B_1 = 47,
    C_2 = 48,
    C_s_2 = 49,
    D_b_2 = 49,
    D_2 = 50,
    D_s_2 = 51,
    E_b_2 = 51,
    E_2 = 52,
    F_2 = 53,
    F_s_2 = 54,
    G_b_2 = 54,
    G_2 = 55,
    G_s_2 = 56,
    A_b_2 = 56,
    A_2 = 57,
    A_s_2 = 58,
    B_b_2 = 58,
    B_2 = 59,
    C_3 = 60,
    C_s_3 = 61,
    D_b_3 = 61,
    D_3 = 62,
    D_s_3 = 63,
    E_b_3 = 63,
    E_3 = 64,
    F_3 = 65,
    F_s_3 = 66,
    G_b_3 = 66,
    G_3 = 67,
    G_s_3 = 68,
    A_b_3 = 68,
    A_3 = 69,
    A_s_3 = 70,
    B_b_3 = 70,
    B_3 = 71,
    C_4 = 72,
    C_s_4 = 73,
    D_b_4 = 73,
    D_4 = 74,
    D_s_4 = 75,
    E_b_4 = 75,
    E_4 = 76,
    F_4 = 77,
    F_s_4 = 78,
    G_b_4 = 78,
    G_4 = 79,
    G_s_4 = 80,
    A_b_4 = 80,
    A_4 = 81,
    A_s_4 = 82,
    B_b_4 = 82,
    B_4 = 83,
    C_5 = 84,
    C_s_5 = 85,
    D_b_5 = 85,
    D_5 = 86,
    D_s_5 = 87,
    E_b_5 = 87,
    E_5 = 88,
    F_5 = 89,
    F_s_5 = 90,
    G_b_5 = 90,
    G_5 = 91,
    G_s_5 = 92,
    A_b_5 = 92,
    A_5 = 93,
    A_s_5 = 94,
    B_b_5 = 94,
    B_5 = 95,
    C_6 = 96,
    C_s_6 = 97,
    D_b_6 = 97,
    D_6 = 98,
    D_s_6 = 99,
    E_b_6 = 99,
    E_6 = 100,
    F_6 = 101,
    F_s_6 = 102,
    G_b_6 = 102,
    G_6 = 103,
    G_s_6 = 104,
    A_b_6 = 104,
    A_6 = 105,
    A_s_6 = 106,
    B_b_6 = 106,
    B_6 = 107,
    C_7 = 108,
    C_s_7 = 109,
    D_b_7 = 109,
    D_7 = 110,
    D_s_7 = 111,
    E_b_7 = 111,
    E_7 = 112,
    F_7 = 113,
    F_s_7 = 114,
    G_b_7 = 114,
    G_7 = 115,
    G_s_7 = 116,
    A_b_7 = 116,
    A_7 = 117,
    A_s_7 = 118,
    B_b_7 = 118,
    B_7 = 119,
    C_8 = 120,
    C_s_8 = 121,
    D_b_8 = 121,
    D_8 = 122,
    D_s_8 = 123,
    E_b_8 = 123,
    E_8 = 124,
    F_8 = 125,
    F_s_8 = 126,
    G_b_8 = 126,
    G_8 = 127
};

String MidiNoteNames[] = {
  "C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2",
  "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1",
  "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0",
  "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
  "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
  "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
  "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
  "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
  "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
  "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7",
  "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8"
};

bool homed = false;

//Receiving Midi
String data = "";
Receiving_Data Current_Data = NOTE;
int curr_velocity;
#ifdef MANUAL_INPUT
MidiNote curr_note = A_4;
#else
MidiNote curr_note;
#endif

//Stepper
bool dir = false;
int step = 0;
int step_go_to = 0;
HardwareSerial TMCSerial(1);  // Use Serial1 for UART communication
TMC2209Stepper TMCdriver(&TMCSerial, R_SENSE, DRIVER_ADDRESS);

// Functions to get note step values
int get_step_from_note(MidiNote note)
{
  if (note > MAX_NOTE || note < MIN_NOTE)
  {
    return OUT_OF_RANGE_NOTE;
  }
  int note_step = OUT_OF_RANGE_NOTE;
  switch(note)
  {
    
  }
  return note_step;
}

#ifdef SPEAKER
int get_note_frequency(MidiNote note)
{
  double exp = ( (double)(note) - (double)(A_4) ) / (double)(SEMITONES_IN_OCTAVE);
  int freq = (int)((double)(440) * pow(2, exp));
  return freq;
}
#endif

void Handle_Serial_Input()
{
  if (Serial.available()) // Check if data is available in the serial buffer
  {
    
    char data_char = Serial.read(); // Gets the first char in the buffer

    if (Current_Data == NOTE) // If we're currently getting the note value
    {

      curr_note = (MidiNote)(data_char); // Convert char to midi value

      step_go_to = (int)(curr_note) * 100; // Update the step go to
#ifdef SERIAL_MONITOR
      Serial.print("STEP GO TO: ");
      Serial.println(step_go_to);
#endif

#ifdef SPEAKER
      int freq = get_note_frequency((MidiNote)(curr_note));
      analogWriteFrequency(SPEAKER_PIN, freq);
#endif

      Current_Data = VELOCITY; // We are now collecting the velocity data
    }
    else if (Current_Data == VELOCITY) // If we are collecting the velocity data
    {

      curr_velocity = (int)(data_char); // Convert the data_char to a velocity value
#ifdef SPEAKER
      if (curr_velocity > 0)
      {
        analogWrite(SPEAKER_PIN, SPEAKER_ON);
      }
      else
      {
        analogWrite(SPEAKER_PIN, SPEAKER_OFF);
      } 
#endif
      Current_Data = NOTE; // Collecting note data next
    }
  }
}

/*
  Should read HIGH when not homed, and LOW when homed
*/
void Home_Stepper()
{

  uint debounce = 0;

  // Begin homing sequence
  if (digitalRead(HOME_PIN) != HOMED)
  {
#ifdef SERIAL_MONITOR
    Serial.println("HOMING: NOT HOMED");
#endif
    digitalWrite(DIR_PIN, DIR_DOWN); //always moving down, becuase we are above it
#ifdef LED_WHEN_STEP
    digitalWrite(LED_BUILTIN, HIGH);
#endif
#ifdef SERIAL_MONITOR
  Serial.println("HOMING: MOVING DOWN");
#endif
    while(debounce <= DEBOUNCE_THRESHOLD)
    {
      delayMicroseconds(STEP_DELAY_HOME);
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(STEP_DELAY_HOME);
      digitalWrite(STEP_PIN, LOW);
      if (digitalRead(HOME_PIN) == HOMED)
      {
#ifdef SERIAL_MONITOR
        Serial.println("HOMING: DEBOUNCE");
#endif
        debounce++;
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
#ifdef SERIAL_MONITOR
  Serial.println("HOMING: HOMED");
#endif
  // We are now touching the switch

  //Move it up some steps
  step = 0;
  step_go_to = STEPS_MOVE_WHEN_HOME;
#ifdef SERIAL_MONITOR
  Serial.println("HOMING: MOVING UP");
#endif
#ifdef LED_WHEN_STEP
  digitalWrite(LED_BUILTIN, HIGH);
#endif
  Handle_Stepper();
#ifdef LED_WHEN_STEP
  digitalWrite(LED_BUILTIN, LOW);
#endif

  //Make sure that the pin is not homed, or something is wrong
  if (digitalRead(HOME_PIN) == HOMED)
  {
  #ifdef SERIAL_MONITOR
    Serial.println("HOMING: FAILED");
  #endif
    homed = false;
    return;
  }

  debounce = 0; // Reset debounce

  //Bring it back down until it touches the switch
#ifdef SERIAL_MONITOR
  Serial.println("HOMING: MOVING DOWN");
#endif
  digitalWrite(DIR_PIN, DIR_DOWN); //always moving down, becuawse we are above it
#ifdef LED_WHEN_STEP
  digitalWrite(LED_BUILTIN, HIGH);
#endif
  while(debounce <= DEBOUNCE_THRESHOLD)
  {
    delayMicroseconds(STEP_DELAY_HOME);
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY_HOME);
    digitalWrite(STEP_PIN, LOW);
    if (digitalRead(HOME_PIN) == HOMED)
    {
#ifdef SERIAL_MONITOR
      Serial.println("HOMING: DEBOUNCE");
#endif
      debounce++;
    }
  }
#ifdef LED_WHEN_STEP
  digitalWrite(LED_BUILTIN, LOW);
#endif

  // We have now homed the pipe
#ifdef SERIAL_MONITOR
  Serial.println("HOMING: HOMED");
#endif
  // Now we will add some steps so it is not hitting the switch while playing
  step = 0;
  step_go_to = STEP_OFFSET;
#ifdef LED_WHEN_STEP
  digitalWrite(LED_BUILTIN, HIGH);
#endif
  Handle_Stepper();
#ifdef LED_WHEN_STEP
  digitalWrite(LED_BUILTIN, LOW);
#endif

  //Zero values
  step_go_to = 0;
  step = 0;
#ifdef SERIAL_MONITOR
  Serial.println("HOMING: OFFSET SET");
  Serial.println("HOMING: COMPLETED");
#endif
  homed = true;
  curr_note = OUT_OF_RANGE_NOTE;
}

/*
  Handles the stepper

  THIS FUNCTION ASSUMES THAT THE CURRENT NOTE IS NOT THE SOLENOID TRIGGER

  positive steps are UP
  negative steps are DOWN
  start at step 0
  dir = false is the UP direction
  dir = true is the DOWN direction
*/
void Handle_Stepper()
{
 if (step != step_go_to) // If we are not where we should be
  {
    if (step > step_go_to) // If we need to move down
    {
      dir = DIR_DOWN; // True = down
      digitalWrite(DIR_PIN, dir);         // Update direction pin
      TMCdriver.shaft(dir);               // Update driver direction
    }
    else if (step < step_go_to) // If we need to move up
    {
      dir = DIR_UP; // False = up
      digitalWrite(DIR_PIN, dir);         // Update direction pin
      TMCdriver.shaft(dir);               // Update driver direction
    }

    int step_delay = STEP_DELAY_RAMP_START; //Initialize the step delay
  #ifdef LED_WHEN_STEP
    digitalWrite(LED_BUILTIN, HIGH); // Turn on LED while moving
  #endif
    while (step != step_go_to) // While we are not where we should be
    {
      delayMicroseconds(step_delay);
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(step_delay);
      digitalWrite(STEP_PIN, LOW);

      if (abs(step - step_go_to) <= STEPS_TO_DECELERATE) // Decelerate if true
      {
        step_delay = step_delay + STEP_DELAY_RAMP;
      }
      else if (step_delay != STEP_DELAY) // Accelerate if true
      {
        step_delay = step_delay - STEP_DELAY_RAMP;
      }

      if (dir) // DOWN
      {
        step--;
      }
      else // UP
      {
        step++;
      }
    }
#ifdef LED_WHEN_STEP
    digitalWrite(LED_BUILTIN, LOW); // Done moving turn off LED
#endif
  }
}

/*
This function handles the stepper

THIS FUNCTION ASSUMES THAT THE SOLENOID TRIGGER IS THE CURRENT NOTE

If velocity > 0, turn on the pin, else turn it off

*/
void Handle_Solenoid()
{
  if (curr_velocity > 0 )
  {
    digitalWrite(SOLENOID_PIN, HIGH);
  }
  else
  {
    digitalWrite(SOLENOID_PIN, LOW);
  }
}

#ifdef MANUAL_INPUT
void Input_Step_For_Testing()
{
  if (Serial.available())
  {
    String str = Serial.readStringUntil('\n');
    if (str == "ON")
    {
      digitalWrite(SOLENOID_PIN, HIGH);
#ifdef SERIAL_MONITOR
      Serial.println("SOLENOID: ON");
#endif
    }
    else if (str == "OFF")
    {
      digitalWrite(SOLENOID_PIN, LOW);
#ifdef SERIAL_MONITOR
      Serial.println("SOLENOID: OFF");
#endif
    }
    else if (str == "HOME")
    {
      Home_Stepper();
    }
    else
    {
      step_go_to = str.toInt();
#ifdef SERIAL_MONITOR
      Serial.print("GOING TO STEP: ");
#endif
      Serial.println(step_go_to);
    }
  }
}
#endif

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    // Wait for Serial connection
    delayMicroseconds(100);  
  }
#ifdef SERIAL_MONITOR
  Serial.println("Serial Initialized");
#endif

  TMCSerial.begin(9600, SERIAL_8N1, SW_RX, SW_TX);  // Start UART for TMC2209
  TMCdriver.begin();                  // Initialize TMC2209 driver

  // Configure pins
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(SOLENOID_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
#ifdef SPEAKER
  pinMode(SPEAKER_PIN, OUTPUT);
#endif
  pinMode(HOME_PIN, INPUT);

  // TMC2209 settings
  TMCdriver.toff(5);                  // Enable driver in software
  TMCdriver.rms_current(900);         // Increase RMS current for more torque (adjust as needed)
  TMCdriver.microsteps(32);           // Set microsteps (16 is a good starting point)
  TMCdriver.en_spreadCycle(false);    // Enable StealthChop mode
  TMCdriver.pwm_autoscale(true);      // Enable automatic PWM scaling

  // Set initial direction
  digitalWrite(DIR_PIN, dir);
  TMCdriver.shaft(dir);

#ifdef SPEAKER
  analogWriteFrequency(SPEAKER_PIN, DEFAULT_FREQUENCY); //Initialized speaker frequency
  analogWrite(SPEAKER_PIN, SPEAKER_OFF);
#endif

  Home_Stepper();
}

void loop()
{
#ifdef MANUAL_INPUT
  Input_Step_For_Testing();
  Handle_Stepper();
#else
  Handle_Serial_Input();
  if (curr_note == SOLENOID_TRIGGER)
  {
    Handle_Solenoid();
  }
  else if (curr_note == HOME_TRIGGER)
  {
    Home_Stepper();
  }
  else if (curr_note != OUT_OF_RANGE_NOTE)
  {
    Handle_Stepper();
  }
#endif
  
}