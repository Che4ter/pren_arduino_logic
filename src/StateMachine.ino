#include "Arduino.h"
#include "PREN2.h"

/* Aufbau der Regelung anhand des Blockdiagramms.
 * Die jeweiligen Blocknummern beziehen sich auf das Blockdiagramm
 * Regelkreis mit P-Regler
 *
 */

/* Implementation vom Ablauf des Regelkreises anahand des Blockdiagramms
 */

void wechsleStateParcour(PARKOUR_STATES neuerState) {

	parkourState = neuerState;
}
void startParkour(void) {

	switch (parkourState) {

	case ST1_FahrzeugAusgeschaltet:
		//todo: links oder rechtskurve definieren

		break;
	case ST2_FahrzeugInitialisierung:
		startZentrifuge();
		myMotor->setSpeed(speedZentrifuge);
		myMotor->run(FORWARD);
		break;
	case ST3_ParkourErsteCM:
		if (fahreNormal(13, 3500, 70, 70)) {
			wechsleStateParcour(ST4_ParkourGeradeAusFahren);
			}
		break;

	case ST4_ParkourGeradeAusFahren:
		readUltraschallRechts();

		reglerErrorRK0 = block10010(reglerSollwertMitKorrekturRK0,
				reglerDistanzIstwertRK0Rechts);

		if ((reglerErrorRK0 <= 100.0) && (reglerErrorRK0 >= -100.0)) {
			startSpurRegelung0(speedStair);
			startSpurRegelung1(speedStair);
		}

		motorGo(0, CW, reglerSollwertPWM_IntRK0);
		motorGo(1, CCW, reglerSollwertPWM_IntRK1);

		break;

	case ST11_WartenAufKurveLinks:
		readUltraschallRechts();
		if (reglerDistanzIstwertRK0Rechts > 200) {
			wechsleStateParcour(ST12_AbarbeitenKurveLinks);

		} else {
			reglerErrorRK0 = block10010(reglerSollwertMitKorrekturRK0,
					reglerDistanzIstwertRK0Rechts);

			if ((reglerErrorRK0 <= 100.0) && (reglerErrorRK0 >= -100.0)) {
				startSpurRegelung0(speedParcour);
				startSpurRegelung1(speedParcour);
			}

			motorGo(0, CW, reglerSollwertPWM_IntRK0);
			motorGo(1, CCW, reglerSollwertPWM_IntRK1);
		}

		break;

	case ST12_AbarbeitenKurveLinks:
		startKurve();
		break;

	case ST14_AbarbeitenKurveRechts:

		break;

	case ST20_ParkourGeradeAusFahren:
		readUltraschallRechts();

			reglerErrorRK0 = block10010(reglerSollwertMitKorrekturRK0,
					reglerDistanzIstwertRK0Rechts);

			if ((reglerErrorRK0 <= 100.0) && (reglerErrorRK0 >= -100.0)) {
				startSpurRegelung0(speedParcour);
				startSpurRegelung1(speedParcour);
			}

			motorGo(0, CW, reglerSollwertPWM_IntRK0);
			motorGo(1, CCW, reglerSollwertPWM_IntRK1);

			break;
		break;



	case ST25_ParkourVorbereitenEnde:

		break;

	case ST30_ParkourEnde:

		break;

	case ST31_STOP:
		motorGo(0, 3, 255);
		motorGo(1, 3, 255);
		break;
	}

}
