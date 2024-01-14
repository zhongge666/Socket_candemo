CC = gcc
CFLAGS = -std=c99 -Wall
LIBS = -lsocketcan

all: cansend candump

cansend: cansend.c
	$(CC) $(CFLAGS) -o cansend cansend.c $(LIBS)

candump: candump.c
	$(CC) $(CFLAGS) -o candump candump.c $(LIBS)

clean:
	rm -f cansend candump

