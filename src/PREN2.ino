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
	AFMS = Adafruit_MotorShield();
	myMotor = AFMS.getMotor(3);
	AFMS.begin();

delay(1000000);
myMotor->setSpeed(150);
myMotor->run(BACKWARD);
}

// The loop function is called in an endless loop
void loop() {

		//startZentrifuge();



	// fahreMitRegelungSensorRechts();
	//motorGo(0, CW, 150);
	//motorGo(1, CW, 150);
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

}

/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
