//Samuel Leonard
//sleonar5
//Homework 10 1 and 2
//Race

package race;

import java.util.*;

public class TimeKeeper{
	int i;
	int j = 0;
	int nRacers;
	boolean state = false;
	racerInfo[] racers;
	racerInfo[] finished;
	//Constructor that creates a list of racers
	public TimeKeeper(int n){
		racers = new racerInfo[n];
		finished = new racerInfo[n];
		nRacers = n;
		
		for(i = 0; i < nRacers; i++){
			racers[i] = new racerInfo();
			racers[i].racerNumber = i+1;
		}
	}
	
	//Local Object for holding info
	public class racerInfo{
		int racerNumber;
		int lastSeg;
		int segComp;
		int tet; //Total Elasped Time
		
		//Constructor for racerInfo
		public racerInfo(){
			racerNumber = 0;
			lastSeg = 0;
			segComp = 0;
			tet = 0;
		}
	}
		
	//A method to gather info from the contestant
	public synchronized void updateRacerInfo(int rn, int ls, int sc){
		racers[rn-1].racerNumber = rn;
		racers[rn-1].lastSeg = ls;
		racers[rn-1].segComp = sc;
		racers[rn-1].tet = racers[rn-1].tet + ls;
	}
	
	//A method to put the finished racers in the queue
	public synchronized void putInQueue(int fRacer){
		finished[j] = new racerInfo();
		finished[j] = racers[fRacer - 1];
		j++;
	}
	
	//A method to send racer info to the reporter
	public synchronized void printRacerInfo(){
		state = false;
		for(i = 0; i < nRacers; i++){
			System.out.printf("%10d   %8d   %5d   %11d%n", racers[i].racerNumber,
			racers[i].segComp, racers[i].tet, racers[i].lastSeg);
			if(racers[i].segComp < 4){
				state = true;
			}
		}
		System.out.println("");
	}
	
	//A method to say when the race is done
	public synchronized boolean getStatus(){
		return state;
	}
	
	//A method to print the final result
	public synchronized void printQueue(){
		for(i = 0; i < nRacers; i++){
			System.out.printf("%10d   %10d%n", finished[i].racerNumber, finished[i].tet);
		}
	}
}