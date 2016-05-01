
// z control states

enum ZSTATES
{
 ZIDLE,                         /*  0 idle */
 ZWAITBKLS,                     /*  1 wait for backlash move complete */
 ZSTARTMOVE,                    /*  2 start z move */
 ZWAITMOVE,                     /*  3 wait for move complete */
 ZDONE,                         /*  4 clean up state */
};

// x control states

enum XSTATES
{
 XIDLE,                         /*  0 idle */
 XWAITBKLS,                     /*  1 wait for backlash move complete */
 XSTARTMOVE,                    /*  2 start x move */
 XWAITMOVE,                     /*  3 wait for move complete */
 XDONE,                         /*  4 clean up state */
};

// move control states

enum M_STATES
{
 M_IDLE,                        /*  0 idle state */
 M_WAIT_Z,                      /*  1 wait for z to complete */
 M_WAIT_X,                      /*  2 wait for x to complete */
 M_WAIT_SPINDLE,                /*  3 wait for spindle start */
};

// move control commands

enum M_COMMANDS
{
 MOVE_Z,                        /*  0 move z */
 MOVE_X,                        /*  1 move x */
 SAVE_Z,                        /*  2 save z */
 SAVE_X,                        /*  3 save x */
 SAVE_TAPER,                    /*  4 save taper */
 MOVE_ZX,                       /*  5 move x in sync with z */
 MOVE_XZ,                       /*  6 move z in sync with x */
 TAPER_ZX,                      /*  7 taper x */
 TAPER_XZ,                      /*  8 taper z */
 QUE_START,                     /*  9 spindle start */
 QUE_STOP,                      /* 10 spindle stop */
 PASS_NUM,                      /* 11 set pass number */
};
