//Trimit la server un caracter si un sir
//si trebuie sa-mi returneze un sir care nu contine caracterul trimis
import java.net.*;
import java.io.*;
 
public class Client {
	 
	public static void main(String args[]) throws Exception {
		  Socket c = new Socket("127.0.0.1", 1234);
		  BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

		  System.out.print("character = ");
		  char character = reader.readLine().charAt(0);
		  
		  System.out.print("sir = ");
		  String string = reader.readLine();
		  DataInputStream socketIn = new DataInputStream(c.getInputStream());
		  DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());
		  
		  //trimit un caracter		  
		  socketOut.writeByte(character);
		  socketOut.flush();
		  
		  //trimit lungimea sirului
		  int len = string.length();
		  socketOut.writeInt(len);

		  //trimit un sir - NU SE VA TRIMITE \0
		  socketOut.writeBytes(string);

		  //primesc un caracter
	    	  byte b = socketIn.readByte();
		  char newChar = (char)b;
		  //System.out.println(newChar);	  
		  
		  //primesc un sir
		  byte[] sir = new byte[100];
		  int no = socketIn.read(sir);
		  String rez = new String(sir);

		  System.out.println("Rezultatul este: " + rez);
		  reader.close();
		  c.close();  
	}
	 
}
