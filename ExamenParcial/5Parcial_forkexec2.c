//Rojas Ruiz Luis Enrique



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


/*
Al analizar el codigo y el comportamiento de este al ejecutarlo, me puedo dar cuenta que en esta ocasión se hizo uso de la llamada a wait(), a diferencia del el primer ejercicio realizado. 
Ya que en esta ocasión el proceso hijo fue completado sin la interrupcion del proceso padre. 
Esto se debe a que se hizo una comparacion  utilizando una varible llamada child_status, el cual nos indica el numero de procesos hijo que tiene que esperar antes de terminar con el proceso padre y con esto evitar un proceso zombie o huerfano.

Como se puede observar en el encabezado se indica que se tiene que esperar un proceso hijo, este le indicara al padre que tiene que esperar, es aquí donde entra la funcion wait. 
Ya ejecutado y terminado el proceso hijo se vuelve a obtener el estado de los hijos, al marcar cero. 
El proceso padre termina y nos arroja la informacion del arg_wait el cual nos indica cero que significa que termino con normalidad y por medio de una llamada exit()

*/
int spawn (char* program, char** arg_list)
{
  pid_t child_pid;
  /* Duplicate this process. */
  child_pid = fork ();
  if (child_pid != 0) /* This is the parent process. */
    return child_pid;
  else {
    /* Now execute PROGRAM, searching for it in the path. */
    printf("soy el hijo, lanzo el ls y termino\n");
    execvp (program, arg_list);
    /* The execvp function returns only if an error occurs. */
    fprintf (stderr, "an error occurred in execvp\n");
    abort ();
  }
}

int main ()
{
  printf("Rojas Ruiz Luis Enrique\n");
  int child_status=1;
  printf("1.child_status=%d\n",child_status);
  /* The argument list to pass to the "ls" command. */
  char* arg_list[] = {
    "ls", /* argv[0], the name of the program. */
    "-l",
    "/",
    NULL /* The argument list must end with a NULL. */
  };

  /* Spawn a child process running the "ls" command. Ignore the
   * 	returned child process ID. */
  spawn ("ls", arg_list);
  printf("soy el padre, voy a esperar a que el hijo termine\n");
  /* Wait for the child process to complete. */
  wait (&child_status);
  if (WIFEXITED (child_status)){
    printf("2.child_status=%d\n",child_status);
    printf ("the child process exited normally, with exit code %d\n", WEXITSTATUS (child_status));
  }
  else
    printf ("the child process exited abnormally\n");
  return 0;
}

