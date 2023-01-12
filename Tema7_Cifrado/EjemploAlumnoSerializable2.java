import java.io.FileInputStream;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.Serializable;

public class EjemploAlumnoSerializable2 implements Serializable
{
 public static void main(String[] args) throws Exception
 {
  System.out.println( "Ahora se leera el objeto desde el archivo SER");
  System.out.println("----------------------------");
  ObjectInput in = new ObjectInputStream(new FileInputStream("alumno.ser"));
  EjemploAlumnoSerializable1 alumno = (EjemploAlumnoSerializable1)in.readObject();
  in.close();
  System.out.println( "Despues de asignar valores a atributos");
  System.out.println( "nombre=" + alumno.nombre );
  System.out.println( "edad=" + alumno.edad );
 }
}
