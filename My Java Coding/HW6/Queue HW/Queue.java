//Samuel Leonard
//sleonar5
//HW 6
//Queue.java

package queue;

import java.util.*;

public class Queue<T>{
	public Queue(){
		size = 100;
		head = 0;
		tail = 0;
		q = new ArrayList<T>(100);
	}
	
	public Queue(int maxCapacity){
		size = maxCapacity;
		head = 0;
		tail = 0;
		q = new ArrayList<T>(maxCapacity);
	}
	
	void enqueue(T value){
		if(((tail + 1) % q.size()) == head){
			throw new OverflowException();
		}
		q.add(value);
		tail++;
	}
	
	public T dequeue(){
		if(q.isEmpty()){
			throw new UnderflowException();
		}
		return q.remove(q.size()-1);
	}
	
	public boolean isEmpty(){
		if(head == tail)return true;
		else return false;
	}
	
	int size;
	int head;
	int tail;
	ArrayList<T> q;	
}