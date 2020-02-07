/*
  KnightDriver
  Jonathan Crawford
  COP3252 Spring 2019 Assignment 4
*/

import java.util.Scanner;
import java.util.Random;

public class KnightDriver
{  	
  private static Scanner kybd = new Scanner(System.in);
  public static void main(String args[])
  {
    Random rand = new Random();
    boolean finished = false;        
    while(!finished)
    {      
      String userName = "";
      String done ="";
      System.out.println("A Test of Bravery Awaits..\n");
      Knight user = new Knight();
      System.out.printf("Welcome, what is your Knight's name?: ");
      userName = kybd.nextLine();
      user.setName(userName);
      pick(user);  
      System.out.println("\nYour Knight:\n" + user.toString());      
      System.out.printf("\nWould you like to autogenerate your opponent?: (y|n) ");      
      String in = kybd.nextLine();
      Knight cpu = new Knight();
      if(in.equals("y")) 
        System.out.println("\nYour random opponent is:\n" + cpu.toString());
      else
      { 
        System.out.printf("What is your opponent's name? ");
        String cpuName = kybd.nextLine();
        cpu.setName(cpuName);       
        pick(cpu);       
        System.out.println("\nYour opponent's setup is:\n" + cpu.toString());
      }
      System.out.print("\nPress Enter key if ready or start over? (x = Restart) ");      
      String pause = kybd.nextLine();
      if(pause.equals("x")) continue;
      System.out.println("\nThe Battle Commences...\n");      
      int round = 1, turn = 0;
      // coin toss to determine who goes first
      int coinFlip = rand.nextInt(50);
      if(coinFlip % 2 == 0) turn = 1;
      while(user.getHealth() >= 0 && cpu.getHealth() >= 0)
      {
        System.out.printf("\nWelcome to Round %d\n", round);
        if(turn == 1)
        {
          user.fight(cpu);          
          turn = 0;
        }
        else 
        {
          cpu.fight(user);
          turn = 1;
        }
        if(user.getHealth() <= 0 || cpu.getHealth() <= 0)
          break;        
        System.out.printf("\nChoose?: (Enter = Just Keep fighting!|s = See Knights Readouts and continue|x = Give up the fight) ");
        done = kybd.nextLine();        
        if(done.equals("x")) break;
        if(done.equals("s"))
        {
          System.out.println("\n" + user.toString());        
          System.out.println("\n" + cpu.toString());
        }           
        ++round;
        continue;         
      } 
      if(user.getHealth() > cpu.getHealth() && !done.equals("x"))
        System.out.printf("\n%s is the Victor! Well done my Lord!\n", user.getName());
      else if(user.getHealth() == cpu.getHealth() && !done.equals("x"))
        System.out.println("\nLooks like their houses have agreed to a draw\n");
      else
        System.out.printf("\nOh no! %s is the Winner! A stain on our house..\n", cpu.getName());        
      System.out.printf("\nWhat would you like to do?: (x = quit|Enter = play again) ");
      String cont = kybd.nextLine();      
      if(cont.equals("x"))
        finished = true;
      else
        continue;          
    }    
    kybd.close(); 
  } 
  public static void pick(Knight temp)
  {
    int armor, weapon;     
    Random rand = new Random();       
    System.out.println("\nNow select a weapon! (Choose number)");
    System.out.println("1) Long Sword");
    System.out.println("2) Battle Axe");
    System.out.println("3) Spear");
    System.out.println("4) Warhammer");
    System.out.printf("Your choice my liege?: ");
    weapon = kybd.nextInt();    
    switch(weapon)
    {
      case 1: temp.setWeapon(0); break;
      case 2: temp.setWeapon(1); break;
      case 3: temp.setWeapon(2); break;
      case 4: temp.setWeapon(3); break;    
      default:
      System.out.println("Invalid, selecting random weapon.."); 
      temp.setWeapon(rand.nextInt(4)); 
      break;
    }   
    System.out.println("\nNow select an armor! (Choose number)");
    System.out.println("1) Leather");
    System.out.println("2) Steel");
    System.out.println("3) Bronze");    
    System.out.printf("Your choice my liege?: ");
    armor = kybd.nextInt();     
    switch(armor)
    {
      case 1: temp.setArmor(0); break;
      case 2: temp.setArmor(1); break;
      case 3: temp.setArmor(2); break;         
      default: 
      System.out.println("Invalid, selecting random armor..");
      temp.setArmor(rand.nextInt(3)); 
      break;
    }  
    kybd.nextLine();   
  }    
}
