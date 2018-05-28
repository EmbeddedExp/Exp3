exp:ser_test.o ser.o
	gcc -o exp ser_test.o ser.o

ser_test.o:ser_test.c ser_cfg.h ser.h
	gcc -c ser_test.c -o ser_test.o

ser.o:ser.c ser_cfg.h
	gcc -c ser.c -o ser.o

clean:
	rm -rf *.o exp

