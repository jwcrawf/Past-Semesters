/*
  cleanup.cpp

  Jon Crawford

  2/15/2018

  a slave file to cleanup input strings
*/

#include <wordsmith.h>

void WordSmith::Cleanup(fsu::String& s)
{
  size_t i = 0;
  char ch = s.Element(i);
  while (!( ch == '\0' 
            || isalnum(ch) 
            || ch == '\\' 
            || (ch == '-' && isdigit(s.Element(i+1))) 
            || (ch == ':' && (s.Element(i+1) == ':') && isalnum(s.Element(i+2))))) 
  {
    ch = s.Element(++i);
  }
 
  size_t beg = i;
  while ( isalnum(ch)     
          || (ch == '\\' && isalnum(s.Element(i+1)))
          || (ch == '\'' && isalnum(s.Element(i+1)))
          || (ch == '-'  && isalnum(s.Element(i+1)))
          || (ch == '.'  && isalnum(s.Element(i+1)))
          || (i > 0 && ch == ',' && isdigit(s.Element(i+1)) && isdigit(s.Element(i-1)))
          || (i > 0 && ch == ':' && isdigit(s.Element(i+1)) && isdigit(s.Element(i-1))))  
 {
   s[i - beg] = tolower(ch);
   ch = s.Element(++i);
 }
 size_t end = i;
 s.SetSize(end-beg);         
          
}
