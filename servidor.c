#include <stdio.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include "mensajes.h"

const int cero = 0;

int init_server() {
	// Se crea los atributos de la cola
	struct mq_attr attr;
	attr.mq_msgsize = sizeof(struct Respuesta);
	attr.mq_maxmsg = 1;
	
	// Se crea la estructura de respuesta
	struct Respuesta r;
	memset(&r, sizeof(r), cero);
	
	// Se crea la cola de respuesta al cliente
	mqd_t q_client = mq_open("/CLIENTE", O_WRONLY, 0700, &attr);
	
	// Se envía el mensaje 
	mq_send(q_client, (char*)&r, sizeof(r), 0);
	
	// Se cierra la cola
	mq_close(q_client);
	printf("Init hecho\n");
	return 0;
}

int set_value_server(struct Peticion p) {
	return 1;
}

int get_value_server(struct Peticion p) {
	return 2;
}

int modify_value_server(struct Peticion p) {
	return 3;
}

int delete_key_server(struct Peticion p) {
	return 4;
}

int exist_server(struct Peticion p) {
	return 5;
}

int main() {
	// Se crean los atributos y la estructura de petición
	struct mq_attr attr;
	struct Peticion p;
	
	// Se inicializan los valores de attr y e p
	attr.mq_msgsize = sizeof(struct Peticion);
	attr.mq_maxmsg = 10;
	memset(&p, sizeof(p), cero);
	
	// Se abre la cola del servidor y se comprueba que se abra bien
	mqd_t q_server = mq_open("/SERVIDOR", O_CREAT | O_RDONLY, 0700, &attr);
	if (q_server == -1) {
		perror("");
		return -1;
	}
	
	// Bucle de espera a las peticiones
	ssize_t b_read;
	while(1) {
		b_read = mq_receive(q_server, (char *)&p, sizeof(p), NULL);
		if (b_read == -1) {
			perror("");
			return -1;
		}
		
		// Llamada a las funciones
		switch(p.op) {
			case 0: init_server();
			case 1: set_value_server(p);
			case 2: get_value_server(p);
			case 3: modify_value_server(p);
			case 4: delete_key_server(p);
			case 5: exist_server(p);
		}
		
	}
	return 0;
}
