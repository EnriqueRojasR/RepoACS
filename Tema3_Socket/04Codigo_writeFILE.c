//Rojas Ruiz Luis Enrique

#include<stdio.h>

int main()
{
  // Este es el apuntador a FILE
  FILE *filePointer;

  // Se abre el archivo para escritura
  filePointer = fopen("archivo_con_file.txt", "w");

  printf("Escribiendo en el archivo archivo_con_FILE.txt usando FILE *\n");

  // Se escriben las 3 lineas de texto al archivo
  fprintf(filePointer, "%s\n", "Mi nombre es: Rojas Ruiz Luis Enrique" );
  fprintf(filePointer, "%s\n", "Este es un archivo de prueba" );
  fprintf(filePointer, "%s\n", "para la materia ACS" );

  // Se cierra el archivo
  fclose( filePointer );
  return 0;
}
