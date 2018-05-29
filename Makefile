CC = gcc
PR = -g

all: send recive


send: send.o connect.o connect.h md5calc.o
	$(CC) $(PR) send.o connect.o md5calc.o -o send -lssl -lcrypto 

recive: recive.o connect.o connect.h md5calc.o
	$(CC) $(PR) recive.o connect.o md5calc.o -o recive -lssl -lcrypto 

send.o: send.c
	$(CC) $(PR) -c send.c -o send.o

recive.o: recive.c
	$(CC) $(PR) -c recive.c -o recive.o

connect.o: connect.c
	$(CC) $(PR) -c connect.c -o connect.o

md5calc.o: md5calc.c
	$(CC) $(PR) -Wall -c md5calc.c -o md5calc.o 

clean:
	rm *.o send recive
