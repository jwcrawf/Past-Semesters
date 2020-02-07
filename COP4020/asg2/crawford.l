/*
   cxref.l
   Jonathan Crawford
   COP4020 Spring 2019 Assignment 2
   cxref - lexical analysis for a C cross reference listing
   Note: Portions of this code attributed to Gang-Ryung Uh 
         and suggestions from the class discussion board.
   Compile using: flex -o ley.yy.cc crawford.l 
                  g++ -o cxref.exe lex.yy.cc -lfl
*/

%{

#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <iomanip>

#define ID 258

int character(0);
int string(0);
int count(1);

%}

quote    \'
back     \\
ditto    \"
octal    [0-7]
octch    ({back}{octal}|{back}{octal}{octal}|{back}{octal}{octal}{octal})
digit    [0-9]
alpha    [a-zA-Z_]
schar    [^\'\"\\n\\]
char     ({back}?({schar}|{ditto})|{back}{back}|{back}{quote}|{octch})
spec1    (auto|break|int|long|case|char|register|return|const|short|continue) 
spec2    (signed|default|sizeof|do|double|static|struct|else|switch|extern)  
spec3    (enum|float|for|union|unsigned|goto|void|volatile|if|while|typedef)
spec     ({spec1}|{spec2}|{spec3})

%x BLOCK
%x COMMENT
%x PROC

%%
{spec}                          { ; }

\/\/                            { if(!character && !string) BEGIN COMMENT; }
<COMMENT>
{
  .     {;}  
  \n    { ++count; BEGIN INITIAL; }
}

\/\*                            { if(!character && !string) BEGIN BLOCK; }
<BLOCK>
{
  .     {;}
  \n    { ++count; }
  \*\/  { BEGIN INITIAL; }
}

^#                              { if(!character && !string) BEGIN PROC; }
<PROC>
{
  .     {;}
  \n    { ++count; BEGIN INITIAL; }
}


{back}{back}                    { ; }
({back}{ditto}|{back}{quote})   { ; }
\n                              { ++count;}
{quote}                         { if(!string) character = !character; }
{ditto}                         { if(!character) string = !string;}
{alpha}({alpha}|{digit})*       { if(!character && !string) return ID; }
{digit}+                        { ; }
<<EOF>>                         { return EOF; }
.                               { ; }

%%
/* As with last assignment, map is good for sorted output.
   I realize it might be considered passe to conflate 
   the vector with duplicate entries but this helped me debug
   to make sure I got every instance and the amount of times the
   same word is on the same line is not that many occurences. 
   This gives me an index in the vector that I handle in print */
std::map<std::string, std::vector<int> > bin;
int main(void)
{
  int toktype;
  while((toktype = yylex()) != EOF)  
    if(toktype == ID)      
      bin[yytext].push_back(count);   
  std::map<std::string, std::vector<int> >::iterator i;
  for(i = bin.begin(); i != bin.end(); ++i)
  {
    std::cout << std::setw(25) << i->first << ": ";
    std::vector<int>::iterator j;
    for(j = i->second.begin(); j != i->second.end(); ++j)
    {      
      // this if can be commented out for debug
      if(*j != *(j-1))
      {
        // this peek works for first and final element
        if(*j != i->second.back())
          std::cout << *j << ", ";
        else
          std::cout << *j << std::endl;
      }
    } // end vector page index values print    
  } // end hash identification categories
  return 0;
} // end main