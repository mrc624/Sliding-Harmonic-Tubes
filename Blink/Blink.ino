/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#include <Arduino.h>
#include <math.h>
#include <MIDI.h>
#include <LittleFS.h>

#include "FS.h"
#include "USB.h"
#include "USBMIDI.h"

#define MINIMUM_BPM 60
#define MAX_BPM 120
#define INVALID_BPM 0

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long interval = 0;

static bool ledState = false;

bool SongLoaded = false;
uint bpm = 0;
String note_data = "";

uint BPMtoInterval(uint data)
{
  return (60 * 1000) / data;
}

void GatherMusicInfo()
{
  bpm = INVALID_BPM;
  while ((bpm < MINIMUM_BPM) || (bpm > MAX_BPM)) {

    Serial.println("Enter a BPM: ");

    while (!Serial.available()) {
      delay(10);
    }

    String input = Serial.readStringUntil('\n');
    int input_bpm = input.toInt();

    if (input_bpm < MINIMUM_BPM) {
      Serial.print("Invalid BPM, Minimum BPM is: ");
      Serial.println(MINIMUM_BPM);
    } else if (input_bpm > MAX_BPM) {
      Serial.print("Invalid BPM, Maximum BPM is: ");
      Serial.println(MAX_BPM);
    } else {
      bpm = input_bpm;
      interval = BPMtoInterval(bpm);
      Serial.print("BPM set to: ");
      Serial.println(bpm);
    }
  }

  Serial.println("Enter a note followed by a length");
  Serial.println("Full: 1, Half: 2, Quarter: 4)");

  note_data = "C 1";

  SongLoaded = true;
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }
  Serial.println("Serial Initialized");
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("LED Initialized");
}

// the loop function runs over and over again forever
void loop() {

  if (Serial.available())
  {
    if(Serial.readStringUntil('\n') == "reset")
    {
      SongLoaded = false;
    }
  }

  if (!SongLoaded)
  {
    GatherMusicInfo();
    Serial.println(note_data);
  }

  currentMillis = millis();

  if ( ((currentMillis - previousMillis) >= (interval / 2)) && SongLoaded)
  {
    previousMillis = currentMillis;

    // Toggle the LED state
    ledState = !ledState;
    
    // Turn the LED on or off based on ledState
    if (ledState) {
      digitalWrite(LED_BUILTIN, HIGH);  // LED ON
      Serial.println("BEAT");
    } else {
      digitalWrite(LED_BUILTIN, LOW);   // LED OFF
    }
  }

}
