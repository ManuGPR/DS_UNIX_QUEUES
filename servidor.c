#include <stdio.h>
#include <mqueue.h>
#include <errno.h>
#include "mensajes.h"

int init_server() {
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
	struct mq_attr attr;
	struct Peticion p;
	
	attr.mq_msgsize = sizeof(struct Peticion);
	attr.mq_maxmsg = 10;
	
	mqd_t q_server = mq_open("/SERVIDOR", O_CREAT | O_RDONLY, 0700, &attr);
	if (q_server == -1) {
		perror("");
		return -1;
	}
	
	ssize_t b_read;
	while(1) {
		b_read = mq_receive(q_server, (char *)&p, sizeof(p), NULL);
		if (b_read == -1) {
			perror("");
			return -1;
		}
		
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
