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
 Z_MOVE_POS,                    /* 0x1e z move position */
 Z_JOG_DIR,                     /* 0x1f x jog direction */
 Z_SET_LOC,                     /* 0x20 z location to set */
 Z_LOC,                         /* 0x21 z location */
 Z_Flag,                        /* 0x22 z move flag */
 X_MOVE_DIST,                   /* 0x23 x move distance */
 X_MOVE_POS,                    /* 0x24 x move position */
 X_JOG_DIR,                     /* 0x25 x jog direction */
 X_SET_LOC,                     /* 0x26 x location to set */
 X_LOC,                         /* 0x27 x location */
 X_Flag,                        /* 0x28 x move flag */
 INDEX_PRE_SCALER,              /* 0x29 index prescaler */
 INDEX_PERIOD,                  /* 0x2a index period */

// encoder counts per revolution

 ENC_MAX,                       /* 0x2b encoder counts per revolution */

// test encoder setup variables

 ENC_ENABLE,                    /* 0x2c encoder enable flag */
 ENC_PRE_SCALER,                /* 0x2d encoder prescaler */
 ENC_TIMER,                     /* 0x2e encoder timer counts */
 ENC_RUN_COUNT,                 /* 0x2f encoder run count */

// test encoder status variables

 ENC_RUN,                       /* 0x30 encoder running flag */
 ENC_COUNTER,                   /* 0x31 encoder count in rev */
 ENC_REV_COUNTER,               /* 0x32 encoder revolution counter */

// measured spindle speed

 RPM,                           /* 0x33 current rpm */

// xilinx frequency variables

 X_FREQUENCY,                   /* 0x34 xilinx clock frequency */
 FREQ_MULT,                     /* 0x35 frequency multiplier */

// xilinx configuration register

 X_CFG_REG,                     /* 0x36 xilinx configuration register */

// max parameter number

 MAX_PARM,                      /* 0x37 maximum parameter */
};
