#include <stdio.h>
#include <stdlib.h>
#include "claves.h"

int main() {
	int a = init();
	printf("%d\n", a);

    double vector[2];
    vector[0] = 1;
    vector[1] = 2;
    int b = set_value(1, "pepito", 2, vector);
    printf("%d\n", b);
	return 0;
}
