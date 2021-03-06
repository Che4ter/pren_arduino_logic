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
		case PAR_FAHRZEUG_AUSGESCHALTET:
	  	readUltraschallRechts();

			break;
		case PAR_FAHRZEUG_INITIALISIERUNG:
			//startZentrifuge();
			//myMotor->setSpeed(speedZentrifuge);
			//myMotor->run(FORWARD);
			break;

		case PAR_ERSTE_CM:
			if (fahreNormal(13, 3000, 140, 140)) {
				wechsleStateParcour(PAR_GERADEAUS_STAIR);
				}

			break;

		case PAR_GERADEAUS_STAIR:
				fahreMitRegelungSensorRechts(speedStair);
			break;

		case PAR_WARTE_AUF_KURVE:
			fahreMitRegelungSensorRechts(speedParcour);
			if (reglerDistanzIstwertRK0Rechts > 350) {
				if(parcourDirection == 0){
					wechsleStateParcour(PAR_FAHRE_KURVE_LINKS);
				} else	{
					wechsleStateParcour(PAR_FAHRE_KURVE_RECHTS);
				}
			}
			break;

		case PAR_FAHRE_KURVE_LINKS:
			startKurveLinks();
			break;

		case PAR_FAHRE_KURVE_RECHTS:
			startKurveRechts();
			break;

		case PAR_FAHRE_GERADEAUS_BIS_ENDE:
			fahreMitRegelungSensorRechts(speedParcour);
			if(parcourDirection == 0){
				if (readUltraschallLinks() > 400) {
					wechsleStateParcour(PAR_SET_SCHLITTEN);
				}
			}
			else{
				if (reglerDistanzIstwertRK0Rechts > 400) {
						wechsleStateParcour(PAR_SET_SCHLITTEN);
					}
			}
			break;
		case PAR_SET_SCHLITTEN:
			motorGo(0, 3, 255);
			motorGo(1, 3, 255);
				if(schlittenToPosition())
				{
					ticksMotor0 = 0;
					ticksMotor1 = 0;
					wechsleStateParcour(PAR_PRESSBUTTON);
				}
				break;
		case PAR_PRESSBUTTON:
				if (fahreNormal(13, 2000, 75, 75)) {
					wechsleStateParcour(PAR_STOP);
				}
				break;
		case PAR_STOP:
			motorGo(0, 3, 255);
			motorGo(1, 3, 255);
			myMotor->setSpeed(speedZentrifuge);
			zentrifugeState = ST1_Step1;
			break;
		}
}
