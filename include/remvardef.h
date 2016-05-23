
// spindle parameters

 EXT int16_t spinSteps;         /* 0x00 spindle motor steps */
 EXT int16_t spinMicro;         /* 0x01 spindle micro steps */
 EXT float spinMinRpm;          /* 0x02 spindle minimum rpm */
 EXT float spinMaxRpm;          /* 0x03 spindle maxmum rpm */
 EXT float spinAccelTime;       /* 0x04 spindle accel time */
 EXT char spinDirFlag;          /* 0x05 spindle invert direction */

// z axis parameters

 EXT float zPitch;              /* 0x06 z axis leadscrew pitch */
 EXT float zRatio;              /* 0x07 z axis ratio */
 EXT int16_t zMicro;            /* 0x08 z axis micro steps */
 EXT int16_t zMotor;            /* 0x09 z axis motor steps */
 EXT float zAccel;              /* 0x0a z axis acceleration */
 EXT float zBacklash;           /* 0x0b z axis backlash */
 EXT char zDirFlag;             /* 0x0c z invert direction */

// x axis parameters

 EXT float xPitch;              /* 0x0d x axis leadscrew pitch */
 EXT float xRatio;              /* 0x0e x axis ratio */
 EXT int16_t xMicro;            /* 0x0f x axis micro steps */
 EXT int16_t xMotor;            /* 0x10 x axis motor steps */
 EXT float xAccel;              /* 0x11 x axis acceleration */
 EXT float xBacklash;           /* 0x12 x axis backlash */
 EXT char xDirFlag;             /* 0x13 x invert direction */

// z move parameters

 EXT float zMoveMin;            /* 0x14 z move min speed */
 EXT float zMoveMax;            /* 0x15 z move max speed */

// z jog parameters

 EXT float zJogMin;             /* 0x16 z jog min speed */
 EXT float zJogMax;             /* 0x17 z jog max speed */

// x move parameters

 EXT float xMoveMin;            /* 0x18 x move min speed */
 EXT float xMoveMax;            /* 0x19 x move max speed */

// x jog parameters

 EXT float xJogMin;             /* 0x1a x jog min speed */
 EXT float xJogMax;             /* 0x1b x jog max speed */

// pass information

 EXT int16_t totalPasses;       /* 0x1c total passes */
 EXT int16_t springPasses;      /* 0x1d spring passes */
 EXT int16_t springPassInt;     /* 0x1e spring pass interval */
 EXT int16_t currentPass;       /* 0x1f current passes */

// axis move values

 EXT float zMoveDist;           /* 0x20 z move distance */
 EXT float zMovePos;            /* 0x21 z move position */
 EXT int zJogDir;               /* 0x22 x jog direction */
 EXT float zSetLoc;             /* 0x23 z location to set */
 EXT int zLoc;                  /* 0x24 z location */
 EXT int zFlag;                 /* 0x25 z move flag */
 EXT float xMoveDist;           /* 0x26 x move distance */
 EXT float xMovePos;            /* 0x27 x move position */
 EXT int xJogDir;               /* 0x28 x jog direction */
 EXT float xSetLoc;             /* 0x29 x location to set */
 EXT int xLoc;                  /* 0x2a x location */
 EXT int xFlag;                 /* 0x2b x move flag */
 EXT int16_t feedType;          /* 0x2c feed parameter type */
 EXT float feed;                /* 0x2d feed parameter */
 EXT int indexPreScaler;        /* 0x2e index prescaler */
 EXT int indexPeriod;           /* 0x2f index period */

// encoder counts per revolution

 EXT uint16_t encMax;           /* 0x30 encoder counts per revolution */

// test encoder setup variables

 EXT char encEnable;            /* 0x31 encoder enable flag */
 EXT uint16_t encPreScaler;     /* 0x32 encoder prescaler */
 EXT uint16_t encTimer;         /* 0x33 encoder timer counts */
 EXT int encRunCount;           /* 0x34 encoder run count */

// test encoder status variables

 EXT char encRun;               /* 0x35 encoder running flag */
 EXT int16_t encCounter;        /* 0x36 encoder count in rev */
 EXT int32_t encRevCounter;     /* 0x37 encoder revolution counter */

// measured spindle speed

 EXT int16_t rpm;               /* 0x38 current rpm */

// xilinx frequency variables

 EXT int32_t xFrequency;        /* 0x39 xilinx clock frequency */
 EXT int16_t freqMult;          /* 0x3a frequency multiplier */

// xilinx configuration register

 EXT int16_t xCfgReg;           /* 0x3b xilinx configuration register */

// max parameter number

 EXT int16_t maxParm;           /* 0x3c maximum parameter */
