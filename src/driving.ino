void fahreMitRegelungSensorRechts(){
  readUltraschallRechts();

  reglerErrorRK0 = block10010(reglerSollwertMitKorrekturRK0,
      reglerDistanzIstwertRK0Rechts);

  if ((reglerErrorRK0 <= 100.0) && (reglerErrorRK0 >= -100.0)) {
    startSpurRegelung0(speedStair);
    startSpurRegelung1(speedStair);
  }

  motorGo(0, CW, reglerSollwertPWM_IntRK0);
  motorGo(1, CCW, reglerSollwertPWM_IntRK1);
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

bool fahreKurveLinks(int encoder, int ticks, int speedMotor0, int speedMotor1) {
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

bool fahreKurveRechts(int encoder, int ticks, int speedMotor0, int speedMotor1) {
	encStateMotor1 = digitalReadFast(encoder);

	if (encStateMotor1 != lastEncStateMotor1) {
		ticksMotor1++;
		lastEncStateMotor1 = encStateMotor1;
	}

	if (ticksMotor1 <= ticks) {
		motorGo(0, CCW, speedMotor0);
		motorGo(1, CCW, speedMotor1);
		return false;

	} else {

		return true;
	}
}
