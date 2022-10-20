#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

/*
 * Rutina de tratamiento para la seÃ±al 2 SIGINT
 */
void manejador_senales(int sig)
{
  static int cnt = 0;

  printf("SeÃ±al nÃºmero %d recibida\n", sig);
  if( sig == SIGINT )
  {
    printf("seÃ±al SIGINT %d recibida\n", sig);
    if( cnt < 5 )
      printf("contador = %d\n", cnt++);
    else
      exit( 0 );
  }
}

/*
 * main: Inicializa el manejador de la seÃ±al SIGINT y
 * se pone en espera para recibir la seÃ±al
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
