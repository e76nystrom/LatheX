#if !defined(INCLUDE)

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
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
 float minFeed;			/* minimum feed rate */
 float maxFeed;			/* maximum feed rate */
 float accel;			/* acceleration rate */
 float pitch;			/* pitch for threading or feed */
 int stepsInch;			/* axis steps per inch */
 char taper;			/* set up for tapering second */
 float taperInch;		/* taper per inch */

 /* calculated values */
 int clockFreq;
 int clocksPerInch;
 float accelTime;
 int accelSteps;

 int steps;
 int stepsSec;
 int time;

 /* intermediate value for hardware setup */
 int scale;
 int dx;
 int dyIni;
 int dyMax;
 int intIncPerClock;

 /* values for hardware setup */
 int sum;			/* sum initial value */
 int incr1;			/* incr 1 value */
 int incr2;			/* incr 2 value */
 int intAccel;			/* acceleration adder */
 int accelClocks;		/* acceleration clocks */
 int freqDivider;		/* frequency divider for move */
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

void accelCalc(P_ACCEL ac);

void turnPitch(P_ACCEL ac, float pitch);
void threadTPI(P_ACCEL ac, float tpi);
void threadMetric(P_ACCEL ac, float pitch);
void turnAccel(P_ACCEL ac, float accel);
void accelSetup(P_ACCEL ac);

void taperCalc(P_ACCEL a0, P_ACCEL a1, float taper);

void zTaperInit(P_ACCEL ac, char dir);
void xTaperInit(P_ACCEL ac, char dir);

int tmp(int x);

EXT char zflag;
EXT char xflag;

#if !defined(INCLUDE)

#ifdef WIN32

void stopMove(){}
void zJMove(int dir){}
void zMove(int32_t pos, char cmd){}
void zMoveRel(int32_t dist, char cmd){}
void xJMove(int dir){}
void xMove(int32_t pos, char cmd){}
void xMoveRel(int32_t dist, char cmd){}

char cmdStop;
char cmdPause;
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

 ac->minFeed = zMoveMin;
 ac->maxFeed = zMoveMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nz move accel\n");
 accelCalc(ac);

 ac = &zJA;

 ac->minFeed = zJogMin;
 ac->maxFeed = zJogMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nz jog accel\n");
 accelCalc(ac);
}

void zSynSetup()
{
 if (DBG_SETUP)
  printf("\nz sync accel\n");
 P_ACCEL ac = &zTA;
 ac->stepsInch = zAxis.stepsInch;
 ac->minFeed = zMA.minFeed;	/* set minimum */
 switch (feedType)
 {
 case FEED_PITCH:
  turnPitch(ac, feed);
  break;
 case FEED_TPI:
  threadTPI(ac, feed);
  break;
 case FEED_METRIC:
  threadMetric(ac, feed);
  break;
 }
 turnAccel(ac, zAccel);
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
 P_ACCEL ac = &xMA;

 ac->minFeed = xMoveMin;
 ac->maxFeed = xMoveMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nx move accel\n");
 accelCalc(ac);

 ac = &xJA;

 ac->minFeed = xJogMin;
 ac->maxFeed = xJogMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nx jog accel\n");
 accelCalc(ac);
}

void xSynSetup()
{
 if (DBG_SETUP)
  printf("\nx sync accel\n");
 P_ACCEL ac = &xTA;
 ac->stepsInch = xAxis.stepsInch;
 ac->minFeed = xMA.minFeed;	/* set minimum */
 switch (feedType)
 {
 case FEED_PITCH:
  turnPitch(ac, feed);
  break;
 case FEED_TPI:
  threadTPI(ac, feed);
  break;
 case FEED_METRIC:
  threadMetric(ac, feed);
  break;
 }
 turnAccel(ac, xAccel);
}

void xTaperSetup()
{
}

/* calculate acceleration for move */

void accelCalc(P_ACCEL ac)
{
 int stepsSecMax = (int) ((ac->maxFeed / 60.0) * ac->stepsInch);
 ac->clockFreq = stepsSecMax * freqMult;
 ac->clocksPerInch = ac->clockFreq;
 ac->freqDivider = (xFrequency / ac->clockFreq) - 1;
 if (DBG_P)
  printf("freqGenMax %d freqDivider %d\n", ac->clockFreq, ac->freqDivider);

 accelSetup(ac);
}

void turnPitch(P_ACCEL ac, float pitch)
{
 if (DBG_P)
  printf("\nturnPitch\n");
 ac->pitch = pitch;
}

void threadTPI(P_ACCEL ac, float tpi)
{
 if (DBG_P)
  printf("\nturnTPI\n");
 ac->pitch = (float) (1.0 / tpi);
}

void threadMetric(P_ACCEL ac, float pitch)
{
 if (DBG_P)
  printf("\nturnMetric\n");
 ac->pitch = (float) (pitch / 25.4);
}

/* calculate acceleration for turn */

void turnAccel(P_ACCEL ac, float accel)
{
 ac->maxFeed = rpm * ac->pitch;
 ac->clocksPerInch = (int) (encMax * ac->pitch);
 ac->clockFreq = (int) (rpm / 60.0) * encMax;
 if (ac->maxFeed < ac->minFeed)	/* if below minimum */
 {
  ac->intAccel = 0;
  ac->accelClocks = 0;
 }
 else
 {
  accelSetup(ac);
 }
}

#define MAX_SCALE 12

int bitSize(int val)
{
 int bits = 0;
 while (bits < 32)
 {
  if (val == 0)
   break;
  val >>= 1;
  bits += 1;
 }
 return(bits);
}

void accelSetup(P_ACCEL ac)
{
 if (DBG_SETUP)
  printf("minFeed %6.2f feedRate %6.2f ipm\n", ac->minFeed, ac->maxFeed);
 int stepsSecMax = (int) ((ac->maxFeed / 60.0) * ac->stepsInch);
 int stepsSecMin = (int) ((ac->minFeed / 60.0) * ac->stepsInch);
 if (DBG_SETUP)
  printf("stepsSecMin %d stepsSecMax %d\n", stepsSecMin, stepsSecMax);

 float stepsSec2 = (float) (ac->accel * ac->stepsInch);
 ac->accelTime = (float) ((stepsSecMax - stepsSecMin) / stepsSec2);
 ac->accelClocks = (int) (ac->clockFreq * ac->accelTime);
 if (DBG_SETUP)
  printf("stepsSec2 %0.0f accelTime %8.6f accelClocks %d\n",
	 stepsSec2, ac->accelTime, ac->accelClocks);

 int accelMinStep = (int) (((stepsSecMin / stepsSec2) * stepsSecMin) / 2.0);
 int accelMaxStep = (int) (((stepsSecMax / stepsSec2) * stepsSecMax) / 2.0);
 ac->accelSteps = accelMaxStep - accelMinStep;
 if (DBG_SETUP)
  printf("accelSteps %d accelMinStep %d accelMaxStep %d\n", 
	 ac->accelSteps, accelMinStep, accelMaxStep);

 int dxBase = ac->clocksPerInch;
 int dyMaxBase = stepsSecMax;
 int dyMinBase = stepsSecMin;
 if (DBG_SETUP)
  printf("dxBase %d dyMaxBase %d dyMinBase %d",
	 dxBase, dyMaxBase, dyMinBase);

 int scale;
 int accelClocks = ac->accelClocks;
 int intIncPerClock = 0;
 for (scale = 0; scale < MAX_SCALE; scale++)
 {
  ac->dx = dxBase << scale;
  ac->dyMax = dyMaxBase << scale;
  int dyMin = dyMinBase << scale;
  int dyDelta = ac->dyMax - dyMin;
  if (DBG_SETUP)
   printf("\nscale %d dx %d dyMin %d dyMax %d dyDelta %d\n",
	  scale, ac->dx, dyMin, ac->dyMax, dyDelta);

  float incPerClock = (float) dyDelta / accelClocks;
  intIncPerClock = (int) (incPerClock + 0.5);
  if (intIncPerClock == 0)
   continue;
  ac->intIncPerClock = intIncPerClock;
  int dyDeltaC = intIncPerClock * accelClocks;
  int err = (int) (abs(dyDelta - dyDeltaC)) >> scale;
  ac->dyIni = ac->dyMax - intIncPerClock * accelClocks;
#if 0
  if (DBG_SETUP)
   printf("dyIni %d dyMax %d intIncPerClock %d accelClocks %d\n",
	  ac->dyIni, ac->dyMax, intIncPerClock, accelClocks);
#endif

  int bits = bitSize(ac->dx) + 1;
  if (DBG_SETUP)
   printf("dyIni %d dyMax %d dyDelta %d incPerClock %6.2f "
	  "err %d bits %d\n",
	  ac->dyIni, ac->dyMax, dyDelta, incPerClock, err, bits);
  if ((bits >= 30)
  ||  (err == 0))
   break;
 }
 ac->scale = scale;
 ac->incr1 = 2 * ac->dyIni;
 ac->sum = ac->incr1 - ac->dx;
 ac->incr2 = ac->sum - ac->dx;
 ac->intAccel = 2 * intIncPerClock;
 if (DBG_SETUP)
  printf("\nincr1 %d incr2 %d sum %d\n", ac->incr1, ac->incr2, ac->sum);
 
 if (intIncPerClock != 0)
 {
  int64_t totalSum = (int64_t) accelClocks * ac->incr1 + ac->sum;
  int64_t totalInc = ((int64_t) accelClocks * (accelClocks - 1) * 
		      ac->intAccel) / 2;
  ac->accelSteps = (int) ((totalSum + totalInc) / (2 * ac->dx));
#ifdef WIN32
  if (DBG_SETUP)
   printf("accelClocks %d "
	  "totalSum %" PRId64 " totalInc %" PRId64 " accelSteps %d\n", 
	  ac->accelClocks, totalSum, totalInc, ac->accelSteps);
#else
  if (DBG_SETUP)
   printf("accelClocks %d accelSteps %d\n", 
	  ac->accelClocks, ac->accelSteps);
#endif
 }
 else
 {
  ac->accelSteps = 0;
 }
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
