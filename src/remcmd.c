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

 case ZMOVEREL:
  zMoveRelCmd();
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

 case XMOVEREL:
  xMoveRelCmd();
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
 {
  char buf[10];
  if (zAxis.stepsInch != 0)
  {
   sprintf(buf, "%0.4 ", ((float) zLoc) / zAxis.stepsInch);
   putstr1(buf);
  }
  else
   putstr1("# ");
  if (xAxis.stespInch != 0)
  {
   sprintf(buf, "%0.4 ", ((float) xLoc) / xAxis.stepsInch);
   putstr1(buf);
  }
  else
   putstr1("# ");
  int clocksRev = indexPreScaler * indexPeriod;
  if (clocksRev != 0)
  {
   sprintf(buf, "%0.4", ((float) FCY / clocksRev) * 60);
   putstr1(buf);
  }
  else
   putstr1("#");
 }
 break;

#if DBGMSG
 case READDBG:
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
  break;

 case CLRDBG:
  clrDbgBuf();
  break;
#endif

 case ENCSTART:
  encStart(true);
  break;

 case ENCSTOP:
  encStop();
  break;
 }
 putx1('*');
}

#endif
