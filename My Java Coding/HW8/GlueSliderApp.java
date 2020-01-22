//Samuel Leonard
//sleonar5
//Homework 8
//SliderApp using MVC

package SliderApp;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class GlueSliderApp extends JFrame{
	SliderAppModel model = new SliderAppModel();
	
	public GlueSliderApp(String args[]){
		//Check to make sure there are correct number of args
		if (args.length != 4) {
			System.err.println("usage: java SliderApp min max initialValue incrementValue");
			System.exit(1);
		}
		//Catch any value that is not an integer
		try {
			model.setMinVal(Integer.parseInt(args[0]));
			model.setMaxVal(Integer.parseInt(args[1]));
			model.setCurVal(Integer.parseInt(args[2]));
			model.setIncVal(Integer.parseInt(args[3]));
		}
		catch (NumberFormatException e) {
			System.out.println(e.getMessage() + "--should be an integer");
			System.exit(1);
		}
		//Use separate thread to create and show frame
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
	}
	
	private void createAndShowGUI(){
		//Create and set up the window.
        JFrame frame = new JFrame("SliderApp");
		JPanel contentPane = (JPanel)frame.getContentPane();

		// empty border creates a nice spacing around the edge of the window
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        contentPane.setBorder(BorderFactory.createEmptyBorder(
                                        20, //top
                                        20, //left
                                        20, //bottom
                                        20) //right
                                        );

        JPanel buttonView = new ButtonView(model);
		JPanel textView = new TextView(model);

		// add the views to the window and put a nice vertical gap between
		// them
        contentPane.add(textView, BorderLayout.NORTH);
        contentPane.add(buttonView, BorderLayout.CENTER);
		BorderLayout layoutMgr = (BorderLayout)contentPane.getLayout();
		layoutMgr.setVgap(20);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
	}
	
	public static void main(String args[]){
		new GlueSliderApp(args);
	}
}

