#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define SERVER "localhost"
//#define SERVER "132.248.59.6"
#define PORT 4897
#define BLEN 128

void main(int argc, char *argv[])
{
  struct sockaddr_in socket_cliente;
  struct hostent *h;
  int fd_c,fd_s;
  int n;
  char *host;
  char respuesta[BLEN];


  fd_c = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);



  // memset((char *) &socket_cliente, 0, sizeof(struct sockaddr_in));
  socket_cliente.sin_family = AF_INET;
  socket_cliente.sin_port = htons((u_short) PORT);
  h = gethostbyname(SERVER);
  memcpy(&socket_cliente.sin_addr, h->h_addr, h->h_length);


  connect(fd_c, (struct sockaddr *) &socket_cliente, sizeof(socket_cliente));


  char *buf = "Rojas Ruiz Luis Enrique";
  send(fd_c, buf, strlen(buf), 0);
  printf("Envio mi nombre: %s \n", buf);

  n = recv(fd_c, respuesta, sizeof(respuesta), 0);
  printf("Espero la respuesta del servidor \n");
  write(1,respuesta,n);
  printf("\n");

  close(fd_c);
  exit(0);
}
