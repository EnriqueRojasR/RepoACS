import javax.crypto.*;

public class Codigo02MAC
{
  public static void main (String[] args) throws Exception
  {
    if (args.length !=1)
    {
     System.exit(1);
    }
    byte[] textoPlano = args[0].getBytes("UTF8");
    bytesToBits(textoPlano);
    System.out.println( "\n Generando la clave.................." );
    KeyGenerator keyGen = KeyGenerator.getInstance("HmacMD5");
    SecretKey key = keyGen.generateKey();
    System.out.print( "Clave generada" );
    Mac mac = Mac.getInstance("HmacMD5");
    mac.init(key);
    mac.update(textoPlano);
    System.out.println( "\nMAC: " );
    byte resultadoMD5[] = mac.doFinal();
    for(int i=0; i < resultadoMD5.length; i++)
      System.out.print( (char)resultadoMD5[i] );
    System.out.println( "\nAhora como bytes y bits" );
    // NO SE DEBE PASAR A String
    // System.out.println( new String( resultadoMD5, "UTF8") );
    bytesToBits( resultadoMD5 );
    System.out.println( "\n-------------------------------\n" );
    System.out.println( "\n Generando la clave.................." );

    Mac mac2 = Mac.getInstance("HmacSHA1");
    mac2.init( key );
    mac2.update(textoPlano);
    System.out.println( "\nMAC: " );
    byte resultadoSHA1[] = mac2.doFinal();
    System.out.println( new String( resultadoSHA1 , "UTF8") );
    bytesToBits( resultadoSHA1 );
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
