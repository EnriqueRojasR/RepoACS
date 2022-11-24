#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>
/*
#include <sys/wait.h>
*/

/*
 * En esta funcion, el cliente envÃ­a la cabecera propia de la especificacion HTTP
 * y el servidor responde con una respuesta codigo HTML
 *
 */
void get_home_page (int socket_fd)
{
 char buffer[10000];

 sprintf (buffer, "GET / HTTP/1.0\n\n");
 write (socket_fd, buffer, strlen (buffer));
 /* el ciclo while(1), la funcion read() y la impresion de la respuesta se comenta porque no queremos saturar muestro cliente */
 /*
 while (1)
 {
  if ( read (socket_fd, buffer, 10000) == 0 )
   return;

  fwrite (buffer, sizeof (char), number_characters_read, stdout);
 }
 */
}

void main(int argc, char *argv[])
{
  int socket_fd;
  struct sockaddr_in name;
  struct hostent* hostinfo;

  if(argc < 3)
  {
    fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
    exit(1);
  }

  int contador_de_hijos = 0;
  int retorno_fork;
  while( contador_de_hijos < atoi( argv[3] ) )
  {
    if( (retorno_fork = fork()) == 0 )
    {
      /* Crea el socket */
      socket_fd = socket (PF_INET, SOCK_STREAM, 0);
      /* Inicializa la estructura */
      name.sin_family = AF_INET;
      hostinfo = gethostbyname (argv[1]);
      if (hostinfo == NULL)
        exit(1);
      else
        name.sin_addr = *((struct in_addr *) hostinfo->h_addr);
      /* Servidor Web utiliza el puerto 80. */
      name.sin_port = htons ( atoi( argv[2] ) );
      /* Se conecta al servidor */
      if (connect (socket_fd, (struct sockaddr *)&name, sizeof (struct sockaddr_in)) == -1) {
       perror ("connect");
       exit(1);
      }
      /* Llama a la funcion get_home_page para obtener la pagina principal o home page */
      printf("Hijo %d enviando peticion...\n", contador_de_hijos);
      get_home_page (socket_fd);
      close(socket_fd);
      exit(0);
    }
    else
    {

      int returnStatus;
      waitpid(retorno_fork, &returnStatus, 0);
      if (returnStatus == 0)
      {
        printf("El proceso hijo %d termino normalmente\n", retorno_fork);
      }
      else
      {
        printf("El proceso hijo termino con error!");
      }

      contador_de_hijos++;
    }
  }

  exit(0);
}
