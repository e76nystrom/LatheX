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
 PARM(zJogDir),                 /* 0x1e x jog direction */
 PARM(zSetLoc),                 /* 0x1f z location to set */
 PARM(zLoc),                    /* 0x20 z location */
 PARM(xMoveDist),               /* 0x21 x move distance */
 PARM(xJogDir),                 /* 0x22 x jog direction */
 PARM(xSetLoc),                 /* 0x23 x location to set */
 PARM(xLoc),                    /* 0x24 x location */

// z turn/face parameters

 PARM(zStartLoc),               /* 0x25 z start */
 PARM(zEndLoc),                 /* 0x26 z end */
 PARM(zRetract),                /* 0x27 z retract */
 PARM(zFeedPass),               /* 0x28 z feed per pass */

// x turn/face parameters

 PARM(xStartLoc),               /* 0x29 x start */
 PARM(xEndLoc),                 /* 0x2a x end */
 PARM(xRetract),                /* 0x2b x retract */
 PARM(xFeedPass),               /* 0x2c x feed per pass */

// feed parameters

 PARM(feedDir),                 /* 0x2d feed direction */
 PARM(feedType),                /* 0x2e feed parameter type */
 PARM(feed),                    /* 0x2f feed parameter */

// taper parameters

 PARM(taperZ),                  /* 0x30 z distance for taper */
 PARM(taperX),                  /* 0x31 x distance for taper */
 PARM(taperFlag),               /* 0x32 taper flag */

// general turn thread parameters

 PARM(turnFlag),                /* 0x33 turn flag */
 PARM(threadDepth),             /* 0x34 thread depth */
 PARM(threadLastFeed),          /* 0x35 thread last feed depth */
 PARM(threadHFactor),           /* 0x36 height Factor */
 PARM(threadAngle),             /* 0x37 thread angle */
 PARM(indexPreScaler),          /* 0x38 index prescaler */
 PARM(indexPeriod),             /* 0x39 index period */

// encoder counts per revolution

 PARM(encMax),                  /* 0x3a encoder counts per revolution */

// test encoder setup variables

 PARM(encEnable),               /* 0x3b encoder enable flag */
 PARM(encPreScaler),            /* 0x3c encoder prescaler */
 PARM(encTimer),                /* 0x3d encoder timer counts */
 PARM(encRunCount),             /* 0x3e encoder run count */

// test encoder status variables

 PARM(encRun),                  /* 0x3f encoder running flag */
 PARM(encCounter),              /* 0x40 encoder count in rev */
 PARM(encRevCounter),           /* 0x41 encoder revolution counter */

// measured spindle speed

 PARM(rpm),                     /* 0x42 current rpm */

// xilinx frequency variables

 PARM(xFrequency),              /* 0x43 xilinx clock frequency */
 PARM(freqMult),                /* 0x44 frequency multiplier */

// xilinx configuration register

 PARM(xCfgReg),                 /* 0x45 xilinx configuration register */

// max parameter number

 PARM(maxParm),                 /* 0x46 maximum parameter */
};
