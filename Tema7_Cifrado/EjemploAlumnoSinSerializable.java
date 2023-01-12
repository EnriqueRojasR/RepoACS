public class EjemploAlumnoSinSerializable
{
 String nombre;
 int edad;

 public static void main(String[] args)
 {
  EjemploAlumnoSinSerializable alumno = new EjemploAlumnoSinSerializable();
  System.out.println( "Antes de asignar valores a atributos");
  System.out.println( "nombre=" + alumno.nombre );
  System.out.println( "edad=" + alumno.edad );
  System.out.println("----------------------------");
  alumno.nombre = "Juan";
  alumno.edad = 23;
  System.out.println( "Despues de asignar valores a atributos");
  System.out.println( "nombre=" + alumno.nombre );
  System.out.println( "edad=" + alumno.edad );
 }
}
