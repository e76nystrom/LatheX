enum COMMANDS
{

// z motion commands

 ZMOVE,                         /* 0x00 start z movement */
 ZJMOV,                         /* 0x01 start z jog */
 ZSTOP,                         /* 0x02 stop z movement */
 ZHOME,                         /* 0x03 set current z location as home */
 ZSETLOC,                       /* 0x04 set current z location */
 ZGOHOME,                       /* 0x05 z go to home position */

// x motion commands

 XMOVE,                         /* 0x06 start x movement */
 XJMOV,                         /* 0x07 start x jog */
 XSTOP,                         /* 0x08 stop x movement */
 XHOME,                         /* 0x09 set current x location as home */
 XSETLOC,                       /* 0x0a set current x location */
 XGOHOME,                       /* 0x0b x go to home position */

// spindle operations

 SPINDLE_START,                 /* 0x0c start spindle */
 SPINDLE_STOP,                  /* 0x0d stop spindle */

// end operations

 CMD_PAUSE,                     /* 0x0e pause current operation */
 CMD_RESUME,                    /* 0x0f resume current operation */
 CMD_STOP,                      /* 0x10 stop current operation */

// setup operations

 CMD_CLEAR,                     /* 0x11 clear all tables */
 CMD_SETUP,                     /* 0x12 setup everything */
 CMD_SPSETUP,                   /* 0x13 setup spindle */
 CMD_ZSETUP,                    /* 0x14 setup z axis */
 CMD_ZSYNSETUP,                 /* 0x15 setup z axis sync */
 CMD_ZTAPERSETUP,               /* 0x16 setup z axis taper */
 CMD_XSETUP,                    /* 0x17 setup x axis */
 CMD_XSYNSETUP,                 /* 0x18 setup z axis sync */
 CMD_XTAPERSETUP,               /* 0x19 setup z axis taper */

// state information

 READSTAT,                      /* 0x1a read status */
 READISTATE,                    /* 0x1b read states of state machines */

// load processor and xilinx parameters

 LOADVAL,                       /* 0x1c load parameters */
 READVAL,                       /* 0x1d read parameters */
 LOADXREG,                      /* 0x1e load xilinx registers */
 READXREG,                      /* 0x1f read xilinx registers */

// move command operations

 SENDMOVE,                      /* 0x20 send move command */
 MOVEQUESTATUS,                 /* 0x21 read move queue status */

// location and debug info

 READLOC,                       /* 0x22 read location */
 READDBG,                       /* 0x23 read debug message */

// encoder commands

 ENCSTART,                      /* 0x24 encoder start */
 ENCSTOP,                       /* 0x25 encoder stop */
};
