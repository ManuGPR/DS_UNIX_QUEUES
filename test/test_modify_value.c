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

    printf("Test de modify_value\n\n");
    //Declaración de variables
    int  modify;
    int n = 1;
    double vector[32];
    int k = 1;

    //Se borran todos lor archivos y se crea un archivo
    init();
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    set_value(k, "archivo", n, vector);

    //Se obtine la path del diretorio tuplas donde estan almacanadas las key y se abre el directorio
    const char *rel_path = "./tuplas";
    char *abs_path;
    abs_path = realpath(rel_path, NULL);

    /*Test 1: funcionamiento corecto*/
    printf("Test 1: todo correcto\n");

    print_files(abs_path);
    printf("Los datos que ha en el archivo creado: \n");
    leer_fichero(abs_path, k);

    //Se modifica el archivo
    n = 3;
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    modify = modify_value(k, "archivo_cambiado", n , vector);
    printf("Resultado prueba 1: %d\n", modify);

    print_files(abs_path);
    printf("Los datos que ha en el archivo modificado: \n");
    leer_fichero(abs_path, k);


    /*Test 2: no hay ningun archivo*/
    printf("\nTest 2: no exite ninguna clave\n");
    //Se borran los archivos
    init();
    print_files(abs_path);
    modify = modify_value(k, "archivo_cambiado", n , vector);
    printf("Resultado prueba 2: %d\n", modify);


    /*Test 3: se modifica el archivo y N = 0 */
    printf("\nTest 3: N = 0 \n");
    //Se borran todos lor archivos y se crea un archivo
    init();
    n = 1;
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    set_value(k, "archivo", n, vector);
    printf("Los datos que ha en el archivo creado: \n");
    leer_fichero(abs_path, k);
    //Se modifica el archivo
    n = 0;
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    modify = modify_value(k, "archivo_cambiado", n , vector);
    printf("Resultado prueba 3: %d\n", modify);
    printf("Los datos del archivo: \n");
    leer_fichero(abs_path, k);


    /*Test4: Modifica el archivo*/
    printf("\nTest 4: N = 32\n");
    //Se modifica el archivo
    n = 32;
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    modify = modify_value(k, "archivo_cambiado", n , vector);
    printf("Resultado prueba 4: %d\n", modify);

}