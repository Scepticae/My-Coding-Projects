//Samuel Leonard
//sleonar5
//Homework 10.3
//JTalk
//ChatServer.java

import java.net.*;
import java.io.*;
import java.util.*;

public class ChatServer{
	public ChatServer(String[] args) throws IOException{
		//Declarations
		int i;
		ChatData room;
		Map<String, ChatData> chatRooms = new HashMap<String, ChatData>();
		int portNumber = Integer.parseInt(args[0]);
		
		//Set the Chat Room names
		for(i = 1; i < args.length; i++){
			room = new ChatData();
			chatRooms.put(args[i], room);
		}
		
		//Set up the server socket to wait for connection
		try{
			ServerSocket server = new ServerSocket(portNumber);
			while(true){
				new ChatServerThread(server.accept(), chatRooms).start();
			}
		}
		catch(IOException e){
			System.err.println("Port: " + portNumber + " is not valid.");
			System.exit(1);
		}
	}
	
	public static void main(String[] args) throws IOException{
		//Check to make sure there are at least two arguments
		if(args.length < 2){
			System.err.println("Usage: requires a <port number> and at least one chat room name");
			System.exit(1);
		}
		
		new ChatServer(args);
	}
}