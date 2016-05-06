enum XILINX
{

// load control registers

 XLDZCTL,                       /* 0x00 z control register */
 XLDXCTL,                       /* 0x01 x control register */
 XLDTCTL,                       /* 0x02 load taper control */
 XLDPCTL,                       /* 0x03 position control */
 XLDCFG,                        /* 0x04 configuration */
 XLDDCTL,                       /* 0x05 load debug control */
 XLDDREG,                       /* 0x06 load display reg */
 XREADREG,                      /* 0x07 read register */

// status register

 XRDSR,                         /* 0x08 read status register */

// read phase

 XRDPSYN,                       /* 0x09 read sync phase val */
 XRDTPHS,                       /* 0x0a read tot phase val */

// phase counter

 XLDPHASE,                      /* 0x0b load phase max */

// load z motion

 XLDZFREQ,                      /* 0x0c load z frequency */
 XLDZD,                         /* 0x0d load z initial d */
 XLDZINCR1,                     /* 0x0e load z incr1 */
 XLDZINCR2,                     /* 0x0f load z incr2 */
 XLDZACCEL,                     /* 0x10 load z syn accel */
 XLDZACLCNT,                    /* 0x11 load z syn acl cnt */
 XLDZDIST,                      /* 0x12 load z distance */
 XLDZLOC,                       /* 0x13 load z location */

// load x motion

 XLDXFREQ,                      /* 0x14 load x frequency */
 XLDXD,                         /* 0x15 load x initial d */
 XLDXINCR1,                     /* 0x16 load x incr1 */
 XLDXINCR2,                     /* 0x17 load x incr2 */
 XLDXACCEL,                     /* 0x18 load x syn accel */
 XLDXACLCNT,                    /* 0x19 load x syn acl cnt */
 XLDXDIST,                      /* 0x1a load x distance */
 XLDXLOC,                       /* 0x1b load x location */

// read z motion

 XRDZSUM,                       /* 0x1c read z sync sum */
 XRDZXPOS,                      /* 0x1d read z sync x pos */
 XRDZYPOS,                      /* 0x1e read z sync y pos */
 XRDZACLSUM,                    /* 0x1f read z acl sum */
 XRDZASTP,                      /* 0x20 read z acl stps */

// read x motion

 XRDXSUM,                       /* 0x21 read x sync sum */
 XRDXXPOS,                      /* 0x22 read x sync x pos */
 XRDXYPOS,                      /* 0x23 read x sync y pos */
 XRDXACLSUM,                    /* 0x24 read x acl sum */
 XRDXASTP,                      /* 0x25 read z acl stps */

// read distance

 XRDZDIST,                      /* 0x26 read z distance */
 XRDXDIST,                      /* 0x27 read x distance */

// read location

 XRDZLOC,                       /* 0x28 read z location */
 XRDXLOC,                       /* 0x29 read x location */

// read frequency and state

 XRDFREQ,                       /* 0x2a read encoder freq */
 XRDSTATE,                      /* 0x2b read state info */

// phase limit info

 XLDZLIM,                       /* 0x2c load z limit */
 XRDZPOS,                       /* 0x2d read z position */

// test info

 XLDTFREQ,                      /* 0x2e load test freq */
 XLDTCOUNT,                     /* 0x2f load test count */
};
