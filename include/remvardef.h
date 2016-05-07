
// phase parameters

 EXT int16_t phase;             /* 0x00 encoder counts per rev */

// z synchronized motion parameters

 EXT int32_t sdx;               /* 0x01 synchronized dx */
 EXT int32_t sdyini;            /* 0x02 synchronized initial dy */
 EXT int32_t sdy;               /* 0x03 synchronized final dy */
 EXT int32_t sd;                /* 0x04 synchronized d */
 EXT int32_t sincr1;            /* 0x05 synchronized incr1 */
 EXT int32_t sincr2;            /* 0x06 synchronized incr2 */
 EXT int16_t saccel;            /* 0x07 synchronized accel rate */
 EXT int32_t saclclks;          /* 0x08 synchronized accel clocks */

// taper parameters

 EXT int32_t tdx;               /* 0x09 taper dx */
 EXT int32_t tdy;               /* 0x0a taper dy */
 EXT int32_t td;                /* 0x0b taper d */
 EXT int32_t tincr1;            /* 0x0c taper incr1 */
 EXT int32_t tincr2;            /* 0x0d taper incr2 */

// z move and location

 EXT int32_t zlocin;            /* 0x0e received z location */
 EXT int32_t zdistin;           /* 0x0f received z distance to move */
 EXT int32_t zdist;             /* 0x10 z move distance */
 EXT int32_t zloc;              /* 0x11 z location */
 EXT int32_t zstart;            /* 0x12 z start */
 EXT int32_t zend;              /* 0x13 z end */
 EXT int32_t zcur;              /* 0x14 z current location */
 EXT int32_t zref;              /* 0x15 z reference */
 EXT int32_t ztotfeed;          /* 0x16 z total feed */
 EXT int32_t zfeed;             /* 0x17 z feed per pass */
 EXT int32_t zretract;          /* 0x18 z retract value */
 EXT int32_t zrtcloc;           /* 0x19 z retract location */

// z unsynchronized motion

 EXT int32_t zfreq;             /* 0x1a z frequency count */
 EXT int32_t zdx;               /* 0x1b z move dx value */
 EXT int32_t zd;                /* 0x1c z move d value */
 EXT int32_t zincr1;            /* 0x1d z move incr1 value */
 EXT int32_t zincr2;            /* 0x1e z move incr2 value */
 EXT int32_t zdyini;            /* 0x1f z move initial dy value */
 EXT int32_t zdyjog;            /* 0x20 z move jog dy value */
 EXT int32_t zdymax;            /* 0x21 z move max dy value */
 EXT int32_t zaccel;            /* 0x22 z move accel rate */
 EXT int32_t zacljog;           /* 0x23 z move jog accel clocks */
 EXT int32_t zaclrun;           /* 0x24 z move run accel clocks */
 EXT int32_t zaclmax;           /* 0x25 z move max accel clocks */
 EXT int32_t zbacklash;         /* 0x26 z backlash */
 EXT uint16_t zctlreg;          /* 0x27 z control register */

// x move and location

 EXT int32_t xlocin;            /* 0x28 received x location */
 EXT int32_t xdistin;           /* 0x29 received x distance to move */
 EXT int32_t xdist;             /* 0x2a x move distance */
 EXT int32_t xloc;              /* 0x2b x location */
 EXT int32_t xstart;            /* 0x2c x start */
 EXT int32_t xend;              /* 0x2d x end */
 EXT int32_t xcur;              /* 0x2e x current location */
 EXT int32_t xref;              /* 0x2f x reference */
 EXT int32_t xtotfeed;          /* 0x30 x total feed */
 EXT int32_t xfeed;             /* 0x31 x feed per pass */
 EXT int32_t xretract;          /* 0x32 x retract value */
 EXT int32_t xrtcloc;           /* 0x33 x retract location */

// x unsynchronized motion

 EXT int32_t xfreq;             /* 0x34 x frequency count */
 EXT int32_t xdx;               /* 0x35 x move dx value */
 EXT int32_t xdyini;            /* 0x36 x move initial dy value */
 EXT int32_t xd;                /* 0x37 x move d value */
 EXT int32_t xincr1;            /* 0x38 x move incr1 value */
 EXT int32_t xincr2;            /* 0x39 x move incr2 value */
 EXT int32_t xdyjog;            /* 0x3a x move jog dy value */
 EXT int32_t xdymax;            /* 0x3b x move max dy value */
 EXT int32_t xaccel;            /* 0x3c x move accel rate */
 EXT int32_t xacljog;           /* 0x3d x move jog accel clocks */
 EXT int32_t xaclrun;           /* 0x3e x move run accel clocks */
 EXT int32_t xaclmax;           /* 0x3f x move max accel clocks */
 EXT int32_t xbacklash;         /* 0x40 x backlash */
 EXT uint16_t xctlreg;          /* 0x41 x control register */

// threading

 EXT int32_t thtan;             /* 0x42 tangent of thread angle */
 EXT int16_t thfeed;            /* 0x43 threading feed */
 EXT int16_t thzoffset;         /* 0x44 threading z offset */

// feed index

 EXT int16_t feedidx;           /* 0x45 threading feed table index */

// pass count parameters

 EXT int16_t passes;            /* 0x46 total number of passes */
 EXT int16_t spassint;          /* 0x47 spring pass interval */
 EXT int16_t spasses;           /* 0x48 number of spring passes */

// pass counters

 EXT int16_t curpass;           /* 0x49 current pass */
 EXT int16_t spassctr;          /* 0x4a spring pass counter */
 EXT int16_t spring;            /* 0x4b current spring pass */

// feed direction

 EXT char feeddir;              /* 0x4c feed direction */
 EXT char feedlimit;            /* 0x4d feed limit */

// control registers

 EXT int16_t trnctl;            /* 0x4e turn control register */
 EXT int16_t taperctlf;         /* 0x4f taper control register */
 EXT int16_t threadctl;         /* 0x50 thread control register */

// state variables

 EXT char zstate;               /* 0x51 z state */
 EXT char xstate;               /* 0x52 x state */
 EXT char tstate;               /* 0x53 turn state */
 EXT char fstate;               /* 0x54 face state */

// debug registers

 EXT int16_t dbgreg;            /* 0x55 debug register */

// limit registers

 EXT int32_t zlim;              /* 0x56  */
 EXT int32_t pstate;            /* 0x57  */

// spindle parameters

 EXT int16_t spinSteps;         /* 0x58 spindle motor steps */
 EXT int16_t spinMicro;         /* 0x59 spindle micro steps */
 EXT float spinMinRpm;          /* 0x5a spindle minimum rpm */
 EXT float spinMaxRpm;          /* 0x5b spindle maxmum rpm */
 EXT float spinAccelTime;       /* 0x5c spindle accel time */

// z axis parameters

 EXT float zPitch;              /* 0x5d z axis leadscrew pitch */
 EXT float zRatio;              /* 0x5e z axis ratio */
 EXT int16_t zMicro;            /* 0x5f z axis micro steps */
 EXT int16_t zMotor;            /* 0x60 z axis motor steps */
 EXT float zAccel;              /* 0x61 z axis acceleration */
 EXT float zBacklash;           /* 0x62 z axis backlash */

// x axis parameters

 EXT float xPitch;              /* 0x63 x axis leadscrew pitch */
 EXT float xRatio;              /* 0x64 x axis ratio */
 EXT int16_t xMicro;            /* 0x65 x axis micro steps */
 EXT int16_t xMotor;            /* 0x66 x axis motor steps */
 EXT float xAccel;              /* 0x67 x axis acceleration */
 EXT float xBacklash;           /* 0x68 x axis backlash */

// z move parameters

 EXT float zMoveMin;            /* 0x69 z move min speed */
 EXT float zMoveMax;            /* 0x6a z move max speed */

// z jog parameters

 EXT float zJogMin;             /* 0x6b z jog min speed */
 EXT float zJogMax;             /* 0x6c z jog max speed */

// x move parameters

 EXT float xMoveMin;            /* 0x6d x move min speed */
 EXT float xMoveMax;            /* 0x6e x move max speed */

// x jog parameters

 EXT float xJogMin;             /* 0x6f x jog min speed */
 EXT float xJogMax;             /* 0x70 x jog max speed */

// pass information

 EXT int16_t totalPasses;       /* 0x71 total passes */
 EXT int16_t springPasses;      /* 0x72 spring passes */
 EXT int16_t springPassInt;     /* 0x73 spring pass interval */
 EXT int16_t currentPass;       /* 0x74 current passes */

// axis move values

 EXT float zMoveDist;           /* 0x75 z move distance */
 EXT int zJogDir;               /* 0x76 x jog direction */
 EXT float zSetLoc;             /* 0x77 z location to set */
 EXT int zLoc;                  /* 0x78 z location */
 EXT float xMoveDist;           /* 0x79 x move distance */
 EXT int xJogDir;               /* 0x7a x jog direction */
 EXT float xSetLoc;             /* 0x7b x location to set */
 EXT int xLoc;                  /* 0x7c x location */

// z turn/face parameters

 EXT float zStartLoc;           /* 0x7d z start */
 EXT float zEndLoc;             /* 0x7e z end */
 EXT float zRetract;            /* 0x7f z retract */
 EXT float zFeedPass;           /* 0x80 z feed per pass */

// x turn/face parameters

 EXT float xStartLoc;           /* 0x81 x start */
 EXT float xEndLoc;             /* 0x82 x end */
 EXT float xRetract;            /* 0x83 x retract */
 EXT float xFeedPass;           /* 0x84 x feed per pass */

// feed parameters

 EXT int16_t feedDir;           /* 0x85 feed direction */
 EXT int16_t feedType;          /* 0x86 feed parameter type */
 EXT float feed;                /* 0x87 feed parameter */

// taper parameters

 EXT float taperZ;              /* 0x88 z distance for taper */
 EXT float taperX;              /* 0x89 x distance for taper */
 EXT int16_t taperFlag;         /* 0x8a taper flag */

// general turn thread parameters

 EXT int16_t turnFlag;          /* 0x8b turn flag */
 EXT float threadDepth;         /* 0x8c thread depth */
 EXT float threadLastFeed;      /* 0x8d thread last feed depth */
 EXT float threadHFactor;       /* 0x8e height Factor */
 EXT float threadAngle;         /* 0x8f thread angle */
 EXT int indexPreScaler;        /* 0x90 index prescaler */
 EXT int indexPeriod;           /* 0x91 index period */
 EXT int16_t encPreScaler;      /* 0x92 encoder prescaler */
 EXT int16_t encTimer;          /* 0x93 encoder timer counts */
 EXT int16_t encMax;            /* 0x94 encoder counts per revolution */
 EXT int encRunCount;           /* 0x95 encoder run count */
 EXT int16_t encCounter;        /* 0x96 encoder count in rev */
 EXT int32_t encRevCounter;     /* 0x97 encoder revolution counter */
 EXT int16_t maxParm;           /* 0x98 maximum parameter */
