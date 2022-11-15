#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int server (int client_socket)
{
 while (1)
 {
  int length;
  char* text;
  /* Primero, lee la longitud del mensaje.
  Si read() regresa cero, es porque el cliente cerro la conexion */
  if (read (client_socket, &length, sizeof (length)) == 0)
   return 0;
  printf("la longitud del mensaje es: %d\n", length);

  /* Asigna un buffer para mantener el mensaje
  Reserva la memoria con malloc() */
  text = (char*) malloc (length);

  /* Lee el mensaje y lo imprime */
  read (client_socket, text, length);
  printf ("%s\n", text);

  /* Si el cliente envia el mensaje "quit", el servidor termina */
  if (!strcmp (text, "quit"))
   return 1;
  else
  {
   /* Si no envia "quit", libera el buffer para el proximo mensaje */
   free (text);
  }
 }
}

int main (int argc, char* const argv[])
{
 /* File descriptor del socket servidor */
 int socket_fd;

 /* estructura socket servidor */
 struct sockaddr_un name;
 int client_sent_quit_message;
 const char* const socket_name = argv[1]; /*

 /* Crea el socket. */
 socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);

 /* Indica que este es el servidor */
 name.sun_family = AF_LOCAL;
 strcpy (name.sun_path, socket_name);
 bind (socket_fd, (struct sockaddr *)&name, SUN_LEN (&name));

 /* Escucha por conexiones */
 listen (socket_fd, 5);

 /* Acepta conexiones repetidamente, con cada conexion llama a la funcion server()
 para tratar a cada cliente. Continua asi hasta que el cliente envie "quit"
 */
 do
 {
  /* Esta es la estructura socket cliente en el servidor */
  struct sockaddr_un client_name;
  socklen_t client_name_len;
  int client_socket_fd;

  /* Acepta una conexion */
  client_socket_fd = accept (socket_fd, (struct sockaddr *)&client_name, &client_name_len);

  /* Maneja la conexion */
  client_sent_quit_message = server (client_socket_fd);

  /* Cierra la conexion con este cliente en especifico */
  close (client_socket_fd);
 }
 while (!client_sent_quit_message);

 /* Remueve el archivo del socket */
 close (socket_fd);
 unlink (socket_name);
 return 0;
}
