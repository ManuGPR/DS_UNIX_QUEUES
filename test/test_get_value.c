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

int leer_fichero(char *abs_path, int k){

    // Escribe los datos
    FILE *archivo;
    //char caracter[10];
    char number[20];
    sprintf(number, "%i",k);

    char nombre_archivo[100];
    memset(&nombre_archivo, 0, sizeof(nombre_archivo));
    strcat(nombre_archivo, abs_path);
    strcat(nombre_archivo, "/");
    strcat(nombre_archivo, number);


    // Abre el archivo en modo lectura
    archivo = fopen(nombre_archivo, "r");
    if(archivo == NULL){
        printf("Error al abrir el fichro");
        return -1;
    }

    //printf("El contenido del fichero es:\n");
    // Lee y muestra cada caracter del archivo
    char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }

    // Cierra el archivo
    fclose(archivo);
    printf("\n");
    return 0;
}

int main(){

    printf("Test de get_value\n\n");
    //Declaración de variables
    int N;
    double v2[32];
    char v1[256];
    int  get;

    //Se obtine la path del diretorio tuplas donde estan almacanadas las key y se abre el directorio
    const char *rel_path = "./tuplas";
    char *abs_path;
    abs_path = realpath(rel_path, NULL);

    //Se borran todos lor archivos y se crea un archivo
    init();
    int n = 1;
    double vector[n];
    int k = 1;
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    set_value(k, "archivo", n, vector);

    /*Test 1: funcionamiento corecto*/
    printf("Test 1: todo correcto\n");
    //k = 1;

    //printf("En el directorio tuplas hay los siguientes archivos: ");
    print_files(abs_path);
    printf("Los datos que ha en el archivo creado: \n");
    leer_fichero(abs_path, k);

    //Se obtine el resultado
    get = get_value(k, v1, &N , v2);
    printf("Resultado prueba 1: %d\n", get);

    printf("Los datos que se han obtenido son:\n");
    printf("K: %i\n", k);
    printf("V1: %s\n", v1);
    printf("N: %i\n", N);
    printf("V2: ");
    for(int i = 0; i < N; i++){
        printf("%lf\n", v2[i]);
    }

    printf("\nTest 2: no exite ninguna clave\n");

    //Se borran los archivos
    init();

    get = get_value(k, v1, &N , v2);
    printf("Resultado prueba e: %d\n", get);

    printf("\nTest 3: N > 32 \n");
    printf("\nTest 4: len(value1) > 255\n");

}