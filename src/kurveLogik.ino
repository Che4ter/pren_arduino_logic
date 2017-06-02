#include "Arduino.h"
#include "PREN2.h"
#include "digitalWriteFast.h"

/* Aufbau der Regelung anhand des Blockdiagramms.
 * Die jeweiligen Blocknummern beziehen sich auf das Blockdiagramm
 * Regelkreis mit P-Regler
 *
 */

/* Implementation vom Ablauf des Regelkreises anahand des Blockdiagramms
 */

void wechsleState(KURVE_STATES neuerState) {
	ticksMotor0 = 0;
	ticksMotor1 = 0;
	kurveState = neuerState;
}

bool fahreNormal(int encoder, int ticks, int speedMotor0, int speedMotor1) {
	encStateMotor1 = digitalReadFast(encoder);

	if (encStateMotor1 != lastEncStateMotor1) {
		ticksMotor1++;
		lastEncStateMotor1 = encStateMotor1;
	}

	if (ticksMotor1 <= ticks) {
		motorGo(0, CW, speedMotor0);
		motorGo(1, CCW, speedMotor1);
		return false;

	} else {

		return true;
	}
}

bool fahreKurve(int encoder, int ticks, int speedMotor0, int speedMotor1) {
	encStateMotor1 = digitalReadFast(encoder);

	if (encStateMotor1 != lastEncStateMotor1) {
		ticksMotor1++;
		lastEncStateMotor1 = encStateMotor1;
	}

	if (ticksMotor1 <= ticks) {
		motorGo(0, CW, speedMotor0);
		motorGo(1, CW, speedMotor1);
		return false;

	} else {

		return true;
	}
}

void startKurve(void) {
	bool encStateMotor1;
	switch (kurveState) {
	case ST1_KurveAus:
		motorGo(0, 3, 255);
		motorGo(1, 3, 255);
		wechsleState(ST2_FahreAufPos1);
		break;
	case ST2_FahreAufPos1:
		if (fahreNormal(13, 4800, 70, 70)) {
			wechsleState(ST3_Drehung90Grad);
		}
		break;
	case ST3_Drehung90Grad:
		if (fahreKurve(12, 3500, 80, 60)) {
			wechsleState(ST4_FahreAufPos2);
		}
		break;
	case ST4_FahreAufPos2:
		if (fahreNormal(13, 3700, 60, 60)) {
			wechsleState(ST5_Drehung2);
		}
		break;

	case ST5_Drehung2:
		if (fahreKurve(12, 2000, 80, 70)) {
			wechsleState(ST8_FahreAufPos4);
		}
		break;
	case ST8_FahreAufPos4:
		if (fahreNormal(13, 1650, 50, 50)) {
			wechsleState(ST7_Drehung3);
		}
		break;
	case ST7_Drehung3:
		if (fahreKurve(12, 1000, 80, 70)) {
			wechsleState(ST6_FahreAufPos3);
		}
		break;
	case ST6_FahreAufPos3:
		if (fahreNormal(13, 4000, 70, 70)) {
			wechsleStateParcour(ST20_ParkourGeradeAusFahren);
				}

		break;
	}
}

