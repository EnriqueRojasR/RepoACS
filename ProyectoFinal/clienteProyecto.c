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
#define MAXDATASIZE 300

int main(int argc, char *argv[]){
  int long_mensaje;

  //Sockfd es el descriptor que utilizara la funcion, numbytes el temaño de bytes que recibira
  int sockfd, numbytes;

  //Se declara un arreglo de tamaño definido por MAXDATASIZE
  char buf[MAXDATASIZE];

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
  int menu = 0;
  do{
  char mensaje[100];
  printf("Esperando comando:\n>> ");
  fgets(mensaje, 100,stdin);
  long_mensaje = strlen(mensaje);

  int res_send;
  if((res_send = send(sockfd, mensaje, long_mensaje, 0)) == -1){
    perror("Send");
  exit(1);
  }

  //'numbytes' es el tamaño que se recibe del Servidor, este se obtiene con el descriptor
  //el buffer donde recibe la Informacion, el tamaño maximo que puede tener el buffer y el protocolo utilizado
  //en caso de que exista un error se imprimira que tipo de error
  if((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1){
    perror("recv()");
    exit(1);
  }
  else if(strcmp(buf,"\n>> HASTA LUEGO \n")==0){
    menu = menu + 1;
    exit(1);}
  else
   //Si todo va bien, se imprime OK
   printf("Client-The recv() is OK...\n");

   //Obtenemos la Informacion del buffer
   buf[numbytes] = '\0';
   //Imprimimos el buffer que se recibio y cerramos el socket
   printf("Client-Received: \n\t %s\n", buf);
 }while(menu == 0);
 printf("Client-closing sockfd \n");
 close(sockfd);
 return 0;
  }

}
