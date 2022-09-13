#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Este ejemplo muestra la funcion execl con el comando ls -l /
int main(void)
{
  puts("En el proceso inicial, antes de llamar a execl\n");
  // como es execl entonces es una lista
  // la sintaxis es:
  // int execl (char *path, char *arg0,... char *argn, (char *)0);
  // path es la ruta incluyendo el nombre del comando/ejecutable
  // En C el nombre del comando/ejecutable es el argumento 0
  // por eso se repite
  // con NULL se indica que se llego al final de la lista de argumentos
  // Si execl falla devuelve -1 y entra al if por lo que termina
  // con exit(EXIT_FAILURE)
  if( execl("/bin/ls", "/bin/ls", "-l", "/", NULL) == -1)
  {
    puts("execl genero error y devolvio -1");
    perror("execl");
    exit(EXIT_FAILURE);
  }
  // Por lo tanto, sea exito o error, las sig 2 sentencias
  // JAMAS se ejecutan
  puts("Si execl es exitoso, esto no se imprime");
  exit(EXIT_SUCCESS);
}
