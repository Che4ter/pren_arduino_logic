#include "Arduino.h"
#include "PREN2.h"
#include "digitalWriteFast.h"

void wechsleState(KURVE_STATES neuerState) {
	ticksMotor0 = 0;
	ticksMotor1 = 0;
	kurveState = neuerState;
}

void startKurveLinks() {
	bool encStateMotor1;
	switch (kurveState) {
	case KURV_AUS:
		motorGo(0, 3, 255);
		motorGo(1, 3, 255);
		wechsleState(KURV_FAHRE_AUF_POS1);
		break;
	case KURV_FAHRE_AUF_POS1:
		if (fahreNormal(13, 4500, 120, 120)) {
			wechsleState(KURV_DREHUNG_90GRAD);
		}
		break;
	case KURV_DREHUNG_90GRAD:
		if (fahreKurveLinks(12, 2600, 170, 170)) {
			wechsleState(KURV_FAHRE_AUF_POS2);
		}
		break;
	case KURV_FAHRE_AUF_POS2:
			if (fahreNormal(13, 4500, 130, 130)) {
				wechsleState(KURV_FAHRE_IN_WAND);
			}
			break;
	case KURV_FAHRE_IN_WAND:
			if (fahreNormal(13, 3000, 100, 100)) {
				wechsleState(KURV_FAHRE_RETOUR_WAND);
			}
			break;
	case KURV_FAHRE_RETOUR_WAND:
							if (fahreRetour(13, 100, 90, 90)) {
								wechsleState(KURV_DREHUNG_HALB_1);
							}
							break;
	case KURV_DREHUNG_HALB_1:
		if (fahreKurveLinks(12, 2400, 170, 170)) {
			wechsleState(KURV_FAHRE_DURCH_BOGEN);
		}
		break;
	case KURV_FAHRE_AUF_POS3:
		if (fahreNormal(13, 1900, 100, 100)) {
			wechsleState(KURV_DREHUNG_HALB_2);
		}
		break;
	case KURV_DREHUNG_HALB_2:
		if (fahreKurveLinks(12, 500, 140, 140)) {
			wechsleState(KURV_FAHRE_DURCH_BOGEN);
		}
		break;
	case KURV_FAHRE_DURCH_BOGEN:
		if (fahreNormal(13, 6000, 90, 90)) {
			speedParcour = 95;
			wechsleStateParcour(PAR_FAHRE_GERADEAUS_BIS_ENDE);
		}
		break;
	}
}

void startKurveRechts() {
	bool encStateMotor1;
	switch (kurveState) {
	case KURV_AUS:
		motorGo(0, 3, 255);
		motorGo(1, 3, 255);
		wechsleState(KURV_FAHRE_AUF_POS1);
		break;
	case KURV_FAHRE_AUF_POS1:
		if (fahreNormal(13, 4500, 120, 120)) {
			wechsleState(KURV_DREHUNG_90GRAD);
		}
		break;
	case KURV_DREHUNG_90GRAD:
		if (fahreKurveRechts(13, 2600, 170, 170)) {
			wechsleState(KURV_FAHRE_AUF_POS2);
		}
		break;
	case KURV_FAHRE_AUF_POS2:
		if (fahreNormal(13, 4500, 130, 130)) {
			wechsleState(KURV_FAHRE_IN_WAND);
		}
		break;
	case KURV_FAHRE_IN_WAND:
			if (fahreNormal(13, 2500, 300, 100)) {
				wechsleState(KURV_FAHRE_RETOUR_WAND);
			}
			break;
	case KURV_FAHRE_RETOUR_WAND:
					if (fahreRetour(13, 150, 100, 100)) {
						wechsleState(KURV_DREHUNG_HALB_1);
					}
					break;
	case KURV_DREHUNG_HALB_1:
		if (fahreKurveRechts(13, 2600, 170, 170)) {
			wechsleState(KURV_FAHRE_DURCH_BOGEN);
		}
		break;
	case KURV_FAHRE_AUF_POS3:
		if (fahreNormal(13, 1750, 90, 90)) {
			wechsleState(KURV_DREHUNG_HALB_2);
		}
		break;
	case KURV_DREHUNG_HALB_2:
		if (fahreKurveRechts(13, 800, 140, 140)) {
			wechsleState(KURV_FAHRE_DURCH_BOGEN);
		}
		break;
	case KURV_FAHRE_DURCH_BOGEN:
	if (fahreNormal(13, 7000, 85, 85)) {
		speedParcour = 95;
		wechsleStateParcour(PAR_FAHRE_GERADEAUS_BIS_ENDE);
	}
		break;
	}
}
