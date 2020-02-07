import java.util.Random;

public class Knight
{
  Random rand = new Random();
  private String weapons[] = {"Long Sword","Battle Axe","Spear","Warhammer"};
  private String armors[] = {"Leather","Steel","Bronze"};  
  private String name;
  private int health, armor, weapon;
  // Constructors
  public Knight()
  {
    this.name = "Theodore of Schumania";
    this.health = 100;     
    this.armor = rand.nextInt(3);
    this.weapon = rand.nextInt(4);     
  }
  public Knight(String name, int armor, int weapon)
  {
    this.name = name;
    this.health = 100;    
    this.armor = armor;
    this.weapon = weapon;
  }
  // Getters
  public String getName()
  {
    return this.name;
  }
  public int getHealth()
  {
    return this.health;
  }  
  public int getArmor()
  {
    return this.armor;
  }
  public int getWeapon()
  {
    return this.weapon;
  }
  // Setters
  public void setName(String name)
  {
    this.name = name;
  }
  public void setHealth(int health)
  {
    this.health = health;
  }   
  public void setArmor(int armor)
  {
    this.armor = armor;
  }
  public void setWeapon(int weapon)
  {
    this.weapon = weapon;
  }
  @Override
  public String toString()
  {      
    return "Name: " + this.getName() + "\nWeapon: " + weapons[this.getWeapon()]
            + "\nArmor: " + armors[this.getArmor()] + "\nHealth: " + this.getHealth(); 
  }  
}