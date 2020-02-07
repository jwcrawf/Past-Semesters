/*
  ranmaze2t.cpp

  Jon Crawford

  COP4531 Summer 2019 proj3 - Mazes on the Web

*/

#include <partition2.h>
#include <xran.h>
#include <vector.h>
#include <cmath>
#include <fstream>
#include <iostream>

const uint8_t NORTH = 0x01;
const uint8_t EAST  = 0x02;
const uint8_t SOUTH = 0x04;
const uint8_t WEST  = 0x08;
static fsu::Random_unsigned_int ran;

void Connect(
              size_t beg , size_t end ,            // start and goal cells
              size_t numrows, size_t numcols,      // maze dimensions
              fsu::Vector<uint8_t>& maze ,         // walls codes for cells - passed by reference
              fsu::Partition<size_t>& p            // tracks component structure - passed by reference
            );
void WriteMaze(
                std::ofstream& of,
                size_t beg , size_t end ,            // start and goal cells
                size_t numrows, size_t numcols,      // maze dimensions
                fsu::Vector<uint8_t>& maze        // walls codes for cells - passed by reference
              );

int main (int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cout << "** command line arguments required:\n"
              << "   1: number of rows\n"
              << "   2: number of cols\n"
              << "   3: file name for maze\n";
    return 0;
  }
  size_t numrows = atoi(argv[1]), numcols = atoi(argv[2]),  
         numcells = numrows * numcols, trace(0), components,  
         start = numrows / 2 * numcols, goal = start + (numcols - 1);
  fsu::Vector<uint8_t> maze (numcells, 15);   // all closed boxes
  fsu::Partition<size_t> p (numcells);        // all singletons
  std::cout << "Welcome to ranmaze." << '\n'
            << " numrows  = " << numrows << '\n'
            << " numcols  = " << numcols << '\n'
            << " numcells = " << numcells << '\n'
            << " start    = " << start << '\n'
            << " goal     = " << goal << '\n'
            << " trace    = " << trace << '\n';
  // ensure goal is reachable from start:
  std::cout << " components after 0 passes:   " << p.Components() << '\n';
  Connect (start, goal, numrows, numcols, maze, p);
  components = p.Components();
  std::cout << " components after 1 pass:     " << components << '\n';  
  std::ofstream out1;
  size_t n = strlen(argv[3]);    
  // output intermediate result the first time goal is reachable
  if (components > 1) 
  {  
    size_t digits = 1 + (size_t)log10(components);
    size_t s = n + digits;
    char filec[s + 1];
    strcpy(filec, argv[3]);
    filec[n] = '.';
    for (size_t i = 0; i < digits; ++i)
    {
      char digit = '0' + (char)(components % 10); 
      filec[s - i] = digit;
      components /= 10;
    } 
    filec[s + 1] = '\0'; 
    out1.open(filec);  
    WriteMaze(out1, start, goal, numrows, numcols, maze);
    out1.close();
    out1.clear();
    std::cout << "1-pass maze written to file " << filec << '\n';  
    for (size_t cell = 1; cell < numcells; ++cell)       
      Connect (0, cell, numrows, numcols, maze, p); 
  }
  std::cout << " components after all passes: " << p.Components() << '\n'; 
  char file1[n + 3];
  strcpy(file1, argv[3]);
  file1[n] = '.';
  file1[n + 1] = '1';
  file1[n + 2] = '\0';  
  out1.open(file1);
  WriteMaze(out1, start, goal, numrows, numcols, maze);
  out1.close();
  out1.clear();
  std::cout << "n-pass maze written to file " << file1 << '\n';
  return 0;
}

void Connect(size_t beg, size_t end, size_t numrows, size_t numcols, 
              fsu::Vector<uint8_t>& maze, fsu::Partition<size_t>& p)
{  
  while(!p.Find(beg, end))
  {    
    size_t cell = ran(0, (numrows * numcols) - 1), compass = ran(0, 4);
    size_t zero(0), neighbor;     
    switch (compass)
    {
      case 0:
        if(cell >= zero && cell < numcols)
          continue;
        else
          neighbor = cell - numcols; 
        break;
      case 1:
        if((cell + 1) % numcols == 0)
          continue;
        else
          neighbor = cell + 1;
        break;
      case 2:
        if(cell >= (cell - numcols))
          continue;
        else
          neighbor = cell + numcols;        
        break;
      case 3:
        if(cell % numcols == 0)
          continue;
        else
          neighbor = cell - 1;
        break;
      default: //should be unreachable
        std::cerr << "Error calling fsu::random..." << std::endl; 
        break;
    }
    if(!p.Find(cell, neighbor))
    {
      switch (compass)
      {
        case 0:
          maze[cell] &= ~NORTH;
          maze[neighbor] &= ~SOUTH;
          break;
        case 1:
          maze[cell] &= ~EAST;
          maze[neighbor] &= ~WEST;
          break;
        case 2:
          maze[neighbor] &= ~NORTH;
          maze[cell] &= ~SOUTH;          
          break;
        case 3:
          maze[neighbor] &= ~EAST;
          maze[cell] &= ~WEST;          
          break;
        default: //should be unreachable
          std::cerr << "Error calling fsu::random..." << std::endl; 
          break;
      }
      p.Union(cell, neighbor);
    }
  }  
}

void WriteMaze(std::ofstream& of, size_t start, size_t goal, size_t numrows, 
                size_t numcols, fsu::Vector<uint8_t>& maze)
{  
  size_t index = 0;
  of << '\t' << numrows << '\t' << numcols << '\n';  
  for(size_t i = 0; i < numrows; ++i)
  {
    for(size_t j = 0; j < numcols; ++j)      
      of << '\t' << (size_t)maze[index++];  
    of << '\n';
  }
  of << '\t' << start << '\t' << goal << '\n';
}