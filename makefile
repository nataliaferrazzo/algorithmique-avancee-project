CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lcjson  # Add this line to link with cJSON library
OBJ = main.o patricia.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o main $(OBJ)  # Add $(LDFLAGS) here to link with cJSON

main.o: main.c patricia.h
	$(CC) $(CFLAGS) -c main.c

patricia.o: patricia.c patricia.h
	$(CC) $(CFLAGS) -c patricia.c

clean:
	rm -f *.o main