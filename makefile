CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lcjson  # Add this line to link with cJSON library
OBJ = main2.o hybrid.o patricia.o 

all: main2

# usr/local/include
# usr/local/lib
main2: $(OBJ)
	$(CC) $(CFLAGS) -o main2 $(OBJ) -I/cJSON -L/cJSON $(LDFLAGS) 
# Add $(LDFLAGS) to the uper to link with cJSON

main2.o: main2.c hybrid.h patricia.h
	$(CC) $(CFLAGS) -c main2.c

patricia.o: patricia.c patricia.h
	$(CC) $(CFLAGS) -c patricia.c

hybrid.o: hybrid.c hybrid.h
	$(CC) $(CFLAGS) -c hybrid.c

clean:
	rm -f *.o main2