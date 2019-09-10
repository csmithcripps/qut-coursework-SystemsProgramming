CC = c99
CFLAGS = -Wall -pedantic # Show all reasonable warnings
LDFLAGS =

all: fib shm

fib: fibfork.o fib.o

fibfork.o: fibfork.c

fib.o: fib.c

shm: shm_client shm_server

shm_client: shm_client.o

shm_client.o: shm_client.c

shm_server: shm_server.o

shm_server.o: shm_server.c

clean:
	rm -f fib *.o shm_client shm_server

.PHONY: all clean
