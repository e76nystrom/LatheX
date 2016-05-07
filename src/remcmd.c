#if !defined(INCLUDE)
#if !defined(WIN32)
#include "stm32f4xx_hal.h"
#include "stm32f401xe.h"
#endif
#include <stdio.h>
#include <stdint.h>          /* For uint16_t definition */
#include <stdbool.h>         /* For true/false definition */
#include "remvar.h"
#include "Xilinx.h"
#if !defined(WIN32)
#include "serialio.h"
#include "spi.h"
#include "lathe.h"
#include "encoder.h"
#endif
#include "runctl.h"
#define EXT
#endif

void remcmd();

#include "cmdList.h"
#include "parmList.h"
#include "ctlbits.h"

#if !defined(INCLUDE)

#if defined(WIN32)

typedef union
{
 char b[4];			/* char array */
 int32_t i;			/* long interger */
} byte_long;

int16_t val;
byte_long readval;

#define LOAD(a, b)
#define putx(a)
#define SNDHEX(a)
#define sndhex(a, b)
#define gethex()
#define read1(x)

char chgmask;
char zstop;
char xstop;
char cmdStop;
char cmdPause;

void zLoad()
{
}

void xLoad()
{
}

void zMove(int dist, char flag)
{
}

void zMoveRel(int dist)
{
}

void xMove(int dist, char flag)
{
}

void xMoveRel(int dist)
{
}

#endif

#include "remparm.h"

void remcmd()
{
 P_PARM valptr;
 int parm;
 int size;

 putx1('-');
 gethex1();			/* read parameter */
 parm = val;
 switch (parm)
 {
 case ZMOVE:
  zMoveCmd();
  break;

 case ZJMOV:
  zJogCmd();
  break;

 case ZSTOP:
  zStop();
  break;

 case ZHOME:
  zHomeCmd();
  break;

 case ZSETLOC:
  zLocCmd();
  break;

 case ZGOHOME:
  zGoHomeCmd();
  break;

 case XMOVE:
  xMoveCmd();
  break;

 case XJMOV:
  xJogCmd();
  break;

 case XSTOP:
  xStop();
  break;

 case XHOME:
  xHomeCmd();
  break;
   
 case XSETLOC:
  xLocCmd();
  break;

 case XGOHOME:
  xGoHomeCmd();
  break;

 case SPINDLE_START:
  spindleStart();
  break;

 case SPINDLE_STOP:
  spindleStop();
  break;

 case CMD_PAUSE:
  pauseCmd();
  break;

 case CMD_RESUME:
  resumeCmd();
  break;

 case CMD_STOP:
  stopCmd();
  break;

 case CMD_CLEAR:
  clearCmd();
  break;

 case CMD_SETUP:
  setup();
  break;

 case CMD_SPSETUP:
  spindleSetup();
  break;

 case CMD_ZSETUP:
  zSetup();
  break;

 case CMD_ZSYNSETUP:
  zSynSetup();
  break;

 case CMD_ZTAPERSETUP:
  zTaperSetup();
  break;

 case CMD_XSETUP:
  xSetup();
  break;

 case CMD_XSYNSETUP:
  xSynSetup();
  break;

 case CMD_XTAPERSETUP:
  xTaperSetup();
  break;

 case READSTAT:
  break;

 case READISTATE:
 {
  char tmpval = zMoveCtl.state;
  tmpval |= xMoveCtl.state << 4;
  SNDHEX1(tmpval);
 }
 break;
  
 case LOADVAL:			/* load a local parameter */
  gethex1();			/* read the parameter number */
  parm = val;			/* save it */

  if (parm < MAX_PARM)		/* if in range */
  {
   valptr = &remparm[parm];	/* pointer to parameter info */
   p = valptr->p;		/* destination pointer */
   size = valptr->size;		/* value size */

   int type = getnum1();	/* get the value */
   if (type == 1)		/* if integer */
   {
    if (size == 4)		/* if a long word */
     *(int32_t *) p = val;	/* save as a long word */
    else if (size == 1)		/* if a character */
     *p = (char) val;		/* save the character */
    else if (size == 2)		/* if a short integer */
     *(int16_t *) p = val;	/* save the value */
   }
   else if (type == 2)		/* if floating value */
   {
    *(float *) p = fVal;	/* save as a long word */
   }
  }
  break;

 case READVAL:			/* read a local parameter */
  gethex1();			/* save the parameter number */
  parm = val;			/* save it */
  valptr = &remparm[parm];	/* pointer to parameters */
  sndhex1(valptr->p,valptr->size); /* send the response */
  break;

 case LOADXREG:			/* load a xilinx register */
  gethex1();			/* save the parameter number */
  parm = val;			/* save it */
  gethex1();			/* get the value */
  LOAD(parm,val);		/* load value to xilinx register */
  break;

 case READXREG:			/* read a xilinx register */
  gethex1();			/* save the parameter number */
  parm = val;			/* save it */
//   read(parm);			/* read the xilinx register */
  read1(parm);			/* read the xilinx register */
  SNDHEX1(readval);		/* return the parameter */
  break;

 case SENDMOVE:
  gethex1();			/* save op code and flag */
  parm = val;			/* save input value */
  char rtn = getnum1();		/* read parameter */
  if (rtn != NO_VAL)		/* if valid number */
  {
   if (rtn == FLOAT_VAL)	/* if floating */
    queMoveCmd(parm, fVal);	/* que command */
   else				/* if integer */
    queIntCmd(parm, val);	/* que command */
  }
  break;

 case MOVEQUESTATUS:
  parm = MAX_CMDS - moveQue.count; /* calculate amount empty */
  sndhex1((unsigned char *) &parm, sizeof(parm)); /* send it back */
  break;

 case READLOC:
  getnum1();
  sndhex1((unsigned char *) (int32_t) val,sizeof(int16_t));
  break;

 case READDBG:
#if DBGMSG
  if (dbgcnt > 0)		/* if debug messages */
  {
   P_DBGMSG p;
   --dbgcnt;			/* count off a message */
   p = &dbgdata[dbgemp];	/* get pointer to data */
   dbgemp++;			/* update empty pointer */
   if (dbgemp >= MAXDBGMSG)	/* if past end */
    dbgemp = 0;			/* point back to beginning */

   int16_t count = sizeof(p->str); /* get maximum length */
   char *p1 = p->str;		/* get poninter to string */
   while (--count >= 0)		/* while not at end of buffer */
   {
    char ch = *p1++;		/* read a character */
    if (ch == 0)		/* if null */
     break;			/* exit loop */
    putx1(ch);			/* output character */
   }
   putx1(' ');			/* output a space */
   if (p->val < 0)
   {
    putx1('-');
    p->val = -p->val;
   }
   sndhex1((unsigned char *) &p->val,sizeof(p->val)); /* output data */
  }
#endif
  break;

 case ENCSTART:
  encStart(true);
  break;

 case ENCSTOP:
  encStop();
  break;
 }
 putx1('*');
}

#if 0

void remcmd()
{
 P_PARM valptr;
 int16_t parm;
 int16_t size;
 int32_t tmpval;

 putx('-');
 gethex();			/* read parameter */
 parm = val;
#if 0
 if (parm < CMDS)		/* if load command */
 {
#if 0
  gethex();			/* read value */
  switch (parm)
  {
  case LOADFEEDTBL:
   if (feedidx < MAXFEEDINDEX)
    feedtbl[feedidx] = val;
   break;
  }
#endif
 }
 else
#endif
 {
  switch (parm)
  {
  case ZMOVE:
   if (zstate == ZIDLE)
    zMoveRel(zdistin);
   break;

  case ZSTOP:
   zstop = 1;
   break;

  case ZHOME:
   if (zstate == ZIDLE)
   {
    LOAD(XLDZLOC,0);
    LOAD(XLDZCTL,ZSET_LOC | ZRESET);
    LOAD(XLDZCTL,0);
   }
   break;

  case ZSETLOC:
   if (zstate == ZIDLE)
   {
    LOAD(XLDZLOC,zlocin);
    LOAD(XLDZCTL,ZSET_LOC | ZRESET);
    LOAD(XLDZCTL,0);
   }
   break;

  case ZGOHOME:
   if (zstate == ZIDLE)
    zMove(0,ZMOV);
   break;

  case XMOVE:
   if (xstate == XIDLE)
    xMoveRel(xdistin);
   break;

  case XSTOP:
   xstop = 1;
   break;

  case XHOME:
   if (xstate == XIDLE)
   {
    LOAD(XLDXLOC,0);		/* set location */
    LOAD(XLDXCTL,XSET_LOC | XRESET); /* reset and set location */
    LOAD(XLDXCTL,0);		/* set to enable operation */
   }
   break;
   
  case XGOHOME:
   if (xstate == XIDLE)
    xMove(0,XMOV);
   break;

  case XSETLOC:
   if (xstate == XIDLE)
   {
    LOAD(XLDXLOC,xlocin);
    LOAD(XLDXCTL,XSET_LOC | XRESET);
    LOAD(XLDXCTL,0);
   }
   break;

#if 0
  case CMDTURN:
   turn();
   break;
  case CMDFACE:
   face();
   break;
  case CMDTAPER:
   if (taperctlf & TAPERX)	/* if tapering x */
   {
    turn();			/* use turn operation */
   }
   else if (taperctlf & TAPERZ)	/* if tapering z */
   {
    face();			/* use face operation */
   }
   break;
  case CMDTHREAD:
   thread();
   break;
#endif

#if 0
  case CMDPAUSE:
   cmdpause = 1;
   break;
  case CMDRESUME:
   cmdpause = 0;
   break;
  case CMDSTOP:
   tstate = TIDLE;		/* return to idle state */
   fstate = FIDLE;		/* return to idle state */
   xstop = 1;
   zstop = 1;
   cmdstop = 1;
   cmdpause = 0;
   break;
#endif

  case LOADZPRM:
   zLoad();
   break;
  case LOADXPRM:
   xLoad();
   break;
  case LOADSPRM:
   break;
  case LOADTPRM:
   break;

#if 0
  case READFEEDTBL:
   if (feedidx < MAXFEEDINDEX)
   {
    readval.i = feedtbl[feedidx];
    SNDHEX(readval);
   }
   break;
#endif

  case READSTAT:
//   parm = (portb >> 9) & 3;
   SNDHEX(parm);
   break;

  case READISTATE:
   tmpval = zstate;
   tmpval |= xstate << 4;
   if (tstate)
    tmpval |= tstate << 8;
   if (fstate)
    tmpval |= fstate << 12;
   SNDHEX(tmpval);
   break;

  case LOADVAL:			/* load a local parameter */
   gethex();			/* read the parameter number */
   parm = val;			/* save it */
#if 0
   p = remparm[parm].p;		/* get destination pointer */
   size = remparm[parm].size;	/* read the size field */
   chgmask |= remparm[parm].flag; /* update change flag */
#else
   valptr = &remparm[parm];	/* pointer to parameter info */
   char *p = valptr->p;		/* destination pointer */
   size = valptr->size;		/* value size */
//   chgmask |= valptr->flag;	/* update change flag */
#endif
   gethex();			/* get the value */
   if (size == 4)		/* if a long word */
    *(int32_t *) p = val;	/* save as a long word */
   else if (size == 1)		/* if a character */
    *p = (char) val;		/* save the character */
   else if (size == 2)		/* if a short integer */
    *(int16_t *) p = val;	/* save the value */
   break;

  case LOADXREG:		/* load a xilinx register */
   gethex();			/* save the parameter number */
   parm = val;			/* save it */
   gethex();			/* get the value */
   LOAD(parm,val);		/* load value to xilinx register */
   break;

  case READVAL:			/* read a local parameter */
   gethex();			/* save the parameter number */
   parm = val;			/* save it */
   //   printf("p %x",(uint16_t) remparm[parm].p);
#if 0
   sndhex(remparm[parm].p,remparm[parm].size); /* send the response */
#else
   valptr = &remparm[parm];	   /* pointer to parameters */
   sndhex(valptr->p,valptr->size); /* send the response */
#endif
   break;

  case READXREG:		/* read a xilinx register */
   gethex();			/* save the parameter number */
   parm = val;			/* save it */
//   read(parm);			/* read the xilinx register */
   read1(parm);			/* read the xilinx register */
   SNDHEX(readval);		/* return the parameter */
   break;

//  case READTBL:
//   gethex();			/* read the parameter number */
//   parm = val;			/* save it */
//#if 0
//   printf("%x %x",(uint16_t) remparm[parm].p,remparm[parm].size);
//#else
//   valptr = &remparm[parm];	   /* pointer to parameters */
//   printf("%x %x",(uint16_t) valptr->p,valptr->size);
//#endif
//   break;

  case READLOC:
   gethex();
   sndhex((unsigned char *) (int32_t) val,sizeof(int32_t));
   break;

  case READDBG:
#if DBGMSG
   if (dbgcnt > 0)		/* if debug messages */
   {
    P_DBGMSG p;
    --dbgcnt;			/* count off a message */
    p = &dbgdata[dbgemp];	/* get pointer to data */
    dbgemp++;			/* update empty pointer */
    if (dbgemp >= MAXDBGMSG)	/* if past end */
     dbgemp = 0;		/* point back to beginning */

    int16_t count = sizeof(p->str); /* get maximum length */
    char *p1 = p->str;		/* get poninter to string */
    while (--count >= 0)	/* while not at end of buffer */
    {
     char ch = *p1++;		/* read a character */
     if (ch == 0)		/* if null */
      break;			/* exit loop */
     putx(ch);			/* output character */
    }
    putx(' ');			/* output a space */
    if (p->val < 0)
    {
     putx('-');
     p->val = -p->val;
    }
    sndhex((unsigned char *) &p->val,sizeof(p->val)); /* output data */
   }
#endif
   break;
  }
 }
 putx('*');
}

#endif

#endif
