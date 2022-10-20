#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

/*
 * Rutina de tratamiento para la senal 2 SIGINT
 */
void manejador_senales(int sig) //deber ser void y recibir un entero.
{
  printf("Senal numero %d recibida\n", sig);
  if( sig == SIGINT )
    printf("senal SIGINT %d recibida\n", sig);
}

/*
 * main: Inicializa el manejador de la senal SIGINT y
 * se pone en espera para recibir la senal
 */
int main()
{
  if( signal(SIGINT, manejador_senales) == SIG_ERR )
  {
    printf("no puedo cachar SIGINT\n");
    perror("signal");
  }

  while( 1 )
  {
    printf("En espera de Control-C para cachar SIGINT\n");
    sleep( 5 );
  }

  return 0;
}
