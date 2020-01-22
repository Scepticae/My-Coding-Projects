//Samuel Leonard
//sleonar5
//Homework 8
//SliderApp using MVC

package SliderApp;

import java.util.*;

class SliderAppModel{
	int minValue;
    int maxValue;
    int currentValue;
    int incrementValue;
	String choice;
	
	//Constructor to set default values
	SliderAppModel(){
		minValue = 0;
		maxValue = 100;
		currentValue = 0;
		incrementValue = 1;
		choice = "textView";
	}
	
	//Set up list of observers for the different views
    List<ChoiceView> observers = new ArrayList<ChoiceView>();

	//Setters and getter functions
	int getMinVal(){ return minValue; }
	int getMaxVal(){ return maxValue; }
	int getCurVal(){ return currentValue; }
	int getIncVal(){ return incrementValue; }
    String getChoice(){ return choice; }

	void setMinVal(int min){ minValue = min; }
	void setMaxVal(int max){ maxValue = max; }
	void setCurVal(int cur){ currentValue = cur; }
	void setIncVal(int inc){ incrementValue = inc; }
    void setChoice(int newChoice) { 
		int oldChoice = currentValue;
		currentValue = newChoice; 
		for (ChoiceView view : observers) {
			view.update(oldChoice);
		}
    }

	//Adds an observer for each view
    void addObserver(ChoiceView view) { observers.add(view); }
}