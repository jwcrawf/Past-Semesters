import java.util.Random;

public class SpringBreaker extends Enemy
{
  Random rand = new Random();
  private int weapon;
  public SpringBreaker()
  {
    this.setHealth(25 + rand.nextInt(5));
    this.weapon = 3;
  }
  public SpringBreaker(int weapon)
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
    return "An Obnoxious under age Spring Breaker with their parent's "
      + "credit card and " + this.getHealth() + " health remaining!\n";          
  }
  @Override
  public int fight()
  {
    int strike = rand.nextInt(5) + this.getWeapon();    
    System.out.printf("\nA Spring Breaker swipes a blow of %d power with their credit card!\n", strike);    
    return strike;    
  }
}