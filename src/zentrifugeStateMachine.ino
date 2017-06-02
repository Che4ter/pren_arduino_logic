#include "Arduino.h"
#include "PREN2.h"


/* Aufbau der Regelung anhand des Blockdiagramms.
 * Die jeweiligen Blocknummern beziehen sich auf das Blockdiagramm
 * Regelkreis mit P-Regler
 *
 */

/* Implementation vom Ablauf des Regelkreises anahand des Blockdiagramms
 */

void startZentrifugeStateMachine(void) {



	switch (zentrifugeState) {

	case ST1_Step1:
		if (zentrifugeEvent == EV1_Event1) {
			zentrifugeState = ST2_Step2;
		}

		break;

	case ST2_Step2:
			if (zentrifugeEvent == EV2_Event2) {
				zentrifugeState = ST3_Step3;
			}

			break;

	case ST3_Step3:
			if (zentrifugeEvent == EV3_Event3) {
				zentrifugeState = ST4_Step4;
			}
			break;

	case ST4_Step4:
			if (zentrifugeEvent == EV4_Event4) {
				zentrifugeState = ST5_Step5;
			}
			break;

	case ST5_Step5:
			if (zentrifugeEvent == EV5_Event5) {
				zentrifugeState = ST6_Step6;
			}

			break;

	case ST6_Step6:
			if (zentrifugeEvent == EV6_Event6) {
				zentrifugeState = ST7_Step7;
			}
			break;

	case ST7_Step7:
			if (zentrifugeEvent == EV7_Event7) {
				zentrifugeState = ST8_Step8;
			}
			break;

	case ST8_Step8:
			if (zentrifugeEvent == EV8_Event8) {
				zentrifugeState = ST9_Step9;
			}
			break;

	case ST9_Step9:
			if (zentrifugeEvent == EV9_Event9) {
				zentrifugeState = ST10_Step10;
			}
			break;

	case ST10_Step10:
			if (zentrifugeEvent == EV10_Event10) {
				zentrifugeState = ST11_Step11;
			}
			break;

	case ST11_Step11:
			if (zentrifugeEvent == EV11_Event11) {
				zentrifugeState = ST12_Step12;
			}
			break;

	case ST12_Step12:
			if (zentrifugeEvent == EV12_Event12) {
				zentrifugeState = ST13_Step13;
			}
			break;

	case ST13_Step13:
			if (zentrifugeEvent == EV13_Event13) {
				zentrifugeState = ST14_Step14;
			}
			break;

	case ST14_Step14:
			if (zentrifugeEvent == EV14_Event14) {
				zentrifugeState = ST15_Step15;
			}
			break;

	case ST15_Step15:
			if (zentrifugeEvent == EV15_Event15) {
				zentrifugeState = ST16_Step16;
			}
			break;

	case ST16_Step16:
			if (zentrifugeEvent == EV16_Event16) {
				zentrifugeState = ST17_Step17;
			}
			break;

	case ST17_Step17:
			if (zentrifugeEvent == EV17_Event17) {
				zentrifugeState = ST18_Step18;
			}
			break;

	case ST18_Step18:
			if (zentrifugeEvent == EV18_Event18) {
				zentrifugeState = ST19_Step19;
			}
			break;

	case ST19_Step19:
			if (zentrifugeEvent == EV19_Event19) {
				zentrifugeState = ST20_Step20;
			}
			break;

	case ST20_Step20:
			if (zentrifugeEvent == EV20_Event20) {
				zentrifugeState = ST21_Step21;
			}
			break;

	case ST21_Step21:
			if (zentrifugeEvent == EV21_Event21) {
				zentrifugeState = ST22_Step22;
			}
			break;


	case ST22_Step22:
			if (zentrifugeEvent == EV22_Event22) {
				zentrifugeState = ST1_Step1;
			}
			break;


}

}

