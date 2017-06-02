#include "Arduino.h"
#include "PREN2.h"

/* Aufbau der Regelung anhand des Blockdiagramms.
 * Die jeweiligen Blocknummern beziehen sich auf das Blockdiagramm
 * Regelkreis mit P-Regler
 *
 */

/* Implementation vom Ablauf des Regelkreises anahand des Blockdiagramms
 */

void startZentrifuge(void) {

	bool ende = false;


	if (zentrifugeState == ST1_Step1) {
			delay(8);
		zentrifugeEvent = EV1_Event1;
		speedZentrifuge = 250;

	}

	if (zentrifugeState == ST2_Step2) {
		delay(8);
		zentrifugeEvent = EV2_Event2;
		speedZentrifuge = 120;

	}

	if (zentrifugeState == ST3_Step3) {
		delay(8);
			zentrifugeEvent = EV3_Event3;
		speedZentrifuge = 90;

	}

	if (zentrifugeState == ST4_Step4) {
		delay(8);
		zentrifugeEvent = EV4_Event4;
		speedZentrifuge = 80;

	}

	if (zentrifugeState == ST5_Step5) {
		delay(8);
		zentrifugeEvent = EV5_Event5;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST6_Step6) {
		delay(8);
		zentrifugeEvent = EV6_Event6;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST7_Step7) {
		delay(8);
		zentrifugeEvent = EV7_Event7;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST8_Step8) {
		delay(8);
		zentrifugeEvent = EV8_Event8;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST9_Step9) {
		delay(8);
		zentrifugeEvent = EV9_Event9;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST10_Step10) {
		delay(8);
		zentrifugeEvent = EV10_Event10;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST11_Step11) {
		delay(8);
		zentrifugeEvent = EV11_Event11;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST12_Step12) {
		delay(8);
		zentrifugeEvent = EV12_Event12;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST13_Step13) {
		delay(8);
		zentrifugeEvent = EV13_Event13;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST14_Step14) {
		delay(8);
		zentrifugeEvent = EV14_Event14;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST15_Step15) {
		delay(8);
		zentrifugeEvent = EV15_Event15;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST16_Step16) {
		delay(8);
		zentrifugeEvent = EV16_Event16;
		speedZentrifuge = 70;

	}

	if (zentrifugeState == ST17_Step17) {
		delay(8);
		zentrifugeEvent = EV17_Event17;
		speedZentrifuge = 80;

	}

	if (zentrifugeState == ST18_Step18) {
		delay(8);
		zentrifugeEvent = EV18_Event18;
		speedZentrifuge = 100;

	}

	if (zentrifugeState == ST19_Step19) {
		delay(8);
		zentrifugeEvent = EV19_Event19;
		speedZentrifuge = 110;

	}

	if (zentrifugeState == ST20_Step20) {
		delay(8);
		zentrifugeEvent = EV20_Event20;
		speedZentrifuge = 120;

	}

	if (zentrifugeState == ST21_Step21) {
		delay(8);
		zentrifugeEvent = EV21_Event21;
		speedZentrifuge = 250;

	}

	if (zentrifugeState == ST22_Step22) {
		pos =0;

		if (ende) {
			zentrifugeEvent = EV22_Event22;
			speedZentrifuge = 250;

		}
	}

	startZentrifugeStateMachine();

}

