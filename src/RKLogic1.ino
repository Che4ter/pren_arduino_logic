#include "Arduino.h"
#include "PREN2.h"

/* Aufbau der Regelung anhand des Blockdiagramms.
 * Die jeweiligen Blocknummern beziehen sich auf das Blockdiagramm
 * Regelkreis mit P-Regler
 *
 */

/* Implementation vom Ablauf des Regelkreises anahand des Blockdiagramms
 */

void startSpurRegelung1(int speed) {

	speedMotorBetriebRK1 = speed; // in PRZ
	reglerAusgangGainMitLimitRK1 = reglerAusgangGainMitLimitRK0 * (-1);
	reglerOutputRK1 = block10040(reglerAusgangGainMitLimitRK1, speedMotorBetriebRK0);

	reglerOutputMitLimitRK1 = block10050(reglerOutputRK1, 100.0, 0.0);

	reglerExternalSpeedRK1 = 10.0;
	reglerEinBefehlRK1 = 1;
	reglerSollwertPRZ_floatRK1 = block10060(reglerOutputMitLimitRK1,
			reglerExternalSpeedRK1, reglerEinBefehlRK1);

	reglerSollwertPWM_floatRK1 = block10070(reglerSollwertPRZ_floatRK1);
	reglerSollwertPWM_IntRK1 = (int) reglerSollwertPWM_floatRK1;

}

