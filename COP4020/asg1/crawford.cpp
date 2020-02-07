/*
  cscan.cpp
  Jon Crawford
  COP4020 Spring 2019  
  asg1 - Implementing a C scanner
  Note: Code is mostly self-documenting and compact per COP3330 style
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <cstring>
#include <iomanip>
#include <vector>
#include <algorithm>

#define MAXTOKEN 256 
// credit to TA for Map suggestion, a clever storage hangar
std::map<std::string, int> hangar;
int current, peek, count(1);
// decending custom comparator, kind of like Kevin Bacon
bool desc(const std::pair<std::string,int> &a, const std::pair<std::string,int> &b) 
{ 
  if (a.first.length() > b.first.length() && a.second == b.second)
    return a.second;
  else if (a.first.length() == b.first.length() && a.second == b.second)
    return a.first < b.first;
  else    
    return a.second > b.second; 
} 
// used frequently and manually counts lines
void increment()
{
  if (current == '\n') ++count;
  current = peek;   
  peek = std::fgetc(stdin);
}
// simple white space skip
int skip() 
{
  if(isspace(current)) 
    while (isspace(current))
      increment();     
  return current;
}
// Find a token and store the chars into lexeme buffer 
int scan(char *lexeme) 
{
  int i = 0;
  if (skip() == EOF)
    return EOF; 
  // idents
  else if (isalpha(current) || current == '_')
  {    
    while (isalnum(current) || current == '_') 
    {
      lexeme[i++] = current;
      increment();
    }    
    hangar["ident"]++;
    return i; 
  } 
  // numbers  
  else if (isdigit(current))
  {
    while(isdigit(current))
    {
      lexeme[i++] = current;
      increment();
    }  
    hangar["number"]++;    
    return i;
  } 
  // single line comments
  else if (current == '/' && peek == '/')
  {          
    while (current != '\n')
    {
      if(peek == EOF) return EOF;
      increment();
    }      
    increment();                         
  } 
  // multiple line comments    
  else if (current == '/' && peek == '*')
  {
    increment(); 
    increment();
    if(peek == EOF)
    {
      std::cerr << "unclosed comment\n";
      return EOF; 
    }
    while (current != '*' && peek != '/')
    {
      increment();
      if(peek == EOF)
      {
        std::cerr << "unclosed comment\n";
        return EOF; 
      }
    } 
    increment();
    increment();           
  }
  // begin symbols phase
  else if (ispunct(current))
  {
    // doubles like ++ -- == <<= >>= etc
    if(ispunct(peek) && (current == peek))
    {
      std::string z;
      switch(peek)
      {
        case'<': case '>': case'+': case'-': case'&': case'|': case'=':          
          z.push_back(current);
          lexeme[i++] = current; 
          increment();
          z.push_back(current);
          lexeme[i++] = current;
          if((current == '<' || current == '>') && peek == '=')
          {
            increment();
            z.push_back(current); 
            lexeme[i++] = current;           
          }          
          hangar[z]++;      
          increment();          
          return i;
          break;
        default:
          break;
      }
    }
    // doubles with second equals sign like += *= etc
    if(peek == '=')
    {
      std::string e;
      switch(current)
      {
        case'*': case'/': case'+': case'-': case'!': case'%': case'|': case'&': case'^':
          e.push_back(current);
          lexeme[i++] = current; 
          increment();
          e.push_back(current);
          lexeme[i++] = current;  
          hangar[e]++;      
          increment();
          return i;
          break; 
        default:
          break;
      }
    }
    switch(current)
    {
      // strings
      case '"':
      {                  
        std::string a;
        a.push_back(current);                
        increment();
        while(current != '\n')
        {          
          if (current == '"' && a.back() != '\\')
            break;          
          a.push_back(current);
          increment();
        } 
        if (current == '\n' && a.back() == '\\')
        {
          a.pop_back();
          increment();
          while (current != '"')
          {
            a.push_back(current);
            increment();
          }
        }
        if (current != '\n')
          a.push_back(current);
        if(a.back() != '\"' || a.length() == 1)        
          std::cerr << "missing \" for " << a << " on line " << count << '\n';        
        else 
        {
          hangar["string"]++;
          std::cout << a << '\n';
        }   
        if (peek == EOF || current == EOF) return EOF;      
        increment();            
        break;
      }
      // special characters
      case'\'':
      {        
        std::string c;
        c.push_back(current);        
        increment();        
        while(current != '\n' && current != '\'')
        {                       
          c.push_back(current);
          increment();
        } 
        if (current != '\n')
          c.push_back(current);        
        if (peek == '\'') 
        {
          increment();
          c.push_back(current);          
        }              
        std::size_t found = c.find(' ');
        if(c.length() > 6 && c.back() == '\'')        
          std::cerr << "character constant " << c << " too long on line " << count << '\n';            
        else if (c.at(1) == '\\' && found != std::string::npos)
          std::cerr << "illegal octal constant " << c << " on line " << count << '\n';
        else if (c.front() == '\'' && c.back() == '\'' && c.length() == 2)
          std::cerr << "character has zero length on line " << count << '\n';               
        else if (c.back() != '\'' || current == EOF)
          std::cerr << "missing \' for " << c << " on line " << count << '\n';        
        else
        {  
          hangar["char"]++;
          std::cout << c << '\n';
        }
        if(peek == EOF || current == EOF) return EOF;
        increment();
        break; 
      }  
      // illegal characters
      case '#': case '$': case '@': case '\\': case '`':
        std::cerr << "illegal character: " << (char)current << " on line " << count << '\n'; 
        increment();
        return '\0';
      // - or ->        
      case '-':        
        if (peek == '>')
        {
          std::string m;
          m.push_back(current);
          lexeme[i++] = current; 
          increment();
          m.push_back(current);
          lexeme[i++] = current;  
          hangar[m]++;      
          increment();
          return i;
          break;
        }
        else
        {
          std::string mm; 
          mm.push_back(current);
          hangar[mm]++;
          lexeme[i++] = current;
          increment();
          return i;
          break;
        }
      // at this point its a single valid character  
      default:
        std::string s; 
        s.push_back(current);
        hangar[s]++;
        lexeme[i++] = current;
        increment();
        return i;
        break;
    } //end punct switch    
  } // end punctuation phase 
  else  
    return EOF; // we shouldn't get here hopefully   
  if (current == EOF || peek == EOF) return EOF;
  return 0;
} // end scan
// continually scans and relays valid chars to output until EOF
int main()
{
  char lexeme[MAXTOKEN];
  int  result;  
  current = peek = std::fgetc(stdin);
  if (current != EOF)
    peek = std::fgetc(stdin);
  while ((result = scan(lexeme)) != EOF)    
  {
    if (*lexeme != '\0')
      std::cout << lexeme << std::endl;
    memset(lexeme, 0, sizeof(lexeme));
  }  
  printf("\n        token          count\n");
  printf("---------------------  -----\n");
  // move the hangar contents out to the launchpad, sort and launch
  std::vector<std::pair<std::string, int>> launch(hangar.begin(), hangar.end());
  std::sort(launch.begin(), launch.end(), desc);
  for(std::vector<std::pair<std::string, int>>::iterator i = launch.begin(); i != launch.end(); ++i)
    std::cout << std::setw(21)<< i->first << std::setw(7) << i->second << '\n';  
  return 0;
} // end main
