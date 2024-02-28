#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include "mensajes.h"
#include "claves.h"



int init() {
	printf("Hola\n");
	attr.mq_msgsize = sizeof(struct Peticion);
	attr.mq_maxmsg = 10;
	mq_open("/SERVIDOR", O_WRONLY, 0700, &attr);
	
	struct Peticion p;
	//struct Respuesta r;
	
	memset(&p, sizeof(p), cero);
	p.op = 0;
	
	mq_send(q_server, (char *)&p, sizeof(p), 0);
	return 0;
}
