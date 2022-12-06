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

int main(int argc, char *argv[])
{

 int numbytes;
 char buf[100];

 // del lado server tenemos 2 estructuras sockaddr_in
 // una para el propio server y otra para la conexion cliente
 // por lo que necesitamos 2 file descriptor
 int server_fd, cliente_fd;

 // Estas son las 2 estructuras, la primera  llamada servidor,
 // que se asociara a server_fd
 // y la segunda estructura llamada cliente que se asociara a cliente_fd
 struct sockaddr_in servidor;    // información sobre mi direccion (servidor)
 struct sockaddr_in cliente; // información sobre la dirección del cliente

 // La longitud o tamaño de servidor y de cliente
 int sin_size_servidor;
 int sin_size_cliente;

 if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
 {
  perror("socket");
  exit(1);
 }

 if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) == -1)
 {
   perror("Server-setsockopt() error!");
   exit(1);
 }
 else
   printf("Server-setsockopt is OK...\n");

 servidor.sin_family = AF_INET;         // Ordenación de bytes de la máquina
 servidor.sin_port = htons( atoi(argv[1]) );     // short, Ordenación de bytes de la red
 servidor.sin_addr.s_addr = INADDR_ANY; // Rellenar con mi dirección IP
 memset(&(servidor.sin_zero), '\0', 8); // Poner a cero el resto de la estructura

 sin_size_servidor = sizeof( servidor );
 if (bind(server_fd, (struct sockaddr *)&servidor, sin_size_servidor) == -1)
 {
  perror("bind");
  exit(1);
 }

 if (listen(server_fd, 1) == -1)
 {
  perror("listen");
  exit(1);
 }

 sin_size_cliente = sizeof( cliente );

 if ((cliente_fd = accept(server_fd, (struct sockaddr *)&cliente, &sin_size_cliente)) == -1)
 {
  perror("accept");
  exit(1);
 }
 printf("server: conexion cliente desde %s\n", inet_ntoa(cliente.sin_addr));

 if ((numbytes=recv(cliente_fd, buf, 100-1, 0)) == -1) {
    perror("recv");
    exit(1);
 }

 buf[numbytes] = ' ';
 buf[numbytes+1] = '>';
 buf[numbytes+2] = ' ';
 buf[numbytes+3] = 'a';
 buf[numbytes+4] = '.';
 buf[numbytes+5] = 't';
 buf[numbytes+6] = 'x';
 buf[numbytes+7] = 't';
 buf[numbytes+8] = '\0';

 // printf("Received: %s\n",buf);

 system(buf);

 // Se lee el archivo a.txt
 char* fs_name="a.txt";
 char sdbuf[LENGTH]; // Send buffer
 printf("[Server] Enviando salida al Cliente...\n");
 FILE *fs = fopen(fs_name, "r");
 if(fs == NULL)
 {
  printf("ERROR: File %s not found on server.\n", fs_name);
  exit(1);
 }

 bzero(sdbuf, LENGTH);
 int fs_block_sz;
 while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
 {
  if(send(cliente_fd, sdbuf, fs_block_sz, 0) < 0)
  {
   printf("ERROR: al enviar la salida del comando al cliente\n");
   exit(1);
  }
  bzero(sdbuf, LENGTH);
 }
 fclose( fs );
 printf("Ok sent to client!\n");


 close(cliente_fd);

 close(server_fd);
 shutdown(server_fd, SHUT_RDWR);

 // Termina con exit(0) que significa terminacion exitosa
 exit(0);

 return 0;
}
