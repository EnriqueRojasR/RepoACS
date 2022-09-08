#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
  int result;

  result = rename("this.txt","that.txt");
  if( result != 0 )
  {
    printf("errno:%d\n", errno);
    printf("File renaming error: ");
    switch(errno)
    {
     case EPERM:
                printf("Operation not permitted\n");
                break;
     case ENOENT:
                printf("%d: %s\n", errno,strerror(errno));
                printf("File not found\n");
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
