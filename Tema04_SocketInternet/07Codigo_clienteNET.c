#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <limits.h>

void main(int argc, char *argv[])
{
  struct sockaddr_in server;
  struct hostent *sp;
  int sd;
  int n;
  char *host;
  char buf_peticion[LINE_MAX];
  char buf_respuesta[LINE_MAX];

  sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  memset((char *) &server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons( (u_short) atoi(argv[2]) );
  sp = gethostbyname( argv[1] );
  memcpy(&server.sin_addr, sp->h_addr, sp->h_length);

  connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr_in));

  while( strcmp(buf_peticion,"adios \n") != 0 )
  {
    fgets(buf_peticion, LINE_MAX, stdin);   //obtenemos de la entrada estandar(teclado), se mete al buf peticion
    printf("El mensaje al servidor es %s\n", buf_peticion);   //se imprime a pantalla para corroborar el mensaje
    send( sd, buf_peticion, strlen(buf_peticion), 0 );

    n = recv ( sd, buf_respuesta, sizeof(buf_respuesta), 0 );
    printf(" numero real de bytes leidos=%d\n",n);
    write(1,buf_respuesta,n);   //manera alternativa de imprimir a pantalla
  }

  close(sd);
  exit(0);
}
