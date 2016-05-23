enum PARM
{

// spindle parameters

 SPIN_STEPS,                    /* 0x00 spindle motor steps */
 SPIN_MICRO,                    /* 0x01 spindle micro steps */
 SPIN_MIN_RPM,                  /* 0x02 spindle minimum rpm */
 SPIN_MAX_RPM,                  /* 0x03 spindle maxmum rpm */
 SPIN_ACCEL_TIME,               /* 0x04 spindle accel time */
 SPIN_DIR_FLAG,                 /* 0x05 spindle invert direction */

// z axis parameters

 Z_PITCH,                       /* 0x06 z axis leadscrew pitch */
 Z_RATIO,                       /* 0x07 z axis ratio */
 Z_MICRO,                       /* 0x08 z axis micro steps */
 Z_MOTOR,                       /* 0x09 z axis motor steps */
 Z_ACCEL,                       /* 0x0a z axis acceleration */
 Z_BACKLASH,                    /* 0x0b z axis backlash */
 Z_DIR_FLAG,                    /* 0x0c z invert direction */

// x axis parameters

 X_PITCH,                       /* 0x0d x axis leadscrew pitch */
 X_RATIO,                       /* 0x0e x axis ratio */
 X_MICRO,                       /* 0x0f x axis micro steps */
 X_MOTOR,                       /* 0x10 x axis motor steps */
 X_ACCEL,                       /* 0x11 x axis acceleration */
 X_BACKLASH,                    /* 0x12 x axis backlash */
 X_DIR_FLAG,                    /* 0x13 x invert direction */

// z move parameters

 Z_MOVE_MIN,                    /* 0x14 z move min speed */
 Z_MOVE_MAX,                    /* 0x15 z move max speed */

// z jog parameters

 Z_JOG_MIN,                     /* 0x16 z jog min speed */
 Z_JOG_MAX,                     /* 0x17 z jog max speed */

// x move parameters

 X_MOVE_MIN,                    /* 0x18 x move min speed */
 X_MOVE_MAX,                    /* 0x19 x move max speed */

// x jog parameters

 X_JOG_MIN,                     /* 0x1a x jog min speed */
 X_JOG_MAX,                     /* 0x1b x jog max speed */

// pass information

 TOTAL_PASSES,                  /* 0x1c total passes */
 SPRING_PASSES,                 /* 0x1d spring passes */
 SPRING_PASS_INT,               /* 0x1e spring pass interval */
 CURRENT_PASS,                  /* 0x1f current passes */

// axis move values

 Z_MOVE_DIST,                   /* 0x20 z move distance */
 Z_MOVE_POS,                    /* 0x21 z move position */
 Z_JOG_DIR,                     /* 0x22 x jog direction */
 Z_SET_LOC,                     /* 0x23 z location to set */
 Z_LOC,                         /* 0x24 z location */
 Z_FLAG,                        /* 0x25 z move flag */
 X_MOVE_DIST,                   /* 0x26 x move distance */
 X_MOVE_POS,                    /* 0x27 x move position */
 X_JOG_DIR,                     /* 0x28 x jog direction */
 X_SET_LOC,                     /* 0x29 x location to set */
 X_LOC,                         /* 0x2a x location */
 X_FLAG,                        /* 0x2b x move flag */
 FEED_TYPE,                     /* 0x2c feed parameter type */
 FEED,                          /* 0x2d feed parameter */
 INDEX_PRE_SCALER,              /* 0x2e index prescaler */
 INDEX_PERIOD,                  /* 0x2f index period */

// encoder counts per revolution

 ENC_MAX,                       /* 0x30 encoder counts per revolution */

// test encoder setup variables

 ENC_ENABLE,                    /* 0x31 encoder enable flag */
 ENC_PRE_SCALER,                /* 0x32 encoder prescaler */
 ENC_TIMER,                     /* 0x33 encoder timer counts */
 ENC_RUN_COUNT,                 /* 0x34 encoder run count */

// test encoder status variables

 ENC_RUN,                       /* 0x35 encoder running flag */
 ENC_COUNTER,                   /* 0x36 encoder count in rev */
 ENC_REV_COUNTER,               /* 0x37 encoder revolution counter */

// measured spindle speed

 RPM,                           /* 0x38 current rpm */

// xilinx frequency variables

 X_FREQUENCY,                   /* 0x39 xilinx clock frequency */
 FREQ_MULT,                     /* 0x3a frequency multiplier */

// xilinx configuration register

 X_CFG_REG,                     /* 0x3b xilinx configuration register */

// max parameter number

 MAX_PARM,                      /* 0x3c maximum parameter */
};
