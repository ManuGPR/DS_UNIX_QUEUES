#include <stdio.h>
#include "../claves.h"
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int print_files(char *abs_path) {
    //Imprime por pantalla los archivos que hay en el directorio tuplas
    DIR *dir = opendir(abs_path);
    struct dirent *tuplas;
    printf("En el directorio tuplas hay los siguientes archivos:  ");
    while ((tuplas = readdir(dir)) != NULL) {
        printf("%s  ", tuplas->d_name);
    }
    printf("\n");
    return 0;
}



int main(){
    printf("Test de delete_key\n\n");

    //Se obtine la path del diretorio tuplas donde estan almacanadas las key y se abre el directorio
    const char *rel_path = "./tuplas";
    char *abs_path;
    abs_path = realpath(rel_path, NULL);

    //Se borran todos lor archivos y se crea un archivo
    init();
    int delete;
    int n = 1;
    double vector[n];
    int k = 1;
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    set_value(k, "archivo", n, vector);

    /*Test 1: funcionamiento corecto*/
    printf("Test 1: todo correcto\n");

    print_files(abs_path);

    //Se borrael archvo
    delete = delete_key(k);
    printf("Resultado prueba 1: %d\n", delete);
+   print_files(abs_path);

    printf("\nTest 2: no exite ninguna clave\n");
    //Se borran los archivos
    delete = delete_key(k);
    printf("Resultado prueba 2: %d\n", delete);
}