//Samuel Leonard
//sleonar5
//Homework 10 1 and 2
//Race

package race;

import java.util.*;

public class Race{
	//Creates Instances
	SynchronizedRandom rand;
	TimeKeeper keeper;
	
	//Constructor for race class
	public Race(String args[]){
		int i = 0;
		int n = Integer.parseInt(args[0]);
		
		//Create Instances of the TimeKeeper and SynchronizedRandom
		rand = new SynchronizedRandom();
		keeper = new TimeKeeper(n);
		Thread t = new Thread(new Reporter(keeper));
		t.start();
		
		//Creates the threads for each contestant
		while(i < n){
			Thread t1 = new Thread(new Contestant(rand, keeper, i+1));
			
			//Starts the thread
			t1.start();
			i++;
		}
	}
	
	public static void main(String args[]){
		new Race(args);
	}
}