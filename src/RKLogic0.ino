#include "Arduino.h"
#include "PREN2.h"

/* Aufbau der Regelung anhand des Blockdiagramms.
 * Die jeweiligen Blocknummern beziehen sich auf das Blockdiagramm
 * Regelkreis mit P-Regler
 *
 */

/* Implementation vom Ablauf des Regelkreises anahand des Blockdiagramms
 */

void startSpurRegelung0(int speed) {
	reglerKorrekturRK0 = 0.0;
	reglerDistanzSollwertRK0 = 100.0;
	reglerSollwertMitKorrekturRK0 = block10000(reglerDistanzSollwertRK0,
			reglerKorrekturRK0);

	reglerErrorRK0 = block10010(reglerSollwertMitKorrekturRK0, reglerDistanzIstwertRK0Rechts);

	i2GainBlockRK0 = 100.0;
	i3GainBlockRK0 = 250.0;
	reglerAusgangGainRK0 = block10020(reglerErrorRK0, i2GainBlockRK0, i3GainBlockRK0);

	reglerAusgangGainMitLimitRK0 = block10030(reglerAusgangGainRK0, 100.0, -100.0);

	speedMotorBetriebRK0 = speed; // in PRZ
	reglerOutputRK0 = block10040(reglerAusgangGainMitLimitRK0, speedMotorBetriebRK0);

	reglerOutputMitLimitRK0 = block10050(reglerOutputRK0, 100.0, 0.0);

	reglerExternalSpeedRK0 = 10.0;
	reglerEinBefehlRK0 = 1;
	reglerSollwertPRZ_floatRK0 = block10060(reglerOutputMitLimitRK0,
			reglerExternalSpeedRK0, reglerEinBefehlRK0);

	reglerSollwertPWM_floatRK0 = block10070(reglerSollwertPRZ_floatRK0);
	reglerSollwertPWM_IntRK0 = (int) reglerSollwertPWM_floatRK0;
}
