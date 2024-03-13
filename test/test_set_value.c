#include <stdio.h>
#include "../claves.h"
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int print_files(char *abs_path) {
    //Imprime por pantalla los archivos que hay en el directorio tuplas
    DIR *dir = opendir(abs_path);
    struct dirent *tuplas;
    printf("Archivos en carpatea tuplas: ");
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

    printf("El contenido del fichero es:\n");
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

int main() {
    int set;
    //Se obtine la path del diretorio tuplas donde estan almacanadas las key y se abre el directorio
    const char *rel_path = "./tuplas";
    char *abs_path;
    abs_path = realpath(rel_path, NULL);
    printf("Test de set value");
    printf("Se borran todos los archivos\n");

    /*Test 1: Crea un archivo */
    printf("Test 1: funcionamiento para N = 2\n");
    init();
    print_files(abs_path);
    int n = 1;
    double vector[n];
    int k = 1;
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    set = set_value(k, "prueba_1", n, vector);
    printf("Prueba 1: %d\n", set);
    print_files(abs_path);

    if (set == 0){
        leer_fichero(abs_path, k);
    }


    /*Test 2: ya exite la key*/
    printf("\nTest 2: key ya existe\n");
    print_files(abs_path);
    k = 1;
    n = 1;
    for (int i = 0; i < n; i++) { vector[i] = (double) i; }
    set = set_value(k, "prueba_2", n, vector);
    printf("Prueba 2: %d\n", set);
    print_files(abs_path);
    if (set == 0){
        leer_fichero(abs_path, k);
    }


    /*Test 3: N = 0*/
    printf("\nTest 3: N=0\n");

    print_files(abs_path);
    n = 0;
    k = 3;
    for (int i = 0; i <= n; i++) { vector[i] = (double) i; }
    set = set_value(k, "prueba_3", n, vector);
    printf("Prueba 3 (N=0): %d\n", set);
    print_files(abs_path);
    if (set == 0){
        leer_fichero(abs_path, k);
    }

    /*Test 4: N = 2 */
    printf("\nTest 4: N=2\n");
    print_files(abs_path);
    n = 2;
    k = 4;
    for (int i = 0; i <= n; i++) { vector[i] = (double) i; }
    set = set_value(k, "prueba_4", n, vector);
    printf("Prueba 4 (N=2): %d\n", set);
    print_files(abs_path);
    if (set == 0){
        leer_fichero(abs_path, k);
    }

    /*Test 5: N = 31 */
    printf("\nTest 5: N=31\n");
    /*
    print_files(abs_path);
    n = 31;
    k = 5;
    for (int i = 0; i <= n; i++) { vector[i] = (double) i; }
    set = set_value(k, "prueba_5", n, vector);
    printf("Prueba 5 (N=31): %d\n", set);
    print_files(abs_path);
     if (set == 0){
        leer_fichero(abs_path, k);
    }
     */


    /*Test 6: N = 32 */
    printf("\nTest 6: N=32\n");
    /*
    print_files(abs_path);
    n = 32;
    k = 6;
    for (int i = 0; i <= n; i++) { vector[i] = (double) i; }
    set = set_value(k, "prueba_6", n, vector);
    printf("Prueba 6 (N=32): %d\n", set);
    print_files(abs_path);
     if (set == 0){
        leer_fichero(abs_path, k);
    }
    */

    /*Test 7: N = 33 */
    printf("\nTest 7: N=32\n");
    /*
    print_files(abs_path);
    n = 33;
    k = 7;
    for (int i = 0; i <= n; i++) { vector[i] = (double) i; }
    set = set_value(k, "prueba_7", n, vector);
    printf("Prueba 7 (N=33): %d\n", set);
    print_files(abs_path);
     if (set == 0){
        leer_fichero(abs_path, k);
    }
     */


    /*Test 8: len(cadena) > 255 */
    printf("\nTest 8: len(cadena) > 255 \n");
    print_files(abs_path);
    n = 1;
    k = 8;
    for (int i = 0; i <= n; i++) { vector[i] = (double) i; }
    char cadena[300];
    for (int i = 0; i <= 20; i++){ strcat(cadena, "prueba_8");}
    set = set_value(k, cadena, n, vector);
    printf("Prueba 8 (len(cadena) >255): %d\n", set);
    print_files(abs_path);
    if (set == 0){
        leer_fichero(abs_path, k);
    }


    return 0;
}