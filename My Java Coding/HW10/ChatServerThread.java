//Samuel Leonard
//sleonar5
//Homework 10
//JTalk
//ChatServerThread.java

import java.net.*;
import java.io.*;
import java.util.*;

public class ChatServerThread extends Thread{
	private Socket socket = null;
	Map<String, ChatData> cRooms;

	//Constructor for ChatServerThread
	public ChatServerThread(Socket s, Map<String, ChatData> cr){
		this.socket = s;
		cRooms = cr;
	}
	
	//Create the runnable
	public void run(){
		try{
			//Create the input and output streams
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			BufferedReader in = new BufferedReader(new InputStreamReader(
				socket.getInputStream()));
				
			//Declare Input and Output variables
			String input;
			String output;
			String prompt = "\nEnter a chat room: ";
			String chatName;
			
			//Send out the list of users in chat room
			for( Map.Entry<String, ChatData> mElements : cRooms.entrySet()){
				output = cRooms.get(mElements.getKey()).broadcastMembers();
				out.println(mElements.getKey()+ ":");
				if(output != null){
					out.println(output);
				}
			}
			
			//Prompt the user for the Chat Room
			out.println(prompt);
			
			//Get the chat room name wished to join
			input = in.readLine();
			
			//Get the Chat Name to put in the room
			chatName = in.readLine();
			
			//Setup the chatData object for in and out
			output = cRooms.get(input).addClient(chatName);
			out.println(output);
		}
		catch(IOException e){
			e.printStackTrace();
		}
	}
}