#define GPIO_PIN_DIR 18
#define GPIO_PIN_STEP 19 
#define GPIO_PIN_CLK 21

String data = "";
String buff = "";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // Wait for Serial connection
    delay(10);
  }

  Serial.println("Welcome, System Ready");
}

void loop() {
  // Check if data is available in the serial buffer
  if (Serial.available()) {
    data = Serial.readStringUntil('\n');
    buff += data + '\n';
    Serial.println(buff);
  }
}
