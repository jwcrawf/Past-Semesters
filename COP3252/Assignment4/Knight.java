import java.util.Random;

public class Knight
{
  Random rand = new Random();
  private String weapons[] = {"Long Sword","Battle Axe","Spear","Warhammer"};
  private String armors[] = {"Leather","Steel","Bronze"};
  private String names[] = {"Theodore of Schumania","The Mountain","Brienne of Tarth"};
  private String name;
  private int health, armor, weapon;
  // Constructors
  public Knight()
  {
    this.name = names[rand.nextInt(3)];
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
  public void fight(Knight opp)
  {
    /* Each round it is possible for the Knight to strike a random blow between 1 - 5 
       strength, that value is then multiplied by 10 to make the game go faster, obviously
       that can be altered, the users weapon then adds on an additional 1-4 points based
       based on its strength. I felt their needed to be the chance for glancing blows 
       and haymakers basically. To keep the program simple i used their index value as a 
       progression, with the higher numbers getting stronger for both weapon and armor.
       The opponents armor then counteracts some of the damage given and the result is 
       subtracted from their total health. There's many ways to go about this and the 
       multiplier could be tweaked based on difficulty or whatnot, in the end i think
       thats not what the assignment is really about so i just picked a way. */
    System.out.printf("It is %s's turn..\n", this.getName());
    int hitStrength = (rand.nextInt(5) + 1) * 10;
    int damage = (this.getWeapon() + 1) + hitStrength;
    System.out.printf("They have struck a blow of %d power dealing %s damage with the %s\n", hitStrength, damage, weapons[this.getWeapon()]);
    int block = (opp.getArmor() + 1) * 3;
    opp.setHealth(opp.getHealth() - (damage-block));
    System.out.printf("%s's Health now reads %d after armor!\n", opp.getName(), opp.getHealth());
  }
}