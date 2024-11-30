#include <math.h>

#define SPEAKER_PIN 13 // Built-in LED on most Arduino boards

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

#define SPEAKER_OFF 0
#define SPEAKER_ON 128
#define DEFAULT_FREQUENCY 0
#define SEMITONES_IN_OCTAVE 12

String data = "";

Receiving_Data Current_Data = NOTE;
int curr_velocity;
MidiNote curr_note;

int get_note_frequency(MidiNote note)
{
  double exp = ( (double)(note) - (double)(A_4) ) / (double)(SEMITONES_IN_OCTAVE);
  int freq = (int)((double)(440) * pow(2, exp));
  return freq;
}

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    // Wait for Serial connection
    delay(10);  
  }
  Serial.println("Serial Initialized");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  analogWriteFrequency(SPEAKER_PIN, DEFAULT_FREQUENCY);
  analogWrite(SPEAKER_PIN, SPEAKER_OFF);
  Serial.println("GPIO Initialized");

  Serial.println("System Ready");
}

void loop()
{
  // Check if data is available in the serial buffer
  if (Serial.available())
  {

    char data_char = Serial.read();

    if (data_char == 'A')
    {
      Serial.println(data);
    }
    else
    {
      if (Current_Data == NOTE)
      {
        curr_note = (MidiNote)(data_char);
        data += "NOTE: " + MidiNoteNames[curr_note] + " ";
        int freq = get_note_frequency((MidiNote)(curr_note));
        analogWriteFrequency(SPEAKER_PIN, freq);
        Current_Data = VELOCITY;
      }
      else if (Current_Data == VELOCITY)
      {
        curr_velocity = (int)(data_char);
        data += "VELOCITY: " + (String)(curr_velocity) + "\n";
        Current_Data = NOTE;

        if (curr_velocity > 0)
        {
          digitalWrite(LED_BUILTIN, HIGH);
          analogWrite(SPEAKER_PIN, SPEAKER_ON);
        }
        else
        {
          digitalWrite(LED_BUILTIN, LOW);
          analogWrite(SPEAKER_PIN, SPEAKER_OFF);
        }
      }
    }
  }
}