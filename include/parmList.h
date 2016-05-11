enum PARM
{

// spindle parameters

 SPIN_STEPS,                    /* 0x00 spindle motor steps */
 SPIN_MICRO,                    /* 0x01 spindle micro steps */
 SPIN_MIN_RPM,                  /* 0x02 spindle minimum rpm */
 SPIN_MAX_RPM,                  /* 0x03 spindle maxmum rpm */
 SPIN_ACCEL_TIME,               /* 0x04 spindle accel time */

// z axis parameters

 Z_PITCH,                       /* 0x05 z axis leadscrew pitch */
 Z_RATIO,                       /* 0x06 z axis ratio */
 Z_MICRO,                       /* 0x07 z axis micro steps */
 Z_MOTOR,                       /* 0x08 z axis motor steps */
 Z_ACCEL,                       /* 0x09 z axis acceleration */
 Z_BACKLASH,                    /* 0x0a z axis backlash */

// x axis parameters

 X_PITCH,                       /* 0x0b x axis leadscrew pitch */
 X_RATIO,                       /* 0x0c x axis ratio */
 X_MICRO,                       /* 0x0d x axis micro steps */
 X_MOTOR,                       /* 0x0e x axis motor steps */
 X_ACCEL,                       /* 0x0f x axis acceleration */
 X_BACKLASH,                    /* 0x10 x axis backlash */

// z move parameters

 Z_MOVE_MIN,                    /* 0x11 z move min speed */
 Z_MOVE_MAX,                    /* 0x12 z move max speed */

// z jog parameters

 Z_JOG_MIN,                     /* 0x13 z jog min speed */
 Z_JOG_MAX,                     /* 0x14 z jog max speed */

// x move parameters

 X_MOVE_MIN,                    /* 0x15 x move min speed */
 X_MOVE_MAX,                    /* 0x16 x move max speed */

// x jog parameters

 X_JOG_MIN,                     /* 0x17 x jog min speed */
 X_JOG_MAX,                     /* 0x18 x jog max speed */

// pass information

 TOTAL_PASSES,                  /* 0x19 total passes */
 SPRING_PASSES,                 /* 0x1a spring passes */
 SPRING_PASS_INT,               /* 0x1b spring pass interval */
 CURRENT_PASS,                  /* 0x1c current passes */

// axis move values

 Z_MOVE_DIST,                   /* 0x1d z move distance */
 Z_JOG_DIR,                     /* 0x1e x jog direction */
 Z_SET_LOC,                     /* 0x1f z location to set */
 Z_LOC,                         /* 0x20 z location */
 X_MOVE_DIST,                   /* 0x21 x move distance */
 X_JOG_DIR,                     /* 0x22 x jog direction */
 X_SET_LOC,                     /* 0x23 x location to set */
 X_LOC,                         /* 0x24 x location */

// z turn/face parameters

 Z_START_LOC,                   /* 0x25 z start */
 Z_END_LOC,                     /* 0x26 z end */
 Z_RETRACT,                     /* 0x27 z retract */
 Z_FEED_PASS,                   /* 0x28 z feed per pass */

// x turn/face parameters

 X_START_LOC,                   /* 0x29 x start */
 X_END_LOC,                     /* 0x2a x end */
 X_RETRACT,                     /* 0x2b x retract */
 X_FEED_PASS,                   /* 0x2c x feed per pass */

// feed parameters

 FEED_DIR,                      /* 0x2d feed direction */
 FEED_TYPE,                     /* 0x2e feed parameter type */
 FEED,                          /* 0x2f feed parameter */

// taper parameters

 TAPER_Z,                       /* 0x30 z distance for taper */
 TAPER_X,                       /* 0x31 x distance for taper */
 TAPER_FLAG,                    /* 0x32 taper flag */

// general turn thread parameters

 TURN_FLAG,                     /* 0x33 turn flag */
 THREAD_DEPTH,                  /* 0x34 thread depth */
 THREAD_LAST_FEED,              /* 0x35 thread last feed depth */
 THREAD_H_FACTOR,               /* 0x36 height Factor */
 THREAD_ANGLE,                  /* 0x37 thread angle */
 INDEX_PRE_SCALER,              /* 0x38 index prescaler */
 INDEX_PERIOD,                  /* 0x39 index period */

// encoder counts per revolution

 ENC_MAX,                       /* 0x3a encoder counts per revolution */

// test encoder setup variables

 ENC_ENABLE,                    /* 0x3b encoder enable flag */
 ENC_PRE_SCALER,                /* 0x3c encoder prescaler */
 ENC_TIMER,                     /* 0x3d encoder timer counts */
 ENC_RUN_COUNT,                 /* 0x3e encoder run count */

// test encoder status variables

 ENC_RUN,                       /* 0x3f encoder running flag */
 ENC_COUNTER,                   /* 0x40 encoder count in rev */
 ENC_REV_COUNTER,               /* 0x41 encoder revolution counter */

// measured spindle speed

 RPM,                           /* 0x42 current rpm */

// xilinx frequency variables

 X_FREQUENCY,                   /* 0x43 xilinx clock frequency */
 FREQ_MULT,                     /* 0x44 frequency multiplier */

// xilinx configuration register

 X_CFG_REG,                     /* 0x45 xilinx configuration register */

// max parameter number

 MAX_PARM,                      /* 0x46 maximum parameter */
};
