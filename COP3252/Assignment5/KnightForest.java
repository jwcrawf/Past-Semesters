import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.Random;

public class KnightForest
{
  private static Scanner kybd = new Scanner(System.in);
  public static void main(String[] args)
  {
    Random rand = new Random();
    boolean finished = false;
    while(!finished)
    {
      System.out.printf("\nWelcome, what is your knight's name?: ");
      String userName = kybd.nextLine();
      System.out.printf("\nOn their way home from the Colombian Crusades \n %s " +
      "decides to take a shortcut through the JavaBean forest... \n\n", userName);
      Knight user = new Knight();
      user.setName(userName);
      int count = 0;     
      System.out.println("\nOur knight sets off into the wood with this loadout leftover from the crusades..");
      System.out.println('\n' + user.toString());
      System.out.printf("\nAs darkness begins to fall on the wood %s crosses a bridge \n into ",user.getName());
      System.out.println("an abandoned farm's field and head's toward the crumbling cabin to make camp..\n");      
      boolean taken = false;
      // input mismatch exception chapter 11.3
      while(!taken)
      {  
        try   
        {
          System.out.printf("\nThey hear a rustling coming from the trees, how many enemies are approaching? (Enter 1-10):");
          count = kybd.nextInt();
        } 
        catch (InputMismatchException exception)
        {        
          System.out.println("Non-number input, try again..");
          kybd.next();
          continue;
        }       
        taken = true;
      } 
      kybd.nextLine();    
      Enemy[] enemies = new Enemy[count];
      for (int i = 0; i < count; ++i)      
        enemies[i] = Enemy.getRandomEnemy();
      System.out.println("\nLook who is approaching now, get ready for a fight!\n");
      printEnemies(enemies);      
      boolean quitter = false;
      int round = 1;
      while(!quitter)
      {
        System.out.printf("\nWelcome to round %d\n", round);
        for(int i = 0; i < count; ++i)
        { //only fights living enemies
          if(enemies[i].getHealth() > 0 && user.getHealth() > 0) 
          {
            int strike = enemies[i].fight();
            user.setHealth(user.getHealth() - strike);
            int response = 2 * (rand.nextInt(10)+ 1) + user.getWeapon();
            System.out.printf("%s has struck back with a strike of %d power!\n", user.getName(), response);
            try
            {
              enemies[i].takeDamage(response);
            }
            catch (DeathBlow exception)
            {
              enemies[i].setHealth(0);
              System.out.println(exception);  //the msg is optional but i like it           
            } 
            if(enemies[i].getHealth() == 0)  
              System.out.println("Knockout!");
            else   
              System.out.printf("This enemy's health now reads %d\n", enemies[i].getHealth());
          }
        }
        if (user.getHealth() <= 0 || !enemyCheck(enemies)) break;  
        System.out.printf("\nAfter round %d, %s's health now reads %d\n", round, user.getName(), user.getHealth());     
        System.out.printf("\nChoose: (Enter = continue, s = see remaining enemies, q = give up and die):");
        String pause = kybd.nextLine();
        if(pause.equals("s"))
          printEnemies(enemies);
        if(pause.equals("q"))                  
          quitter = true;               
        ++round;
      } 
      if(user.getHealth() > 0 && !quitter)
        System.out.printf("\n%s has survived the night, well done my lord!\n", user.getName());
      else
      {
        System.out.printf("\n%s has has failed to survive the forest, their body consumed by gators\n", user.getName());
        System.out.println("\nSurviving enemies:\n");
        printEnemies(enemies);
      }
      System.out.printf("\nThis fight is over, would you like to play again? (y|n):");
      String end = kybd.nextLine();
      if(end.equals("n")) finished = true;
    }
    kybd.close();
  }// end main
  public static boolean enemyCheck(Enemy[] enemies) //checks to see if any enemies are alive
  {
    for(int i = 0; i < enemies.length; ++i)
      if(enemies[i].getHealth() > 0)
        return true;
    return false;
  }
  public static void printEnemies(Enemy[] enemies) // Prints live enemies
  {
    for(int i = 0; i < enemies.length; ++i)
      if(enemies[i].getHealth() > 0) 
      {
        System.out.printf("Enemy %d: ", i + 1);
        System.out.println(enemies[i].toString());
      }
    System.out.printf("Hit enter to continue\n");
    kybd.nextLine();
  }   
}