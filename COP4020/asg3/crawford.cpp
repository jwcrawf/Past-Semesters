/*
  cparse.cpp
  Jon Crawford
  COP4020 Assignment 3 Spring 2019
  compile: g++ -Wall -Wextra -std=c++11  cparse.exe cparse.cpp
  Library: http://www.cplusplus.com/reference/clibrary/
  string find: http://www.cplusplus.com/reference/string/basic_string/find/
  algorithm swap: http://www.cplusplus.com/reference/string/string/find/
  algorith find: http://www.cplusplus.com/reference/algorithm/find/
  My strategy was to use a vector of pairs so they would already be split
  Then use a map for the I# states to find if they exist quicker
  I think I made it harder on myself by using pairs because i found
  it hard to bring back the new states i created, I either brought back 
  too many or not enough because i messed up the follow rules
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

typedef std::pair<char,std::string> prod; //typedefined pair of N->rhs eg. E->E+T
std::vector<prod> grammar; // given grammar 
std::vector<std::vector<prod>> sets; // Each I# set is a vector of pairs
std::map<std::string,int> mapKey; // key to the I# levels

void printSets(int count);
size_t count(0), level(1);

int main()
{   
  std::string line;
  std::vector<std::string> input;
  while(getline(std::cin, line))
    input.push_back(line);  
  std::string frt = "'->" + input.front(); 
  input.front() = frt;
  std::cout << "Augmented Grammar" << std::endl;
  std::cout << "-----------------" << std::endl;  
  for(std::vector<std::string>::iterator i = input.begin(); i != input.end(); ++i)
  {      
    std::cout << *i << std::endl;
    (*i).insert((*i).find('>') + 1, 1,'@'); //inserts the first @ symbol
    char n = (*i).front(); // creates N->rhs     
    std::string rhs = (*i).substr((*i).find('>') + 1, (*i).back());     
    grammar.push_back(prod(n, rhs));  //add N->@rhs  
  } 
  sets.push_back(grammar); // pushback first set I0 with N->@rhs
  std::cout << "\nSets of LR(0) Items" << std::endl;
  std::cout << "-------------------" << std::endl;  
  while(count < sets.size())
  {   // check to see if a rule for that one exists and bring back followers   
    for(std::vector<prod>::iterator j = grammar.begin(); j != grammar.end(); ++j)
    {   
      bool found = false, term = false;
      for(size_t i = 0; i < sets[count].size(); ++i)
      {  
        std::string check = sets[count][i].second;     
        prod follow = prod(j->first, j->second);
        char next = check[check.find('@') + 1];
        char bef = check[check.find('@') - 1];
        char jbef = j->second[j->second.find('@') - 1];
        if(islower(next)) // stop at @i
        { 
          term = true; 
          break;
        }            
        if(j->first == next || (jbef == bef && j->second.back() != '@')) //uppercase match
        {    
          for(std::vector<prod>::iterator y = sets[count].begin(); y != sets[count].end(); ++y)           
            if(y->second == j->second) found = true;               
          if(!found) sets[count].push_back(follow);  //add follower        
        }         
      }
      if(term) break;
      found = false;  //reset      
    }  // end for loop for adding followers
    std::cout << 'I' << count << ':' << std::endl;
    printSets(count++);       
    std::cout << std::endl;     
  } // end while loop for producing/printing sets and followers
  return 0;
} // end main
void printSets(int count)
{ 
  std::vector<char> lastChars;   //pool of already printed chars 
  for(std::vector<prod>::iterator i = sets[count].begin(); i != sets[count].end(); ++i)  
  {  
    char next = i->second[i->second.find('@') + 1]; 
    std::string upToNext = i->second.substr(0, i->second.find('@') + 2); //A->ABB
    std::map<std::string,int>::iterator mapEntry = mapKey.find(upToNext);
    std::string shift = i->second;     
    // moves the @ symbol one spot to the right
    std::swap(shift[shift.find('@')], shift[(shift.find('@') + 1)]);
    grammar.push_back(prod(i->first,shift));
    if(i->second.back() == '@') printf("%4c->%s\n", i->first, i->second.c_str());
    else
    { //if it has been created already only print the first goto for that instance
      if(mapEntry != mapKey.end())
      {  //if that char hasnt been printed print whole goto
        if(std::find(lastChars.begin(), lastChars.end(), next) == lastChars.end())
        {    
          printf("%4c->%-17s goto(%c)=I%d\n", i->first, i->second.c_str(), next , mapEntry->second);
          lastChars.push_back(next);          
        }
        else // if that goto has already been printed just print the pair       
          printf("%4c->%s\n", i->first, i->second.c_str()); 
        // add this N->rhs pair where the map key int says is goes               
        if(mapEntry->second > count && shift.back() != '@')         
          sets[mapEntry->second].push_back(prod(i->first, shift));                                  
      }
      else
      { // if it hasn't been seen yet create a new level and pushback to that level                        
        mapKey.insert(std::pair<std::string,int>(upToNext, level++));
        printf("%4c->%-17s goto(%c)=I%d\n", i->first, i->second.c_str(), next , (int)level); 
        std::vector<prod> newSet; // new I# set         
        newSet.push_back(prod(i->first, shift));  // add its first production                        
        sets.push_back(newSet); // pushback the new I# and let the follower loop add it's others
        lastChars.push_back(next);        
      }      
    } // end print/add
  } // end for loop for this set 
}
