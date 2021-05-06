import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.Scanner;

// Feito por
// Anderson Yoshio Makino
// Wellington Luiz da Silva Junior
public class Server {
	
	private static int port = 8001;
	private static int fileSize = 1024;
	private static FileInputStream fis;

	public static void main(String[] args) throws Exception {
		DatagramSocket rcp = new DatagramSocket(port);
		message (rcp);
		rcp.close();
	}
	
	private static void message(DatagramSocket rcp) throws IOException {
		InetAddress address = InetAddress.getByName("127.0.0.1");
		String sMessage;
		byte[] message = new byte[1024];
		byte[] receiveMessage = new byte[1024];
		sMessage = leitor();
		message = sMessage.getBytes();
		DatagramPacket receivePacket = new DatagramPacket(receiveMessage,receiveMessage.length);
		DatagramPacket sendPacket = new DatagramPacket(message,message.length,address,port);
		rcp.receive(receivePacket);
		rcp.send(sendPacket);
		String received = new String(receivePacket.getData(), 0, receivePacket.getLength());
		
		switch(received){
			case "1":
				break;
			case "2":
				break;
			case "3":
				break;
			case "4":
				break;
			case "5":
				break;
			default:
				break;
		}
	}

	public static String leitor() throws IOException {
		BufferedReader buffRead = new BufferedReader(new FileReader("..\\archive.txt"));
		String linha = "";
		while (true) {
			if (linha == null)
				break;
			linha = linha + buffRead.readLine();
		}
		buffRead.close();
		return linha;
	}
	public static void escritor(String linha) throws IOException {
		BufferedWriter buffWrite = new BufferedWriter(new FileWriter("..\\archive.txt"));
		buffWrite.append(linha + "\n");
		buffWrite.close();
	}
	public static void editor(String textoAntigo, String texto) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader("..\\archive.txt"));
		BufferedWriter writer = new BufferedWriter(new FileWriter("..\\archive_temp.txt"));

		String currentLine;

		while((currentLine = reader.readLine()) != null) {
			String trimmedLine = currentLine.trim();
			if(trimmedLine.equals(textoAntigo)){
				writer.write(texto + System.getProperty("line.separator"));
			}else{
				writer.write(currentLine + System.getProperty("line.separator"));
			}
		}
		writer.close(); 
		reader.close();
	}
	public static void exclusor(String linha) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader("..\\archive.txt"));
		BufferedWriter writer = new BufferedWriter(new FileWriter("..\\archive_temp.txt"));

		String currentLine;

		while((currentLine = reader.readLine()) != null) {
			String trimmedLine = currentLine.trim();
			if(trimmedLine.equals(linha)) continue;
			writer.write(currentLine + System.getProperty("line.separator"));
		}
		writer.close(); 
		reader.close();
	}

}
