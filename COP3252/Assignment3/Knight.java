public class Knight
{
  private String name;
  private int health, battles, age, gold;
  // Constructors
  public Knight()
  {
    this.name = "";
    this.health = 0;
    this.battles = 0;
    this.age = 0;
    this.gold = 0;
  }
  public Knight(String name, int health, int battles, int age, int gold)
  {
    this.name = name;
    this.health = health;
    this.battles = battles;
    this.age = age;
    this.gold = gold;
  }
  // Getters
  public String getName()
  {
    return name;
  }
  public int getHealth()
  {
    return health;
  }
  public int getBattles()
  {
    return battles;
  }
  public int getAge()
  {
    return age;
  }
  public int gold()
  {
    return gold;
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
  public void setBattles(int battles)
  {
    this.battles = battles;
  }
  public void setAge(int age)
  {
    this.age = age;
  }
  public void setGold(int gold)
  {
    this.gold = gold;
  }
  public void printKnight()
  {
    System.out.printf("Knight Name: Sir %s of Jav-a-lot\n", name);
    System.out.printf("Knight Health: %d\n", health);
    System.out.printf("Knight Battles: %d\n", battles);
    System.out.printf("Knight Age: %d\n", age);
    System.out.printf("Knight Gold: $%d\n", gold);
  }
}