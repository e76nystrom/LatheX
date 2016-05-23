T_PARM remparm[] =
{

// spindle parameters

 PARM(spinSteps),               /* 0x00 spindle motor steps */
 PARM(spinMicro),               /* 0x01 spindle micro steps */
 PARM(spinMinRpm),              /* 0x02 spindle minimum rpm */
 PARM(spinMaxRpm),              /* 0x03 spindle maxmum rpm */
 PARM(spinAccelTime),           /* 0x04 spindle accel time */
 PARM(spinDirFlag),             /* 0x05 spindle invert direction */

// z axis parameters

 PARM(zPitch),                  /* 0x06 z axis leadscrew pitch */
 PARM(zRatio),                  /* 0x07 z axis ratio */
 PARM(zMicro),                  /* 0x08 z axis micro steps */
 PARM(zMotor),                  /* 0x09 z axis motor steps */
 PARM(zAccel),                  /* 0x0a z axis acceleration */
 PARM(zBacklash),               /* 0x0b z axis backlash */
 PARM(zDirFlag),                /* 0x0c z invert direction */

// x axis parameters

 PARM(xPitch),                  /* 0x0d x axis leadscrew pitch */
 PARM(xRatio),                  /* 0x0e x axis ratio */
 PARM(xMicro),                  /* 0x0f x axis micro steps */
 PARM(xMotor),                  /* 0x10 x axis motor steps */
 PARM(xAccel),                  /* 0x11 x axis acceleration */
 PARM(xBacklash),               /* 0x12 x axis backlash */
 PARM(xDirFlag),                /* 0x13 x invert direction */

// z move parameters

 PARM(zMoveMin),                /* 0x14 z move min speed */
 PARM(zMoveMax),                /* 0x15 z move max speed */

// z jog parameters

 PARM(zJogMin),                 /* 0x16 z jog min speed */
 PARM(zJogMax),                 /* 0x17 z jog max speed */

// x move parameters

 PARM(xMoveMin),                /* 0x18 x move min speed */
 PARM(xMoveMax),                /* 0x19 x move max speed */

// x jog parameters

 PARM(xJogMin),                 /* 0x1a x jog min speed */
 PARM(xJogMax),                 /* 0x1b x jog max speed */

// pass information

 PARM(totalPasses),             /* 0x1c total passes */
 PARM(springPasses),            /* 0x1d spring passes */
 PARM(springPassInt),           /* 0x1e spring pass interval */
 PARM(currentPass),             /* 0x1f current passes */

// axis move values

 PARM(zMoveDist),               /* 0x20 z move distance */
 PARM(zMovePos),                /* 0x21 z move position */
 PARM(zJogDir),                 /* 0x22 x jog direction */
 PARM(zSetLoc),                 /* 0x23 z location to set */
 PARM(zLoc),                    /* 0x24 z location */
 PARM(zFlag),                   /* 0x25 z move flag */
 PARM(xMoveDist),               /* 0x26 x move distance */
 PARM(xMovePos),                /* 0x27 x move position */
 PARM(xJogDir),                 /* 0x28 x jog direction */
 PARM(xSetLoc),                 /* 0x29 x location to set */
 PARM(xLoc),                    /* 0x2a x location */
 PARM(xFlag),                   /* 0x2b x move flag */
 PARM(feedType),                /* 0x2c feed parameter type */
 PARM(feed),                    /* 0x2d feed parameter */
 PARM(indexPreScaler),          /* 0x2e index prescaler */
 PARM(indexPeriod),             /* 0x2f index period */

// encoder counts per revolution

 PARM(encMax),                  /* 0x30 encoder counts per revolution */

// test encoder setup variables

 PARM(encEnable),               /* 0x31 encoder enable flag */
 PARM(encPreScaler),            /* 0x32 encoder prescaler */
 PARM(encTimer),                /* 0x33 encoder timer counts */
 PARM(encRunCount),             /* 0x34 encoder run count */

// test encoder status variables

 PARM(encRun),                  /* 0x35 encoder running flag */
 PARM(encCounter),              /* 0x36 encoder count in rev */
 PARM(encRevCounter),           /* 0x37 encoder revolution counter */

// measured spindle speed

 PARM(rpm),                     /* 0x38 current rpm */

// xilinx frequency variables

 PARM(xFrequency),              /* 0x39 xilinx clock frequency */
 PARM(freqMult),                /* 0x3a frequency multiplier */

// xilinx configuration register

 PARM(xCfgReg),                 /* 0x3b xilinx configuration register */

// max parameter number

 PARM(maxParm),                 /* 0x3c maximum parameter */
};
