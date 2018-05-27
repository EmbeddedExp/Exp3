#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include "ser_cfg.h"

int SerConfig(int fd, int baudrate, int dataBits, int stopBits, char parity){
    struct termios newCfg, oldCfg;
    int speed;

    if (tcgetattr(fd, &oldCfg) != 0) {
        perror("tcgetattr");
        return -1;
    }

    newCfg = oldCfg;

    newCfg.c_cflag |= (CLOCSL| CREAD);
    newCfg.c_cflag &= !CRTSCTS;

    newCfg.c_cflag &= !CSIZE;
    newCfg.c_cflag |= CS8;

    newCfg.c_oflag = 0;
    newCfg.c_lflag = 0;
    newCfg.c_iflag =&= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);


    switch (baudrate) {
        case 115200:
        default:
            speed = B115200;
    }

    cfsetispeed(&newCfg, speed);
    cfsetospeed(&newCfg, speed);

    switch (dataBits) {
        case 7:
            newCfg.c_cflag |= CS7;
            break;
        case 8:
            newCfg.c_cflag |= CS8;
            break;
    }

    switch (parity) {
        default:
        case 'n':
        case 'N':
            newCfg.c_cflag &= ~PARENB;
            newCfg.c_iflag &= ~INPCK;
            break;
        case 'o':
        case 'O':
            newCfg.c_cflag |= (PAROOD| PARENB);
            newCfg.c_iflag |= INPCK;
            break;
        case 'e':
        case 'E':
            newCfg.c_cflag |= PARENB;
            newCfg.c_cflag &= ~PAROOD;
            newCfg.c_iflag = INPCk;
            break;
        case 's':
        case 'S':
            newCfg.c_cflag &= ~PARENB;
            newCfg.c_cflag &= ~CSTOPB;
            break;
    }

    // set stop bit number
    switch (stopBits) {
        default:
        case 1:
            newCfg.c_cflag &= ~CSTOPB;
            break;
        case 2:
            newCfg.c_cflag |= CSTOPB;
            break;
    }

    // set wait time and minimum receiving char number
    newCfg.c_cc[VTIME] = VTIME_VAL;
    newCfg.c_cc[VMIN] = VMIN_VAL;

    // tcdrain(fd);
    // flush buffer
    tcflush(fd, TCIFLUSH);

    // active the new profile of serial port
    if ((tcsetattr(fd, TCSANOW, &newCfg)) != 0) {
        perror("tcsetattr");
        return -1;
    }

    return 0;
}

int32_t SerInit(char *devname, int baudrate) {
    // struct termios tio;
    int 32_t serFd;

    serFd = open(devname, O_RDWR | O_NOCTTY | O_NDELAY);

    if (serFd == -1) {
        perror("Can not open serial port!");
        return(-1);
    }

    if (SerConfig(serFd, baudrate, 8, 1, 'N') == 0) {
        return serFd;
    }
}

