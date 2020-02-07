public class Stars
{
  private int row, column;
  private String starLine ="";
  public Stars()
  {
    this.row = 0;
    this.column = 0;    
  }
  public Stars(int row, int column)
  {
    this.row = row;
    this.column = column;    
  }
  public int getRow()
  {
    return row;
  }
  public int getColumn()
  {
    return column;
  }  
  public void setRow(int row)
  {
    this.row = row;
  }
  public void setColumn(int column)
  {
    this.column = column;
  }  
  public void printStars()
  {
    makeLine();
    for (int i = 0; i < row; ++i)
    {
      if(i % 2 != 0) System.out.print(" ");
      System.out.println(starLine);
    }
  }
  public void makeLine()
  {
    for (int i = 0; i < column; ++i)
      starLine += "* ";
  }
}