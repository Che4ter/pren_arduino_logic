#include "Arduino.h"
#include "PREN2.h"

void initSchlitten() {
  schlitten->setSpeed(150);
  schlitten->run(BACKWARD);
}

void schlittenTicks(){
		if (digitalRead(mStop)) {
		    encState = digitalRead(enc);
  	    if (encState != lastEncState) {
  		      ticks++;
    	      lastEncState = encState;
            Serial.println(ticks);
		    }
		    if (ticks <= 30) {
		        myMotor->run(FORWARD);
				}
        else if (ticks > 30 && ticks <= 60) {
		        myMotor->run(BACKWARD);
				}
        else {
			       ticks = 0;
			  }
		}
		if(!digitalRead(mStop)) {
      encState != lastEncState;
    }
}
