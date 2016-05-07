#if !defined(INCLUDE)
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include "remvar.h"
#if !defined(EXT)
#define EXT
#endif
#endif

#define ENCTEST 1
#define ENCMAX (2540 * 8)
#define FCY 42000000

EXT int16_t encState;		/* state of encoder */
EXT char encRun;		/* encoder running */

void encInit();
void encStart(int tEna);
void encStop();

#if !defined(INCLUDE)

#if ENCTEST

#define encTmrISR(x)  TIM1_BRK_TIM9_IRQHandler(x)
#define encTmrClrIE() TIM9->DIER &= ~TIM_IT_UPDATE
#define encTmrSetIE() TIM9->DIER |= TIM_IT_UPDATE
#define encTmrClrIF() TIM9->SR = ~TIM_FLAG_UPDATE
#define encTmrInit()  TIM9->CR1 &= ~TIM_CR1_CEN
#define encTmrStart() __HAL_RCC_TIM9_CLK_ENABLE(); TIM9->CR1 |= TIM_CR1_CEN
#define encTmrStop()  TIM9->CR1 &= ~TIM_CR1_CEN
#define encTmrScl(x)  TIM9->PSC = (x - 1)
#define encTmrRead()  TIM9->CNT
#define encTmrClr()   TIM9->CNT = 0
#define encTmrMax(x)  TIM9->ARR = (x - 1)
#define encTmrMaxRead() TIM9->ARR

#define ENC_A_BIT (1 << 15) 
#define ENC_B_BIT (1 << 14) 
#define SYNC_BIT  (1 << 13) 

#define initABit()
#define setABit() GPIOB->BSRR = ENC_A_BIT
#define clrABit() GPIOB->BSRR = (ENC_A_BIT << 16)

#define initBBit()
#define setBBit() GPIOB->BSRR = ENC_B_BIT
#define clrBBit() GPIOB->BSRR = (ENC_B_BIT << 16)

#define initSync()
#define setSync() GPIOB->BSRR = SYNC_BIT
#define clrSync() GPIOB->BSRR = (SYNC_BIT << 16)

void encInit()
{
 encMax = ENCMAX;		/* set encoder maximum */
 encPreScaler = 0;		/* prescale 1 */
 encTimer = FCY / encMax;	/* timer for one sync per second */
}

void encStart(int tEna)
{
 clrABit();			/* clear outputs */
 clrBBit();
 clrSync();

 initABit();			/* init encoder outputs */
 initBBit();
 initSync();			/* init sync output */

 encTmrStop();			/* disable timer */
 encTmrClrIF();			/* clear interrupt flag */
 encTmrClr();			/* clear counter register */
 encTmrScl(encPreScaler);	/* load prescaler */
 encTmrMax(encTimer);		/* set timer period */
 encState = 0;
 encCounter = 0;
 encRevCounter = 0;
 encRun = true;

 if (tEna)
 {
  encTmrSetIE();		/* enable interrupt */
  encTmrStart();   		/* turn timer on */
 }
}

void encStop()
{
 encRun = false;		/* clear run flag */
 encTmrClrIE();			/* disable interrupt */
 encTmrStop();			/* stop timer */
 encTmrClrIF();			/* clear interrupt flag */
 clrABit();			/* clear outputs */
 clrBBit();
}

void encTmrISR(void)
{
 encTmrClrIF();	 		/* clear interrupt */
 if (encRun)
 {
  if (encRunCount != 0)		/* if encoder counting */
  {
   if (--encRunCount == 0)	/* if count is now zero */
   {
    encStop();			/* stop encoder */
   }
  }

  encCounter += 1;		/* update counter */
  if (encCounter >= encMax)	/* if at maximum */
  {
   encCounter = 0;		/* reset */
   encRevCounter += 1;		/* count a revolution */
   setSync();			/* set the sync bit */
  }
  else				/* if not at maximum */
  {
   clrSync();			/* clear sync bit */
  }

  switch (encState)		/* select on state */
  {
  case 0:
   setABit();
   break;
  case 1:
   setBBit();
   break;
  case 2:
   clrABit();
   break;
  case 3:
   clrBBit();
   break;
  }
  encState += 1;		/* update state */
  encState &= 0x3;		/* mas in range */
 }
}
#endif
#endif
