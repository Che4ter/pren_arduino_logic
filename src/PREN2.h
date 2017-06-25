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
#include "Servo.h"

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100
#define trigPinRechts 2 // Sensor auf Seite Motor Rechts (RHO)
#define echoPinRechts 3 // Sensor auf Seite Motor Rechts (RHO)

#define trigPinLinks 10 // Sensor auf Seite Motor Links (LH1)
#define echoPinLinks A3 // Sensor auf Seite Motor Links (LH1)

#define schalterBeatetigungPin 9
#define wippeMITTE 125
#define wippeLINKS 137
#define wippeRECHTS 116
//0 = Links Kurve
//1 = Rechts Kurve
int parcourDirection = 0;

int digit = 0;

int speedStair = 50;
int speedParcour = 50;
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
	PAR_FAHRZEUG_AUSGESCHALTET,
	PAR_FAHRZEUG_INITIALISIERUNG,
	PAR_ERSTE_CM,
	PAR_GERADEAUS_STAIR,
	PAR_WARTE_AUF_KURVE,
	PAR_FAHRE_KURVE_LINKS,
	PAR_FAHRE_KURVE_RECHTS,
	PAR_FAHRE_GERADEAUS_BIS_ENDE,
	PAR_STOP,
} PARKOUR_STATES;

PARKOUR_STATES parkourState = PAR_FAHRZEUG_AUSGESCHALTET;


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
	KURV_AUS,
	KURV_FAHRE_AUF_POS1 ,
	KURV_DREHUNG_90GRAD,
	KURV_FAHRE_AUF_POS2,
	KURV_FAHRE_IN_WAND,
	KURV_DREHUNG_HALB_1,
	KURV_FAHRE_AUF_POS3,
	KURV_DREHUNG_HALB_2,
	KURV_FAHRE_DURCH_BOGEN
} KURVE_STATES;

KURVE_STATES kurveState = KURV_AUS;

//Do not add code below this line
#endif /* _testV2_H_ */
