enum COMMANDS
{

// z motion commands

 ZMOVE,                         /* 0x00 move z absolute */
 ZMOVEREL,                      /* 0x01 move z relative */
 ZJMOV,                         /* 0x02 start z jog */
 ZSTOP,                         /* 0x03 stop z movement */
 ZHOME,                         /* 0x04 set current z location as home */
 ZSETLOC,                       /* 0x05 set current z location */
 ZGOHOME,                       /* 0x06 z go to home position */

// x motion commands

 XMOVE,                         /* 0x07 move x absolute */
 XMOVEREL,                      /* 0x08 move x relative */
 XJMOV,                         /* 0x09 start x jog */
 XSTOP,                         /* 0x0a stop x movement */
 XHOME,                         /* 0x0b set current x location as home */
 XSETLOC,                       /* 0x0c set current x location */
 XGOHOME,                       /* 0x0d x go to home position */

// spindle operations

 SPINDLE_START,                 /* 0x0e start spindle */
 SPINDLE_STOP,                  /* 0x0f stop spindle */

// end operations

 CMD_PAUSE,                     /* 0x10 pause current operation */
 CMD_RESUME,                    /* 0x11 resume current operation */
 CMD_STOP,                      /* 0x12 stop current operation */

// setup operations

 CMD_CLEAR,                     /* 0x13 clear all tables */
 CMD_SETUP,                     /* 0x14 setup everything */
 CMD_SPSETUP,                   /* 0x15 setup spindle */
 CMD_ZSETUP,                    /* 0x16 setup z axis */
 CMD_ZSYNSETUP,                 /* 0x17 setup z axis sync */
 CMD_ZTAPERSETUP,               /* 0x18 setup z axis taper */
 CMD_XSETUP,                    /* 0x19 setup x axis */
 CMD_XSYNSETUP,                 /* 0x1a setup z axis sync */
 CMD_XTAPERSETUP,               /* 0x1b setup z axis taper */

// state information

 READSTAT,                      /* 0x1c read status */
 READISTATE,                    /* 0x1d read states of state machines */

// load processor and xilinx parameters

 LOADVAL,                       /* 0x1e load parameters */
 READVAL,                       /* 0x1f read parameters */
 LOADXREG,                      /* 0x20 load xilinx registers */
 READXREG,                      /* 0x21 read xilinx registers */

// move command operations

 SENDMOVE,                      /* 0x22 send move command */
 MOVEQUESTATUS,                 /* 0x23 read move queue status */

// location and debug info

 READLOC,                       /* 0x24 read location */
 READDBG,                       /* 0x25 read debug message */
 CLRDBG,                        /* 0x26 clear debug message buffer */

// encoder commands

 ENCSTART,                      /* 0x27 encoder start */
 ENCSTOP,                       /* 0x28 encoder stop */
};
