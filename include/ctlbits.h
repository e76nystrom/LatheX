
// z move command bits

#define ZMSK         (7 << 0)    /* z move mask */
#define ZMOV         (1 << 0)    /* z a set distance */
#define ZJOG         (2 << 0)    /* z while cmd are present */
#define ZSYN         (3 << 0)    /* z dist sync to rotation */
#define ZMAX         (4 << 0)    /* z rapid move */
#define ZPOS         (1 << 3)    /* z in positive direction */
#define ZNEG         (0 << 3)    /* z in negative direction */
#define Z_SYN_START  (1 << 4)    /* start on sync pulse */
#define X_SYN_TAPER  (1 << 5)    /* taper on x */

// x move command bits

#define XMSK         (7 << 0)    /* xmove mask */
#define XMOV         (1 << 0)    /* x a set distance */
#define XJOG         (2 << 0)    /* x while cmd are present */
#define XSYN         (3 << 0)    /* x dist sync to rotation */
#define XMAX         (4 << 0)    /* x rapid move */
#define XPOS         (1 << 3)    /* x in positive direction */
#define XNEG         (0 << 3)    /* x in negative direction */
#define Z_SYN_TAPER  (1 << 5)    /* taper on z */

// feed types

#define FEED_PITCH   0           /* feed inch per rev */
#define FEED_TPI     1           /* feed threads per inch */
#define FEED_METRIC  2           /* feed mm per rev */

// turn control bits

#define TURNSYN      (1 << 0)    /* turn with sync motion */
#define TURNCONT     (1 << 1)    /* cont turning operation */

// taper control bits

#define TAPERX       (1 << 0)    /* taper x axis */
#define TAPERZ       (1 << 1)    /* taper z axis */
#define TAPEROUT     (1 << 2)    /* one taper out, zero in */

// thread control bits

#define THREAD       (1 << 0)    /* threading enabled */
#define TINTERNAL    (1 << 1)    /* internal threads */

// debug control bits

#define DBGPASS      (1 << 0)    /* pause before each pass */
#define DBGEND       (1 << 1)    /* pause at end of a pass */
#define DBGSEQ       (1 << 2)    /* generate sequence data */
