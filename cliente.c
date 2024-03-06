#include <stdio.h>
#include <stdlib.h>
#include "claves.h"

int main() {
	int a = init();
	printf("%d\n", a);
	int n = 32;
    double vector[n];
   	for (int i = 0; i < n; i++) {vector[i] = (double)i;}
    int b = set_value(10, "pepito", n, vector);
    printf("%d\n", b);


    int N;
    double v2[32];
    char v1[256];

    int c = get_value(10, v1, &N , v2);
    printf("%d\n", c);
    printf("%s\n", v1);
    printf("%i\n", N);
    for(int i = 0; i < N; i++){
        printf("%lf\n", v2[i]);
    }


    double vector3[2];
    vector3[0] = 1;
    vector3[1] = 2;
    int d= modify_value(10, "manu:(", 2, vector3);
    printf("%d\n", d);

    int k = 10;
    int e = delete_key(k);
    printf("%d\n", e);


    set_value(10, "pepito", n, vector);

    int g = 10;
    int f = exist(g);
    printf("%d\n", f);
	return 0;
}
