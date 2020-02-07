/*
Crawford, Jon
COP-3252
Assignment 6
3/31/2019
*/

// ArrayAccess.java
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import java.lang.String;

public class ArrayAccess extends JFrame 
{
   private JTextField inputField;
   private JTextField retrieveField1;
   private JTextField retrieveField2;
   private JTextField outputField;
   private JPanel inputArea; 
   private JPanel retrieveArea;
   private JPanel outputArea;

   private int num;
   private int index = 0;
   private int array[] = new int[ 10 ];
   private String result;
   private String numError = "Please enter only integer values";
   // set up GUI
   public ArrayAccess()
   {
      super( "Accessing Array values" );
      setLayout( new FlowLayout() );
      
      // set up input Panel
      inputArea = new JPanel();
      inputArea.add( new JLabel( "Enter array elements here" ) );
      inputField = new JTextField( 10 );
      inputArea.add( inputField );
      inputField.addActionListener( 
         new ActionListener()
         {
            public void actionPerformed( ActionEvent e )
            {
                              
               try
               {
                  String input = inputField.getText();
                  num = Integer.parseInt(input);
                  array[index++] = num;
               }
               catch(NumberFormatException exception)
               {
                  JOptionPane.showMessageDialog(null, numError,
                  "Invalid Input", JOptionPane.ERROR_MESSAGE);
               }
               catch(ArrayIndexOutOfBoundsException exception)
               {
                  JOptionPane.showMessageDialog(null, "Array may contain only 10 elements", 
                  "Array Full", JOptionPane.ERROR_MESSAGE);
               }               
               
               inputField.setText( "" );
            } // end method actionPerformed
         } // end anonymous inner class
      ); // end call to addActionListener
      
      // set up retrieve Panel
      retrieveArea = new JPanel( new GridLayout( 2, 2 ) );
      retrieveArea.add( new JLabel( "Enter number to retrieve" ) );
      retrieveField1 = new JTextField( 10 );
      retrieveArea.add( retrieveField1 );
      retrieveField1.addActionListener( 
         new ActionListener() 
         {
            public void actionPerformed( ActionEvent event ) 
            {
               
               try
               {
                  String input1 = retrieveField1.getText();
                  num = Integer.parseInt(input1);                  
                  String build = "";
                  boolean find = false;  
                  for(int i = 0; i < array.length; ++i)
                  {
                     if(array[i] == num)
                     {                     
                        build += (i + ", ");
                        find = true;
                     }
                  }  
                  if(!find)                 
                     throw new NumberNotFoundException(); 
                  else
                  {
                     // you can't pop_back() in java for the extra comma ", "
                     // https://www.baeldung.com/java-remove-last-character-of-string                     
                     build = build.substring(0, build.length() - 2);
                     result = "Found " + num + " at index " + build;
                     outputField.setText(result + ".");
                  }   
               }
               catch(NumberNotFoundException exception)
               {
                  outputField.setText("");   //reset for if you search again 
                  JOptionPane.showMessageDialog(null,"Number not found in array", 
                  "Not Found", JOptionPane.ERROR_MESSAGE);
               }
               catch(NumberFormatException exception)
               {
                  outputField.setText("");   
                  JOptionPane.showMessageDialog(null, numError, 
                  "Invalid Input", JOptionPane.ERROR_MESSAGE);
               }                               
               retrieveField1.setText( "" );
            } // end method actionPerformed
         } // end anonymous inner class
      ); // end call to addActionListener
            
      retrieveArea.add( new JLabel( "Enter index to retrieve" ) );
      retrieveField2 = new JTextField( 10 );
      retrieveArea.add( retrieveField2 );
      retrieveField2.addActionListener(
         new ActionListener() 
         {
            public void actionPerformed( ActionEvent event )
            {
                              
               try
               {
                  String input2 = retrieveField2.getText();
                  num = Integer.parseInt(input2);
                  if(num > index - 1) // location not used yet
                     throw new ArrayIndexOutOfBoundsException();
                  else
                  {            
                     String output = num + " is " + Integer.toString(array[num]);
                     outputField.setText("Value at index " + output + ".");
                  }
               }
               catch(NumberFormatException exception)               
               {
                  outputField.setText("");    
                  JOptionPane.showMessageDialog(null, numError, 
                  "Invalid Input", JOptionPane.ERROR_MESSAGE);
               }
               catch(ArrayIndexOutOfBoundsException exception)
               {
                  outputField.setText(""); 
                  JOptionPane.showMessageDialog(null,"Index Not Found.", 
                  "Index Out of Bounds", JOptionPane.ERROR_MESSAGE);
               }
               retrieveField2.setText( "" );
            } // end anonymous inner class
         } // end new ActionListener
      ); // end call to addActionListener
      
      // set up output Panel
      outputArea = new JPanel();
      outputArea.add( new JLabel( "Result" ) );
      outputField = new JTextField( 30 );
      outputField.setEditable( false );
      outputArea.add( outputField );

      add( inputArea );
      add( retrieveArea );
      add( outputArea );
   }  // end constructor
} // end class ArrayAccess