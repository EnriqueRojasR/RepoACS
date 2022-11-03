#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//Rojas Ruiz Luis Enrique

int main()
{
  printf("Rojas Ruiz Luis Enrique \n");
  int arg_wait;                                                 //inicializamos la funcion wait
  printf( "\n Iniciando proceso con pid %d\n", getpid() );      
  printf( "Llamando a wait\n" );
  int retorno_wait = wait( &arg_wait );                        //igualamos la salida de wait a la variable de retorno_wait
  printf( "Despues de wait\n" );
  printf( "El valor &arg_wait=%p\n",&arg_wait );               
  printf( "La variable arg_wait=%d\n",arg_wait );             // variable que nos indicara si el proceso se termino de manera correcta o no
  printf( "La variable retorno_wait=%d\n",retorno_wait );     // valor del id del proceso hijo al cual esperaremos. Cuando no hay un segundo proceso por el cual esperar wait() devuelve -1
  return 0;
}
