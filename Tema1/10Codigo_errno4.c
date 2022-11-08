#include <stdio.h>
#include <errno.h>

// Esta version es muy parecida a errno3
// la diferencia es que esta version
// llama a la funcion perror( string )
// observen la linea de perror( "errno" )
// y que imprime en pantalla
int main()
{
  int result;

  result = rename("this.txt","that.txt");
  if( result != 0 )
  {
    printf("errno:%d\n", errno);
    perror( "errno" );
    printf("File renaming error: ");
    switch(errno)
    {
     case EPERM:
                printf("Operation not permitted\n");
                break;
     case ENOENT:
                printf("File not found\n");
                perror("rename");
                break;
     case EACCES:
                printf("Permission denied\n");
                break;
     case ENAMETOOLONG:
                printf("Filename is too long\n");
                break;
     default:
                printf("Unknown error\n");
    }
    return(1);
  }
  puts("File renamed");

  return(0);
}
