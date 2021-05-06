import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.Scanner;

// Feito por
// Anderson Yoshio Makino
// Wellington Luiz da Silva Junior
public class Client {
	
	private static int port = 8001;
	private static int fileSize = 1024;
	public static void main(String[] args) throws Exception {
		DatagramSocket rcp = new DatagramSocket();
		message (rcp);
		rcp.close();
	}
	
	private static void message(DatagramSocket rcp) throws IOException {
		InetAddress address = InetAddress.getByName("127.0.0.1");
		Integer iMessage = 0;
		String sMessage;
		Scanner scann = new Scanner(System.in);
		byte[] message = new byte[1024];
		byte[] receiveMessage = new byte[1024];

		while(true){ 
			System.out.println("1 - Ler");
			System.out.println("2 - Adicionar");
			System.out.println("3 - Editar");
			System.out.println("4 - Excluir");
			System.out.println("5 - Sair");
			System.out.print("Insira a opção: ");
			iMessage = scann.nextInt();
			if(iMessage == 5) break;
			switch(iMessage){
				case 2:
					System.out.print("Insira o texto que quer adicionar: ");
					sMessage = scann.next();
					break;
				case 3:
					System.out.print("Qual linha quer editar: ");
					sMessage = scann.next();
					break;
				case 4:
					System.out.print("Qual linha quer excluir: ");
					sMessage = scann.next();
					break;
				default:
					break;
			}
			message = iMessage.getBytes();
			DatagramPacket receivePacket = new DatagramPacket(receiveMessage,receiveMessage.length);
			DatagramPacket sendPacket = new DatagramPacket(message,message.length,address,port);
			rcp.receive(receivePacket);
			rcp.send(sendPacket);
		}
	}
}
