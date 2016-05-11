
// spindle parameters

 EXT int16_t spinSteps;         /* 0x00 spindle motor steps */
 EXT int16_t spinMicro;         /* 0x01 spindle micro steps */
 EXT float spinMinRpm;          /* 0x02 spindle minimum rpm */
 EXT float spinMaxRpm;          /* 0x03 spindle maxmum rpm */
 EXT float spinAccelTime;       /* 0x04 spindle accel time */

// z axis parameters

 EXT float zPitch;              /* 0x05 z axis leadscrew pitch */
 EXT float zRatio;              /* 0x06 z axis ratio */
 EXT int16_t zMicro;            /* 0x07 z axis micro steps */
 EXT int16_t zMotor;            /* 0x08 z axis motor steps */
 EXT float zAccel;              /* 0x09 z axis acceleration */
 EXT float zBacklash;           /* 0x0a z axis backlash */

// x axis parameters

 EXT float xPitch;              /* 0x0b x axis leadscrew pitch */
 EXT float xRatio;              /* 0x0c x axis ratio */
 EXT int16_t xMicro;            /* 0x0d x axis micro steps */
 EXT int16_t xMotor;            /* 0x0e x axis motor steps */
 EXT float xAccel;              /* 0x0f x axis acceleration */
 EXT float xBacklash;           /* 0x10 x axis backlash */

// z move parameters

 EXT float zMoveMin;            /* 0x11 z move min speed */
 EXT float zMoveMax;            /* 0x12 z move max speed */

// z jog parameters

 EXT float zJogMin;             /* 0x13 z jog min speed */
 EXT float zJogMax;             /* 0x14 z jog max speed */

// x move parameters

 EXT float xMoveMin;            /* 0x15 x move min speed */
 EXT float xMoveMax;            /* 0x16 x move max speed */

// x jog parameters

 EXT float xJogMin;             /* 0x17 x jog min speed */
 EXT float xJogMax;             /* 0x18 x jog max speed */

// pass information

 EXT int16_t totalPasses;       /* 0x19 total passes */
 EXT int16_t springPasses;      /* 0x1a spring passes */
 EXT int16_t springPassInt;     /* 0x1b spring pass interval */
 EXT int16_t currentPass;       /* 0x1c current passes */

// axis move values

 EXT float zMoveDist;           /* 0x1d z move distance */
 EXT int zJogDir;               /* 0x1e x jog direction */
 EXT float zSetLoc;             /* 0x1f z location to set */
 EXT int zLoc;                  /* 0x20 z location */
 EXT float xMoveDist;           /* 0x21 x move distance */
 EXT int xJogDir;               /* 0x22 x jog direction */
 EXT float xSetLoc;             /* 0x23 x location to set */
 EXT int xLoc;                  /* 0x24 x location */

// z turn/face parameters

 EXT float zStartLoc;           /* 0x25 z start */
 EXT float zEndLoc;             /* 0x26 z end */
 EXT float zRetract;            /* 0x27 z retract */
 EXT float zFeedPass;           /* 0x28 z feed per pass */

// x turn/face parameters

 EXT float xStartLoc;           /* 0x29 x start */
 EXT float xEndLoc;             /* 0x2a x end */
 EXT float xRetract;            /* 0x2b x retract */
 EXT float xFeedPass;           /* 0x2c x feed per pass */

// feed parameters

 EXT int16_t feedDir;           /* 0x2d feed direction */
 EXT int16_t feedType;          /* 0x2e feed parameter type */
 EXT float feed;                /* 0x2f feed parameter */

// taper parameters

 EXT float taperZ;              /* 0x30 z distance for taper */
 EXT float taperX;              /* 0x31 x distance for taper */
 EXT int16_t taperFlag;         /* 0x32 taper flag */

// general turn thread parameters

 EXT int16_t turnFlag;          /* 0x33 turn flag */
 EXT float threadDepth;         /* 0x34 thread depth */
 EXT float threadLastFeed;      /* 0x35 thread last feed depth */
 EXT float threadHFactor;       /* 0x36 height Factor */
 EXT float threadAngle;         /* 0x37 thread angle */
 EXT int indexPreScaler;        /* 0x38 index prescaler */
 EXT int indexPeriod;           /* 0x39 index period */

// encoder counts per revolution

 EXT uint16_t encMax;           /* 0x3a encoder counts per revolution */

// test encoder setup variables

 EXT char encEnable;            /* 0x3b encoder enable flag */
 EXT uint16_t encPreScaler;     /* 0x3c encoder prescaler */
 EXT uint16_t encTimer;         /* 0x3d encoder timer counts */
 EXT int encRunCount;           /* 0x3e encoder run count */

// test encoder status variables

 EXT char encRun;               /* 0x3f encoder running flag */
 EXT int16_t encCounter;        /* 0x40 encoder count in rev */
 EXT int32_t encRevCounter;     /* 0x41 encoder revolution counter */

// measured spindle speed

 EXT int16_t rpm;               /* 0x42 current rpm */

// xilinx frequency variables

 EXT int32_t xFrequency;        /* 0x43 xilinx clock frequency */
 EXT int16_t freqMult;          /* 0x44 frequency multiplier */

// xilinx configuration register

 EXT int16_t xCfgReg;           /* 0x45 xilinx configuration register */

// max parameter number

 EXT int16_t maxParm;           /* 0x46 maximum parameter */
