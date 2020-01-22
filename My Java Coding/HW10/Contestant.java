//Samuel Leonard
//sleonar5
//Homework 10 1 and 2
//Race

package race;

import java.util.*;

public class Contestant implements Runnable {
	int num;
	int time;
	int segment;
	SynchronizedRandom rNum;
	TimeKeeper tKeeper;
	
	//Constructor for the contestant class
	public Contestant(SynchronizedRandom r, TimeKeeper tk, int number){
		num = number;
		segment = 0;
		time = 0;
		rNum = r;
		tKeeper = tk;
	}
	
	//Runs the thread for the contestant
	public void run(){
		try{
			while(segment != 4){
				time = rNum.getTime(); 
				Thread.sleep(time);
				this.updateSeg();
				tKeeper.updateRacerInfo(num, time, segment);
				if(segment == 4){
					tKeeper.putInQueue(num);
				}
			}
		}
		catch (InterruptedException e){}
	}
	
	//Updates the segment completed
	public void updateSeg(){
		segment++;
	}
}
