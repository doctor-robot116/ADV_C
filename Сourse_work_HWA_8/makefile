CC = gcc
CFLAGS = -Wall -g
LDFLAGS = 
EXECUTABLE = area_calculator

all: $(EXECUTABLE)

$(EXECUTABLE): main.o
	$(CC) $(LDFLAGS) main.o -lm -o $(EXECUTABLE)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o $(EXECUTABLE)