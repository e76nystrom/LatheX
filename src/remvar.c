#if !defined(INCLUDE)
#include <stdint.h>          /* For uint16_t definition                       */
#define EXT
#endif

#include "remvardef.h"
#include "ctlbits.h"
#include "ctlstates.h"

EXT char print;			/* print flags */

EXT char cmdStop;		/* command stop flag */
EXT char cmdPause;		/* pause current operation */

typedef struct
{
 void *p;			/* pointer to parameter */
 char size;			/* parameter size */
} T_PARM, *P_PARM;

#define PARM(x) {(void *) &x,sizeof(x)}
