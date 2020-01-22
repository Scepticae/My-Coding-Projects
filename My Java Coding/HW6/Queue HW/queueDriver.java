//Samuel Leonard
//sleonar5
//HW6: Queue.jar

import java.util.*;
import queue.*;

class queueDriver {
    public static void main(String args[]) {
		queue.Queue<String> myQueue;
		int num;

		Scanner console = new Scanner(System.in);
		Scanner lineTokenizer;
		num = 0;
		if(console.hasNextLine()){
			lineTokenizer = new Scanner(console.nextLine());
			if(lineTokenizer.hasNextInt()){
				num = lineTokenizer.nextInt();
				lineTokenizer.close();
			}
		}
		
		myQueue = new queue.Queue<String>(num);
		
		while (console.hasNextLine()) {
			lineTokenizer = new Scanner(console.nextLine());
			String cmd = lineTokenizer.next();
			if (cmd.equals("enqueue")) {
				String value = lineTokenizer.next();
				try{
					myQueue.enqueue(value);
				}
				catch(OverflowException e){
					System.out.println(e);
				}
				finally{
					lineTokenizer.close();
				}
			}
			else if (cmd.equals("dequeue")) {
				try{
					System.out.println(myQueue.dequeue());
				}
				catch(UnderflowException e){
					System.out.println(e);
				}
				finally{
					lineTokenizer.close();
				}
			}
			lineTokenizer.close();
		}
		console.close();
	}
}
