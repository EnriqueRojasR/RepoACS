//UNAM FI
//Arquitectura Cliente Servidor
//Proyecto Final
//Rojas Ruiz Luis Enrique

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

/* EL puerto que usaremos para conectarnos */

#define LENGTH 20000

#define MYPORT 3490

#define BACKLOG 10

#define MAXDATASIZE 300


void sigchld_handler(int s){
  while (wait(NULL) > 0);
}


int main(int argc, char *argv[ ]){

  int numbytes;
  char buffer[100];

  //Se declara el descriptor y la nueva conexion fd
  int sockfd, new_fd;

  //Se crea la esctructura de mi conexion
  struct sockaddr_in my_addr;

  //Se crea el conector
  struct sockaddr_in their_addr;

  int sin_size;

  int sin_size_servidor;
  int sin_size_cliente;
  struct sigaction sa;
  int yes = 1;

  //Se crea el socket el cual utiliza la familia AF_NET, de tipo stream o de flujo, y se utiliza el protocolo 0
  //Si hay un error al crearlo lo marcaara, si se crea on extio imprime que todo esta bien
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("Server-socket() error lol!");
    exit(1);
  }
  else
    printf("Server-socket() sockfd is OK ... \n");

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
    perror("server - setsockopt() error!");
    exit(1);
  }
  else
    printf("Server-setsockopt is OK...\n");

    // Se indica el tipo de familia de direcciones a utilizar
    my_addr.sin_family =AF_INET;
    my_addr.sin_port =htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    printf("Server-Using %s and port %d ...\n", inet_ntoa(my_addr.sin_addr), MYPORT);
    memset(&(my_addr.sin_zero), '\0', 8);

    //Se asigna el socket al puerto, para ello utiliza el descriptor, el puntero a una estructura SOCKADDR
    //y la longitud de dicha esctructura
    //sin_size_servidor = sizeof( my_addr );
    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
      perror("Server-bind() error");
      exit(1);
    }
    else
      printf("Server-bind() is OK...\n");

    //Listen se utiliza para escuchar el socket, donde se pone el argumento del descriptor y el
    //numero de conexiones permitidas, en este caso esta definida con un valor de 10
    if(listen(sockfd, BACKLOG) == -1){
      perror("Server-listen() error");
      exit(1);
    }
    printf("Server-listen() is OK...Listening...\n");
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    //Usamos SIGNATION que es una funcion usada para indicar la accion realizada al recibir una señal especifica
    //este recibe como se especifica la señal, puede ser cualquiera menos SIGKILL y SIGSTOP
    //seguido de la mascara de la señal manejando y finalizando con las banderas estas pueden ser opcionales
    if(sigaction(SIGCHLD, &sa, NULL) == -1){
      perror("Server-sigaction() error");
      exit(1);
    }
    else
      printf("Server-sigaction() is OK...\n");

    //Iniciamos un ciclo para que se acepten a los clientes a conectarse.
    while(1){
      sin_size = sizeof(struct sockaddr_in);

      //Se realiza la conexion del socket, si es un error se indicara.
      if((new_fd = accept(sockfd,(struct sockaddr *)&their_addr, &sin_size)) == -1){
        perror("Server-accept() error");
        continue;
      }
      else

      //Se imprimira lo siguiente si todo sale perfectamente
      printf("Server-accept() is OK...\n");
      printf("Server-new socket, new_fd is OK...\n");
      printf("Server: Got connection from %s\n", inet_ntoa(their_addr.sin_addr));


      //Creamos un hijo, por cada cliente que se conecte al Servidor
      if(!fork()){
        int menu = 0;
        do{
      char buffer[MAXDATASIZE];
      //char comando[MAXDATASIZE];
      if ((numbytes=recv(new_fd, buffer,MAXDATASIZE-1, 0)) == -1) {
         perror("Server-recv error!");
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

       printf("Received: %s\n",buffer);

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

          //El hijo no necesita el Listener
          //Cerramos el SOCKF por que no lo necesita para escuchar, seguido de esto
          //se envia la siguiente cadena, colocando tambien su longitud de esta y el protocolo a utilizar
          close(sockfd);

        }

      while( strcmp(buffer,"\n") != 0 );
      printf("Se ha cerrado la conexion con el cliente... Este hijo termina\n");
      close(new_fd);
      exit( 0 );
      }//cierra el fork
      else
        printf("Server-send is OK...!\n");
      /* El padre no necesita esto */
      //Se termina la conexion y se indica que se ha hecho el proceso correctamente.
      close(new_fd);
      printf("Server- new socket, new_fd closed successfully... \n");
    }
    close(sockfd);
    shutdown(sockfd,SHUT_RDWR);
    return 0;
}
