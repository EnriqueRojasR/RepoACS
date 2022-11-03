#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//Rojas Ruiz Luis Enrique

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
