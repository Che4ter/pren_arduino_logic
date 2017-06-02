#include "Arduino.h"
#include "PREN2.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "digitalWriteFast.h"
#include "softreset/SoftReset.h"
int pos = 0;
//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(9600);

	initUltraschall();

	// Initialize PWM
	pinMode(statpin, OUTPUT);

	// Initialize digital pins as outputs (PWM)
	for (int i = 0; i < 2; i++) {
		pinMode(inApin[i], OUTPUT);
		pinMode(inBpin[i], OUTPUT);
		pinMode(pwmpin[i], OUTPUT);
	}
	// Initialize braked (PWM)
	for (int i = 0; i < 2; i++) {
		digitalWrite(inApin[i], LOW);
		digitalWrite(inBpin[i], LOW);
	}

	AFMS = Adafruit_MotorShield();
	myMotor = AFMS.getMotor(3);
	schlitten = AFMS.getMotor(1);
	AFMS.begin();

	pinMode(enc, INPUT);
	pinMode(mStop, INPUT_PULLUP);
	ticksMotor1 = 0;
	ticksMotor0 = 0;

	pinModeFast(12, INPUT);
	pinModeFast(13, INPUT);
	pinModeFast(4, OUTPUT);
	pinModeFast(7, OUTPUT);
	pinModeFast(8, OUTPUT);
	pinModeFast(11, OUTPUT);

	schlitten->setSpeed(150);
	schlitten->run(FORWARD);
	kurveState = ST1_KurveAus;
	//wechsleStateParcour(ST11_WartenAufKurveLinks);

}

void handleIncomingPacket(SerialCommunication::serialPacket &packet) {
	//Serial.println("Package received");
	//Serial.println(packet.commandID);

	switch (packet.commandID) {
	case COMMAND_SWITCH_STATE:
		//Serial.println(packet.payload[0]);

		switch (packet.payload[0]) {
		case COMMAND_STATE_START:
			wechsleStateParcour(ST2_FahrzeugInitialisierung);
			break;
		case COMMAND_STATE_DRIVE1:
			wechsleStateParcour(ST3_ParkourErsteCM);
			break;
		case COMMAND_STATE_BEFORE_CURVE:
			wechsleStateParcour(ST11_WartenAufKurveLinks);
			break;
		//currentMainState = (MAINSTATES) packet.payload[0];
		//Serial.print("STATE:");
		//	Serial.println(packet.payload[0], HEX);
		}
		break;
	case COMMAND_STOP:
		motorGo(0, 3, 255);
		motorGo(1, 3, 255);
		wechsleStateParcour(ST31_STOP);
		//currentMainState = (MAINSTATES) packet.payload[0];
		//Serial.print("STATE:");
		//	Serial.println(packet.payload[0], HEX);
		break;
	case COMMAND_RESET:
			motorGo(0, 3, 255);
			motorGo(1, 3, 255);
			wechsleStateParcour(ST31_STOP);

			soft_restart();
			break;
	case COMMAND_SET_DIRECTION:
			parcourDirection = packet.payload[0];
			break;
	case COMMAND_SET_SPEED_STAIR:
			speedStair = packet.payload[0];
			break;
	case COMMAND_SET_SPEED_PARCOUR:
			speedParcour = packet.payload[0];
			break;
	default:
		break;

	}
}

// The loop function is called in an endless loop
void loop() {
	 startParkour();

	//motorGo(0, CW, 150);
	//motorGo(1, CCW, 100);

	 /*	readUltraschallRight();
	 istwertPufferRK0 = fillArrayIstwert(reglerDistanzIstwertRK0);

	 for (int i = 0; i < 10; i++) {
	 istwertPufferMedian[i] = istwertPufferRK0[i];
	 }
	 istwertmedian = median(10, istwertPufferMedian);

	 reglerErrorRK0 = block10010(reglerSollwertMitKorrekturRK0, istwertmedian);

	 if ((reglerErrorRK0 <= 100.0) && (reglerErrorRK0 >= -100.0)) {
	 startSpurRegelung0();
	 startSpurRegelung1();
	 }


	 //fahre gerade aus
	 //solange wand
	 motorGo(0, CW,reglerSollwertPWM_IntRK0);
	 motorGo(1, CCW, reglerSollwertPWM_IntRK1);

	 readUltraschallRight();
	 if (reglerDistanzIstwertRK0 > 200) {
	 pos = 1;

	 }else{
	 istwertPufferRK0 = fillArrayIstwert(reglerDistanzIstwertRK0);

	 for (int i = 0; i < 4; i++) {
	 istwertPufferMedian[i] = istwertPufferRK0[i];
	 }

	 istwertmedian = median(4, istwertPufferMedian);

	 reglerErrorRK0 = block10010(reglerSollwertMitKorrekturRK0, istwertmedian);

	 if ((reglerErrorRK0 <= 100.0) && (reglerErrorRK0 >= -100.0)) {
	 startSpurRegelung0();
	 startSpurRegelung1();
	 }

	 }
	 } else if (pos == 1) {
	 startKurve();
	 }
*/

 		SerialCommunication::serialPacket packet =
 				serialHandler.getIncomingPacket();
 		if (packet.curLoc != 0) {
 			handleIncomingPacket(packet);
 		}
}

/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
	serialHandler.readSerialData();
}