#if !defined(INCLUDE)
#include "stm32f4xx_hal.h"
#include "stm32f401xe.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "remvar.h"
#include "Xilinx.h"
#include "serialio.h"
#include "spi.h"
#include "zcontrol.h"
#include "xcontrol.h"
#include "encoder.h"
#if !defined(EXT)
#define EXT
#endif
#endif

void lclcmd(int ch);
void gpioInfo(GPIO_TypeDef *gpio);
void usartInfo(USART_TypeDef *usart);
void tmrInfo(TIM_TypeDef *tmr);

EXT int16_t addr;

#if !defined(INCLUDE)

#define dx (2540l * 8l)
#define dy 600l

#define incr1 (2 * dy)
#define incr2 (2 * (dy - dx))
#define d (incr1 - dx)

#define FREQ 1000l
#define MINVELOCITY 100l
#define MAXVELOCITY 1000l
#define ACCEL 2000l

#define SCALE 8

#define accelFreq (FREQ << SCALE)
#define minVelocity (MINVELOCITY << SCALE)
#define maxVelocity (MAXVELOCITY << SCALE)
#define accel ((ACCEL << SCALE) / FREQ)

void readreg(char addr,char *str)
{
 read1(addr);			/* read from device */
 printf("\nread addr %2x val %8lx %10ld %s",addr,readval.i,readval.i,str);
}

#define LOADX(a,b) loadreg(a,(byte_long) ((int32_t) b))

void loadreg(char addr, byte_long val)
{
 printf("sending addr %2x %10ld val %8lx\n",addr,val.i,val.i);
 load(addr,val);
}

void loadregb(char addr, char val)
{
 printf("sending addr %2x %10d val %8x\n",addr,val,val);
 loadb(addr,val);
}

void gpioInfo(GPIO_TypeDef *gpio)
{
 printf("gpio %x\n",(unsigned int) gpio);
 printf("MODER   %8x ",(unsigned int) gpio->MODER);
 printf("OTYPER  %8x\n",(unsigned int) gpio->OTYPER);
 printf("OSPEEDR %8x ",(unsigned int) gpio->OSPEEDR);
 printf("PUPDR   %8x\n",(unsigned int) gpio->PUPDR);
 printf("IDR     %8x ",(unsigned int) gpio->IDR);
 printf("ODR     %8x\n",(unsigned int) gpio->ODR);
 printf("BSRR    %8x ",(unsigned int) gpio->BSRR);
 printf("LCKR    %8x\n",(unsigned int) gpio->LCKR);
 printf("AFR[0]  %8x ",(unsigned int) gpio->AFR[0]);
 printf("AFR[1]  %8x\n",(unsigned int) gpio->AFR[1]);
}

void usartInfo(USART_TypeDef *usart)
{
 printf("usart %x\n",(unsigned int) usart);
 printf("SR   %8x ",(unsigned int) usart->SR);
 printf("DR   %8x\n",(unsigned int) usart->DR);
 printf("BRR  %8x ",(unsigned int) usart->BRR);
 printf("CR1  %8x\n",(unsigned int) usart->CR1);
 printf("CR2  %8x ",(unsigned int) usart->CR2);
 printf("CR3  %8x\n",(unsigned int) usart->CR3);
 printf("GTPR %8x\n",(unsigned int) usart->GTPR);
}

void tmrInfo(TIM_TypeDef *tmr)
{
 printf("tmr %x\n",(unsigned int) tmr);
 printf("CR1   %8x ",(unsigned int) tmr->CR1);
 printf("CR2   %8x\n",(unsigned int) tmr->CR2);
 printf("SMCR  %8x ",(unsigned int) tmr->SMCR);
 printf("DIER  %8x\n",(unsigned int) tmr->DIER);
 printf("SR    %8x ",(unsigned int) tmr->SR);
 printf("EGR   %8x\n",(unsigned int) tmr->EGR);
 printf("CCMR1 %8x ",(unsigned int) tmr->CCMR1);
 printf("CCMR2 %8x\n",(unsigned int) tmr->CCMR2);
 printf("CCER  %8x ",(unsigned int) tmr->CCER);
 printf("CNT   %8x\n",(unsigned int) tmr->CNT);
 printf("PSC   %8x ",(unsigned int) tmr->PSC);
 printf("ARR   %8x\n",(unsigned int) tmr->ARR);
 printf("RCR   %8x ",(unsigned int) tmr->RCR);
 printf("CCR1  %8x\n",(unsigned int) tmr->CCR1);
 printf("CCR2  %8x ",(unsigned int) tmr->CCR2);
 printf("CCR3  %8x\n",(unsigned int) tmr->CCR3);
 printf("CCR4  %8x ",(unsigned int) tmr->CCR4);
 printf("BDTR  %8x\n",(unsigned int) tmr->BDTR);
 printf("DCR   %8x ",(unsigned int) tmr->DCR);
 printf("OR    %8x\n",(unsigned int) tmr->OR);
}

void lclcmd(int ch)
{
 if (ch == 'D')			/* dump dbg buffer */
 {
  newline();
  int empty = dbgemp;
  for (int i = 0; i < dbgcnt; i++)
  {
   P_DBGMSG p = &dbgdata[empty];
   float t = (float) p->time / 1000;
   printf("%8.3f %8s %8x %12d\n", t, p->str, (unsigned int) p->val, (int) p->val);
   empty++;
   if (empty >= MAXDBGMSG)
    empty = 0;
  }
  printf("z %d x %d\n", zLoc, xLoc);
 }
 else if (ch == 'E')		/* clear debug buffer */
 {
  memset(&dbgdata, 0, sizeof(dbgdata));
  dbgcnt = 0;
  dbgfil = 0;
  dbgemp = 0;
 }
 else if (ch == 'd')		/* dump memory */
 {
  putx(' ');
  if (gethex())
  {
   unsigned char *p;

   p = (unsigned char *) (int) val;
   if (gethex())
   {
    newline();
    prtbuf(p,val);
   }
  }
 }
#if ENCTEST
 else if (ch == 'e')
 {
  printf(" counts ");
  fflush(stdout);
  if (getnum())
  {
   encInit();
   encRunCount = val;
   encStart(true);
  }
  else
  {
   printf(" stop[y] ");
   fflush(stdout);
   ch = getx();
   if (ch == 'y')
   {
    encStop();
   }
  }
 }
#endif
 else if (ch == 'q')
 {
  gpioInfo(GPIOA);
  usartInfo(USART1);
  usartInfo(USART2);
  usartInfo(USART6);
  putstr1("start remcmd\n");
 }
 else if (ch == 'r')		/* read memory */
 {
  putx(' ');
  if (gethex())
  {
   printf("%x",*(int16_t *) (int) val);
  }
 }
 else if (ch == 'w')		/* write memory */
 {
  putx(' ');
  if (gethex())
  {
   int16_t *p;
   p = (int16_t *) (int) val;
   printf(" %x ",*p);
   if (gethex())
   {
    *p = val;
   }
  }
 }
 else if (ch == 'a')		/* set command address */
 {
  putx(' ');
  if (getnum())
   addr = val;
 }
 else if (ch == 'g')		/* read spi data */
 {
  putx(' ');
  if (getnum())
  {
   addr = val;			/* save address */
   read1(addr);			/* read from device */
   printf("\nread addr %x val %8lx %10ld",addr,readval.i,readval.i);
  }
 }
 else if (ch == 'G')		/* read spi repeatedly */
 {
  putx(' ');
  if (getnum())			/* enter address */
  {
   addr = val;			/* save address */
   putx(' ');
   if (getnum())		/* enter number of tries */
   {
    newline();
    int16_t i = (int16_t) val;
    while (1)
    {
     read1(addr);		/* read from device */
     if (chRdy())		/* if character available */
     {
      ch = chRead();
      break;
     }
     if ((i != 0)
     &&  (--i <= 0))
      break;
    }
    printf("spiw0 %d spiw1 %d",spiw0,spiw1);
   }
  }
 }
 else if (ch == 's')		/* send val to address a */
 {
  printf(" addr ");
  fflush(stdout);
  if (getnum())			/* read address */
  {
   addr = val;
   printf(" data ");
   fflush(stdout);
   if (getnum())		/* read data */
   {
    printf("\nsending addr %x %10ld val %8lx",addr,val,val);
    LOAD(addr,val);
   }
  }
 }
 else if (ch == 'p')		/* set print flag */
 {
  putx(' ');
  if (getnum())
  {
   print = val;
  }
 }
 else if (ch == 'r')		/* reset */
 {
  LOAD(XLDZCTL,0);
  LOAD(XLDXCTL,0);
  LOAD(XLDTCTL,0);
  LOAD(XLDDCTL,0);
 }
 else if (ch == 'x')		/* move x rel */
 {
  putx(' ');
  if (getnum())
  {
   xMoveRel(val, XMOV);
  }
 }
 else if (ch == 'z')		/* move z rel */
 {
  putx(' ');
  if (getnum())
  {
   zMoveRel(val, XMOV);
  }
 }
 else if (ch == 'u')		/* send debug message */
 {
  putx(' ');
  if (getnum())
  {
   dbgmsg("test",val);
  }
 }
}

#endif
