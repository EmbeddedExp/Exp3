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