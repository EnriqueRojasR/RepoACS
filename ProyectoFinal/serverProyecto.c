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

#define MYPORT 3490

#define BACKLOG 10

#define MAXDATASIZE 300


void sigchld_handler(int s){
  while (wait(NULL) > 0);
}

int env_mensaje(int total, char *arreglo[], int new_fd){
  int menu= 0;
  do{ //opcion de .....
  if(strcmp(arreglo[0],"INSERT")==0 || strcmp(arreglo[0], "insert")==0){
    if(total >= 5){
      int num_cuenta = (int) strtol(arreglo[1], NULL, 10);
      if (num_cuenta != 0){
        char *cuenta = arreglo[1];
        char tipo[] = ".txt";
        char nombrearchivo[100];
        strcat(strcpy(nombrearchivo, cuenta), tipo);

        FILE *datos = fopen(nombrearchivo, "w");  //Crea archivo de extension txt
        if(!datos){
          printf("ERROR AL CREAR EL ARCHIVO\n");
          return 1;
        }
        for (int j =2; j<total; j++){
          fputs(arreglo[j], datos);
          fputs(" ", datos);
        }
        fclose(datos);    //CIERRA EL ARCHIVO
        if(send(new_fd, ">> COMANDO INSERT RECIBIDO\n", 35, 0) == -1)
          perror("Server-send() error lol!");

      }
    else{       //ERROR SI EL SEGUNDO PARAMETRO NO ES ENTERO MANDA ERROR.
      if(send(new_fd, "\n>> SEGUNDO PARAMETRO NO ES PERMITODO\n", 45, 0) == -1){
        perror("Server-send() error lol! - Insert");
      }
      return 1;
    }
    return 0;
    }
  }
  //OPCION DE SELECT
  else if (strcmp(arreglo[0], "SELECT")==0 || strcmp(arreglo[0], "select")==0){
    if(total >= 2){
      int num_cuenta = (int) strtol(arreglo[1], NULL, 10);
      if(num_cuenta != 0){
        char *cuenta = arreglo[1];
        char tipo[] = ".txt";
        char nombrearchivo[100];
        strcat(strcpy(nombrearchivo, cuenta), tipo);
        char nombre[300];
        int long_nombre;
        FILE *datos = fopen(nombrearchivo, "r");
        if(datos == NULL){
          if(send(new_fd, ">> NO SE ENCONTRO EL NUMERO DE CUENTA\n", 50, 0) == -1)
            perror("Send -send() error lol! - Select");
          return 0;
        }
        fgets(nombre, 100, datos);
        fclose(datos);
        long_nombre = strlen(nombre);
        if(send(new_fd, nombre, long_nombre, 0) == -1)
          perror("Server-send() error lol! - Select");

      }
      else{
        if(send(new_fd, "\n>>SEGUNDO PARAMETRO NO ES UN NUMERO DE CUENTA\n", 45, 0) == -1){
          perror("Server-send() error lol!");
        }
        return 1;
      }
      return 0;
    }
  }
  //OPCION DE QUITAR
  else if(strcmp(arreglo[0], "QUIT") == 0 || strcmp(arreglo[0],"quit")==0){
    if(send(new_fd, "\n>> HASTA LUEGO\n", 16, 0) == -1){
      perror("Server-send() error lol! -2");
    }
    menu = menu+1;
      close(new_fd);
      return 2;
  }
  else{
    if(send(new_fd, ">> COMANDO NO VALIDO\n", 35, 0) == -1){
      perror("Server_send() eroror lol! -3");
    }
    return 0;
  }
 }while(menu == 0);
}

int main(int argc, char *argv[ ]){

  //Se declara el descriptor y la nueva conexion fd
  int sockfd, new_fd;

  //Se crea la esctructura de mi conexion
  struct sockaddr_in my_addr;

  //Se crea el conector
  struct sockaddr_in their_addr;

  int sin_size;
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
    perror("server - setsockopt() error lol!");
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
      int num_bytes_leidos = recv(new_fd, buffer, MAXDATASIZE - 1, 0);
      buffer[num_bytes_leidos] = '\0';

          //El hijo no necesita el Listener
          //Cerramos el SOCKF por que no lo necesita para escuchar, seguido de esto
          //se envia la siguiente cadena, colocando tambien su longitud de esta y el protocolo a utilizar
          close(sockfd);
          int total = 0;
        char ** arreglo = NULL;
        char *token = NULL;
        token = strtok(buffer, " ");
        while(token != NULL){
          arreglo = realloc(arreglo, sizeof(char*) * (total + 1));
          arreglo[total] = token;
          total++;
          token = strtok(NULL," ");
        }

        menu = env_mensaje(total, arreglo, new_fd);
      }while(menu != 2);
        exit(0);
      }//cierra el fork
      else
        printf("Server-send is OK...!\n");
      /* El padre no necesita esto */
      //Se termina la conexion y se indica que se ha hecho el proceso correctamente.
      close(new_fd);
      printf("Server- new socket, new_fd closed successfully... \n");
    }
    return 0;
}
