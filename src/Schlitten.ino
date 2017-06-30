#include "Arduino.h"
#include "PREN2.h"

void initSchlitten() {
  schlitten->setSpeed(200);

  while(digitalRead(mStop)){
    schlitten->run(BACKWARD);

  }

  while(!digitalRead(mStop)){
    schlitten->run(FORWARD);

  }
  while(!schlittenToMitte())
  {

  }

  schlitten->setSpeed(0);
  schlittenTicks = 0;
  schlittenFirstTime = true;
}

bool schlittenToPosition(){
  if(schlittenFirstTime){
    setSchlittenTicksFromNumber();
    schlitten->setSpeed(150);
    schlittenFirstTime = false;
  }
  encState = digitalRead(enc);
  if (encState != lastEncState) {
      schlittenTicks++;
      lastEncState = encState;
  }
  if (schlittenTicks <= MAXSchlittenTICKS) {
      schlitten->run(FORWARD);
      return false;
  }
  else {
       schlitten->setSpeed(0);
       return true;
  }
}

bool schlittenToMitte(){
  if(schlittenFirstTime){
    setSchlittenTicksFromNumber();
    schlitten->setSpeed(255);
    schlittenFirstTime = false;
  }
  encState = digitalRead(enc);
  if (encState != lastEncState) {
      schlittenTicks++;
      lastEncState = encState;
  }
  if (schlittenTicks <= 500) {
      schlitten->run(FORWARD);
      return false;
  }
  else {
       schlitten->setSpeed(0);
       return true;
  }
}

void setSchlittenTicksFromNumber(){
    switch (digit) {
    case 1: MAXSchlittenTICKS = 50;
            break;
    case 2: MAXSchlittenTICKS = 100;
            break;
    case 3: MAXSchlittenTICKS = 150;
            break;
    case 4: MAXSchlittenTICKS = 200;
            break;
    case 5: MAXSchlittenTICKS = 250;
            break;
    default: MAXSchlittenTICKS = 50;
  }

  if(parcourDirection == 0){
    //sensor rechts
    readUltraschallRechts();


  } else	{
    int abstandWand = readUltraschallLinks();
    //sensor links


  }
}



/*void schlittenTicks(){
		if (digitalRead(mStop)) {
		    encState = digitalRead(enc);
  	    if (encState != lastEncState) {
  		      ticks++;
    	      lastEncState = encState;
            Serial.println(ticks);
		    }
		    if (ticks <= 30) {
		        schlitten->run(FORWARD);
				}
        else if (ticks > 30 && ticks <= 60) {
		        schlitten->run(BACKWARD);
				}
        else {
			       ticks = 0;
			  }
		}
		if(!digitalRead(mStop)) {
      encState != lastEncState;
    }
}*/
