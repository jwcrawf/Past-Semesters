/*
  Jon Crawford COP3252 TicTacToe 
*/

import java.util.Scanner;
import java.util.Random;

public class TicTacToe
{  	
  private static Scanner kybd = new Scanner(System.in);
  
  public static void main(String args[])
  {
    System.out.println("\nPlease increase your terminal height for best gameplay..\n");
    boolean finished = false;
    while(!finished)
    {      
      System.out.printf("Welcome to TicTacToe, what is player one's name?: ");
      String player1 = kybd.nextLine();
      System.out.printf("And what is player two's name?: ");
      String player2 = kybd.nextLine();
      System.out.println();
      char game[][] = new char [3][3];
      int fill = 49; 
      for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
          game[i][j] = (char)fill++;      
      int round = 1;
      int turn = 0;
      boolean winner = false;
      Random rand = new Random();
      int coinFlip = rand.nextInt(50);
      if(coinFlip % 2 == 0) turn = 1;
      while(!winner)
      {
        if(turn == 0)
        {
          System.out.printf("Round %d, %s(X)'s Turn\n", round, player1);
          print(game);
          System.out.printf("Please pick a remaining value 1-9, or 0 to end game: ");
          int p1 = kybd.nextInt();
          if(p1 == 0)
          {
            System.out.printf("%s is the winner, %s has given up..\n", player2, player1);
            break;
          }           
          pick(game,p1,'X');
          if(check(game,'X'))
          {   
            System.out.println();        
            print(game);  
            System.out.printf("%s(X) is the winner! congratulations!\n", player1);         
            winner = true;
          }
          turn = 1;
        }
        else
        {
          System.out.printf("Round %d, %s(O)'s Turn\n", round, player2);
          print(game);
          System.out.printf("Please pick a remaining value 1-9, or 0 to end game: ");
          int p2 = kybd.nextInt();
          if(p2 == 0) 
          {
            System.out.printf("%s is the winner, %s has given up..\n", player1, player2);            
            break;
          }          
          pick(game,p2,'O');
          if(check(game,'O'))
          {            
            System.out.println(); 
            print(game); 
            System.out.printf("%s(O) is the winner! congratulations!\n", player2);          
            winner = true;
          }
          turn = 0;
        }  
        ++round;
        if(round == 10 && winner == false)
        {
          System.out.println("Too bad, its a draw!");
          print(game);          
          winner = true;
        }        
      }
      kybd.nextLine(); 
      System.out.printf("Would you like to quit? (y|n): ");
      String done = kybd.nextLine();
      if(done.equals("y"))
        finished = true;      
    }
    kybd.close();
  }
  public static void print(char[][] game)
  {    
    System.out.println("-------------------");
    System.out.println("|      F S U      |");
    System.out.println("-------------------");
    for(int i = 0; i < 3; ++i)
    { 
      System.out.printf("|");
      for(int j = 0; j < 3; ++j)      
        System.out.printf("  %c  |", game[i][j]);      
      System.out.println("\n-------------------");      
    }
    System.out.println("| By:Jon Crawford |");
    System.out.println("-------------------");
  }
  public static void pick(char[][] game, int pick, char user)
  {
    switch(pick)
    {
      case 1: game[0][0] = user; break;
      case 2: game[0][1] = user; break;
      case 3: game[0][2] = user; break;
      case 4: game[1][0] = user; break;
      case 5: game[1][1] = user; break;
      case 6: game[1][2] = user; break;
      case 7: game[2][0] = user; break;
      case 8: game[2][1] = user; break;
      case 9: game[2][2] = user; break;
      default: break; 
    }
  }
  public static boolean check(char[][] game, char user) //check for winner
  {
    if(game[0][0] == user && game[0][1] == user && game[0][2] == user) return true; //123
    if(game[1][0] == user && game[1][1] == user && game[1][2] == user) return true; //456
    if(game[2][0] == user && game[2][1] == user && game[2][2] == user) return true; //789
    if(game[0][0] == user && game[1][0] == user && game[2][0] == user) return true; //147
    if(game[0][1] == user && game[1][1] == user && game[2][1] == user) return true; //258
    if(game[0][2] == user && game[1][2] == user && game[2][2] == user) return true; //369
    if(game[0][0] == user && game[1][1] == user && game[2][2] == user) return true; //159
    if(game[0][2] == user && game[1][1] == user && game[2][0] == user) return true; //357
    return false;
  }
}

