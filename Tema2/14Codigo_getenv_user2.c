#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  printf("Rojas Ruiz Luis Enrique \n");
  printf( "el valor de la variable de entorno USER es: %s\n", getenv("USER") );
  printf( "el valor de la variable de entorno MI_VARIABLE es: %s\n", getenv("MI_VARIABLE") );
  return 0;
}
