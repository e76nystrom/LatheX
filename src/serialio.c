#if !defined(INCLUDE)

#include "stm32f4xx_hal.h"

#include <stdio.h>
#include <stdint.h>          /* For uint16_t definition */
#include <stdbool.h>         /* For true/false definition */
#include <stdlib.h>
#include <string.h>
#define EXT
#endif

#define DBGMSG 1

void sndhex(unsigned char *p, int size);
void sndhex1(unsigned char *p, int size);
void newline();
char getx();
char gethex();
char gethex1();
unsigned char getnum();
unsigned char getnum1();
enum RTN_VALUES
{
 NO_VAL,
 INT_VAL,
 FLOAT_VAL,
};
unsigned char getfloat();
char getstr(char *buf, int bufLen);
char getstr1(char *buf, int bufLen);
void prtbuf(unsigned char *p, int size);
void prtibuf(int16_t *p, int size);
void putx(char c);
void putx1(char c);
void putstr(char *p);
void putstr1(char *p);
#if DBGMSG
void dbgmsg(char *str, int32_t val);
void dbgmsgx(char *str, char reg, int32_t val);
#endif
void pollBufChar();
void putBufChar(char ch);
ssize_t _write (int fd, const char* buf, size_t nbyte);

#define DBG_PORT USART1
#define REM_PORT USART6

//EXT char ch;
EXT unsigned char *p;
EXT int32_t val;
EXT float fVal;

#define PUTX(c) while ((DBG_PORT->SR & USART_SR_TXE) == 0); DBG_PORT->DR = c

#define chRdy() (DBG_PORT->SR & USART_SR_RXNE)
#define chRead() DBG_PORT->DR

#define chRdy1() (REM_PORT->SR & USART_SR_RXNE)
#define chRead1() REM_PORT->DR

#define SNDHEX(val) sndhex((unsigned char *) &val,sizeof(val))
#define SNDHEX1(val) sndhex1((unsigned char *) &val,sizeof(val))

#if DBGMSG

#define MAXDBGMSG 200

typedef struct
{
 char str[12];
 int32_t val;
 int32_t time;
} T_DBGMSG, *P_DBGMSG;

EXT T_DBGMSG dbgdata[MAXDBGMSG];

EXT int16_t dbgcnt;
EXT uint16_t dbgfil;
EXT uint16_t dbgemp;

#endif

#if !defined(INCLUDE)

void putx(char c)
{
 while ((DBG_PORT->SR & USART_SR_TXE) == 0)
  ;
 DBG_PORT->DR = c;
}

void putx1(char c)
{
 while ((REM_PORT->SR & USART_SR_TXE) == 0)
  ;
 REM_PORT->DR = c;
}

void putstr(char *p)
{
 while (1)
 {
  char ch = *p++;
  if (ch == 0)
   break;
  if (ch == '\n')
   putx('\r');
  putx(ch);
 }
}

void putstr1(char *p)
{
 while (1)
 {
  char ch = *p++;
  if (ch == 0)
   break;
  if (ch == '\n')
   putx1('\r');
  putx1(ch);
 }
}

char getx()
{
 while ((DBG_PORT->SR & USART_SR_RXNE) == 0)
  pollBufChar();
 return(DBG_PORT->DR);
}

char getx1()
{
 while ((REM_PORT->SR & USART_SR_RXNE) == 0)
  pollBufChar();
 return(REM_PORT->DR);
}

#define CHAR_BUF_SIZE 4096
int charFil;
int charEmp;
int charCount;
char charBuf[CHAR_BUF_SIZE];

void putBufChar(char ch)
{
 if (charCount < CHAR_BUF_SIZE)
 {
  charCount++;
  charBuf[charFil] = ch;
  charFil++;
  if (charFil >= CHAR_BUF_SIZE)
   charFil = 0;
 }
}

void pollBufChar()
{
 if ((DBG_PORT->SR & USART_SR_TXE) != 0)
 {
  if (charCount != 0)
  {
   DBG_PORT->DR = charBuf[charEmp];
   charEmp++;
   if (charEmp >= CHAR_BUF_SIZE)
    charEmp = 0;
   --charCount;
  }
 }
}

ssize_t _write (int fd, const char* buf, size_t nbyte)
{
 int count = (int) nbyte;

#if 1
 while (--count >= 0)
 {
  char ch = *buf++;
  if (ch == '\n')
  {
   putBufChar('\r');
// putx('\r');
  }
  putBufChar(ch);
//  putx(ch);
 }
#else
 HAL_UART_Transmit(&huart1,(uint8_t *) buf,nbyte,HAL_MAX_DELAY);
#endif
 return(nbyte);
}

void newline()
{
#if 0
 PUTX('\n');
 PUTX('\r');
#else
 putchar('\n');
#endif
}

void sndhex(unsigned char *p, int size)
{
 char tmp;
 char ch;

 p += size;
 while (size != 0)
 {
  --size;
  p--;
  tmp = *p;
  ch = tmp;
  ch >>= 4;
  ch &= 0xf;
  if (ch < 10)
   ch += '0';
  else
   ch += 'a' - 10;
//  while (utxbf1);
//  u1txreg = ch;
  PUTX(ch);

  tmp &= 0xf;
  if (tmp < 10)
   tmp += '0';
  else
   tmp += 'a' - 10;
//  while (utxbf1);
//  u1txreg = tmp;
  PUTX(tmp);
 }
}

void sndhex1(unsigned char *p, int size)
{
 char tmp;
 char ch;

 p += size;
 while (size != 0)
 {
  --size;
  p--;
  tmp = *p;
  ch = tmp;
  ch >>= 4;
  ch &= 0xf;
  if (ch < 10)
   ch += '0';
  else
   ch += 'a' - 10;
  putx1(ch);

  tmp &= 0xf;
  if (tmp < 10)
   tmp += '0';
  else
   tmp += 'a' - 10;
  putx1(tmp);
 }
}

char gethex()
{
 char ch;
 int count;

 val = 0;
 count = 0;
 while (count <= 8)
 {
  ch = getx();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   putx(ch);
   ch -= '0';
   count++;
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   putx(ch);
   ch -= 'a' - 10;
   count++;
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (count > 0)
   {
    --count;
    val >>= 4;
    putx(8);
    putx(' ');
    putx(8);
   }
  }
  else if (ch == ' ')
  {
   putx(ch);
   break;
  }
  else if (ch == 13)
   break;
  else
   continue;
  val <<= 4;
  val += ch;
 }
 return(count != 0);
}

char gethex1()
{
 char ch;
 int count;

 val = 0;
 count = 0;
 while (count <= 8)
 {
  ch = getx1();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   putx1(ch);
   ch -= '0';
   count++;
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   putx1(ch);
   ch -= 'a' - 10;
   count++;
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (count > 0)
   {
    --count;
    val >>= 4;
    putx1(8);
    putx1(' ');
    putx1(8);
   }
  }
  else if (ch == ' ')
  {
   putx1(ch);
   break;
  }
  else if (ch == 13)
   break;
  else
   continue;
  val <<= 4;
  val += ch;
 }
 return(count != 0);
}

#define MAXDIG 10		/* maximum input digits */

#if 1

unsigned char getnum()
{
 char ch;			/* input character */
 char chbuf[MAXDIG];		/* input digit buffer */
 unsigned char chidx;		/* input character index */
 unsigned char count;		/* input character count */
 char neg;			/* negative flag */
 char hex;			/* hex flag */

 neg = 0;
 hex = 0;
 val = 0;
 chidx = 0;
 count = 0;
 while (1)
 {
  ch = getx();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   if (chidx < MAXDIG)
   {
    putx(ch);
    chbuf[chidx] = ch - '0';
    chidx++;
   }
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   if (chidx < MAXDIG)
   {
    hex = 1;
    putx(ch);
    chbuf[chidx] = ch - 'a' + 10;
    chidx++;
   }
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (chidx > 0)
   {
    --chidx;
    putx(8);
    putx(' ');
    putx(8);
   }
  }
  else if ((ch == 13)
       ||  (ch == ' '))
  {
   if (hex)
   {
    while (count < chidx)
    {
     val = (val << 4) + chbuf[count];
     count++;
    }
   }
   else
   {
    while (count < chidx)
    {
     val = val * 10 + chbuf[count];
     count++;
    }
   }
   if (neg)
    val = -val;
   return(count);
  }
  else if (chidx == 0)
  {
   if (ch == '-')
   {
    putx(ch);
    neg = 1;
   }
   else if (ch == 'x')
   {
    putx(ch);
    hex = 1;
   }
  }
  else
   printf("%d ",ch);
 }
}

#else

unsigned char getnum()
{
 char ch;
 char chbuf[MAXDIG];		/* input digit buffer */
 int chidx;			/* input character index */
 int count;			/* input character count */

 putx(' ');
 val = 0;
 chidx = 0;
 count = 0;
 while (chidx < 10)
 {
  ch = getx();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   if (chidx < MAXDIG)
   {
    putx(ch);
    chbuf[chidx] = ch - '0';
    chidx++;
   }
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (chidx > 0)
   {
    --chidx;
    putx(8);
    putx(' ');
    putx(8);
   }
  }
  else if ((ch == 13)
       ||  (ch == ' '))
  {
   while (count < chidx)
   {
    val = val * 10 + chbuf[count];
    count++;
   }
   return(count);
  }
 }
}

#endif

unsigned char getfloat()
{
 char chbuf[MAXDIG];		/* input digit buffer */
 
 char len = getstr(chbuf,sizeof(chbuf));
 if (len != 0)
 {
  fVal = atof(chbuf);
  return(1);
 }
 return(0);
}

unsigned char getnum1()
{
 char chbuf[MAXDIG];		/* input digit buffer */
 
 char len = getstr1(chbuf,sizeof(chbuf));
 if (len != 0)
 {
  char *p = chbuf;
  for (int i = 0; i < len; i++)
  {
   char ch = *p++;
   if (ch == '.')
   {
    fVal = atof(chbuf);
    return(FLOAT_VAL);
   }
   if ((ch == 'x') || (ch == 'X'))
   {
    char *endptr;
    val = strtol(p,&endptr,16);
    return(INT_VAL);
   }
  }
  val = atoi(chbuf);
  return(INT_VAL);
 }
 return(NO_VAL);
}

char getstr(char *buf, int bufLen)
{
 int len = 0;
 char *p;
 char ch;
 p = buf;
 while (1)
 {
  ch = getx();
  if ((ch == '\n') || (ch == '\r'))
  {
   if (len < bufLen)
   {
    *p++ = 0;
   }
   newline();
   break;
  }
  else if ((ch == 8) || (ch == 127))
  {
   if (len > 0)
   {
    --len;
    --p;
    putx(8);
    putx(' ');
    putx(8);
   }
  }
  else
  {
   if (len < bufLen)
   {
    putx(ch);
    *p++ = ch;
    len++;
   }
  }
 }
 return(len);
}

char getstr1(char *buf, int bufLen)
{
 int len = 0;
 char *p;
 char ch;
 p = buf;
 while (1)
 {
  ch = getx1();
  if ((ch == ' ') || (ch == '\n'))
  {
   putx1(ch);
   if (ch == '\n')
    putx1('\r');
   if (len < bufLen)
   {
    *p++ = 0;
   }
   break;
  }
  else if ((ch == 8) || (ch == 127))
  {
   if (len > 0)
   {
    --len;
    --p;
    putx1(8);
    putx1(' ');
    putx1(8);
   }
  }
  else
  {
   if (len < bufLen)
   {
    putx1(ch);
    *p++ = ch;
    len++;
   }
  }
 }
 return(len);
}

void prtbuf(unsigned char *p, int size)
{
 char col;

 col = 16;			/* number of columns */
 while (size != 0)		/* while not done */
 {
  --size;			/* count off data sent */
  if (col == 16)		/* if column 0 */
  {
   printf("%8x  ",(unsigned int) p); /* output address */
  }
  printf("%2x",*p++);		/* output value */
   --col;			/* count off a column */
  if (col)			/* if not end of line */
  {
   if ((col & 1) == 0)		/* if even column */
    putx(' ');			/* output a space */
  }
  else				/* if end of line */
  {
   col = 16;			/* reset column counter */
   if (size != 0)		/* if not done */
    newline();
  }
 }
}

void prtibuf(int16_t *p, int size)
{
 char col;

 col = 8;			/* number of columns */
 size >>= 1;			/* make into a count of integers */
 while (size != 0)		/* while not done */
 {
  --size;			/* count off data sent */
  if (col == 8)			/* if column 0 */
  {
   printf("%8x  ",(unsigned int) p); /* output address */
  }
  printf("%4x",*p++);		/* output value */
   --col;			/* count off a column */
  if (col == 0)			/* if not end of line */
  {
   col = 8;			/* reset column counter */
   if (size != 0)		/* if not done */
    newline();
  }
  else
   putx(' ');
 }
}

#if DBGMSG

void dbgmsg(char *str, int32_t val)
{
 P_DBGMSG p;

 if (dbgcnt < MAXDBGMSG)	/* if buffer not full */
 {
  dbgcnt++;			/* update message count */
  p = &dbgdata[dbgfil];		/* get place to put msg */
  dbgfil++;			/* update fill pointer */
  if (dbgfil >= MAXDBGMSG)	/* if at end */
  {
   dbgfil = 0;			/* set to zero */
  }
  p->time = HAL_GetTick();	/* save time */
  strncpy(p->str,str,sizeof(p->str)); /* save string */
  p->val = val;			/* save value */
 }
}

void dbgmsgx(char *str, char reg, int32_t val)
{
 P_DBGMSG p;

 if (dbgcnt < MAXDBGMSG)	/* if buffer not full */
 {
  dbgcnt++;			/* update message count */
  p = &dbgdata[dbgfil];		/* get place to put msg */
  dbgfil++;			/* update fill pointer */
  if (dbgfil >= MAXDBGMSG)	/* if at end */
  {
   dbgfil = 0;			/* set to zero */
  }
  char *d = p->str;
  int size = sizeof(p->str);
  while (--size >= 0)
   *d++ = *str++;
  *d++ = ' ';

  char tmp = reg;
  tmp >>= 4;
  tmp &= 0xf;
  if (tmp < 10)
   tmp += '0';
  else
   tmp += 'a' - 10;
  *d++ = tmp;

  reg &= 0xf;
  if (reg < 10)
   reg += '0';
  else
   reg += 'a' - 10;
  *d++ = reg;
  *d++ = 0;

  p->val = val;			/* save value */
 }
}

#endif

#define STDIN   0
#define STDOUT  1
#define STDERR  2
 
int __attribute__((__weak__, __section__(".libc")))
write (int handle, void *buffer, int len)
{
 int i = len;
 switch (handle)
 {
 case STDOUT:
 case STDERR:
  while (--i >= 0)
   putx(*(char *) buffer++);
  break;
 }
 return (len);
}

#endif
