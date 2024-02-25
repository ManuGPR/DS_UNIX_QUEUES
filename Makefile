CC=gcc
CFLAGS=-g -Wall
LDFLAGS= -L$(INSTALL_PATH)/libclaves.so/ 
BIN_FILES= servidor cliente
.PHONY: all clean 

all: $(BIN_FILES)

clean: 
	rm -f $(BIN_FILES) *.o

cliente: cliente.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

servidor: servidor.o
	$(CC) $(CFLAGS) $^ -o $@ 

libclaves.so: claves.c
	$(CC) $(CFLAGS) -o libclaves.so -shared claves.c -fPIC

%.o: %.c
	$(CC) $(CFLAGS) -c $<
