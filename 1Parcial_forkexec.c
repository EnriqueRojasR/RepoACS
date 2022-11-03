//Rojas Ruiz Luis Enrique

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
//Arriba se muestran las librerias que ocuparemos para que el codigo funcione correctamente.

int spawn (char* program, char** arg_list) //declaramos la funcion spawn que nos ayudara a crear y ejecutar un nuevo proceso hijo
{                                         //duplicamos el proceso.
 pid_t child_pid;                         //declaramos una variable que nos mostrara con los ids de los procesos, en esta caso del proceso hijo sera igual a la del paadre.
 child_pid = fork ();                     //hacemos una llamada a fork 
 if (child_pid != 0)                      // declaramos la funcion if donde la condicion es que el ID del hijo sea diferente de cero
  return child_pid;                       //regresa el valor del id hijo, en caso de que la condicion se cumpla
 else
 {                                        //Esta parte solo se ejecutara si ocurre un error durante la ejecucion
  execvp (program, arg_list);             // en caso de que la condicion del if no se cumpla, recurrimos a llamar a la funcion execv 
  fprintf (stderr, "ocurrio un error al ejecutar execvp(...)\n");
  abort ();
 }
}

int main ()
{
  printf("Rojas Ruiz Luis Enrique \n");   //imprimimos el nombre del alumno
  char* arg_list[] = {                    // declaramos una cadena de caracteres en la cual viene incluido la sentencia que ejecutara el proceso hijo.
   "ls",
   "-l",
   "/",
   NULL
  };

  spawn ("ls", arg_list);               //hacemos el llamado a la funcion spawn previamente declarada.
  printf ("Termina el proceso padre\n");
  return 0;
}
