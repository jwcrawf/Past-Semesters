/*
  KnightDriver
  Jonathan Crawford
  COP3252 Spring 2019 Assignment 3
*/

import javax.swing.JOptionPane;

public class KnightDriver
{
  public static void main(String args[])
  {
    String name = JOptionPane.showInputDialog("Hello friend! What is your knight's name?");
    int battles = Integer.parseInt(JOptionPane.showInputDialog("How many battles have they fought?"));
    int age = Integer.parseInt(JOptionPane.showInputDialog("How old is this knight?"));
    int health = Integer.parseInt(JOptionPane.showInputDialog("How much health do they have?"));
    int gold = Integer.parseInt(JOptionPane.showInputDialog("How much gold have they pillaged?"));
    int row = Integer.parseInt(JOptionPane.showInputDialog("How tall is the night sky?"));
    int column = Integer.parseInt(JOptionPane.showInputDialog("Beautiful, and how wide is the night sky?"));
    Knight knight = new Knight(name, battles, age, health, gold);
    Stars stars = new Stars(row, column);
    knight.printKnight();    
    stars.printStars();
  }  
}
