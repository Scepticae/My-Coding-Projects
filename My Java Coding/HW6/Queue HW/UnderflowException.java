package queue;

public class UnderflowException extends Exception{
	public String toString(){
		return new String("Queue Empty: Cannot dequeue");
	}
}