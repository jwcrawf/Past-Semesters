import java.util.Random;

public class FloridaMan extends Enemy
{
  Random rand = new Random();
  private int weapon;
  public FloridaMan()
  {
    this.setHealth(35 + rand.nextInt(5));
    this.weapon = 2;
  }
  public FloridaMan(int weapon)
  {    
    this.weapon = weapon;
  } 
  public int getWeapon()
  {
    return this.weapon;
  }
  public void setWeapon(int weapon)
  {
    this.weapon = weapon;
  }
  @Override
  public String toString()
  {
    return "A Wasted FloridaMan with a pet gator, matches, duct tape and "
        + this.getHealth() + " health remaining!\n";       
  }
  @Override
  public int fight()
  {
    int strike = rand.nextInt(5) + this.getWeapon();    
    System.out.printf("\nA FloridaMan swings a blow of %d power with their pet gator!\n", strike);
    return strike;
  }
}