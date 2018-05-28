#include <stdio.h>     
#include <stdlib.h>    
#include <unistd.h>    
#include <sys/types.h>  
#include <sys/stat.h>   
#include <fcntl.h>     
#include <termios.h>   
#include <errno.h>     

#include <string.h>

#include "ser_cfg.h"
#include "ser.h"

int main()
{
	char *greeting = "hello Linux\n";
	int ser_fd;

	ser_fd = SerInit(SER_DEV, SER_BDR);
	if(ser_fd < 0) {
		perror("serial open fail!");
		exit(1);
	}

	printf("Progarm is starting:\n");
	write(ser_fd, greeting, strlen(greeting));

	return 0;
}