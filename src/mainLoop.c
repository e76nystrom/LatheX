#include "stm32f4xx_hal.h"

#include <stdint.h>        /* Includes uint16_t definition */
#include <stdbool.h>       /* Includes true/false definition */
#include <stdio.h>

#include "lathe.h"
#include "Xilinx.h"
#include "remvar.h"
#include "serialio.h"
#include "spi.h"
#include "lclcmd.h"
#include "remcmd.h"
#include "zcontrol.h"
#include "xcontrol.h"
#include "runctl.h"

void mainLoop(void)
{
 unsigned char ch;

// printf("s %x m %x b %x\n\r",U1STA,U1MODE,U1BRG);

 printf("start main loop\n");
 putstr1("start remcmd\n");
 while (1)			/* main loop */
 {
  newline();
  while (1)			/* input background loop */
  {
   if (cmdPause == 0)		/* if command not paused */
   {
    procMove();			/* process move command */
   }

   if (zMoveCtl.state != ZIDLE)	/* if z axis active */
   {
    read1(XRDZLOC);		/* read z location */
    zLoc = readval.i;
    read1(XRDSR);		/* read status register */
    if ((readval.i & S_Z_DONE_INT) /* if done bit set */
    ||  (zflag))		/* if z done flag from xilinx set */
    {
     printf("z done\n");
     LOAD(XLDZCTL,0);		/* clear z control register */
     zMoveCtl.done = 1;		/* signal done */
    }
    zControl();			/* run z axis state machine */
   }

   if (xMoveCtl.state != XIDLE)	/* if x axis active */
   {
    read1(XRDXLOC);		/* read x location */
    xLoc = readval.i;
    read1(XRDSR);		/* read status register */
    if ((readval.i & S_X_DONE_INT) /* if done bit set */
    ||  (xflag))		/* if x done flag from xilinx set */
    {
     printf("x done\n");
     LOAD(XLDXCTL,0);		/* clear x control register */
     xMoveCtl.done = 1;		/* set done flag */
    }
    xControl();			/* run x axis state machine */
   }

   if (chRdy())			/* if character available */
   {
    ch = chRead();		/* return it */
    if (ch == 0x11)		/* if xon */
     continue;			/* no echo */
    if (ch == 0x13)		/* if xoff */
     continue;			/* no echo */
    putx(ch);			/* echo input */
    break;
   }

   fflush(stdout);
   pollBufChar();		/* check for data to output */

   if (chRdy1())		/* if character on remote link */
   {
    ch = chRead1();		/* read character */
    if (ch == 1)		/* if control a */
    {
     remcmd();			/* process remote command */
    }
   }
  }

  lclcmd(ch);			/* local commands */
  fflush(stdout);
  pollBufChar();		/* check for data to output */
 }
}
