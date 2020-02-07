/*
   cxref.l
   Jonathan Crawford
   COP4020 Spring 2019 Assignment 2
   cxref - lexical analysis for a C cross reference listing
   Note: Most portions of code from examples provided
*/


%{

#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <cctype>
#include <string>

#define CHAR    256
#define NUM     257
#define IDENT   258
#define INVALID 259

int character(0);
int string(0);
int comment(0);
int count(1);

%}

quote    \'
back     \\
ditto    \"
octal    [0-7]
octch    ({back}{octal}|{back}{octal}{octal}|{back}{octal}{octal}{octal})
digit    [0-9]
alpha    [a-zA-Z_]
schar    [^\'\"\n\\]
char     ({back}?({schar}|{ditto})|{back}{back}|{back}{quote}|{octch})
special1 ({auto} | {break} | {int} | {long} | {case} | {char} | {register} | {return})
special2 ({const} | {short} | {continue} | {signed} | {default} | {sizeof} | {do})
special3 ({double} | {static} | {struct} | {else} | {switch} | {extern} | {typedef})
special4 ({enum} | {float} | {for} | {union} | {unsigned} | {goto} | {void} | {volatile})
special5 ({if} | {while})
special  ({special1} | {special2} | {special3} | {special4} | {special5})


%x COMMENT
%%
\/\/     {BEGIN COMMENT;}
<COMMENT>
{
  .   {;}
  \n  { ++count; BEGIN INITIAL; }
}

     
\n                              { ++count;}
{alpha}({alpha}|{digit})*       { if (!character) return IDENT; }
{digit}+                        { return NUM;  }
<<EOF>>                         { return EOF;  }
.                               { ; }


%%
std::map<std::string, std::vector<int>> bin;
int main(void)
{
   int toktype;
   while ((toktype = yylex()))
   {
      switch(toktype)
      {
        case IDENT:
            printf("I found the ID: %s\n", yytext);
            break;
        default:
            break;
      }
   }
   return 0;
}
