CC = gcc
CFLAGS = -Wall -g
OBJ = main.o patricia.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c patricia.h
	$(CC) $(CFLAGS) -c main.c

patricia.o: patricia.c patricia.h
	$(CC) $(CFLAGS) -c patricia.c

clean:
	rm -f *.o main
