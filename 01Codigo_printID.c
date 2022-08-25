#include<stdio.h>
#include<unistd.h> //usamos esta libreria ya que es la que tiene el comando getpid y getppid

int main()
{
  printf("El process id es %d\n", getpid());
  printf("El parent process id es %d\n", getppid());
  return 0;
}
