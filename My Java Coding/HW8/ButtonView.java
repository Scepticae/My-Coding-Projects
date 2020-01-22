//Samuel Leonard
//sleonar5
//Homework 8
//SliderApp using MVC

package SliderApp;

import javax.swing.*;
import javax.swing.event.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;

class ButtonView extends JPanel implements ChoiceView {
	//Button View Components
	private JSlider slider;
    private JButton incrButton;
    private JButton decrButton;
	private SliderAppModel model;
	
	public ButtonView(SliderAppModel parent){
		model = parent;
		model.addObserver(this);
		
		//Buttons and the slider
		incrButton = new JButton("Increment");
		decrButton = new JButton("Decrement");
		slider = new JSlider(model.getMinVal(), model.getMaxVal(), model.getCurVal());
		
		// put the view components in their appropriate regions
		setLayout(new BorderLayout(10, 10));
		add(incrButton, BorderLayout.LINE_END);
		add(decrButton, BorderLayout.LINE_START);
		add(slider, BorderLayout.CENTER);
		
		// increment and decrement return false if the operation failed
        incrButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (!increment()) {
					JOptionPane.showMessageDialog(incrButton,
					"Cannot further increment the value",
					"Error", JOptionPane.ERROR_MESSAGE);
				}
			}
		});
        decrButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (!decrement()) {
					JOptionPane.showMessageDialog(decrButton,
					"Cannot further decrement the value",
					"Error", JOptionPane.ERROR_MESSAGE);
				}
			}
		});
		slider.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent e) {
				JSlider s = (JSlider)e.getSource();
				model.setCurVal(s.getValue());
			}
    	});
	}
	
	//Checks to see if it can be incremented and then sets the model value
	boolean increment() {
	    int newValue;
	    if (model.getCurVal() == model.getMaxVal()){ return false; }
	    newValue = model.getCurVal() + model.getIncVal();
	    if (newValue > model.getMaxVal()){ newValue = model.getMaxVal(); }
	    model.setCurVal(newValue);
	    return true;
	}
	//Checks to see if it can be decremented and then sets the model value
	boolean decrement() {
	    int newValue;
	    if (model.getCurVal() == model.getMinVal()){ return false; }
	    newValue = model.getCurVal() - model.getIncVal();
	    if (newValue < model.getMinVal()){
			newValue = model.getMinVal();
		}
	    model.setCurVal(newValue);
	    return true;
	}
	
	public void update(int oldChoice){
		int val = model.getCurVal();
		slider.setValue(val);
	}
}