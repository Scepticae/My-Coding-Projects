//Samuel Leonard
//sleonar5
//Homework 8
//SliderApp using MVC

package SliderApp;

import javax.swing.*;
import java.util.*;
import java.awt.*;

class TextView extends JPanel implements ChoiceView {
	private SliderAppModel model;
	private JLabel sliderValue;
	private JLabel valueLabel;
	int newValue;
	
	//TextView Constructor
	public TextView(SliderAppModel parent){
		model = parent;
		model.addObserver(this);
		
		//Create the Text View Components
		sliderValue = new JLabel("");
		valueLabel = new JLabel("Value: ");
		
		//Set up the components for the panel
		setLayout(new FlowLayout());
		sliderValue.setText(Integer.toString(model.getCurVal()));
		add(valueLabel);
		add(sliderValue);
	}
	
	//Text View Updater
	public void update(int oldChoice){
		newValue = model.getCurVal();
		sliderValue.setText(Integer.toString(newValue));
	}
}