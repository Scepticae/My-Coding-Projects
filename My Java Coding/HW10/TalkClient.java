//Samuel Leonard
//sleonar5
//Homework 10.3
//JTalk
//TalkClient.java

import java.net.*;
import java.io.*;

public class TalkClient{
	public static void main(String[] args) throws IOException{
		
		//Check to make sure there are enough arguments
		if(args.length < 3){
			System.err.println("Usage: Arguments should be <host name><port number><chat name>");
			System.exit(1);
		}
		
		String hostName = args[0];
		int portNumber = Integer.parseInt(args[1]);
		String chatName = args[2];
		
		//Setup the Socket, input and output streams
		try{
			Socket socket = new Socket(hostName, portNumber);
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
			String fromServer, toServer;
			
			//Continue util server output is null
			while((fromServer = in.readLine()) != null){
				System.out.println(fromServer);
			}
			
			//Get input from user for chat room
			toServer = stdIn.readLine();
			
			//Send Chat room choice to server
			out.println(toServer);
			
			//Send the ChatName to the server
			out.println(chatName);
			
			//Continue util server output is null
			while((fromServer = in.readLine()) != null){
				System.out.println(fromServer);
			}
		}
		catch(UnknownHostException e){
			System.err.println("Error: Unknown Host.");
			System.exit(1);
		}
		catch(IOException e){
			System.err.println("Error: Could not connect to host.");
		}
	}
}