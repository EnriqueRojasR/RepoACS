//Rojas Ruiz Luis Enrique

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
 int fd;
 int bytes_leidos = 0;
 // Porque 111? Porque esa es la cantidad de bytes que se escribio
 // en el ejemplo fd_write.c
 int longitud = 111;
 char* texto;

 if( (fd = open("archivo_con_fd.txt",  O_RDONLY | O_CREAT) ) == -1 )
 {
  printf("fallo apertura de archivo\n");
  exit(0);
 }
 else
 {
  printf("apertura de archivo exitosa\n");
  printf("file descriptor: %d\n", fd);

  // Previo a leer, hay que reservar la memoria para el texto a leer,
  // para ello debemos saber la longitud de la porcion de texto
  // que queremos leer. En este caso leeremos todo el texto.
  texto = malloc(longitud);

  if( (bytes_leidos = read(fd, texto, longitud ) ) == -1 )
  {
   printf("Error al leer el archivo\n");
   exit(0);
  }
  else
  {
   printf("lei %d bytes del archivo\n", bytes_leidos);
   printf("texto: %s\n", texto);
  }
 }
 return 0;
}
