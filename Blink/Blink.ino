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


#define GPIO_PIN_DIR 18
#define GPIO_PIN_STEP 19 
#define GPIO_PIN_CLK 21

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // Wait for Serial connection
    delay(10);
  }

  pinMode(GPIO_PIN_DIR, OUTPUT);
  digitalWrite(GPIO_PIN_DIR, LOW);
  pinMode(GPIO_PIN_STEP, OUTPUT);
  digitalWrite(GPIO_PIN_STEP, LOW);
  pinMode(GPIO_PIN_CLK, OUTPUT);
  digitalWrite(GPIO_PIN_CLK, LOW);

  Serial.println("Enter ON to turn GPIO on, OFF to turn it off.");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // Read input until newline
    command.trim(); // Remove any whitespace or newline characters

    if (command.equalsIgnoreCase("DIR ON")) 
    {
      digitalWrite(GPIO_PIN_DIR, LOW);
      Serial.println("DIR is now ON");
    } 
    else if (command.equalsIgnoreCase("DIR OFF"))
    {
      digitalWrite(GPIO_PIN_DIR, LOW);
      Serial.println("DIR is now OFF");
    }
    else if (command.equalsIgnoreCase("STEP ON"))
    {
      digitalWrite(GPIO_PIN_STEP, HIGH);
      Serial.println("STEP is now ON");
    }
    else if (command.equalsIgnoreCase("STEP OFF"))
    {
      digitalWrite(GPIO_PIN_STEP, LOW);
      Serial.println("STEP is now OFF");
    }
    else if (command.equalsIgnoreCase("CLOCK ON"))
    {
      digitalWrite(GPIO_PIN_CLK, HIGH);
      Serial.println("CLOCK is now ON");
    }
    else if (command.equalsIgnoreCase("CLOCK OFF"))
    {
      digitalWrite(GPIO_PIN_CLK, LOW);
      Serial.println("CLOCK is now OFF");
    }
    else {
      Serial.println("Invalid command. Type ON or OFF.");
    }
  }
}

