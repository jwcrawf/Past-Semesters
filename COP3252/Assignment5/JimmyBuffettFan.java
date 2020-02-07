import java.util.Random;

public class JimmyBuffettFan extends Enemy
{
  Random rand = new Random();
  private int weapon;
  public JimmyBuffettFan()
  {
    this.setHealth(15 + rand.nextInt(5));
    this.weapon = 1;
  }
  public JimmyBuffettFan(int weapon)
  {
    this.weapon = weapon;
  }
  public int getWeapon()
  {
    return this.weapon;
  }
  @Override
  public String toString()
  {
    return "A Jimmy Buffett Fan with a Bluetooth speaker and "
      + this.getHealth() + " health remaining!\n";           
  }
  @Override
  public int fight()
  {
    int strike = rand.nextInt(5) + this.getWeapon();    
    System.out.printf("\nA Jimmy Buffett fan deals a blow with %d volume on their speaker!\n", strike);
    return strike;
  }
}