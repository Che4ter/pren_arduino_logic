#include "Arduino.h"
#include "PREN2.h"

Servo schalterBeatetigung;

void initButtonPanel() {
  schalterBeatetigung.attach(schalterBeatetigungPin);
  schalterBeatetigung.write(wippeRECHTS);
}

void setTaster(){
	if(digit > 3){
		for (int w = 0; w <= 60; w += 1) {
			 schalterBeatetigung.write(pos);
			 delay(15);
		 }
	} else{
		for (int w = 0; w <= 60; w += 1) {
			 schalterBeatetigung.write(w);
			 delay(15);
		 }
	}
}
