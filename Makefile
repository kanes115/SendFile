CC = gcc
PR = 

all: send recive

send: send.o connect.o connect.h
	$(CC) $(PR) send.o connect.o -o send

recive: recive.o connect.o connect.h
	$(CC) $(PR) recive.o connect.o -o recive

send.o: send.c
	$(CC) $(PR) -c send.c -o send.o

recive.o: recive.c
	$(CC) $(PR) -c recive.c -o recive.o

connect.o: connect.c
	$(CC) $(PR) -c connect.c -o connect.o

clean:
	rm *.o send recive
