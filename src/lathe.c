#if !defined(INCLUDE)

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include "remvar.h"
#include "runctl.h"
#include "zcontrol.h"
#include "xcontrol.h"
#define EXT
#endif

#define DBG_P     1		/* general debug */
#define DBG_SETUP 1		/* setup */

#define JTIMEINITIAL 0.75	/* initial jog time */
#define JTIMEINC 0.15		/* incremental jog time */
#define JTIMEMAX 1.0		/* maximum jog time */

typedef struct
{
 float pitch;			/* axis leadscrew pitch */
 float ratio;			/* motor leadscrew ratio */
 int microSteps;		/* micro steps */
 int motorSteps;		/* motor steps */
 float accel;			/* acceleration */
 float backlash;		/* backlash */
 int stepsInch;			/* axis steps per inch */
 int backlashSteps;		/* backlash steps */
} T_AXIS, *P_AXIS;

typedef struct
{
 /* initial parameters */
 float minSpeed;		/* minimum speed */
 float maxSpeed;		/* maximum speed */
 float accel;			/* acceleration rate */
 float pitch;			/* pitch for threading or feed */
 int stepsInch;			/* axis steps per inch */
 char taper;			/* set up for tapering second */
 float taperInch;		/* taper per inch */

 /* calculated values */
 int stepsSec;			/* steps per second */
 float stepsSec2;		/* acceleration in steps per sec^2 */
 float time;			/* acceleration time */
 int steps;			/* acceleration steps */
 int clocks;			/* acceleration clocks */
 float dist;			/* acceleration distance */
 int remainder;			/* remainder of spindle cyc div z cyc */
 int initialCount;		/* clocks for first accel step */
 int finalCount;		/* clocks for last accel step */
 int isrCount;			/* clocks for isr initial + final*/
 int spindleSteps;		/* spindle steps during acceleration */
 int spindleRem;		/* spindle steps remainder */

 /* control variables for isr */
 float cFactor;			/* factor to get clocks to next step */
 int clocksStep;		/* clocks per step after acceleration */
 int initialStep;		/* initial accel step number */
 int finalStep;			/* final accel step number */
 int d;				/* sum initial value */
 int incr1;			/* incr 1 value */
 int incr2;			/* incr 2 value */
 int stepsCycle;		/* steps in a cycle */
} T_ACCEL, *P_ACCEL;

EXT T_AXIS zAxis;		/* z axis info */
EXT T_AXIS xAxis;		/* x axis info */

EXT T_ACCEL zTA;		/* z threading accel */
EXT T_ACCEL zPA;		/* z taper accel */
EXT T_ACCEL zMA;		/* z move accel */
EXT T_ACCEL zJA;		/* z jog accel */

EXT T_ACCEL xTA;		/* x threading accel */
EXT T_ACCEL xPA;		/* x taper accel */
EXT T_ACCEL xMA;		/* x move accel */
EXT T_ACCEL xJA;		/* x jog accel */

typedef struct
{
 char state;			/* move state */
 char prev;			/* previous state */
 char cmd;			/* move command */
 char stop;			/* stop flag */
 char done;			/* done flag */
 char ctlreg;			/* control register */
 int dir;			/* direction -1 neg, 0 backlash, 1 pos */
 int dirChange;			/* direction */
 int dist;			/* distance to move */
 int loc;			/* current location */
 int iniDist;			/* initial jog distance */
 int maxDist;			/* maximum jog distance */
 int jogInc;			/* jog increment */
} T_MOVECTL, *P_MOVECTL;

EXT T_MOVECTL zMoveCtl;
EXT T_MOVECTL xMoveCtl;

void pauseCmd();
void resumeCmd();
void stopCmd();
void clearCmd();
void allStop();
void clearAll();
void setup();

void spindleStart();		/* start spindle */
void spindleStop();		/* stop spindle */
void spindleSetup();

void zMoveCmd();
void zJogCmd();
void zHomeCmd();
void zLocCmd();
void zGoHomeCmd();
void zStart();
void zStop();
void zSetup();
void zMoveSetup();
void zSynSetup();
void zTaperSetup();

void xMoveCmd();
void xJogCmd();
void xHomeCmd();
void xLocCmd();
void xGoHomeCmd();
void xStart();
void xStop();
void xSetup();
void xMoveSetup();
void xSynSetup();
void xTaperSetup();

void turnPitch(P_ACCEL ac, float pitch);
void threadTPI(P_ACCEL ac, float tpi);
void threadMetric(P_ACCEL ac, float pitch);
void turnCalc(P_ACCEL ac);
void turnAccel(P_ACCEL ac, float accel);

void accelCalc(P_ACCEL accel);
void taperCalc(P_ACCEL a0, P_ACCEL a1, float taper);

void zTaperInit(P_ACCEL ac, char dir);
void xTaperInit(P_ACCEL ac, char dir);

int tmp(int x);

EXT char zflag;
EXT char xflag;

#if !defined(INCLUDE)

#ifdef WIN32

void stopMove(){}
void zJMove(int dir);
void zMove(int32_t pos, char cmd);
void zMoveRel(int32_t dist, char cmd);
void xJMove(int dir);
void xMove(int32_t pos, char cmd);
void xMoveRel(int32_t dist, char cmd);
#if 0
int cmdStop;
int cmdPause;

typedef struct
{
 int fil;
 int emp;
 int count;
 T_MOVECMD cmd[MAX_CMDS];
} T_MOVEQUE, *P_MOVEQUE;
#endif

T_MOVEQUE moveQue;

#endif

int tmp(int x)
{
 return(x);
}

void stopCmd()
{
 stopMove();
 spindleStop();
 zStop();
 xStop();
 xMoveCtl.stop = 1;
 zMoveCtl.stop = 1;
 cmdStop = 1;
 cmdPause = 0;
}

void clearCmd()
{
 allStop();
 clearAll();
}

void pauseCmd()
{
 cmdPause = 1;
}

void resumeCmd()
{
 cmdPause = 0;
}

void allStop()
{
}

void clearAll()
{
}

void setup()
{
}

void spindleStart()
{
}

void spindleStop()
{
}

void spindleSetup()
{
}

void zMoveCmd()
{
 if (zMoveCtl.state == ZIDLE)
 {
  int dist = (int) (zMoveDist * zAxis.stepsInch);
  zMoveRel(dist, ZJOG);
 }
}

void zJogCmd()
{
 if (moveQue.count == 0)	/* if not moving */
 {
  zJMove(zJogDir);
 }
}

void zHomeCmd()
{
 if (zMoveCtl.state == ZIDLE)
 {
  zLoc = 0;
 }
}

void zLocCmd()
{
 if (zMoveCtl.state == ZIDLE)
 {
  zLoc = (int) (zSetLoc * zAxis.stepsInch);
 }
}

void zGoHomeCmd()
{
 if (zMoveCtl.state == ZIDLE)
  zMove(0, ZMOV);
}

void zStart()
{
}

void zStop()
{
}

void zSetup()
{
 P_AXIS axis = &zAxis;

 if (DBG_SETUP)
  printf("\nz axis setup\n");
 axis->pitch = zPitch;
 axis->ratio = zRatio;
 axis->microSteps = zMicro;
 axis->motorSteps = zMotor;
 axis->accel = zAccel;
 axis->backlash = zBacklash;

 axis->stepsInch = (int) rint((axis->microSteps * axis->motorSteps * 
			       axis->ratio) / axis->pitch);
 axis->backlashSteps = (int) rint(axis->backlash * axis->stepsInch);

 zMoveSetup();
}

void zMoveSetup()
{
 zTA.stepsInch = zAxis.stepsInch;

 P_ACCEL ac = &zMA;

 ac->minSpeed = zMoveMin;
 ac->maxSpeed = zMoveMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nz move accel\n");
 accelCalc(ac);

 ac = &zJA;

 ac->minSpeed = zJogMin;
 ac->maxSpeed = zJogMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nz jog accel\n");
 accelCalc(ac);
}

void zSynSetup()
{
}

void zTaperSetup()
{
}

void xMoveCmd()
{
 if (xMoveCtl.state == XIDLE)
 {
  int dist = (int) (xMoveDist * xAxis.stepsInch);
  xMoveRel(dist, XJOG);
 }
}

void xJogCmd()
{
 if (moveQue.count == 0)	/* if not moving */
 {
  xJMove(xJogDir);
 }
}

void xHomeCmd()
{
 if (xMoveCtl.state == XIDLE)
 {
  xLoc = 0;
 }
}

void xLocCmd()
{
 if (xMoveCtl.state == XIDLE)
 {
  xLoc = (int) (xSetLoc * xAxis.stepsInch);
 }
}

void xGoHomeCmd()
{
 if (xMoveCtl.state == XIDLE)
  xMove(0, XMOV);
}

void xStart()
{
}

void xStop()
{
}

void xSetup()
{
 P_AXIS axis = &xAxis;

 if (DBG_SETUP)
  printf("\nX axis setup\n");
 axis->pitch = xPitch;
 axis->ratio = xRatio;
 axis->microSteps = xMicro;
 axis->motorSteps = xMotor;
 axis->accel = xAccel;
 axis->backlash = xBacklash;

 axis->stepsInch = (int) rint((axis->microSteps * axis->motorSteps * 
			       axis->ratio) / axis->pitch);
 axis->backlashSteps = (int) rint(axis->backlash * axis->stepsInch);

 xMoveSetup();
}

void xMoveSetup()
{
 xTA.stepsInch = xAxis.stepsInch;

 P_ACCEL ac = &xMA;

 ac->minSpeed = xMoveMin;
 ac->maxSpeed = xMoveMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nx move accel\n");
 accelCalc(ac);

 ac = &xJA;

 ac->minSpeed = xJogMin;
 ac->maxSpeed = xJogMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nx jog accel\n");
 accelCalc(ac);
}

void xSynSetup()
{
}

void xTaperSetup()
{
}

void turnPitch(P_ACCEL ac, float pitch)
{
}

void threadTPI(P_ACCEL ac, float tpi)
{
}

void threadMetric(P_ACCEL ac, float pitch)
{
}

void turnCalc(P_ACCEL ac)
{
}

void turnAccel(P_ACCEL ac, float accel)
{
}


void accelCalc(P_ACCEL accel)
{
}

void taperCalc(P_ACCEL a0, P_ACCEL a1, float taper)
{
 printf("taperCalc1\n");
#ifdef WIN32
 FILE *f = fopen("test.txt", "a");
 fprintf(f, "taperCalc1\n");
 fclose(f);
#endif
fflush(stdout);
}

void zTaperInit(P_ACCEL ac, char dir)
{
 printf("ztaperInit\n");
 fflush(stdout);
}

void xTaperInit(P_ACCEL ac, char dir)
{
 printf("xtaperInit\n");
 fflush(stdout);
}

#endif
