#include <stdio.h>
#include <string.h>

int main()
{
  int i;

  for(i=0; i < 135; i++)
  {
    printf( "%d: %s\n", i , strerror( i ) );
  }
  return 0;
}
