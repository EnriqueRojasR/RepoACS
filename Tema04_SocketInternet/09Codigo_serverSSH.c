/*
** server.c -- Ejemplo de servidor de sockets internet
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define LENGTH 20000

#define MYPORT 3490

int main(int argc, char *argv[])
{

 int numbytes;
 char buf[100];

 // del lado server tenemos 2 estructuras sockaddr_in
 // una para el propio server y otra para la conexion cliente
 // por lo que necesitamos 2 file descriptor
 int sockfd, new_fd;

 // Estas son las 2 estructuras, la primera  llamada servidor,
 // que se asociara a sockfd
 // y la segunda estructura llamada cliente que se asociara a new_fd
 struct sockaddr_in my_addr;    // información sobre mi direccion (servidor)
 struct sockaddr_in their_addr; // información sobre la dirección del cliente

 // La longitud o tamaño de servidor y de cliente
 int sin_size_servidor;
 int sin_size_cliente;

 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
 {
  perror("socket");
  exit(1);
 }

 if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) == -1)
 {
   perror("Server-setsockopt() error!");
   exit(1);
 }
 else
   printf("Server-setsockopt is OK...\n");

 my_addr.sin_family = AF_INET;         // Ordenación de bytes de la máquina
 my_addr.sin_port = htons( MYPORT );     // short, Ordenación de bytes de la red
 my_addr.sin_addr.s_addr = INADDR_ANY; // Rellenar con mi dirección IP
 memset(&(my_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura

 sin_size_servidor = sizeof( my_addr );
 if (bind(sockfd, (struct sockaddr *)&my_addr, sin_size_servidor) == -1)
 {
  perror("bind");
  exit(1);
 }

 if (listen(sockfd, 1) == -1)
 {
  perror("listen");
  exit(1);
 }

 sin_size_cliente = sizeof( their_addr );

 if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size_cliente)) == -1)
 {
  perror("accept");
  exit(1);
 }
 printf("server: conexion cliente desde %s\n", inet_ntoa(their_addr.sin_addr));

 if ((numbytes=recv(new_fd, buffer,MAXDATASIZE-1, 0)) == -1) {
    perror("recv");
    exit(1);
 }

 buffer[numbytes] = ' ';
 buffer[numbytes+1] = '>';
 buffer[numbytes+2] = ' ';
 buffer[numbytes+3] = 'a';
 buffer[numbytes+4] = '.';
 buffer[numbytes+5] = 't';
 buffer[numbytes+6] = 'x';
 buffer[numbytes+7] = 't';
 buffer[numbytes+8] = '\0';

 // printf("Received: %s\n",buffer);

 system(buffer);

 // Se lee el archivo a.txt
 char* fs_name="a.txt";
 char sdbuf[LENGTH]; // Send buffer
 printf("[Server] Enviando salida al Cliente...\n");
 FILE *fs = fopen(fs_name, "r");
 if(fs == NULL) {
  printf("ERROR: File %s not found on server.\n", fs_name);
  exit(1);
 }

 bzero(sdbuf, LENGTH);
 int fs_block_sz;
 while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
 {
  if(send(new_fd, sdbuf, fs_block_sz, 0) < 0)
  {
   printf("ERROR: al enviar la salida del comando al their_addr\n");
   exit(1);
  }
  bzero(sdbuf, LENGTH);
 }
 fclose( fs );
 printf("Ok sent to client!\n");


 close(new_fd);

 close(sockfd);
 //shutdown(sockfd, SHUT_RDWR);

 // Termina con exit(0) que significa terminacion exitosa
 exit(0);

 return 0;
}
