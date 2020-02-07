/*
  datacache.cpp

  Jon Crawford

  CDA3101 Fall 2018 - Assignment 6 MIPS DataCache Simulator

  Library: http://www.cplusplus.com/reference/clibrary/

  compile: g++ -g datacache.cpp -std=c++11
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

void configs();
void results();
void summary();

unsigned int tag(0), index(0), offset(0), memRef(0),
             dataSize(0), hexAddress(0),             
             tagLine(0), indexLine(0), offsetLine(0);
int numSets(0), setSize(0), lineSize(0), 
    hit(0), miss(0), count(1), lineCount(1);
std::ifstream configFile;
std::string config, datLine, accWord, result;
char delim(':'), access;
bool found = false, set = false;
// cache struct teacher mentioned in discussion board
struct cacheBlock
{
  unsigned int valid, dirty, LRU, bTag;
};
int main()
{
  // Open, store, and print cache configs, allowed to assume they're valid
  configFile.open("trace.config");
  getline(configFile, config, delim);
  configFile >> numSets;
  getline(configFile, config, delim);
  configFile >> setSize;
  getline(configFile, config, delim);
  configFile >> lineSize;
  configFile.close();  
  configs();        
  // Math for global sizes
  offset = log2(lineSize), index = log2(numSets);  
  tag = 32 - (offset + index);    
  // Initialize 2D array of structs per teacher advice
  std::vector<std::vector<cacheBlock>> block;
  block.resize(numSets);
  for(int i =0; i < numSets; ++i)
    block[i].resize(setSize);
  // Begin Loop for References
  while(getline(std::cin, datLine))
  {      
    // Grab all the values, check for R or W, credit to teacher for scan format
    sscanf(datLine.c_str(), "%c:%d:%x", &access, &dataSize, &hexAddress);   
    switch(access)    
    { 
      case 'R':
        accWord = "read";
        break;
      case 'W':
        accWord = "write";
        break;
      default:
        std::cerr << "reference " << std::dec << lineCount << " has unknown access type " 
                  << access << std::endl;
        ++lineCount;
        continue;  
    }  
    // "You should check that the size of each data reference is 1, 2, 4, or 8 bytes."
    switch(dataSize) 
    {   
      case 1: case 2: case 4: case 8:
      // "You should also check if each reference’s address is properly aligned."
      if (hexAddress % dataSize != 0)
      {
        std::cerr << "line " << std::dec <<  lineCount << " has misaligned reference at address " 
                  << std::hex << hexAddress << " for size " << dataSize << std::endl;
        ++lineCount;
        continue; 
      }  
      // calculate the individual line values
      tagLine = hexAddress >> (index + offset);      
      indexLine = (hexAddress >> offset) % numSets;      
      offsetLine = hexAddress % lineSize;
      // Search through index in cache, if found record a hit and update     
      for(int i = 0; i < setSize; ++i)
      {
        if(block[indexLine][i].valid == 1 && block[indexLine][i].bTag == tagLine)
        {
          memRef = 0;
          result = "hit";
          ++hit;          
          if(access == 'W')
            block[indexLine][i].dirty = 1;                      
          found = true;
          for(int i = 0; i < setSize; ++i) 
            block[indexLine][i].LRU += 1;
          block[indexLine][i].LRU = 0;    
          break;     
        }  
      }  
      // if it wasn't found, update and set compulsory miss or search   
      if (!found)
      {      
        memRef = 1; 
        result = "miss"; 
        ++miss;
        for(int i = 0; i < setSize; ++i) 
          block[indexLine][i].LRU += 1;
        // sets the compulsory cache miss 
        for(int i = 0; i < setSize; ++i)
        {
          if(block[indexLine][i].valid == 0)
          {
            block[indexLine][i].valid = 1;
            block[indexLine][i].bTag = tagLine;            
            if(access == 'W')
              block[indexLine][i].dirty = 1;                       
            block[indexLine][i].LRU = 0;  
            set = true; 
            break;          
          }
        } 
        // Then we search for LRU and find the replacement
        if(!set) 
        {     
          int replace(0);                 
          for(int i = 0; i < setSize; ++i)
            if(block[indexLine][i].LRU > block[indexLine][replace].LRU)           
              replace = i;                                                                     
          if(block[indexLine][replace].dirty == 1)
          {
            memRef = 2;
            if(access == 'R') block[indexLine][replace].dirty = 0;
          } 
          else                   
           if(access == 'W') block[indexLine][replace].dirty = 1;                                                                      
          block[indexLine][replace].bTag = tagLine;
          block[indexLine][replace].LRU = 0;
          block[indexLine][replace].valid = 1;          
        } 
      } // End cache search miss, reset identifier bools, print line      
      found = false;
      set = false;
      results();
      ++lineCount;
      ++count;
      break;      
      default:      
        std::cerr << "line " << std::dec << lineCount << " has illegal size " 
                  << dataSize << std::endl;
        ++lineCount;
        continue;
    } // End Outer Byte Check Switch    
  } // End References While loop, adjust count and print summary 
  --count;  
  summary(); 
  return 0;
} // End Main
// Config and pre-roll prints no matter what
void configs()
{
  std::cout << "Cache Configuration\n\n"    
            << "   " << numSets << " " << setSize << "-way set associative entries\n"
            << "   of line size " << lineSize << " bytes\n\n" 
            << "\nResults for Each Reference\n\n" 
            << "Ref  Access Address    Tag   Index Offset Result Memrefs\n"
            << "---- ------ -------- ------- ----- ------ ------ -------" << std::endl;
}
// Formatted output of all the lines
void results()
{     
  std::cout << std::setw(4) << count << std::setw(7) << accWord
            << std::setw(9) << std::hex << hexAddress << std::setw(8) 
            << tagLine << std::setw(6) << std::dec << indexLine << std::setw(7) 
            << offsetLine << std::setw(7) << result << std::setw(8) << memRef << std::endl;   
}
// Summary statistics
void summary()
{    
  std::cout << "\n\nSimulation Summary Statistics\n"
            << "-----------------------------" 
            << "\nTotal hits       : " << hit 
            << "\nTotal misses     : " << miss 
            << "\nTotal accesses   : " << count << std::fixed << std::setprecision(6)
            << "\nHit ratio        : " << (double)hit / (double)count 
            << "\nMiss ratio       : " << (double)miss / (double)count << '\n' << std::endl;
}
