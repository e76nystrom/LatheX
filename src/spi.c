#if !defined(INCLUDE)
#include "stm32f4xx_hal.h"
#include "stm32f401xe.h"
#include <stdio.h>
#include <stdint.h>          /* For uint16_t definition */
#include <stdbool.h>         /* For true/false definition */
#include "lathe.h"
#include "Xilinx.h"
#include "remvar.h"
#include "serialio.h"
#define EXT
#endif

typedef union
{
 char  ub[2];			/* char array */
 int16_t i;			/* interger */
} byte_int;

typedef union
{
 char b[4];			/* char array */
 int32_t i;			/* long interger */
} byte_long;

#define LOAD(a,b) load(a,(byte_long) ((int32_t) b))

void spisel();
void spirel();
void load(char addr, byte_long val);
void loadb(char addr, char val);
void read1(char addr);
void read(char addr);
unsigned char spisend(unsigned char);
unsigned char spiread();

EXT byte_long readval;
EXT int16_t spiw0;
EXT int16_t spiw1;

#if !defined(INCLUDE)

#if 0

void spisel()
{
 spi1sel = 0;
}

void spirel()
{
 spi1sel = 1;
}

#else

#define SPI_SEL_BIT (1 << 7)
#define SPI_SEL_REG GPIOC->BSRR
#define spisel()  SPI1->CR1 |= SPI_CR1_SPE; \
 SPI_SEL_REG = (SPI_SEL_BIT << 16)
#define spirel() SPI_SEL_REG = SPI_SEL_BIT; \
 SPI1->CR1 &= ~SPI_CR1_SPE

#endif

void load(char addr, byte_long val)
{
 if (print & 8)
  printf("load %x %lx\n\r",addr,val.i);
 char buf[8];
 sprintf(buf,"lx %02x",addr);
 dbgmsg(buf,val.i);
 spisel();
 spisend(addr);
 spisend(val.b[3]);
 spisend(val.b[2]);
 spisend(val.b[1]);
 spisend(val.b[0]);
 while ((SPI1->SR & SPI_SR_BSY) == 0)
  ;
 spirel();
}

void loadb(char addr, char val)
{
 if (print & 8)
  printf("load %x %x\n\r",addr,val);
 spisel();
 spisend(addr);
 spisend(val);
 spirel();
}

void read1(char addr)
{
 spisel();			/* select again */
 spisend(addr);			/* set read address */
 readval.b[3] = spiread();	/* read first byte */
 readval.b[2] = spiread();
 readval.b[1] = spiread();
 readval.b[0] = spiread();
 while ((SPI1->SR & SPI_SR_BSY) == 0)
  ;
 spirel();			/* and release */
 if (print & 8)
  printf("read %x %lx\n\r",addr,readval.i);
}

void read(char addr)
{
 spisel();			/* select */
 spisend(addr);			/* output address */
 spisend(0);			/* output one byte to load register */
 spirel();			/* release */

 spisel();			/* select again */
 spisend(XREADREG);		/* set read address */
 readval.b[3] = spiread();	/* read first byte */
 readval.b[2] = spiread();
 readval.b[1] = spiread();
 readval.b[0] = spiread();
 spirel();			/* and release */
 if (print & 8)
  printf("read %x %lx\n\r",addr,readval.i);
}

unsigned char spisend(unsigned char c)
{

 spiw0 = 0;
 spiw1 = 0;
#if 0
 char rsp;
 spi1buf = c;
 while (spi1tbf)
  spiw0++;
 while (!spi1rbf)
  spiw1++;
 rsp = spi1buf;			/* read data response */
#else
 SPI_TypeDef *spi = SPI1;
 spi->DR = c;
 while ((spi->SR & SPI_SR_TXE) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXNE) == 0)
  spiw1++;
 c = spi->DR;
 return(c);
#endif
}

unsigned char spiread()
{
 spiw0 = 0;
 spiw1 = 0;
#if 0
 spi1buf = 0;
 while (spi1tbf)
  spiw0++;
 while (!spi1rbf)
  spiw1++;
 return(spi1buf);
#else
 SPI_TypeDef *spi = SPI1;
 spi->DR = 0;
 while ((spi->SR & SPI_SR_TXE) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXNE) == 0)
  spiw1++;
 char c = spi->DR;
 return(c);
#endif
}

#endif
