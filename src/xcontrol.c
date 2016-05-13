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

void xSynLoad();
void xJMove(int dir);
void xMove(int32_t pos, char cmd);
void xMoveRel(int32_t dist, char cmd);
void xControl();

#if !defined(INCLUDE)

void xLoad(P_ACCEL ac);

void xLoad(P_ACCEL ac)
{
 if (ac->freqDivider != 0)
  LOAD(XLDXFREQ, ac->freqDivider);
 LOAD(XLDXD, ac->sum);
 LOAD(XLDXINCR1, ac->incr1);
 LOAD(XLDXINCR2, ac->incr2);
 LOAD(XLDXACCEL, ac->intAccel);
 LOAD(XLDXACLCNT, ac->accelClocks);
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

 printf("x move %5d\n", (int) pos);
 if (DBGMSG)
  dbgmsg("x mv",  pos);
 read1(XRDXLOC);		/* read x location */
 mov->loc = readval.i;		/* save result */
 xMoveRel(pos - mov->loc, cmd);	/* calculate move distance */
}

void xMoveRel(long dist, char cmd)
{
 P_MOVECTL mov = &xMoveCtl;

 if (mov->state != XIDLE)	/* if not in idle state */
  return;			/* exit now */

 if (DBGMSG)
  dbgmsg("x ds",  dist);
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
   mov->wait = 1;		/* set wait flag */
   xLoad(&xMA);			/* load move parameters */
   mov->ctlreg = XSTART | XBACKLASH; /* initialize ctl reg */
   if (mov->dir == XPOS)	/* if positive direction */
    mov->ctlreg |= XDIR_POS;	/* set direction flag */
   LOAD(XLDXDIST,  xAxis.backlashSteps); /* load backlash */
   LOAD(XLDXCTL,  mov->ctlreg);	/* start move */
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

 if (DBGMSG)
 {
  if (mov->state != mov->prev)
  {
   dbgmsg("x st",  mov->state);
   mov->prev = mov->state;
  }
 }

 switch(mov->state)		/* dispatch on state */
 {
 case XIDLE:			/* 0x00 idle state */
  break;

 case XWAITBKLS:		/* 0x01 wait for backlash move to complete */
  if (mov->done)		/* if done */
  {
   mov->done = 0;		/* clear done flag */
   mov->wait = 0;		/* clear wait flag */
   mov->state = XSTARTMOVE;	/* advance to move state */
  }
  break;

 case XSTARTMOVE:		/* 0x02 start an x move */
  mov->ctlreg = XSTART;		/* initialize control reg */
  char ch = mov->cmd & XMSK;	/* get type of move */
  if (ch == XSYN)		/* if synchronized move */
  {
   xLoad(&xTA);			/* load turn parameters */
   mov->ctlreg |= XSRC_SYN;	/* set sync flags */
  }
  else				/* if not synchronized */
  {
   if (ch == XJOG)		/* if jog */
    xLoad(&xMA);		/* load jog parameters */
   else if (ch == XMAX)		/* if max */
    xLoad(&xMA);		/* load move parameters */
   else				/* else */
    xLoad(&xTA);		/* load turn parameters */
  }
  if (mov->dir == XPOS)		/* if moving positive */
   mov->ctlreg |= XDIR_POS;	/* set direction flag */
  LOAD(XLDXDIST,  mov->dist);	/* set distance to move */
  LOAD(XLDXCTL,  mov->ctlreg);	/* start move */
  if (DBGMSG)
   dbgmsg("ctlx",  mov->ctlreg);
  mov->wait = 1;		/* set wait flag */
  mov->state = XWAITMOVE;	/* wait for move to complete */
  break;

 case XWAITMOVE:		/* 0x03 wait for an x move to complete */
  if (mov->done)		/* if done */
  {
   mov->wait = 0;		/* clear wait flag */
   mov->state = XDONE;		/* clean up everything */
  }
  break;

 case XDONE:			/* 0x04 done state */
 default:			/* all others */
  LOAD(XLDXCTL,  0);		/* stop move */
  mov->stop = 0;		/* clear stop flag */
  mov->done = 0;		/* clear done flag */
  mov->cmd = 0;			/* clear command */
  read1(XRDXLOC);		/* read current location */
  mov->loc = readval.i;		/* save it */
  if (DBGMSG)
   dbgmsg("xloc",  mov->loc);
  mov->state = XIDLE;		/* set state to idle */
  if (DBGMSG)
   dbgmsg("x st",  mov->state);
  break;
 }
}

#endif
