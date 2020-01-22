//Samuel Leonard
//sleonar5
//HW 10 1 and 2
//Race

package race;

import java.util.*;

public class Reporter implements Runnable{
	int change = 2;
	boolean check = true;
	TimeKeeper k;
	
	//Constructor for the reporter class
	public Reporter(TimeKeeper keep){
		k = keep;
	}
	
	//Run the thread and print the scoreboard every two seconds
	public void run(){
		try{
			System.out.println("Start the race!");
			while(check){
				Thread.sleep(2000);
				System.out.println("Results after " + change + " seconds");
				System.out.println("Contestant   Segments   Time   Last Segment");
				k.printRacerInfo();
				check = k.getStatus();
				change += 2;
			}
			
			//Print the final Scoreboard
			System.out.println("Final Result:");
			System.out.println("Contestant   Total Time");
			k.printQueue();
		}
		catch(InterruptedException e){}
	}
}