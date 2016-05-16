T_PARM remparm[] =
{

// spindle parameters

 PARM(spinSteps),               /* 0x00 spindle motor steps */
 PARM(spinMicro),               /* 0x01 spindle micro steps */
 PARM(spinMinRpm),              /* 0x02 spindle minimum rpm */
 PARM(spinMaxRpm),              /* 0x03 spindle maxmum rpm */
 PARM(spinAccelTime),           /* 0x04 spindle accel time */

// z axis parameters

 PARM(zPitch),                  /* 0x05 z axis leadscrew pitch */
 PARM(zRatio),                  /* 0x06 z axis ratio */
 PARM(zMicro),                  /* 0x07 z axis micro steps */
 PARM(zMotor),                  /* 0x08 z axis motor steps */
 PARM(zAccel),                  /* 0x09 z axis acceleration */
 PARM(zBacklash),               /* 0x0a z axis backlash */

// x axis parameters

 PARM(xPitch),                  /* 0x0b x axis leadscrew pitch */
 PARM(xRatio),                  /* 0x0c x axis ratio */
 PARM(xMicro),                  /* 0x0d x axis micro steps */
 PARM(xMotor),                  /* 0x0e x axis motor steps */
 PARM(xAccel),                  /* 0x0f x axis acceleration */
 PARM(xBacklash),               /* 0x10 x axis backlash */

// z move parameters

 PARM(zMoveMin),                /* 0x11 z move min speed */
 PARM(zMoveMax),                /* 0x12 z move max speed */

// z jog parameters

 PARM(zJogMin),                 /* 0x13 z jog min speed */
 PARM(zJogMax),                 /* 0x14 z jog max speed */

// x move parameters

 PARM(xMoveMin),                /* 0x15 x move min speed */
 PARM(xMoveMax),                /* 0x16 x move max speed */

// x jog parameters

 PARM(xJogMin),                 /* 0x17 x jog min speed */
 PARM(xJogMax),                 /* 0x18 x jog max speed */

// pass information

 PARM(totalPasses),             /* 0x19 total passes */
 PARM(springPasses),            /* 0x1a spring passes */
 PARM(springPassInt),           /* 0x1b spring pass interval */
 PARM(currentPass),             /* 0x1c current passes */

// axis move values

 PARM(zMoveDist),               /* 0x1d z move distance */
 PARM(zMovePos),                /* 0x1e z move position */
 PARM(zJogDir),                 /* 0x1f x jog direction */
 PARM(zSetLoc),                 /* 0x20 z location to set */
 PARM(zLoc),                    /* 0x21 z location */
 PARM(zFlag),                   /* 0x22 z move flag */
 PARM(xMoveDist),               /* 0x23 x move distance */
 PARM(xMovePos),                /* 0x24 x move position */
 PARM(xJogDir),                 /* 0x25 x jog direction */
 PARM(xSetLoc),                 /* 0x26 x location to set */
 PARM(xLoc),                    /* 0x27 x location */
 PARM(xFlag),                   /* 0x28 x move flag */
 PARM(indexPreScaler),          /* 0x29 index prescaler */
 PARM(indexPeriod),             /* 0x2a index period */

// encoder counts per revolution

 PARM(encMax),                  /* 0x2b encoder counts per revolution */

// test encoder setup variables

 PARM(encEnable),               /* 0x2c encoder enable flag */
 PARM(encPreScaler),            /* 0x2d encoder prescaler */
 PARM(encTimer),                /* 0x2e encoder timer counts */
 PARM(encRunCount),             /* 0x2f encoder run count */

// test encoder status variables

 PARM(encRun),                  /* 0x30 encoder running flag */
 PARM(encCounter),              /* 0x31 encoder count in rev */
 PARM(encRevCounter),           /* 0x32 encoder revolution counter */

// measured spindle speed

 PARM(rpm),                     /* 0x33 current rpm */

// xilinx frequency variables

 PARM(xFrequency),              /* 0x34 xilinx clock frequency */
 PARM(freqMult),                /* 0x35 frequency multiplier */

// xilinx configuration register

 PARM(xCfgReg),                 /* 0x36 xilinx configuration register */

// max parameter number

 PARM(maxParm),                 /* 0x37 maximum parameter */
};
