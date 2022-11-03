#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//Rojas Ruiz Luis Enrique

int main()
{
  printf("Rojas Ruiz Luis Enrique \n");
  int arg_wait;
  printf( "\n Iniciando proceso con pid %d\n", getpid() );
  printf( "Llamando a wait\n" );
  int retorno_wait = wait( &arg_wait );
  printf( "Despues de wait\n" );
  printf( "El valor &arg_wait=%p\n",&arg_wait );
  printf( "La variable arg_wait=%d\n",arg_wait );
  printf( "La variable retorno_wait=%d\n",retorno_wait );
  return 0;
}
