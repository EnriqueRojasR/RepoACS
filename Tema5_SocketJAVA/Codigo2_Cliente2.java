import java.net.*;
import java.io.*;

public class Codigo2_Cliente2
{
public static void main(String a[])
{
 Socket socket = null;
 String peticion = null;
 String respuesta = null;
 try
 {
 System.out.println("Me conecto al puerto 8000 del servidor");
 socket = new Socket(a[0],8000);
 BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 peticion = br.readLine();
 System.out.println("Le envio mi peticion: " + peticion);
 DataOutputStream dos = new DataOutputStream( socket.getOutputStream());
 dos.writeUTF(peticion);
 DataInputStream dis = new DataInputStream( socket.getInputStream() );
 respuesta = dis.readUTF();
 System.out.println("El mensaje que me envio el servidor es: " + respuesta);
 dos.close();
 dis.close();
 socket.close();
 }
 catch(IOException e)
 {
 System.out.println("java.io.IOException generada");
 e.printStackTrace();
 }
}
}
