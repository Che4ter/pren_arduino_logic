#include "Arduino.h"
#include "PREN2.h"

/* Aufbau der Regelung anhand des Blockdiagramms.
 * Die jeweiligen Blocknummern beziehen sich auf das Blockdiagramm
 * Regelkreis mit P-Regler
 *
 */

/* Initialisierung vom Port 10 (Echopin) und Port 11 (Triggerpin) f�r den Ultraschall Sensor
 */

void initUltraschall() {
	//Links
	pinMode(trigPinLinks, OUTPUT);
	pinMode(echoPinLinks, INPUT);

	//Rechts
	pinMode(trigPinRechts, OUTPUT);
	pinMode(echoPinRechts, INPUT);
}

/* Blocknummer 10100 - Auslesen vom Ultraschallsensor
 */
void readUltraschallLinks() {
	digitalWrite(trigPinLinks, LOW);  // Added this line
	delayMicroseconds(2); // Added this line
	digitalWrite(trigPinLinks, HIGH);
	delayMicroseconds(10); // Added this line
	digitalWrite(trigPinLinks, LOW);
	durationRK0Links = pulseIn(echoPinLinks, HIGH);
	reglerDistanzIstwertRK0Links = (durationRK0Links / 2) / 2.9;

	delay(5);
}

void readUltraschallRechts() {
	digitalWrite(trigPinRechts, LOW);  // Added this line
	delayMicroseconds(2); // Added this line
	digitalWrite(trigPinRechts, HIGH);
	delayMicroseconds(10); // Added this line
	digitalWrite(trigPinRechts, LOW);
	durationRK0Rechts = pulseIn(echoPinRechts, HIGH);
	reglerDistanzIstwertRK0Rechts = (durationRK0Rechts / 2) / 2.9;

	delay(5);
}

long median(int n, long x[]) {
	long temp;
	int i, j;
	// the following two loops sort the array x in ascending order
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (x[j] < x[i]) {
				// swap elements
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}
		}
	}

	if (n % 2 == 0) {
		// if there is an even number of elements, return mean of the two elements in the middle
		return ((x[n / 2] + x[n / 2 - 1]) / 2.0);
	} else {
		// else return the element in the middle
		return x[n / 2];
	}
}

long* fillArrayIstwert(long istwert) {

	static long arrayIstwert[10];

	for (int i = 0; i < (10 - 1); i++) {
		arrayIstwert[(10 - 1) - i] = arrayIstwert[(10 - 1) - (i + 1)];
	}

	arrayIstwert[0] = istwert;

	return arrayIstwert;
}

/* Blocknummer 10000 - Addition ReglerSollwert und ReglerKorrektur
 */
float block10000(float reglerSollwert, float reglerKorrektur) {

	float summe;
	summe = reglerSollwert + reglerKorrektur;

	return summe;
}

/* Blocknummer 10010 - Differenz zwischen ReglerSollwert und ReglerIstwert
 */
float block10010(float reglerSollMitKorrektur, float reglerDistanzIstwert) {

	float differenz;
	differenz = reglerSollMitKorrektur - reglerDistanzIstwert;

	return differenz;
}

/* Blocknummer 10020 - P-Gain Berechnung
 */
float block10020(float i1, float i2, float i3) {

	float gain;
	gain = (i1 * i2) / i3;

	return gain;
}

/* Blocknummer 10030 - Limit der Korrektur
 */
float block10030(float input, float LP, float LM) {

	float output;

	if (input > LP) {
		output = LP;
	} else if (input < LM) {
		output = LM;
	} else {
		output = input;
	}

	return output;
}

/* Blocknummer 10040 - Summe ReglerAusgangMitLimit und BetriebsSollwert vom Motor
 */
float block10040(float reglerAusgangMitLimit, float speedSollwert) {

	float reglerOutput;
	reglerOutput = speedSollwert + reglerAusgangMitLimit;

	return reglerOutput;
}

/* Blocknummer 10050 - Limit von PRZ Ansteuerung Motor
 */
float block10050(float input, float LP, float LM) {

	float output;

	if (input > LP) {
		output = LP;
	} else if (input < LM) {
		output = LM;
	} else {
		output = input;
	}

	return output;
}

/* Blocknummer 10060 - Switch Block f�r Motor Sollwert
 */
float block10060(float reglerOutput, float externalSpeed,
bool reglerEinBefehl) {

	float switchOutput;

	if (reglerEinBefehl) {
		switchOutput = reglerOutput;
	} else {
		switchOutput = externalSpeed;
	}

	return switchOutput;
}

/* Blocknummer 10070 - Skallierung von Sollwert Prozent in Sollwert PWM
 */
float block10070(float sollwertPRZ) {

	float sollwertPWM;

	sollwertPWM = 255.0 * (sollwertPRZ / 100.0);

	return sollwertPWM;
}
