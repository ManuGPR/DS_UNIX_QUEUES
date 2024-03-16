# Pasos para compilar y ejecutar

1. Primero, compila el proyecto con el fichero Makefile usando make. Este fichero compilará también las pruebas.
2. Antes de ejecutar el cliente y el servidor, ejecuta el fichero *setup.sh* con la sentencia *. setup.sh*. Lo que hace es exportar la variable de entorno *LD_LIBRARY_PATH* con un valor igual al path donde está almacenado el proyecto, lo cual se puede hacer manualmente.
3. En la terminal donde se ha importado la variable de entorno, ejecuta el cliente. En otra terminal, ejecuta el servidor.
4. Si se quieren ejecutar los test, ejecuta el fichero *test.sh*. 
