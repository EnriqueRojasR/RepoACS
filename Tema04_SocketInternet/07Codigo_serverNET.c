#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <limits.h>

#define PORT 9000
#define QLEN 2

void main()
{
  struct sockaddr_in servidor;
  struct sockaddr_in cliente;
  struct hostent* info_cliente;
  int fd_s, fd_c;
  int longClient;
  char buf_peticion[256];   //peticion o request es la que va de cliente a servidor
  char buf_respuesta[256];  // el mensaje de servidor a cliente es respuesta o response

  fd_s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);   //funcion socket

    //declaracion de la estructura del socket.
  memset((char *) &servidor, 0, sizeof(servidor));
  servidor.sin_family = AF_INET;
  servidor.sin_addr.s_addr = INADDR_ANY;  //esto nos dice que el servidor aceptara cualquiera conexion en cualquiera de sus interfacez de red.
  servidor.sin_port = htons((u_short) PORT);
  memset(&(servidor.sin_zero), '\0', 8);    //atributo de  llenar 8 ceros char. Esto era obligatorio en las distribuciones viejas de linux.

  bind(fd_s, (struct sockaddr *) &servidor, sizeof(servidor));    //aquie se liga el socket con el puerto

  listen(fd_s, QLEN);

  longClient = sizeof(cliente);   //

  while(1)
  {
    fd_c = accept(fd_s, (struct sockaddr *) &cliente, &longClient);

    info_cliente = gethostbyaddr((char *) &cliente.sin_addr, sizeof(struct in_addr), AF_INET);
    /* Lo siguiente es para obtener la fecha y hora y se impriman en pantalla */
    time_t T = time(NULL);
    struct tm tm = *localtime(&T);
    printf("%02d/%02d/%04d %02d:%02d:%02d-Cliente conectado ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf(" desde: %s\n\n", info_cliente -> h_name);

    printf("0. buf_peticion=%s\n", buf_peticion);
    do
    {
      int n = recv(fd_c, buf_peticion, sizeof(buf_peticion), 0);
      printf("2. longitud de buf_peticion=%d\n", strlen(buf_peticion));
      printf("3. El mensaje del cliente es %s\n", buf_peticion);
      buf_peticion[n] = '\0'; //truncamos el numero de bits enviados, (truncamos el mensaje)
      printf("strcmp(buf_peticion,\"adios\")=%d\n", strcmp(buf_peticion,"adios"));

      fgets(buf_respuesta, LINE_MAX, stdin);    //el mensaje se envia desde el teclado.
      printf("El mensaje para cliente es %s\n", buf_respuesta);
      send( fd_c, buf_respuesta, strlen(buf_respuesta), 0 );
    }
    while( strcmp(buf_peticion,"adios\n") != 0 );
    printf("Se ha cerrado la conexion con el cliente... Esperando al siguiente\n");
    close(fd_c);
  }
  close(fd_s);
  shutdown( fd_s, SHUT_RDWR );
  exit(0);
}
