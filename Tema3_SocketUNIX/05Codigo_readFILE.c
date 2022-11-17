//Rojas Ruiz Luis Enrique

#include<stdio.h>

int main()
{
  // Este es el apuntador a FILE
  FILE *filePointer ;
  // Arreglo donde se almacenarÃ¡n los datos del archivo
  char buff[200];

  // Se abre el archivo para lectura
  filePointer = fopen("archivo_con_file.txt", "r");

  // La funcion fscanf es utilizada para leer una palabra
  // del archivo. Lo leido es almacenado en buff
  // fscanf devuelve EOF cuando llega al final del archivo
  while( fscanf(filePointer, "%s", buff ) != EOF )
  {
    printf("s=%s\n",buff);
  }

  // Se cierra el archivo
  fclose( filePointer );
  return 0;
}
