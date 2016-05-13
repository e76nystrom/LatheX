#if !defined(INCLUDE)

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "remvar.h"
#include "lathe.h"
#include "zcontrol.h"
#include "xcontrol.h"
#define EXT

#define DBG_MOVE  1		/* move operation */
#define DBG_QUE   1		/* que operation */
#define DBG_DISABLE 0		/* disable debugging */

#endif

typedef struct
{
 char state;			/* state */
 int pass;			/* current pass */
 float taper;			/* taper */
 float zVal;			/* saved z value */
 float xVal;			/* saved x value */
} T_RUN_CTL, *P_RUN_CTL;

#define MAX_CMDS 64

typedef struct
{
 union
 {
  struct
  {
   char cmd;
   char flag;
  };
  struct
  {
   int op;
  };
 };
 union
 {
  float val;
  int iVal;
 };
} T_MOVECMD, *P_MOVECMD;

typedef struct
{
 int fil;
 int emp;
 int count;
 T_MOVECMD cmd[MAX_CMDS];
} T_MOVEQUE, *P_MOVEQUE;

EXT T_RUN_CTL moveCtl;
EXT T_MOVEQUE moveQue;

char queMoveCmd(int op, float val);
char queIntCmd(int op, int val);
void stopMove();
void procMove();

#if !defined(INCLUDE)

void moveXZ(int zDest, int xDest);
void moveZX(int zLoc, int xLoc);

char queMoveCmd(int op, float val)
{
 P_MOVEQUE que = &moveQue;
 if (que->count < MAX_CMDS)
 {
  P_MOVECMD cmd = &que->cmd[que->fil];
  que->fil++;
  if (que->fil >= MAX_CMDS)
   que->fil = 0;
  cmd->op = op;
  cmd->val = val;
  que->count++;
  if (DBG_QUE)
   printf("move %2d op %4x val %7.4f\n", que->count, op, val);
  return(1);
 }
 if (DBG_QUE)
  printf("move of op %4x val %7.4f\n", op, val);
 return(0);
}

char queIntCmd(int op, int val)
{
 P_MOVEQUE que = &moveQue;
 if (que->count < MAX_CMDS)
 {
  P_MOVECMD cmd = &que->cmd[que->fil];
  que->fil++;
  if (que->fil >= MAX_CMDS)
   que->fil = 0;
  cmd->op = op;
  cmd->iVal = val;
  que->count++;
  if (DBG_QUE)
   printf("move %2d op %4x val %d\n", que->count, op, val);
  return(1);
 }
 if (DBG_QUE)
  printf("move of op %4x val %d\n", op, val);
 return(0);
}

void stopMove()
{
 memset(&moveQue, 0, sizeof(moveQue));
}

void procMove()
{
 P_RUN_CTL mv = &moveCtl;
 switch (mv->state)
 {
 case M_IDLE:
 {
  P_MOVEQUE que = &moveQue;
  while (que->count != 0)
  {
   --que->count;
   P_MOVECMD cmd = &que->cmd[que->emp];
   que->emp++;
   if (que->emp >= MAX_CMDS)
    que->emp = 0;
   char done = 1;
   int val;
   if (DBG_QUE & DBG_DISABLE)
    printf("cmd %d\n", cmd->cmd);
   switch (cmd->cmd)
   {
   case MOVE_Z:
    val = (int) (cmd->val * zAxis.stepsInch);
    zMove(val, cmd->flag);
    mv->state = M_WAIT_Z;
    break;

   case MOVE_X:
    val = (int) (cmd->val * xAxis.stepsInch);
    xMove(val, cmd->flag);
    mv->state = M_WAIT_X;
    break;

   case SAVE_Z:
    if (DBG_QUE)
     printf("save z %7.4f\n", cmd->val);
    mv->zVal = (int) (cmd->val * zAxis.stepsInch);
    done = 0;
    break;

   case SAVE_X:
    if (DBG_QUE)
     printf("save X %7.4f\n", cmd->val);
    mv->xVal = (int) (cmd->val * xAxis.stepsInch);
    done = 0;
    break;

   case SAVE_TAPER:
    if (DBG_QUE)
     printf("save taper %7.4f\n", cmd->val);
    mv->taper = cmd->val;
    done = 0;
    break;

   case MOVE_ZX:
    if (DBG_QUE)
     printf("move zx %7.4f\n", cmd->val);
    val = (int) (cmd->val * zAxis.stepsInch);
    moveZX(val, mv->xVal);
    mv->state = M_WAIT_Z;
    break;

   case MOVE_XZ:
    if (DBG_QUE)
     printf("move xz %7.4f\n", cmd->val);
    val = (int) (cmd->val * xAxis.stepsInch);
    moveXZ(mv->zVal, val);
    mv->state = M_WAIT_X;
    break;

   case TAPER_ZX:
    if (DBG_QUE)
     printf("taper zx %7.4f\n", cmd->val);
    taperCalc(&zTA, &xPA, mv->taper);
    int dir = ZPOS;
    if (cmd->flag)
     dir = ZNEG;
    xTaperInit(&xPA, dir);
    val = (int) (cmd->val * zAxis.stepsInch);
    zMove(val, ZSYN | Z_SYN_START | X_SYN_TAPER);
    mv->state = M_WAIT_Z;
    break;

   case TAPER_XZ:
    if (DBG_QUE)
     printf("taper xz %7.4f\n", cmd->val);
    taperCalc(&xTA, &zPA, mv->taper);
    int dir = XPOS;
    if (cmd->flag)
     dir = XNEG;
    xTaperInit(&zPA, dir);
    val = (int) (cmd->val * xAxis.stepsInch);
    xMove(val, XSYN | X_SYN_START | Z_SYN_TAPER);
    mv->state = M_WAIT_X;
    break;

   case QUE_START:
    spindleSetup();
    spindleStart();
    mv->state = M_WAIT_SPINDLE;
    break;

   case QUE_STOP:
    spindleStop();
    mv->state = M_WAIT_SPINDLE;
    break;

   case PASS_NUM:
    if (DBG_QUE)
     printf("pass %2d\n", cmd->iVal);
    int tmp = cmd->iVal;
    currentPass = tmp;
    mv->pass = tmp;
    done = 0;
    break;
   }
   if (done)
    break;
  }
 }
 break;

 case M_WAIT_Z:
  if (zMoveCtl.state == ZIDLE)	/* if operation complete */
   mv->state = M_IDLE;
  break;

 case M_WAIT_X:
  if (xMoveCtl.state == XIDLE)	/* if operation complete */
   mv->state = M_IDLE;
  break;

 case M_WAIT_SPINDLE:
#if 0
  if ((sp.accel == 0)		/* if done accelerating */
  ||  (sp.decel == 0))		/* or done decelerating */
#endif
   mv->state = M_IDLE;
  break;
 }
}

void moveZX(int zLoc, int xLoc)
{
 if (DBG_MOVE)
  printf("moveZX %7.4f %7.4f\n", (float) zLoc / zAxis.stepsInch,
	 (float) xLoc / xAxis.stepsInch);
}

void moveXZ(int zDest, int xDest)
{
 if (DBG_MOVE)
  printf("moveZX %7.4f %7.4f\n", (float) zLoc / zAxis.stepsInch,
	 (float) xLoc / xAxis.stepsInch);
#if 0
 int deltaZ = zDest - zLoc;
 int deltaX = xDest - xLoc;
#endif
}

#endif
