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
  else if( sig == SIGKILL )
    printf("seÃ±al SIGKILL %d recibida\n", sig);
  else if( sig == SIGSTOP )
    printf("seÃ±al SIGSTOP %d recibida\n", sig);
  else if( sig == SIGTSTP )
    printf("seÃ±al SIGTSTP %d recibida\n", sig);
  else
    printf("seÃ±al %d recibida\n", sig);
}

/*
 * main: Inicializa el manejador de la seÃ±al SIGINT y
 * se pone en espera para recibir la seÃ±al
 */
int main()
{
  if( signal(SIGUSR1, manejador_senales) == SIG_ERR )
  {
    printf("no puedo cachar SIGUSR1\n");
    perror("signal");
  }
  if( signal(SIGINT, manejador_senales) == SIG_ERR )
  {
    printf("no puedo cachar SIGINT\n");
    perror("signal");
  }
  if( signal(SIGKILL, manejador_senales) == SIG_ERR )
  {
    printf("no puedo cachar SIGKILL\n");
    perror("signal");
  }
  if( signal(SIGSTOP, manejador_senales) == SIG_ERR )
  {
    printf("no puedo cachar SIGSTOP\n");
    perror("signal");
  }
  if( signal(SIGTSTP, manejador_senales) == SIG_ERR )
  {
    printf("no puedo cachar SIGTSTP\n");
    perror("signal");
  }
  while( 1 )
  {
    printf("En espera de Control-C para cachar SIGINT\n");
    sleep( 5 );
  }

  return 0;
}
