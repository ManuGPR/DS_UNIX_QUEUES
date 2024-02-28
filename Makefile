CC=gcc
CFLAGS=-g -Wall
QFLAGS=-lrt
BIN_FILES= servidor cliente
.PHONY: all clean 

all: $(BIN_FILES)

clean: 
	rm -f $(BIN_FILES) *.o
	rm libclaves.so

cliente: cliente.o libclaves.so
	$(CC) $(CFLAGS) $(QFLAGS) -lclaves -L/home/manu/SD cliente.o libclaves.so -o $@

cliente.o: cliente.c
	$(CC) $(CFLAGS) -c cliente.c -o cliente.o

servidor: servidor.c
	$(CC) $(CFLAGS) $(QFLAGS) $^ -o $@ 

libclaves.so: claves.o
	$(CC) $(CFLAGS) -o libclaves.so -shared -fPIC claves.o 
	
claves.o: claves.c
	$(CC) $(CFLAGS) -c -fPIC claves.c -o claves.o
