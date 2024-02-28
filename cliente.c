#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include "mensajes.h"
#include "claves.h"

int main() {
	int a = init_q();
	printf("%d\n", a);
	return 0;
}
