import java.security.*;
import javax.crypto.*;

public class Codigo03PrivateExample
{
 public static void main (String[] args) throws Exception
 {
  if (args.length !=1)
  {
   System.exit(1);
  }
  System.out.println( "El argumento original de la linea de comandos es:" + args[0] );
  byte[] textoPlano = args[0].getBytes("UTF8");
  System.out.println( "El argumento de la linea de comandos pasado a bytes y a bits es:" );
  bytesToBits( textoPlano );
  System.out.println( "La longitud es:" + textoPlano.length);
  System.out.println( "----------------------------------------------------" );
  System.out.println( "Generando la llave..." );
  KeyGenerator keyGen = KeyGenerator.getInstance("DES");
  keyGen.init(56);
  Key clave = keyGen.generateKey();
  System.out.println(clave);

  KeyGenerator keyGen2 = KeyGenerator.getInstance("DES");
  keyGen2.init(56);
  Key clave2 = keyGen2.generateKey();
  System.out.println(clave2);

  Cipher cifrar = Cipher.getInstance("DES/ECB/PKCS5Padding");
  cifrar.init(Cipher.ENCRYPT_MODE, clave);
  byte[] cipherText = cifrar.doFinal(textoPlano);
  System.out.println( "El argumento ENCRIPTADO es:" );
  // NO SE DEBE PASAR A String
  // System.out.println( new String(cipherText, "UTF8") );
  for(int i=0; i < cipherText.length; i++)
    System.out.print( (char)cipherText[i] );
  System.out.println( "\nEl argumento ENCRIPTADO pasado a bytes y a bits es:" );
  bytesToBits( cipherText );
  System.out.println( "La longitud es:" + cipherText.length);
  System.out.println( "----------------------------------------------------" );
  cifrar.init(Cipher.DECRYPT_MODE, clave);
  byte[] newPlainText = cifrar.doFinal(cipherText);
  System.out.println( "El argumento DESENCRIPTADO es:" );
  // NO SE DEBE PASAR A String
  // System.out.println( new String(newPlainText, "UTF8") );
  for(int i=0; i < newPlainText.length; i++)
    System.out.print( (char)newPlainText[i] );
  System.out.println( "\nEl argumento DESENCRIPTADO pasado a bytes y a bits es:" );
  bytesToBits( newPlainText );
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
