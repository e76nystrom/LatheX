T_PARM remparm[] =
{

// phase parameters

 PARM(phase),                   /* 0x00 encoder counts per rev */

// z synchronized motion parameters

 PARM(sdx),                     /* 0x01 synchronized dx */
 PARM(sdyini),                  /* 0x02 synchronized initial dy */
 PARM(sdy),                     /* 0x03 synchronized final dy */
 PARM(sd),                      /* 0x04 synchronized d */
 PARM(sincr1),                  /* 0x05 synchronized incr1 */
 PARM(sincr2),                  /* 0x06 synchronized incr2 */
 PARM(saccel),                  /* 0x07 synchronized accel rate */
 PARM(saclclks),                /* 0x08 synchronized accel clocks */

// taper parameters

 PARM(tdx),                     /* 0x09 taper dx */
 PARM(tdy),                     /* 0x0a taper dy */
 PARM(td),                      /* 0x0b taper d */
 PARM(tincr1),                  /* 0x0c taper incr1 */
 PARM(tincr2),                  /* 0x0d taper incr2 */

// z move and location

 PARM(zlocin),                  /* 0x0e received z location */
 PARM(zdistin),                 /* 0x0f received z distance to move */
 PARM(zdist),                   /* 0x10 z move distance */
 PARM(zloc),                    /* 0x11 z location */
 PARM(zstart),                  /* 0x12 z start */
 PARM(zend),                    /* 0x13 z end */
 PARM(zcur),                    /* 0x14 z current location */
 PARM(zref),                    /* 0x15 z reference */
 PARM(ztotfeed),                /* 0x16 z total feed */
 PARM(zfeed),                   /* 0x17 z feed per pass */
 PARM(zretract),                /* 0x18 z retract value */
 PARM(zrtcloc),                 /* 0x19 z retract location */

// z unsynchronized motion

 PARM(zfreq),                   /* 0x1a z frequency count */
 PARM(zdx),                     /* 0x1b z move dx value */
 PARM(zd),                      /* 0x1c z move d value */
 PARM(zincr1),                  /* 0x1d z move incr1 value */
 PARM(zincr2),                  /* 0x1e z move incr2 value */
 PARM(zdyini),                  /* 0x1f z move initial dy value */
 PARM(zdyjog),                  /* 0x20 z move jog dy value */
 PARM(zdymax),                  /* 0x21 z move max dy value */
 PARM(zaccel),                  /* 0x22 z move accel rate */
 PARM(zacljog),                 /* 0x23 z move jog accel clocks */
 PARM(zaclrun),                 /* 0x24 z move run accel clocks */
 PARM(zaclmax),                 /* 0x25 z move max accel clocks */
 PARM(zbacklash),               /* 0x26 z backlash */
 PARM(zctlreg),                 /* 0x27 z control register */

// x move and location

 PARM(xlocin),                  /* 0x28 received x location */
 PARM(xdistin),                 /* 0x29 received x distance to move */
 PARM(xdist),                   /* 0x2a x move distance */
 PARM(xloc),                    /* 0x2b x location */
 PARM(xstart),                  /* 0x2c x start */
 PARM(xend),                    /* 0x2d x end */
 PARM(xcur),                    /* 0x2e x current location */
 PARM(xref),                    /* 0x2f x reference */
 PARM(xtotfeed),                /* 0x30 x total feed */
 PARM(xfeed),                   /* 0x31 x feed per pass */
 PARM(xretract),                /* 0x32 x retract value */
 PARM(xrtcloc),                 /* 0x33 x retract location */

// x unsynchronized motion

 PARM(xfreq),                   /* 0x34 x frequency count */
 PARM(xdx),                     /* 0x35 x move dx value */
 PARM(xdyini),                  /* 0x36 x move initial dy value */
 PARM(xd),                      /* 0x37 x move d value */
 PARM(xincr1),                  /* 0x38 x move incr1 value */
 PARM(xincr2),                  /* 0x39 x move incr2 value */
 PARM(xdyjog),                  /* 0x3a x move jog dy value */
 PARM(xdymax),                  /* 0x3b x move max dy value */
 PARM(xaccel),                  /* 0x3c x move accel rate */
 PARM(xacljog),                 /* 0x3d x move jog accel clocks */
 PARM(xaclrun),                 /* 0x3e x move run accel clocks */
 PARM(xaclmax),                 /* 0x3f x move max accel clocks */
 PARM(xbacklash),               /* 0x40 x backlash */
 PARM(xctlreg),                 /* 0x41 x control register */

// threading

 PARM(thtan),                   /* 0x42 tangent of thread angle */
 PARM(thfeed),                  /* 0x43 threading feed */
 PARM(thzoffset),               /* 0x44 threading z offset */

// feed index

 PARM(feedidx),                 /* 0x45 threading feed table index */

// pass count parameters

 PARM(passes),                  /* 0x46 total number of passes */
 PARM(spassint),                /* 0x47 spring pass interval */
 PARM(spasses),                 /* 0x48 number of spring passes */

// pass counters

 PARM(curpass),                 /* 0x49 current pass */
 PARM(spassctr),                /* 0x4a spring pass counter */
 PARM(spring),                  /* 0x4b current spring pass */

// feed direction

 PARM(feeddir),                 /* 0x4c feed direction */
 PARM(feedlimit),               /* 0x4d feed limit */

// control registers

 PARM(trnctl),                  /* 0x4e turn control register */
 PARM(taperctlf),               /* 0x4f taper control register */
 PARM(threadctl),               /* 0x50 thread control register */

// state variables

 PARM(zstate),                  /* 0x51 z state */
 PARM(xstate),                  /* 0x52 x state */
 PARM(tstate),                  /* 0x53 turn state */
 PARM(fstate),                  /* 0x54 face state */

// debug registers

 PARM(dbgreg),                  /* 0x55 debug register */

// limit registers

 PARM(zlim),                    /* 0x56  */
 PARM(pstate),                  /* 0x57  */

// spindle parameters

 PARM(spinSteps),               /* 0x58 spindle motor steps */
 PARM(spinMicro),               /* 0x59 spindle micro steps */
 PARM(spinMinRpm),              /* 0x5a spindle minimum rpm */
 PARM(spinMaxRpm),              /* 0x5b spindle maxmum rpm */
 PARM(spinAccelTime),           /* 0x5c spindle accel time */

// z axis parameters

 PARM(zPitch),                  /* 0x5d z axis leadscrew pitch */
 PARM(zRatio),                  /* 0x5e z axis ratio */
 PARM(zMicro),                  /* 0x5f z axis micro steps */
 PARM(zMotor),                  /* 0x60 z axis motor steps */
 PARM(zAccel),                  /* 0x61 z axis acceleration */
 PARM(zBacklash),               /* 0x62 z axis backlash */

// x axis parameters

 PARM(xPitch),                  /* 0x63 x axis leadscrew pitch */
 PARM(xRatio),                  /* 0x64 x axis ratio */
 PARM(xMicro),                  /* 0x65 x axis micro steps */
 PARM(xMotor),                  /* 0x66 x axis motor steps */
 PARM(xAccel),                  /* 0x67 x axis acceleration */
 PARM(xBacklash),               /* 0x68 x axis backlash */

// z move parameters

 PARM(zMoveMin),                /* 0x69 z move min speed */
 PARM(zMoveMax),                /* 0x6a z move max speed */

// z jog parameters

 PARM(zJogMin),                 /* 0x6b z jog min speed */
 PARM(zJogMax),                 /* 0x6c z jog max speed */

// x move parameters

 PARM(xMoveMin),                /* 0x6d x move min speed */
 PARM(xMoveMax),                /* 0x6e x move max speed */

// x jog parameters

 PARM(xJogMin),                 /* 0x6f x jog min speed */
 PARM(xJogMax),                 /* 0x70 x jog max speed */

// pass information

 PARM(totalPasses),             /* 0x71 total passes */
 PARM(springPasses),            /* 0x72 spring passes */
 PARM(springPassInt),           /* 0x73 spring pass interval */
 PARM(currentPass),             /* 0x74 current passes */

// axis move values

 PARM(zMoveDist),               /* 0x75 z move distance */
 PARM(zJogDir),                 /* 0x76 x jog direction */
 PARM(zSetLoc),                 /* 0x77 z location to set */
 PARM(zLoc),                    /* 0x78 z location */
 PARM(xMoveDist),               /* 0x79 x move distance */
 PARM(xJogDir),                 /* 0x7a x jog direction */
 PARM(xSetLoc),                 /* 0x7b x location to set */
 PARM(xLoc),                    /* 0x7c x location */

// z turn/face parameters

 PARM(zStartLoc),               /* 0x7d z start */
 PARM(zEndLoc),                 /* 0x7e z end */
 PARM(zRetract),                /* 0x7f z retract */
 PARM(zFeedPass),               /* 0x80 z feed per pass */

// x turn/face parameters

 PARM(xStartLoc),               /* 0x81 x start */
 PARM(xEndLoc),                 /* 0x82 x end */
 PARM(xRetract),                /* 0x83 x retract */
 PARM(xFeedPass),               /* 0x84 x feed per pass */

// feed parameters

 PARM(feedDir),                 /* 0x85 feed direction */
 PARM(feedType),                /* 0x86 feed parameter type */
 PARM(feed),                    /* 0x87 feed parameter */

// taper parameters

 PARM(taperZ),                  /* 0x88 z distance for taper */
 PARM(taperX),                  /* 0x89 x distance for taper */
 PARM(taperFlag),               /* 0x8a taper flag */

// general turn thread parameters

 PARM(turnFlag),                /* 0x8b turn flag */
 PARM(threadDepth),             /* 0x8c thread depth */
 PARM(threadLastFeed),          /* 0x8d thread last feed depth */
 PARM(threadHFactor),           /* 0x8e height Factor */
 PARM(threadAngle),             /* 0x8f thread angle */
 PARM(indexPreScaler),          /* 0x90 index prescaler */
 PARM(indexPeriod),             /* 0x91 index period */
 PARM(encPreScaler),            /* 0x92 encoder prescaler */
 PARM(encTimer),                /* 0x93 encoder timer counts */
 PARM(encMax),                  /* 0x94 encoder counts per revolution */
 PARM(encRunCount),             /* 0x95 encoder run count */
 PARM(encRun),                  /* 0x96 encoder running flag */
 PARM(encCounter),              /* 0x97 encoder count in rev */
 PARM(encRevCounter),           /* 0x98 encoder revolution counter */
 PARM(maxParm),                 /* 0x99 maximum parameter */
};
