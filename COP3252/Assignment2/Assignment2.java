/*
Jon Crawford 
COP-3252
Assignment 2
1/10/2019
*/

import java.util.Scanner;

public class Assignment2
{ 
  public static void main(String[] args)
  {
    Scanner input = new Scanner(System.in);  
            
    System.out.print("Welcome to Camelot, please enter your knight's name: ");
    String name = input.next();

    System.out.printf("And how old is %s?: ", name);
    int age = input.nextInt();

    System.out.printf("And how much health does %s have?: ", name);
    int health = input.nextInt();

    System.out.printf("And how many battles has %s fought?: ", name);
    int battles = input.nextInt();

    System.out.printf("And how much gold has %s pillaged?: ", name);
    int gold = input.nextInt();

    System.out.printf("\nOur fair Knight %s, known in Camelot as Sir-Jav-a-lot.\n", name);
    System.out.printf("Is %d years old, ", age);
    System.out.printf("with %d units of health.\n", health);
    System.out.printf("They have fought %d battles, ", battles);
    System.out.printf("pillaging %d pieces of gold!\n", gold);

    double averageGold = (double)gold / battles;
    System.out.printf("For an average gold per battle ratio of %f.\n", averageGold);

    input.close();
  }

}