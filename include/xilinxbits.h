
// z control register

#define ZRESET        (1 << 0)  /* reset flag */
#define ZSTART        (1 << 1)  /* start z */
#define ZSRC_SYN      (1 << 2)  /* run z synchronized */
#define ZSRC_FRQ      (0 << 2)  /* run z from clock source */
#define ZDIR_IN       (1 << 3)  /* move z in positive dir */
#define ZDIR_POS      (1 << 3)  /* move z in positive dir */
#define ZDIR_NEG      (0 << 3)  /* move z in negative dir */
#define ZSET_LOC      (1 << 4)  /* set z location */
#define ZBACKLASH     (1 << 5)  /* backlash move no pos upd */
#define ZWAIT_SYNC    (1 << 6)  /* wait for sync to start */
#define ZPULS_MULT    (1 << 7)  /* enable pulse multiplier */
#define ZENC_DIR      (1 << 8)  /* z direction from encoder */

// x control register

#define XRESET        (1 << 0)  /* x reset */
#define XSTART        (1 << 1)  /* start x */
#define XSRC_SYN      (1 << 2)  /* run x synchronized */
#define XSRC_FRQ      (0 << 2)  /* run x from clock source */
#define XDIR_IN       (1 << 3)  /* move x in positive dir */
#define XDIR_POS      (1 << 3)  /* x positive direction */
#define XDIR_NEG      (0 << 3)  /* x negative direction */
#define XSET_LOC      (1 << 4)  /* set x location */
#define XBACKLASH     (1 << 5)  /* x backlash move no pos upd */

// taper control register

#define TENA          (1 << 0)  /* taper enable */
#define TZ            (1 << 1)  /* one for taper z */
#define TX            (0 << 1)  /* zero for taper x */

// position control register

#define PRESET        (1 << 0)  /* reset position */
#define PLIMIT        (1 << 1)  /* set flag on limit reached */
#define PZERO         (1 << 2)  /* set flag on zero reached */

// configuration register

#define ZSTEP_POL     (1 << 0)  /* z step pulse polarity */
#define ZDIR_POL      (1 << 1)  /* z direction polarity */
#define XSTEP_POL     (1 << 2)  /* x step pulse polarity */
#define XDIR_POL      (1 << 3)  /* x direction polarity */
#define ENC_POL       (1 << 4)  /* encoder dir polarity */

// debug control register

#define DBG_ENA       (1 << 0)  /* enable debugging */
#define DBG_SEL       (1 << 1)  /* select dbg encoder */
#define DBG_DIR       (1 << 2)  /* debug direction */
#define DBG_COUNT     (1 << 3)  /* gen count num dbg clks */
#define DBG_INIT      (1 << 4)  /* init z modules */
#define DBG_RSYN      (1 << 5)  /* running in sync mode */
#define DBG_MOVE      (1 << 6)  /* used debug clock for move */
