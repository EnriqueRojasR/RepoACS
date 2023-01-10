import java.security.MessageDigest;
// import javax.xml.bind.DatatypeConverter;

public class Codigo01ClaseResumen
{
  public static void main( String args[] ) throws Exception
  {
    if (args.length !=1)
    {
      System.exit(1);
    }
    System.out.println( "El argumento de la linea de comandos es: " + args[0] );
    byte[] textoPlano = args[0].getBytes("UTF8");
    System.out.println( "El argumento de la linea de comandos pasado a bytes y a bits es:" );
    bytesToBits( textoPlano );
    MessageDigest md1 = MessageDigest.getInstance("MD5");
    System.out.println( "md1.getProvider().getInfo() da el siguiente resultado:" );
    System.out.println( "\n" + md1.getProvider().getInfo() );
    System.out.println( "Ahora con messageDigest MD5 actualizamos el texto plano:" );
    md1.update( textoPlano);
    byte textoResumido[] = md1.digest();
    for(int i=0; i < textoResumido.length; i++)
      System.out.print( (char)textoResumido[i] );
    System.out.println( "\nEl mensaje resumido (TOMADO COMO ARREGLO DE BYTES) con MD5 pasado a bytes y a bits es:" );
    bytesToBits( textoResumido );
    // NO SE DEBE PASAR A String
    System.out.println( "El mensaje resumido (TOMADO COMO String) con MD5 pasado a bytes y a bits es:" );
    // String str = new String( md1.digest(), "UTF8");
    System.out.println( new String( md1.digest(), "UTF8") );
    bytesToBits( md1.digest() );
    System.out.println("\n ------------------------------------\n");
    MessageDigest md2= MessageDigest.getInstance("SHA");
    System.out.println( "md2.getProvider().getInfo() da el siguiente resultado:" );
    System.out.println( "\n" + md2.getProvider().getInfo() );
    System.out.println( "Ahora con messageDigest SHA actualizamos el texto plano:" );
    md2.update( textoPlano);
    System.out.println( "\nresumen:" );
    System.out.println( new String( md2.digest(), "UTF8") );
    System.out.println( "El mensaje cifrado con SHA pasado a bytes y a bits es:" );
    bytesToBits( md2.digest() );
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
