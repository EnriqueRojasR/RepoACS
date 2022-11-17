/************************************************************/
/**************                         cliente.c           **********************/
/************************************************************/
/*********                   proceso cliente con sockets AF_UNIX   **********/
/************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <sys/un.h>           /*  para sockets UNIX  */

#define PROTOCOLO_DEFECTO 0

/****************************************************/

int main()
{
 int dfClient, longitud, resultado;
 struct sockaddr_un dirUNIXServer;
 struct sockaddr* puntSockServer;

 puntSockServer = ( struct sockaddr* ) &dirUNIXServer;
 longitud = sizeof ( dirUNIXServer );

 printf("socket (AF_UNIX, SOCK_STREAM, 0)\n");
 dfClient = socket ( AF_UNIX, SOCK_STREAM, PROTOCOLO_DEFECTO );
                 /* se crea un socket UNIX, bidireccional */

 dirUNIXServer.sun_family = AF_UNIX;    /* tipo de dominio server */
 strcpy ( dirUNIXServer.sun_path, "socket" );   /* nombre server */

 do
  {
  printf("Intentando conectarse\n");
   resultado = connect ( dfClient, puntSockServer, longitud );
   if ( resultado == -1 )
     sleep (1);   /* reintento */
 }
 while ( resultado == -1 );

 printf("Enviando el mensaje \"Este es un mensaje para el servidor\"\n");

 int res_send = send( dfClient, "Este es un mensaje para el servidor\n", 35, 0 );
 printf("res_send=%d\n",res_send);

 printf("close(dfClient)\n");
 close ( dfClient );      /* cierra el socket */
 exit (0);     /* buen fin */

}

/************* fin de cliente.c ****************************/
