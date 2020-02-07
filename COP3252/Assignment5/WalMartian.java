import java.util.Random;

public class WalMartian extends Enemy
{
  Random rand = new Random();
  private int weapon;
  public WalMartian()
  {
    this.setHealth(30 + rand.nextInt(5));
    this.weapon = 5;
  }
  public WalMartian(int weapon)
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
    return "A 2:00am Walmart shopper with a full cart and " 
            + this.getHealth() + " health remaining!\n";            
  }
  @Override
  public int fight()
  {
    int strike = rand.nextInt(5) + this.getWeapon();    
    System.out.printf("\nA WalMartian lands a blow of %d power with their cart!\n", strike);
    return strike;
  }
}