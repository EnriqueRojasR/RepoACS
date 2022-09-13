#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  printf( "el valor de la variable de entorno USER es: %s\n", getenv("USER") );
  return 0;
}
