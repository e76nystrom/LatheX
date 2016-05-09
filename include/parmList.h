enum PARM
{

// phase parameters

 PRMPHASE,                      /* 0x00 encoder counts per rev */

// z synchronized motion parameters

 PRMSDX,                        /* 0x01 synchronized dx */
 PRMSDYINI,                     /* 0x02 synchronized initial dy */
 PRMSDY,                        /* 0x03 synchronized final dy */
 PRMSD,                         /* 0x04 synchronized d */
 PRMSINCR1,                     /* 0x05 synchronized incr1 */
 PRMSINCR2,                     /* 0x06 synchronized incr2 */
 PRMSACCEL,                     /* 0x07 synchronized accel rate */
 PRMSACLCLKS,                   /* 0x08 synchronized accel clocks */

// taper parameters

 PRMTDX,                        /* 0x09 taper dx */
 PRMTDY,                        /* 0x0a taper dy */
 PRMTD,                         /* 0x0b taper d */
 PRMTINCR1,                     /* 0x0c taper incr1 */
 PRMTINCR2,                     /* 0x0d taper incr2 */

// z move and location

 PRMZLOCIN,                     /* 0x0e received z location */
 PRMZDISTIN,                    /* 0x0f received z distance to move */
 PRMZDIST,                      /* 0x10 z move distance */
 PRMZLOC,                       /* 0x11 z location */
 PRMZSTART,                     /* 0x12 z start */
 PRMZEND,                       /* 0x13 z end */
 PRMZCUR,                       /* 0x14 z current location */
 PRMZREF,                       /* 0x15 z reference */
 PRMZTOTFEED,                   /* 0x16 z total feed */
 PRMZFEED,                      /* 0x17 z feed per pass */
 PRMZRETRACT,                   /* 0x18 z retract value */
 PRMZRTCLOC,                    /* 0x19 z retract location */

// z unsynchronized motion

 PRMZFREQ,                      /* 0x1a z frequency count */
 PRMZDX,                        /* 0x1b z move dx value */
 PRMZD,                         /* 0x1c z move d value */
 PRMZINCR1,                     /* 0x1d z move incr1 value */
 PRMZINCR2,                     /* 0x1e z move incr2 value */
 PRMZDYINI,                     /* 0x1f z move initial dy value */
 PRMZDYJOG,                     /* 0x20 z move jog dy value */
 PRMZDYMAX,                     /* 0x21 z move max dy value */
 PRMZACCEL,                     /* 0x22 z move accel rate */
 PRMZACLJOG,                    /* 0x23 z move jog accel clocks */
 PRMZACLRUN,                    /* 0x24 z move run accel clocks */
 PRMZACLMAX,                    /* 0x25 z move max accel clocks */
 PRMZBACKLASH,                  /* 0x26 z backlash */
 PRMZCTLREG,                    /* 0x27 z control register */

// x move and location

 PRMXLOCIN,                     /* 0x28 received x location */
 PRMXDISTIN,                    /* 0x29 received x distance to move */
 PRMXDIST,                      /* 0x2a x move distance */
 PRMXLOC,                       /* 0x2b x location */
 PRMXSTART,                     /* 0x2c x start */
 PRMXEND,                       /* 0x2d x end */
 PRMXCUR,                       /* 0x2e x current location */
 PRMXREF,                       /* 0x2f x reference */
 PRMXTOTFEED,                   /* 0x30 x total feed */
 PRMXFEED,                      /* 0x31 x feed per pass */
 PRMXRETRACT,                   /* 0x32 x retract value */
 PRMXRTCLOC,                    /* 0x33 x retract location */

// x unsynchronized motion

 PRMXFREQ,                      /* 0x34 x frequency count */
 PRMXDX,                        /* 0x35 x move dx value */
 PRMXDYINI,                     /* 0x36 x move initial dy value */
 PRMXD,                         /* 0x37 x move d value */
 PRMXINCR1,                     /* 0x38 x move incr1 value */
 PRMXINCR2,                     /* 0x39 x move incr2 value */
 PRMXDYJOG,                     /* 0x3a x move jog dy value */
 PRMXDYMAX,                     /* 0x3b x move max dy value */
 PRMXACCEL,                     /* 0x3c x move accel rate */
 PRMXACLJOG,                    /* 0x3d x move jog accel clocks */
 PRMXACLRUN,                    /* 0x3e x move run accel clocks */
 PRMXACLMAX,                    /* 0x3f x move max accel clocks */
 PRMXBACKLASH,                  /* 0x40 x backlash */
 PRMXCTLREG,                    /* 0x41 x control register */

// threading

 PRMTHTAN,                      /* 0x42 tangent of thread angle */
 PRMTHFEED,                     /* 0x43 threading feed */
 PRMTHZOFFSET,                  /* 0x44 threading z offset */

// feed index

 PRMFEEDIDX,                    /* 0x45 threading feed table index */

// pass count parameters

 PRMPASSES,                     /* 0x46 total number of passes */
 PRMSPASSINT,                   /* 0x47 spring pass interval */
 PRMSPASSES,                    /* 0x48 number of spring passes */

// pass counters

 PRMCURPASS,                    /* 0x49 current pass */
 PRMSPASSCTR,                   /* 0x4a spring pass counter */
 PRMSPRING,                     /* 0x4b current spring pass */

// feed direction

 PRMFEEDDIR,                    /* 0x4c feed direction */
 PRMFEEDLIMIT,                  /* 0x4d feed limit */

// control registers

 PRMTRNCTL,                     /* 0x4e turn control register */
 PRMTAPERCTLF,                  /* 0x4f taper control register */
 PRMTHREADCTL,                  /* 0x50 thread control register */

// state variables

 PRMZSTATE,                     /* 0x51 z state */
 PRMXSTATE,                     /* 0x52 x state */
 PRMTSTATE,                     /* 0x53 turn state */
 PRMFSTATE,                     /* 0x54 face state */

// debug registers

 PRMDBGREG,                     /* 0x55 debug register */

// limit registers

 PRMZLIM,                       /* 0x56  */
 PRMPSTATE,                     /* 0x57  */

// spindle parameters

 SPIN_STEPS,                    /* 0x58 spindle motor steps */
 SPIN_MICRO,                    /* 0x59 spindle micro steps */
 SPIN_MIN_RPM,                  /* 0x5a spindle minimum rpm */
 SPIN_MAX_RPM,                  /* 0x5b spindle maxmum rpm */
 SPIN_ACCEL_TIME,               /* 0x5c spindle accel time */

// z axis parameters

 Z_PITCH,                       /* 0x5d z axis leadscrew pitch */
 Z_RATIO,                       /* 0x5e z axis ratio */
 Z_MICRO,                       /* 0x5f z axis micro steps */
 Z_MOTOR,                       /* 0x60 z axis motor steps */
 Z_ACCEL,                       /* 0x61 z axis acceleration */
 Z_BACKLASH,                    /* 0x62 z axis backlash */

// x axis parameters

 X_PITCH,                       /* 0x63 x axis leadscrew pitch */
 X_RATIO,                       /* 0x64 x axis ratio */
 X_MICRO,                       /* 0x65 x axis micro steps */
 X_MOTOR,                       /* 0x66 x axis motor steps */
 X_ACCEL,                       /* 0x67 x axis acceleration */
 X_BACKLASH,                    /* 0x68 x axis backlash */

// z move parameters

 Z_MOVE_MIN,                    /* 0x69 z move min speed */
 Z_MOVE_MAX,                    /* 0x6a z move max speed */

// z jog parameters

 Z_JOG_MIN,                     /* 0x6b z jog min speed */
 Z_JOG_MAX,                     /* 0x6c z jog max speed */

// x move parameters

 X_MOVE_MIN,                    /* 0x6d x move min speed */
 X_MOVE_MAX,                    /* 0x6e x move max speed */

// x jog parameters

 X_JOG_MIN,                     /* 0x6f x jog min speed */
 X_JOG_MAX,                     /* 0x70 x jog max speed */

// pass information

 TOTAL_PASSES,                  /* 0x71 total passes */
 SPRING_PASSES,                 /* 0x72 spring passes */
 SPRING_PASS_INT,               /* 0x73 spring pass interval */
 CURRENT_PASS,                  /* 0x74 current passes */

// axis move values

 Z_MOVE_DIST,                   /* 0x75 z move distance */
 Z_JOG_DIR,                     /* 0x76 x jog direction */
 Z_SET_LOC,                     /* 0x77 z location to set */
 Z_LOC,                         /* 0x78 z location */
 X_MOVE_DIST,                   /* 0x79 x move distance */
 X_JOG_DIR,                     /* 0x7a x jog direction */
 X_SET_LOC,                     /* 0x7b x location to set */
 X_LOC,                         /* 0x7c x location */

// z turn/face parameters

 Z_START_LOC,                   /* 0x7d z start */
 Z_END_LOC,                     /* 0x7e z end */
 Z_RETRACT,                     /* 0x7f z retract */
 Z_FEED_PASS,                   /* 0x80 z feed per pass */

// x turn/face parameters

 X_START_LOC,                   /* 0x81 x start */
 X_END_LOC,                     /* 0x82 x end */
 X_RETRACT,                     /* 0x83 x retract */
 X_FEED_PASS,                   /* 0x84 x feed per pass */

// feed parameters

 FEED_DIR,                      /* 0x85 feed direction */
 FEED_TYPE,                     /* 0x86 feed parameter type */
 FEED,                          /* 0x87 feed parameter */

// taper parameters

 TAPER_Z,                       /* 0x88 z distance for taper */
 TAPER_X,                       /* 0x89 x distance for taper */
 TAPER_FLAG,                    /* 0x8a taper flag */

// general turn thread parameters

 TURN_FLAG,                     /* 0x8b turn flag */
 THREAD_DEPTH,                  /* 0x8c thread depth */
 THREAD_LAST_FEED,              /* 0x8d thread last feed depth */
 THREAD_H_FACTOR,               /* 0x8e height Factor */
 THREAD_ANGLE,                  /* 0x8f thread angle */
 INDEX_PRE_SCALER,              /* 0x90 index prescaler */
 INDEX_PERIOD,                  /* 0x91 index period */

// encoder counts per revolution

 ENC_MAX,                       /* 0x92 encoder counts per revolution */

// test encoder setup variables

 ENC_PRE_SCALER,                /* 0x93 encoder prescaler */
 ENC_TIMER,                     /* 0x94 encoder timer counts */
 ENC_RUN_COUNT,                 /* 0x95 encoder run count */

// test encoder status variables

 ENC_RUN,                       /* 0x96 encoder running flag */
 ENC_COUNTER,                   /* 0x97 encoder count in rev */
 ENC_REV_COUNTER,               /* 0x98 encoder revolution counter */

// measured spindle speed

 RPM,                           /* 0x99 current rpm */

// xilinx frequency variables

 X_FREQUENCY,                   /* 0x9a xilinx clock frequency */
 FREQ_MULT,                     /* 0x9b frequency multiplier */

// max parameter number

 MAX_PARM,                      /* 0x9c maximum parameter */
};
