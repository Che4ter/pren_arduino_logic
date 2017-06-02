#include "Arduino.h"
#include "PREN2.h"
#include "digitalWriteFast.h"

void motorOff(int motor) {
	// Initialize braked
	for (int i = 0; i < 2; i++) {
		digitalWrite(inApin[i], LOW);
		digitalWrite(inBpin[i], LOW);
	}
	analogWrite(pwmpin[motor], 0);
}

/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.

 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled

 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND

 pwm: should be a value between ? and 1023, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) {
	const uint8_t a = inApin[motor];
	const uint8_t b = inBpin[motor];

	if (motor <= 1) {
		if (direct <= 4) {
			// Set inA[motor]
			if (direct <= 1) {
				digitalWriteFast(a, HIGH);
			} else {
				digitalWriteFast(a, LOW);
			}

			// Set inB[motor]
			if ((direct == 0) || (direct == 2)) {
				digitalWriteFast(b, HIGH);
			} else {
				digitalWriteFast(b, LOW);
			}

			analogWrite(pwmpin[motor], pwm);
		}
	}
}

