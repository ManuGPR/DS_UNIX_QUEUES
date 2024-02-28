CC=gcc
CFLAGS=-g -Wall
QFLAGS=-lrt
BIN_FILES= servidor cliente

.PHONY: all clean 

all: $(BIN_FILES)

clean: 
	rm -f $(BIN_FILES) *.o
	rm -f *.so

cliente: cliente.c libclaves.so
	$(CC) $(CFLAGS) $(QFLAGS) cliente.c -L. -lclaves -o $@

servidor: servidor.c
	$(CC) $(CFLAGS) $(QFLAGS) $^ -o $@ 

libclaves.so: claves.o
	$(CC) -shared $(CFLAGS) -o libclaves.so claves.o 
	
claves.o: claves.c
	$(CC) $(CFLAGS) -c claves.c -o claves.o
