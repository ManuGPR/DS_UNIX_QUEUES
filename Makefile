CC=gcc
CFLAGS=-g -Wall
QFLAGS=-lrt
BIN_FILES= servidor cliente test_init test_set_value test_get_value test_modify_value test_delete_key test_exist

.PHONY: all clean 

all: $(BIN_FILES)

clean: 
	rm -f $(BIN_FILES) *.o
	rm -f *.so

cliente: cliente.c libclaves.so tuplas
	$(CC) $(CFLAGS) $(QFLAGS) cliente.c -L. -lclaves -o $@

test_init:test/test_init.c libclaves.so tuplas
	$(CC) $(CFLAGS) $(QFLAGS) test/test_init.c -L. -lclaves -o $@

test_set_value:test/test_set_value.c libclaves.so tuplas
	$(CC) $(CFLAGS) $(QFLAGS) test/test_set_value.c -L. -lclaves -o $@

test_get_value:test/test_get_value.c libclaves.so tuplas
	$(CC) $(CFLAGS) $(QFLAGS) test/test_get_value.c -L. -lclaves -o $@

test_modify_value:test/test_modify_value.c libclaves.so tuplas
	$(CC) $(CFLAGS) $(QFLAGS) test/test_modify_value.c -L. -lclaves -o $@

test_delete_key:test/test_delete_key.c libclaves.so tuplas
	$(CC) $(CFLAGS) $(QFLAGS) test/test_delete_key.c -L. -lclaves -o $@

test_exist:test/test_exist.c libclaves.so tuplas
	$(CC) $(CFLAGS) $(QFLAGS) test/test_exist.c -L. -lclaves -o $@

tuplas:
	mkdir tuplas

servidor: servidor.c
	$(CC) $(CFLAGS) $(QFLAGS) $^ -o $@ 

libclaves.so: claves.o
	$(CC) -shared $(CFLAGS) -o libclaves.so claves.o 
	
claves.o: claves.c
	$(CC) $(CFLAGS) -c claves.c -o claves.o
