//Rojas Ruiz Luis Enrique

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
  int fd;
  int bytes_escritos = 0;
  char buff[] = "Prueba para escribir este texto a archivo, con file descriptor\nMi nombre es: Rojas Ruiz Luis Enrique\nMateria ACS";

  if( (fd = open("archivo_con_fd.txt",  O_RDWR | O_CREAT) ) == -1 )
  {
    printf("fallo apertura de archivo\n");
    exit(0);
  }
  else
  {
    printf("apertura de archivo exitosa\n");
    printf("file descriptor: %d\n", fd);

    if( (bytes_escritos = write(fd, buff, strlen(buff) ) ) == -1 )
    {
      printf("Error al escribir al archivo\n");
      exit(0);
    }
    else
    {
      printf("escribi %d bytes al archivo\n", bytes_escritos);
    }
  }
  return 0;
}
