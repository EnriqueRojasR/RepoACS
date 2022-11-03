#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//Rojas Ruiz Luis Enrique

int spawn (char* program, char** arg_list)
{
 pid_t child_pid;
 child_pid = fork ();
 if (child_pid != 0)
  return child_pid;
 else
 {
  execvp (program, arg_list);
  fprintf (stderr, "ocurrio un error al ejecutar execvp(...)\n");
  abort ();
 }
}

int main ()
{
  printf("Rojas Ruiz Luis Enrique \n");
  char* arg_list[] = {
   "ls",
   "-l",
   "/",
   NULL
  };

  spawn ("ls", arg_list);
  printf ("Termina el proceso padre\n");
  return 0;
}
