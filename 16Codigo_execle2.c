#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Este ejemplo muestra la funcion execle
// invocando a un programa nuestro getenv_user
// para leer la variable de entorno USER
int main(void)
{
  printf("Rojas Ruiz Luis Enrique \n");
  puts("En el proceso inicial, antes de llamar a execle\n");
  // como es execle entonces es una lista
  // y ademas puede leer variables de entorno que vienen en un arreglo
  // y que solo son validas para esta ejecucion
  // la sintaxis es:
  // int execle(char *path, char *arg0,... char*argn, (char *)0, char *envp[ ]);
  // path es la ruta incluyendo el nombre del comando/ejecutable
  // En C el nombre del comando/ejecutable es el argumento 0
  // por eso se repite
  // con NULL se indica que se llego al final de la lista de argumentos
  char *variables_entorno[] = { "PATH=/bin:/usr/bin", "USER=joe", NULL };
  printf( "el valor de la variable de entorno USER es: %s\n", getenv("USER") );
  printf( "ahora ejecutando ./getenv_user1, el valor de la variable de entorno USER es: \n" );
  if( execle("./13Codigo_getenv_user1", "./getenv_user1", NULL, variables_entorno) == -1)
  {
    puts("execle genero error y devolvio -1");
    perror("execle");
    exit(EXIT_FAILURE);
  }
  // Por lo tanto, sea exito o error, las sig 2 sentencias
  // JAMAS se ejecutan
  puts("Si execle es exito o error, esto no se imprime");
  exit(EXIT_SUCCESS);
}
