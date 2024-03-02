#include <stdio.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "mensajes.h"

#define PATH_MAX 4096

const int cero = 0;
const char *rel_path="./tuplas";
const char barra[] = "/";
char *abs_path;

int init_server(struct Peticion p) {
	// Se crea la estructura de respuesta
	struct Respuesta r;
	memset(&r, cero, cero);
	r.res = 0;
	
	// Se crea la cola de respuesta al cliente
	mqd_t q_client = mq_open(p.q_clientname, O_WRONLY);
	
	//Implementación de la función init
	
	// Declaración de variables necesarias para el init
	DIR *dir = opendir(abs_path);
	struct dirent* tuplas;
	int rem;
	char* file_name;
	
	// Mientras haya tuplas en el fichero de tuplas
	while ((tuplas = readdir(dir)) != NULL) {
		
		// Si el objeto no es un directorio
		if (strcmp(tuplas->d_name, ".") != 0 && strcmp(tuplas->d_name, "..") != 0) {
			
			// Se reserva espacio para el nombre del fichero y se obtiene su path absoluto
			file_name = calloc(PATH_MAX, sizeof(char));
			strcpy(file_name, abs_path);
			strcat(file_name, barra);
			strcat(file_name, tuplas->d_name);
			
			// Se borra el fichero, si hay algún error, se escribe y la respuesta devolverá -1
			rem = remove(file_name);	
			if (rem == -1) {
				perror("");
				r.res = rem;
			}
			
			// Se libera el espacio dinámico
			free(file_name);
		}
	}
	
	// Se envía el mensaje 
	mq_send(q_client, (char*)&r, sizeof(r), 0);
	
	// Se cierra la cola
	mq_close(q_client);
	return 0;
}

int set_value_server(struct Peticion p) {
    // Se crea la estructura de respuesta
    struct Respuesta r;
    memset(&r, cero, sizeof(r));
    r.res = 0;
	
	// Se crea la cola de respuesta al cliente
    mqd_t q_client = mq_open(p.q_clientname, O_WRONLY);
	
    //printf("Key = %d, value_1 = %s, n_value2 = %d, v_value2 = %lf %lf\n", p.key, p.value1, p.N_value2, p.V_value2[0], p.V_value2[1]);
	// Se obtiene el nombre absoluto del fichero
	char *tuple_name = calloc(PATH_MAX, sizeof(char));
	strcpy(tuple_name, abs_path);
	strcat(tuple_name, barra);
	char key_str[32];
	sprintf(key_str, "%d", p.key);
	strcat(tuple_name, key_str);
	
	// Se mira si existe
	if (access(tuple_name, F_OK) == 0) {	
		printf("Archivo existe\n");
		r.res = -1;
		mq_send(q_client, (char*)&r, sizeof(r), 0);
		mq_close(q_client);
		return -1;
	}
	
	// Crea el fichero
	FILE * tuple;
	tuple = fopen(tuple_name, "w+");
	if (tuple == NULL) {
		perror("");
		r.res = -1;
		mq_send(q_client, (char*)&r, sizeof(r), 0);
		mq_close(q_client);
		return -1;
	}
	
	// Escribe los datos
	if (fprintf(tuple, "%d\n", p.key) < 0) {r.res = -1;}
	if (fprintf(tuple, "%s\n", p.value1) < 0) {r.res = -1;}
	if (fprintf(tuple, "%d\n", p.N_value2) < 0) {r.res = -1;}
	for (int i = 0; i < p.N_value2; i++) {
		if (fprintf(tuple, "%lf", p.V_value2[i]) < 0) {r.res = -1;}
		if (i < p.N_value2 -1) {fprintf(tuple, ", ");}
    }
     
    // Cierra la tupla
    fclose(tuple);
    
    // Se envía el mensaje
    mq_send(q_client, (char*)&r, sizeof(r), 0);

    // Se cierra la cola
    mq_close(q_client);
    
    //printf("Set value hecho\n");
    return 0;
}

int get_value_server(struct Peticion p) {
    // Se crea la estructura de respuesta
    struct Respuesta r;
    memset(&r, cero, sizeof(r));

    double v[2] = {1,2} ;
    strcpy(r.value1, "placeholder");
    r.N_or_exists = 2;
    memcpy(r.V_value2, v, r.N_or_exists* sizeof(double));
    r.res = 0;

    // Se crea la cola de respuesta al cliente
    mqd_t q_client = mq_open(p.q_clientname, O_WRONLY);

    // Se envía el mensaje
    mq_send(q_client, (char*)&r, sizeof(r), 0);

    // Se cierra la cola
    mq_close(q_client);
    //printf("Get value hecho\n");
    return 0;
}

int modify_value_server(struct Peticion p) {
    // Se crea la estructura de respuesta
    struct Respuesta r;
    memset(&r, cero, sizeof(r));

    //printf("Key = %d, value_1 = %s, n_value2 = %d, v_value2 = %lf %lf\n", p.key, p.value1, p.N_value2, p.V_value2[0], p.V_value2[1]);

    // Se crea la cola de respuesta al cliente
    mqd_t q_client = mq_open(p.q_clientname, O_WRONLY);

    // Se envía el mensaje
    mq_send(q_client, (char*)&r, sizeof(r), 0);

    // Se cierra la cola
    mq_close(q_client);
    //printf("Modify value hecho\n");
    return 0;
}

int delete_key_server(struct Peticion p) {
    // Se crea la estructura de respuesta
    struct Respuesta r;
    memset(&r, cero, sizeof(r));

    //printf("Key = %d\n", p.key);

    // Se crea la cola de respuesta al cliente
    mqd_t q_client = mq_open(p.q_clientname, O_WRONLY);

    // Se envía el mensaje
    mq_send(q_client, (char*)&r, sizeof(r), 0);

    // Se cierra la cola
    mq_close(q_client);
    //printf("delete hecho\n");
    return 0;
}

int exist_server(struct Peticion p) {
    // Se crea la estructura de respuesta
    struct Respuesta r;
    memset(&r, cero, sizeof(r));

    //printf("Key = %d\n", p.key);

    // Se crea la cola de respuesta al cliente
    mqd_t q_client = mq_open(p.q_clientname, O_WRONLY);

    // Se envía el mensaje
    mq_send(q_client, (char*)&r, sizeof(r), 0);

    // Se cierra la cola
    mq_close(q_client);
    //printf("exist hecho\n");
    return 0;
}

int main() {
	// Se crean los atributos y la estructura de petición
	struct mq_attr attr;
	struct Peticion p;
	
	// Se le da valor al path de las tuplas
	abs_path = realpath(rel_path, NULL);

	// Se inicializan los valores de attr y e p
	attr.mq_msgsize = sizeof(struct Peticion);
	attr.mq_maxmsg = 10;
	memset(&p, cero, sizeof(p));
	
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
			case 0: init_server(p);
				break;
			case 1: set_value_server(p);
				break;
			case 2: get_value_server(p);
				break;
			case 3: modify_value_server(p);
				break;
			case 4: delete_key_server(p);
				break;
			case 5: exist_server(p);
				break;
		}
		
	}
	return 0;
}
