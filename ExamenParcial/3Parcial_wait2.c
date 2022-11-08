#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Rojas Ruiz Luis Enrique

int main()
{
  printf("Rojas Ruiz Luis Enrique\n");
  int retorno_fork;                          // aqui se guardara el id del proceso fork
  int arg_wait;                               
  int pid = getpid();                        // declaramos la variable que almacenara el ID del proceso
  printf( "Iniciando proceso con pid %d\n", pid );
  printf( "Llamando a fork\n" );
  retorno_fork = fork();                    // declaramos e igualamos fork a la variable retorno_fork
  if( retorno_fork != 0 )                   //
  {
    printf( "Proceso padre, la variable retorno_fork=%d\n",retorno_fork );
    printf( "Proceso padre, llamando a wait\n" );
    int retorno_wait =  wait( &arg_wait );    //bloqueamos el proceso padre para que se ejecute le proceso hijo 
    printf( "Proceso padre, despues de wait\n" );
    printf( "Proceso padre, el valor &arg_wait=%p\n",&arg_wait );   
    printf( "Proceso padre, la variable arg_wait=%d\n",arg_wait );            // variable que nos indicara si el proceso se termino de manera correcta o no
    printf( "Proceso padre, WIFEXITED(arg_wait)=%d\n",WIFEXITED(arg_wait) );      // variable que nos indicara si el proceso termino de manera normal,por exit() o wait()
    printf( "Proceso padre, WEXITSTATUS(arg_wait) codigo de salida del hijo=%d\n",WEXITSTATUS(arg_wait) );    //variable que evalúa     los   ocho   bits   menos   significativos   del   código   de retorno del hijo que terminó
    printf( "Proceso padre, la variable retorno_wait=%d\n",retorno_wait );          // es el valor del ID del proceso hijo al cual se espero
    printf( "EXIT_SUCCESS en el proceso padre=%d\n", EXIT_SUCCESS );
    exit( EXIT_SUCCESS );       // //argumento de la llamada a exit()= true
  }
  else
  {
    printf( "Proceso hijo, el pid es %d\n", getpid() );
    printf( "Proceso hijo, a dormir 10 seg\n" );
    sleep( 10 );      // tiempo por el cual estara dormido el proceso hijo.
    printf( "Proceso hijo, despierta\n" );
    printf( "proceso hijo=%d\n", 2 );
    exit( 2 ); //argumento de la llamada a exit(2)
  }
}
