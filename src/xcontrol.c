#if !defined(INCLUDE)
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "remvar.h"
#include "Xilinx.h"
#include "remcmd.h"
#include "spi.h"
#include "serialio.h"
#include "lathe.h"
#endif

void xLoad();
void xSynLoad();
void xJMove(int dir);
void xMove(int32_t pos, char cmd);
void xMoveRel(int32_t dist, char cmd);
void xControl();

#if !defined(INCLUDE)

void xLoad()
{
 dbgmsg("ldx ",0);
 LOAD(XLDXCTL,0);		/* reset control register */
 LOAD(XLDXFREQ,xfreq);
 xincr1 = (2 * xdyini);
 xincr2 = (2 * (xdyini - xdx));
 xd = (xincr1 - xdx);
 LOAD(XLDXD,xd);
 LOAD(XLDXINCR1,xincr1);
 LOAD(XLDXINCR2,xincr2);
 LOAD(XLDXACCEL,xaccel);
 LOAD(XLDXACLCNT,xaclmax);
}

void xSynLoad()
{
 dbgmsg("ldxs",0);
 LOAD(XLDZFREQ,zfreq);
 sincr1 = (2 * sdy);
 sincr2 = (2 * (sdy - sdx));
 sd = (sincr1 - sdx);
 LOAD(XLDZD,sd);
 LOAD(XLDZINCR1,sincr1);
 LOAD(XLDZINCR2,sincr2);
 LOAD(XLDZACCEL,saccel);
 LOAD(XLDZACLCNT,saclclks);
}

void xJMove(int dir)
{
 P_MOVECTL mov = &xMoveCtl;
 if (mov->state == XIDLE)	/* if not moving */
 {
  P_ACCEL ac = &xJA;		/* pointer to jog */
  float time = JTIMEINITIAL - ac->time; /* time after accel */
  int d = ac->steps + (int) (ac->stepsSec * time); /* initial steps */
  mov->iniDist = d;		/* save initial distance */
  if (dir < 0)			/* if direction negative */
   d = -d;			/* set to negative */
  mov->stop = 0;		/* clear stop flag */
  mov->jogInc = (int) (JTIMEINC * ac->stepsSec); /* save increment */
  mov->maxDist = (int) (JTIMEMAX * ac->stepsSec); /* save maximum */
  printf("xJMove dist %5d xLoc %5d inc %5d max %5d\n",
	 d, xLoc, mov->jogInc, mov->maxDist);
  xMoveRel(d, XJOG);		/* start movement */
 }
 else if (mov->state == XWAITBKLS) /* if waiting for backlash */
 {
 }
 else				/* if moving */
 {
 }
}

void xMove(long pos, char cmd)
{
 P_MOVECTL mov = &xMoveCtl;
#if DBGMSG
// if (print & 4)
//  printf("x %ld\n\r",pos);
 dbgmsg("x mv",pos);
#endif
 read1(XRDXLOC);		/* read x location */
 mov->loc = readval.i;		/* save result */
 xMoveRel(pos - mov->loc, cmd);	/* calculate move distance */
}

void xMoveRel(long dist, char cmd)
{
 P_MOVECTL mov = &xMoveCtl;

 if (mov->state != XIDLE)	/* if not in idle state */
  return;			/* exit now */

 xLoad();			/* load parameters for move */

 dbgmsg("x ds",dist);
 mov->cmd = cmd;		/* save command */
 if (dist != 0)			/* if distance non zero */
 {
  mov->dist = dist;		/* save move distance */
  if (mov->dist > 0)		/* if moving positive */
  {
   mov->state = (mov->dir == XNEG) ?  XWAITBKLS : XSTARTMOVE; /* dir chg ? */
   mov->dir = XPOS;		/* set to move positive direction */
  }
  else
  {
   mov->dist = -mov->dist;	/* make distance a positive number */
   mov->state = (mov->dir == XPOS) ?  XWAITBKLS : XSTARTMOVE; /* dir chg ? */
   mov->dir = XNEG;		/* set move direction to negative */
  }

  if (mov->state == XWAITBKLS)	/* if backlash move needed */
  {
   mov->ctlreg = XSTART | XBACKLASH; /* initialize ctl reg */
   if (mov->dir == XPOS)	/* if positive direction */
    mov->ctlreg |= XDIR_POS;	/* set direction flag */
   LOAD(XLDXDIST,xbacklash);	/* load backlash */
   LOAD(XLDXCTL,mov->ctlreg);	/* start move */
  }
  mov->done = 0;		/* clear done flag */
  mov->stop = 0;		/* clear stop flag */
 }
}

void xControl()
{
 P_MOVECTL mov = &xMoveCtl;
 if (mov->stop)			/* if stop */
  mov->state = XDONE;		/* clean up in done state */

#if DBGMSG
// if (print & 2)
 {
  if (mov->state != mov->prev)
  {
//   printf("x %2d to %2d\n\r",mov->prev,mov->state);
   dbgmsg("x st",mov->state);
   mov->prev = mov->state;
  }
 }
#endif

 switch(mov->state)		/* dispatch on state */
 {
 case XIDLE:			/* 0x00 idle state */
  break;

 case XWAITBKLS:		/* 0x01 wait for backlash move to complete */
  if (mov->done)		/* if done */
  {
   mov->done = 0;		/* clear done flag */
   mov->state = XSTARTMOVE;	/* advance to move state */
  }
  break;

 case XSTARTMOVE:		/* 0x02 start an x move */
  mov->ctlreg = XSTART;		/* initialize control reg */
  char ch = mov->cmd & XMSK;	/* get type of move */
  if (ch == XSYN)		/* if synchronized move */
  {
   xSynLoad();			/* load sync parameters */
   mov->ctlreg |= XSRC_SYN;	/* set sync flags */
  }
  else				/* if not synchronized */
  {
   if (ch == XJOG)		/* if jog */
    LOAD(XLDXACLCNT,xacljog);	/* load jog accelerate time */
   else if (ch == XMAX)		/* if max */
    LOAD(XLDXACLCNT,xaclmax);	/* load time for max */
   else				/* else */
    LOAD(XLDXACLCNT,xaclrun);	/* load time for run */
  }
  if (mov->dir == XPOS)		/* if moving positive */
   mov->ctlreg |= XDIR_POS;	/* set direction flag */
  LOAD(XLDXDIST,mov->dist);	/* set distance to move */
  LOAD(XLDXCTL,mov->ctlreg);	/* start move */
  dbgmsg("ctlx",mov->ctlreg);
  mov->state = XWAITMOVE;	/* wait for move to complete */
  break;

 case XWAITMOVE:		/* 0x03 wait for an x move to complete */
  if (mov->done)		/* if done */
   mov->state = XDONE;		/* clean up everything */
  break;

 case XDONE:			/* 0x04 done state */
 default:			/* all others */
  LOAD(XLDXCTL,0);		/* stop move */
  mov->stop = 0;		/* clear stop flag */
  mov->done = 0;		/* clear done flag */
  mov->cmd = 0;			/* clear command */
  read1(XRDXLOC);		/* read current location */
  mov->loc = readval.i;		/* save it */
  dbgmsg("xloc",mov->loc);
  mov->state = XIDLE;		/* set state to idle */
#if DBGMSG
  dbgmsg("x st",mov->state);
#endif
  break;
 }
}

#endif
