#ifndef _SER_CFG_H__
#define _SER_CFG_H__ 1

#include "ser_cfg.h"

extern char *greeting;
// global var
/*
...
*/
int SerConfig(int fd, int baudrate, int dataBits, int stopBits, char partity);
int32_t SerInit(char *devname, int baudrate);

#endif