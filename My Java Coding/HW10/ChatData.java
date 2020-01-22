//Samuel Leonard
//sleonar5
//Homework 10.3
//JTalk
//ChatData.java

import java.util.*;

public class ChatData{
	ArrayList<String> clients;
	public ChatData(){
		clients = new ArrayList<String>();
	}
	
	//Method to Distribute Message to all clients in chat room
	public String distributeMessage(String input){
		return input;
	}
	//Method to add client socket and create a message showing joined room
	public String addClient(String name){
		clients.add(name);
		
		//Message handled by distributeMessage method
		String joinMessage = name + " has joined the room.";
		return (distributeMessage(joinMessage));
	}
	//Method to delete the client socket and create a message saying left room
		//Message handled by distributeMessage
	
	//Method to broadcast members which shows what members are in what room
	public String broadcastMembers(){
		String users = null;
		for(String elements : clients){
			if(users != null){
				users += "   " + elements + "\n";
			}
			else{
				users = "   " + elements + "\n";
			}
		}
		return users;
	}
		//Send this to the TalkClient to display the info
}