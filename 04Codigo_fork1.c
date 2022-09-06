#include <stdio.h>
#include <unistd.h>

int main ()
{
    pid_t id_hijo;
    printf( "1: el id del proceso main es %d\n", getpid() );
    id_hijo = fork ();
    printf( "2: Este printf saldra duplicado\n");
    printf( "3: El id del proceso hijo es %d\n", id_hijo );
    return 0;
}
