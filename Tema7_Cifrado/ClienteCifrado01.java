import java.net.*;
import java.io.*;
import java.security.*;
import javax.crypto.*;

public class ClienteCifrado01
{
  public static void main(String a[]) throws Exception
  {
    Socket socket = null;
    // Peticion es lo que envia el Cliente
    String peticion = "";

    try
    {
      /*
      System.out.println( "Generando la llave..." );
      KeyGenerator keyGen = KeyGenerator.getInstance("DES");
      keyGen.init(56);
      Key llave = keyGen.generateKey();
      System.out.println( "Llave generada!" );
      System.out.println( "llave=" + llave );
      */

      ObjectInput in = new ObjectInputStream(new FileInputStream("llave.ser"));
      Key llave = (Key)in.readObject();
      System.out.println( "llave=" + llave );
      in.close();

      System.out.println("Me conecto al puerto 8000 del servidor");
      socket = new Socket(a[0],8000);
      // Como ya hay socket, obtengo los flujos asociados a este
      DataInputStream dis = new DataInputStream( socket.getInputStream() );
      DataOutputStream dos = new DataOutputStream( socket.getOutputStream() );
      // Ya que me conecte con el Servidor, debo leer del teclado para despues eso mismo enviarlo al Servidor
      BufferedReader br = new BufferedReader( new InputStreamReader( System.in ) );
      peticion = br.readLine();
      System.out.println( "Mi peticion es: " + peticion );
      System.out.println( "Ahora encriptamos la peticion..." );
      byte[] arrayPeticion = peticion.getBytes();
      Cipher cifrar = Cipher.getInstance("DES");
      cifrar.init(Cipher.ENCRYPT_MODE, llave);
      byte[] cipherText = cifrar.doFinal( arrayPeticion );
      System.out.println( "El argumento ENCRIPTADO es:" );
      // NO SE DEBE PASAR A String
      // System.out.println( new String( cipherText ) );
      for(int i=0; i < cipherText.length; i++)
        System.out.print( (char)cipherText[i] );
      System.out.println( "" );
      // Como yo escribo la peticion a la red,
      // el Servidor debe leer de la red
      bytesToBits( cipherText );
      dos.write( cipherText, 0, cipherText.length );
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

  public static void bytesToBits( byte[] texto )
  {
    StringBuilder stringToBits = new StringBuilder();
    for( int i=0; i < texto.length; i++ )
    {
      StringBuilder binary = new StringBuilder();
      byte b = texto[i];
      int val = b;
      for( int j = 0; j < 8; j++ )
      {
        binary.append( (val & 128) == 0 ? 0 : 1 );
        val <<= 1;
      }
      System.out.println( (char)b + " \t " + b + " \t " + binary );
      stringToBits.append( binary );
    }
    System.out.println( "El mensaje completo en bits es:" + stringToBits );
  }

}
