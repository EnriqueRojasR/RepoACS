import java.io.FileOutputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class EjemploAlumnoSerializable1 implements Serializable
{
 String nombre;
 int edad;

 public static void main(String[] args) throws Exception
 {
  EjemploAlumnoSerializable1 alumno = new EjemploAlumnoSerializable1();
  System.out.println( "Antes de asignar valores a atributos");
  System.out.println( "nombre=" + alumno.nombre );
  System.out.println( "edad=" + alumno.edad );
  System.out.println("----------------------------");
  alumno.nombre = "Juan";
  alumno.edad = 23;
  System.out.println( "Despues de asignar valores a atributos");
  System.out.println( "nombre=" + alumno.nombre );
  System.out.println( "edad=" + alumno.edad );
  System.out.println("----------------------------");
  System.out.println( "Ahora se guardara el objeto en un archivo SER");
  ObjectOutput out = new ObjectOutputStream(new FileOutputStream("alumno.ser"));
  out.writeObject( alumno );
  out.close();
 }
}
