#include <TMCStepper.h>

#define EN_PIN           15 // Enable
#define DIR_PIN          2 // Direction
#define STEP_PIN         4 // Step
#define CS_PIN           5 // Chip select
#define SW_MOSI          18 // Software Master Out Slave In (MOSI)
#define SW_MISO          19 // Software Master In Slave Out (MISO)
#define SW_SCK           21 // Software Slave Clock (SCK)

#define R_SENSE 0.075f

TMC5160Stepper driver = TMC5160Stepper(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);

bool dir = true;

void setup() {
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Start...");
	driver.begin(); 			// Initiate pins and registeries
	driver.rms_current(2000); 	// Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
	driver.en_pwm_mode(0);  	// Enable extremely quiet stepping

	pinMode(EN_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
	digitalWrite(EN_PIN, LOW); 	// Enable driver in hardware

	Serial.print("DRV_STATUS=0b");
	Serial.println(driver.DRV_STATUS(), BIN);
}

void loop() {
	digitalWrite(STEP_PIN, HIGH);
	delayMicroseconds(1);
	digitalWrite(STEP_PIN, LOW);
	delayMicroseconds(1);
	uint32_t ms = millis();
	static uint32_t last_time = 0;
	if ((ms - last_time) > 5000) {
		if (dir) {
			Serial.println("Dir -> 0");
			driver.shaft(0);
		} else {
			Serial.println("Dir -> 1");
			driver.shaft(1);
		}
		dir = !dir;
		last_time = ms;
	}
}
