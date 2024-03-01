#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "mensajes.h"
#include "claves.h"

int init() {
	//Función init que manda el mensaje de init al servidor
	// Se inicializan las colas
	mqd_t q_server, q_client;
	size_t cero = 0;
	
	// Se inicializan los
	struct mq_attr attr;
	attr.mq_msgsize = sizeof(struct Peticion);
	attr.mq_maxmsg = 10;
	
	struct mq_attr attr_r;
	attr_r.mq_msgsize = sizeof(struct Respuesta);
	attr_r.mq_maxmsg = 1;

	char q_clientname[16];
	sprintf(q_clientname, "/CLIENTE-%d", getpid());
	
	q_server = mq_open("/SERVIDOR", O_WRONLY, 0700, &attr);
	q_client = mq_open(q_clientname, O_CREAT | O_RDONLY, 0700, &attr_r);

	struct Peticion p;
	struct Respuesta r;
	memset(&p, sizeof(p), cero);
	strcpy(p.q_clientname, q_clientname);
	p.op = 0;
	
	mq_send(q_server, (char *)&p, sizeof(p), 0);
	mq_receive(q_client, (char *)&r, sizeof(r), 0);
	mq_close(q_client);
	mq_close(q_server);
	mq_unlink(q_clientname);
	return r.res;
}

