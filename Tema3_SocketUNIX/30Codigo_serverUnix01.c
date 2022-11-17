#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
 // este es el descriptor de archivo o file descriptor
 // se le asignara el valor devuelto por la funcion socket
 int socket_fd;

 // creamos el socket
 // la funcion socket devuelve un int que es el file descriptor
 printf("socket (AF_UNIX, SOCK_STREAM, 0)\n");
 socket_fd = socket (AF_UNIX, SOCK_STREAM, 0);

 printf("socket_fd=%d\n",socket_fd);

 // una variable de tipo struct sockaddr_un
 // que sera nuestra estructura server socket
 struct sockaddr_un servidor;

 // un apuntador a la variable anterior
 struct sockaddr* pservidor = (struct sockaddr*)&servidor;

 // este int almacenara el size de la estructura
 // sockaddr_un que es nuestra estructura server socket
 int size_servidor = sizeof(servidor);

 // el archivo con el que se nombrara al socket
 // el archivo no debe existir y se creara con size 0
 const char* const socket_name = "/tmp/archivo";

 // inicializamos el atributo sun_family de la struct
 servidor.sun_family = AF_UNIX;

 // inicializamos el atributo sun_path con el nombre del archivo
 strcpy( servidor.sun_path, socket_name );

 printf("bind(socket_fd,pservidor,size_servidor)\n");
 bind(socket_fd,pservidor,size_servidor);

 printf("Hasta aqui llegan las funciones, vamos a dormir el proceso 10 seg.\n");

 printf("sleep por 10 segundos\n");
 sleep( 10 );

 printf("Antes de terminar el proceso hay que cerrar el descriptor y desligar el socker del archivo\n");

 printf("close(socket_fd)\n");
 close( socket_fd );
 printf("unlink( socket_name )\n");
 unlink( socket_name );
 return 0;
}
