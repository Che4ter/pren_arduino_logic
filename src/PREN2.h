// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _PREN2_H_
#define _PREN2_H_
#include "Arduino.h"
#include "SerialCommunication.h"
#include "Adafruit_MotorShield.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"



#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100
#define trigPinRechts 2 // Sensor auf Seite Motor Rechts (RHO)
#define echoPinRechts 3 // Sensor auf Seite Motor Rechts (RHO)

#define trigPinLinks 0 // Sensor auf Seite Motor Links (LH1)
#define echoPinLinks 1 // Sensor auf Seite Motor Links (LH1)

//0 = Links
//1 = Rechts
int parcourDirection = 0;

int speedStair = 50;
int speedParcour = 80;
/*  VNH2SP30 pin definitions
 xxx[0] controls '1' outputs
 xxx[1] controls '2' outputs */
int inApin[2] = { 7, 4 };  // INA: Clockwise input
int inBpin[2] = { 8, 11 }; // INB: Counter-clockwise input
int pwmpin[2] = { 5, 6 }; // PWM input
int cspin[2] = { 2, 3 }; // CS: Current sense ANALOG input
int enpin[2] = { 0, 1 }; // EN: Status of switches output (Analog pin)

const int enc = A0;
const int mStop = A1;
int encState = false;
int lastEncState = false;
int ticks = 0;

const int encoderMotor0 = 13;
const int encoderMotor1 = 12;
int encStateMotor0 = false;
int encStateMotor1 = false;
int lastEncStateMotor0 = false;
int lastEncStateMotor1 = false;
int ticksMotor0 = 0;
int ticksMotor1 = 0;

int statpin = 13;
long durationRK0Links, reglerDistanzIstwertRK0Links;
long durationRK0Rechts, reglerDistanzIstwertRK0Rechts;

float reglerKorrekturRK0;
float reglerDistanzSollwertRK0;
float reglerSollwertMitKorrekturRK0;
float reglerErrorRK0;
float i2GainBlockRK0;
float i3GainBlockRK0;
float reglerAusgangGainRK0;
float reglerAusgangGainMitLimitRK0;
float reglerOutputRK0;
float reglerOutputMitLimitRK0;
float speedMotorBetriebRK0;
float reglerExternalSpeedRK0;
bool reglerEinBefehlRK0;
float reglerSollwertPRZ_floatRK0;
int reglerSollwertPRZ_INTRK0;
int reglerSollwertPWM_floatRK0;
int reglerSollwertPWM_IntRK0;
uint8_t reglerSollwertPWM_uint8RK0;
long* istwertPufferRK0 = NULL;
long istwertPufferMedian[10];
long istwertmedian;
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *myMotor;
Adafruit_DCMotor *schlitten;

long medianIstwertRK0;
int motorSpeed0;
int motorSpeed1;
bool motorStart;
float distanzEncoder;

float reglerAusgangGainMitLimitRK1;
float reglerOutputRK1;
float speedMotorBetriebRK1;
float reglerOutputMitLimitRK1;
float reglerExternalSpeedRK1;
bool reglerEinBefehlRK1;
float reglerSollwertPRZ_floatRK1;
int reglerSollwertPRZ_INTRK1;
int reglerSollwertPWM_floatRK1;
int reglerSollwertPWM_IntRK1;
uint8_t reglerSollwertPWM_uint8RK1;
SerialCommunication serialHandler;
int speedZentrifuge;

typedef enum {
	ST1_FahrzeugAusgeschaltet,
	ST2_FahrzeugInitialisierung,
	ST3_ParkourErsteCM,
	ST4_ParkourGeradeAusFahren,
	ST11_WartenAufKurveLinks,
	ST12_AbarbeitenKurveLinks,
	ST13_WartenAufKurveRechts,
	ST14_AbarbeitenKurveRechts,
	ST20_ParkourGeradeAusFahren,
	ST22_ParkourGeradeausFahren,
	ST25_ParkourVorbereitenEnde,
	ST30_ParkourEnde,
	ST31_STOP,
} PARKOUR_STATES;

PARKOUR_STATES parkourState = ST1_FahrzeugAusgeschaltet;


typedef enum {
	ST1_Step1,
	ST2_Step2,
	ST3_Step3,
	ST4_Step4,
	ST5_Step5,
	ST6_Step6,
	ST7_Step7,
	ST8_Step8,
	ST9_Step9,
	ST10_Step10,
	ST11_Step11,
	ST12_Step12,
	ST13_Step13,
	ST14_Step14,
	ST15_Step15,
	ST16_Step16,
	ST17_Step17,
	ST18_Step18,
	ST19_Step19,
	ST20_Step20,
	ST21_Step21,
	ST22_Step22
} ZENTRIFUGE_STATES;

ZENTRIFUGE_STATES zentrifugeState = ST1_Step1;

typedef enum {
	EV1_Event1,
	EV2_Event2,
	EV3_Event3,
	EV4_Event4,
	EV5_Event5,
	EV6_Event6,
	EV7_Event7,
	EV8_Event8,
	EV9_Event9,
	EV10_Event10,
	EV11_Event11,
	EV12_Event12,
	EV13_Event13,
	EV14_Event14,
	EV15_Event15,
	EV16_Event16,
	EV17_Event17,
	EV18_Event18,
	EV19_Event19,
	EV20_Event20,
	EV21_Event21,
	EV22_Event22,
	EV23_Event23

} ZENTRIFUGE_EVENTS;

ZENTRIFUGE_EVENTS zentrifugeEvent;

typedef enum {
	ST1_KurveAus = 1,
	ST2_FahreAufPos1 = 2,
	ST3_Drehung90Grad = 3,
	ST4_FahreAufPos2 = 4,
	ST5_Drehung2 = 5,
	ST6_FahreAufPos3 = 6,
	ST7_Drehung3 = 7,
	ST8_FahreAufPos4 = 8
} KURVE_STATES;

KURVE_STATES kurveState = ST1_KurveAus;

//Do not add code below this line
#endif /* _testV2_H_ */
