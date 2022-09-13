#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Este ejemplo muestra la funcion execv con el comando ls -l /
int main(void)
{
  // como es execv entonces es un vector/arreglo
  // el cual debe declararse previo a la llamada a execv
  // la sintaxis es:
  // int execv (char *path, char *argv[ ]);
  // path es la ruta incluyendo el nombre del comando/ejecutable
  // En C el nombre del comando/ejecutable es el argumento 0
  // por eso se repite
  // con NULL se indica que se llego al final del vector de argumentos
  // Si execl falla devuelve -1 y entra al if por lo que termina
  // con exit(EXIT_FAILURE)
  char *args[]={"/bin/ls","-l","/",NULL};
  if( execv("/bin/ls", args) == -1)
  {
    puts("execl genero error y devolvio -1");
    perror("execv");
    exit(EXIT_FAILURE);
  }
  // Por lo tanto, sea exito o error, las sig 2 sentencias
  // JAMAS se ejecutan
  puts("Si execv es exitoso, esto no se imprime");
  exit(EXIT_SUCCESS);
}
