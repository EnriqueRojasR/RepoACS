import java.net.*;
import java.io.*;

public class ClienteMultiThread
{
	public static void main(String a[])
	{
		Socket socket = null;
		// Peticion es lo que envia el Cliente
		String peticion = "";
		// Respuesta es lo que le respondo al Cliente
		String respuesta = "";

		try
		{
			System.out.println("Me conecto al puerto 8000 del servidor");
			socket = new Socket(a[0],8000);
			// Como ya hay socket, obtengo los flujos asociados a este
			DataInputStream dis = new DataInputStream( socket.getInputStream() );
			DataOutputStream dos = new DataOutputStream( socket.getOutputStream() );
			// Ya que me conecte con el Servidor, debo leer del teclado para despues eso mismo enviarlo al Servidor
			BufferedReader br = new BufferedReader( new InputStreamReader( System.in ) );
			while( !respuesta.equals( "bye" ) )
			{
				peticion = br.readLine();
				// Como yo escribo la peticion a la red,
				// el Servidor debe leer de la red
				System.out.println("Le envio mi peticion: " + peticion);
				dos.writeUTF(peticion);
				// Como el Servidor va a escribir, ahora yo leo
				respuesta = dis.readUTF();
				System.out.println("El mensaje que me envio el servidor es: " + respuesta);
			}
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
