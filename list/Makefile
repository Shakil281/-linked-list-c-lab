CC = gcc
CFLAGS = -Wall -Wextra -g

list: main.o list.o
	$(CC) $(CFLAGS) -o list main.o list.o

main.o: main.c list.h
	$(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

clean:
	rm -f *.o list
