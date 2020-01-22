//Samuel Leonard
//sleonar5
//Homework 10 1 and 2
//Race

package race;

import java.util.*;

public class SynchronizedRandom{
	int rtime;
	Random r = new Random();
	
	//Gets the time for the segment
	public synchronized int getTime(){
		rtime = r.nextInt(7000)+1000;
		return rtime;
	}
}