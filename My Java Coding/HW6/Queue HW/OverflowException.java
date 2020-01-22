package queue;

public class OverflowException extends Exception{
	public Object o;
	public OverflowException(Object val){
		o = (String)val;
	}
	public String toString(){
		return new String("Queue Full: Cannot enqueue " + o);
	}
}