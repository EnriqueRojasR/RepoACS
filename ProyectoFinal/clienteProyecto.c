//UNAM FI
//Arquitectura Cliente Servidor
//Proyecto Final
//Rojas Ruiz Luis Enrique

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>


//El puerto del cliente al que nos conectaremos
#define PORT 3490
//Maximo numero de bytes que usaremos
#define MAXDATASIZE 3000
//maximo numero de bytes para la respuesta
#define MAXDATASIZE_RESP 20000

int main(int argc, char *argv[]){
  int long_mensaje;

  //Sockfd es el descriptor que utilizara la funcion, numbytes el temaño de bytes que recibira
  int sockfd, numbytes;

  //Se declara un arreglo de tamaño definido por MAXDATASIZE
  //char comando[MAXDATASIZE];
  int len_comando;

char buffer[MAXDATASIZE_RESP];


  //char buf[MAXDATASIZE_RESP];

  //indica que es un host de Internet
  struct hostent *he;

  //Informacion de la direccion
  struct sockaddr_in their_addr;

  //Se verifica que el segundo argumento recibido sea una direccion IP
  if(argc != 2){
    fprintf(stderr, "Client-Usage: %s host_servidor \n", argv[0]);

    //Solo salimos
    exit(1);
  }

  //Obtiene información del host y se almacena en 'he'
  if((he=gethostbyname(argv[1])) == NULL){
    perror("gethostbyname()");
    exit(1);
  }
  else
    //Se indica desde que IP se esta haciendo la conexion
    printf("Client-The remote host is: %s\n", argv[1]);

  // Crea un soket, si este tiene algun error lo imprime
  // El socket utiliza la clase AF_INET, es de tipo streamo de flujo y utiliza el protocolo 0
  //Esta variable sockfd es el descriptor
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("socket()");
    exit(1);
  }

  //En caso contrario indica que se ha creado exitosamente
  else
    printf("Cliente-The socket() sockfd is OK...\n");

  //Indica la familia de direcciones del host
  their_addr.sin_family = AF_INET;

  // Se manda a imprimir la direccion y el puerto
  printf("Server-using %s and port %d ...\n", argv[1], PORT);

  //Realiza una conversion de NODO a variable corta de red, que es el puerto.
  their_addr.sin_port = htons(PORT);

  //Pasa la Informacion del host, la direccion de Internet
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);

  memset(&(their_addr.sin_zero), '\0', 8);

  //Realiza la conexion entre el socket y mi direccion, en caso de error indica el error
  // recibe el descriptor, la direccion IP y puerto, y el tamaño del socket
  if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1){
    perror("connect()");
    exit(1);
  }

  //Si la conexion es correcta indica OK
  else
    printf("Client-The connect() is OK...\n");

  do{
  char comando[MAXDATASIZE];

  printf("Esperando comando:\n>> ");
  fgets(comando, 100,stdin);
  len_comando = strlen(comando);

  int res_send;
  if((res_send = send(sockfd, comando, len_comando, 0)) == -1){
    perror("Send");
  exit(1);
}else
printf("Comando enviado... \n");

  //'numbytes' es el tamaño que se recibe del Servidor, este se obtiene con el descriptor
  //el buffer donde recibe la Informacion, el tamaño maximo que puede tener el buffer y el protocolo utilizado
  //en caso de que exista un error se imprimira que tipo de error
  if((numbytes = recv(sockfd, buffer, MAXDATASIZE_RESP-1, 0)) == -1){
    perror("recv()");
    exit(1);
  }
   //Si todo va bien, se imprime OK
   printf("Client-The recv() is OK...\n");

   //Obtenemos la Informacion del buffer
   buffer[numbytes] = '\0';
   printf("Client-Received:\n%s\n",buffer);

 }while(len_comando != 0);
 printf("Client-closing sockfd \n");
 close(sockfd);
 return 0;
}
