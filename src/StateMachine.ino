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
			startZentrifuge();
			myMotor->setSpeed(speedZentrifuge);
			myMotor->run(FORWARD);
			break;

		case PAR_ERSTE_CM:
			if (fahreNormal(13, 3000, 140, 140)) {
				wechsleStateParcour(PAR_GERADEAUS_STAIR);
				}
			break;

		case PAR_GERADEAUS_STAIR:
				fahreMitRegelungSensorRechts();
			break;

		case PAR_WARTE_AUF_KURVE:
			fahreMitRegelungSensorRechts();
			if (reglerDistanzIstwertRK0Rechts > 200) {
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
			fahreMitRegelungSensorRechts();
			if(parcourDirection == 0){
				//sofort anhalten da sensor noch nicht funktioniert
				wechsleStateParcour(PAR_STOP);

				if (readUltraschallLinks() > 400) {
					wechsleStateParcour(PAR_STOP);
				}
			}
			else{
				if (reglerDistanzIstwertRK0Rechts > 400) {
						wechsleStateParcour(PAR_STOP);
					}
			}
			break;
		case PAR_STOP:
			motorGo(0, 3, 255);
			motorGo(1, 3, 255);
			break;
		}
}
