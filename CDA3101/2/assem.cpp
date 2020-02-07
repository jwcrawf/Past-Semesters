/*
   Jon Crawford
   
   CDA3101 Fall 2018
   
   Assignment 2 - MIPS Assembler
   
   Library from: http://www.cplusplus.com/reference/clibrary/
   
   Compile: "g++ -g assem.cpp -std=c++11" 
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cstring>
#include <array>
#include <ios>
#include <iomanip>
#include <sstream>

#define MAXLINE 80
#define MAXREG 5
#define MAXP 32768
#define MAXSYM 10

struct
{
  union 
  {
    unsigned int x;      
    struct 
    {
      unsigned int func:6;
      unsigned int shift:5;
      unsigned int rd:5;
      unsigned int rs:5;
      unsigned int rt:5;
      unsigned int oper:6;
    } rFormat;
    
    struct
    {
      unsigned int target:26;
      unsigned int oper:6;
    } jFormat;
    
    struct
    {
      unsigned int offset:16;
      unsigned int rt:5;
      unsigned int rs:5;      
      unsigned int oper:6;
    } iFormat;
    
  } u;  
} inArray[MAXP] = {0}; // the array of instructions to print

int main()
{
 
  char line[MAXLINE]={0}, tempLine[MAXLINE],labelTemp[MAXSYM],
       oper[MAXSYM]={0}, 
       offset[MAXSYM]={0},
       rd[MAXREG]={0},
       rs[MAXREG]={0},
       rt[MAXREG]={0},
       shift[MAXREG]={0},        
       target[MAXSYM] = {0},
       directive[MAXSYM]={0},
       label[MAXSYM]={0},
       exLabel[MAXP][MAXSYM]={0},
       textLabel[MAXP][MAXSYM]={0},
       dataLabel[MAXP][MAXSYM]={0},       
       textCopy[MAXP][MAXLINE]={0};

  unsigned int  count = 0, iCount = 0, dataCount = 0, copyCount = 0;
  bool dataSegment = false; 
  int data[MAXP]={0}; 
  
  char regIndex[32][MAXREG] = { "zero", "at", "v0", "v1", "a0", 
  "a1", "a2", "a3", "t0","t1", "t2", "t3", "t4", "t5",
  "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", 
  "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra" };

  while (fgets(textCopy[copyCount], MAXLINE, stdin)) 
    ++copyCount;
  int lCount = 0;
  while (textCopy[lCount][0] != '\0')    
  {  
    strcpy(line, textCopy[lCount]);    
    if(!dataSegment)
    {
      if(sscanf(line, "%[^:]: %[^#]#" , label, tempLine) == 2)
        strcpy(textLabel[count], label);
      //++count;
    }
    
    
    if (dataSegment)
    {
      if(sscanf(line, "%[^:]: %s %s", label , directive, tempLine) == 3)
      {
        strcpy(textLabel[count], label);
        //++count;
        if(strcmp(directive,".word") == 0)
        {                   
          std::string str = tempLine;
          std::stringstream stream (str);
          int i = 0;
          while (stream >> i)
          {
            data[dataCount] = i;
            if (stream.peek() == ',' || stream.peek() == ' ')
              stream.ignore();
          //data[dataCount] = atoi(tempLine);
            ++dataCount;
          }
        }
        if (strcmp(directive,".space") == 0)
        {
          int n = atoi(tempLine);
          dataCount += n;
          for(int i = 0; i < n; ++i)
          {
            data[dataCount] = 0;            
          }     

        }
        
      }
      if (sscanf(line, "%s %s", directive, tempLine) == 2)
      {
        if(strcmp(directive,".word") == 0)
        {
          std::string str = tempLine;
          std::stringstream stream (str);
          int i = 0;
          while (stream >> i)
          {
            data[dataCount] = i;
            if (stream.peek() == ',' || stream.peek() == ' ' )
              stream.ignore();
            //data[dataCount] = atoi(tempLine);                                                                                                                      
            ++dataCount;
          }  
        }
        if (strcmp(directive,".space") == 0)
        {
          int n = atoi(tempLine);
          dataCount += n;
          for(int i = 0; i < n; ++i)
          {
            data[dataCount] = 0;
           
          }  
        }        
      } 
    
       
    }      
     
   
    if(sscanf(line, " .%s", directive) == 1) 
    {    
      if (strcmp(directive,"text") == 0)
      {
        dataSegment = false;
        ++lCount;        
        continue;
      }
      if (strcmp(directive,"data") == 0)
      {
        dataSegment = true; 
        ++lCount;        
        continue;              
      }       
    }
        
    
    ++count;  
  ++lCount;
       
  } 
  lCount = 0; 
  count = 0;
  while (textCopy[lCount][0] != '\0')
  {
    
    strcpy(line, textCopy[lCount]);
    
    if(sscanf(line, " .%s", exLabel[lCount]) == 1) 
    {    
      if (strcmp(exLabel[lCount],"text") == 0)
      {
        dataSegment = false;
        ++lCount;        
        continue;
      }
      if (strcmp(exLabel[lCount],"data") == 0)
      {
        dataSegment = true; 
        ++lCount;        
        continue;              
      } 
      
    }
    
     // label stripper
      if(sscanf(line, "%[^:]: %[^#]#" , exLabel[count], tempLine) == 2)
      {      
        for( int i = 0; i < MAXLINE; ++i)
          line[i] = tempLine[i];     
        //printf("clean line: %s\n", line);
        //std::cout << exLabel[count] << '\n';
      }
    if(sscanf(line, " .%s %s", directive, tempLine) == 2)
    {
      ++lCount;        
      continue;
    }  

      // 3 address R format
      if (sscanf(line, "%s $%[^,],$%[^,],$%s", oper, rd, rs, rt) == 4) 
      {
        //printf("parsed line: op:%s rd:%s rs:%s rt:%s\n",oper[count], rd[count], rs[count], rt[count]);
        inArray[count].u.rFormat.oper = 0;
        inArray[count].u.rFormat.shift = 0;
        for(int i = 0; i < 32; ++i)
        {
          if (strcmp(rd,regIndex[i]) == 0)
            inArray[count].u.rFormat.rd = i;
          if (strcmp(rs,regIndex[i]) == 0)
            inArray[count].u.rFormat.rt = i;
          if (strcmp(rt,regIndex[i]) == 0)
            inArray[count].u.rFormat.rs = i;  
        }
        if (strcmp(oper, "addu") == 0)
          inArray[count].u.rFormat.func = 33;
        if (strcmp(oper, "subu") == 0)
          inArray[count].u.rFormat.func = 35;
        if (strcmp(oper, "and") == 0)
          inArray[count].u.rFormat.func = 36;
        if (strcmp(oper, "or") == 0)
          inArray[count].u.rFormat.func = 37;
        if (strcmp(oper, "slt") == 0)
          inArray[count].u.rFormat.func = 42;      
        ++count;
      } 
      // I format instruction 
      else if (sscanf(line, "%s $%[^,],$%[^,],%s", oper, rt, rs, offset ) == 4)
      {
        //printf("parsed line: op:%s rt:%s rs:%s offset:%s\n",oper[count], rt[count], rs[count], offset[count]);        
        if (strcmp(oper, "addiu") == 0)
        {
          inArray[count].u.iFormat.oper = 9;
          inArray[count].u.iFormat.offset = atoi(offset);
          for(int i = 0; i < 32; ++i)
          {
          if (strcmp(rt,regIndex[i]) == 0)
            inArray[count].u.iFormat.rt = i;
          if (strcmp(rs,regIndex[i]) == 0)
            inArray[count].u.iFormat.rs = i;        
          }
        }
        else 
        {     
          if (strcmp(oper, "beq") == 0) 
            inArray[count].u.iFormat.oper = 4;        
          if (strcmp(oper, "bne") == 0)        
            inArray[count].u.iFormat.oper = 5;  
            for(int i = 0; i < 32; ++i)
          {
          if (strcmp(rt,regIndex[i]) == 0)
            inArray[count].u.iFormat.rs = i;
          if (strcmp(rs,regIndex[i]) == 0)
            inArray[count].u.iFormat.rt = i;        
          }
          
          for (int i = 0; i < sizeof(textLabel); ++i)
          { 
            if (strcmp(offset, textLabel[i]) == 0)
            {
              //printf("data offset: %d\n", i);
              inArray[count].u.iFormat.offset = ((i-1)-count);
            } 
          }     
        }  
        ++count;
      }
      // I with parentheses format instruction
      else if (sscanf(line, "%s $%[^, ] , %[^( ] ( $%[^) ])", oper, rt, offset, rs ) == 4)
      {
        //printf("parsed line: op:%s rt:%s offset:%s rs:%s \n",oper[count], rt[count], offset[count], rs[count]);
        for(int i = 0; i < 32; ++i)
        {
          if (strcmp(rt,regIndex[i]) == 0)
            inArray[count].u.iFormat.rt = i;
        }
        for(int i = 0; i < 32; ++i)
        { 
          if (strcmp(rs,regIndex[i]) == 0)
            inArray[count].u.iFormat.rs = i; 
        }      
        
        if (strcmp(oper, "lw") == 0)
          inArray[count].u.iFormat.oper = 35;
        if (strcmp(oper, "sw") == 0)
          inArray[count].u.iFormat.oper = 43;      
        if (isdigit(offset[0]))
          inArray[count].u.iFormat.offset = atoi(offset);
        else
        {        
          for (int i = 0; i < sizeof(textLabel); ++i)
          {           
            if (strcmp(offset, textLabel[i]) == 0)
              inArray[count].u.iFormat.offset = data[i];
          }          
        }
        ++count;
      }
      // 2 address R format
      else if (sscanf(line, "%s $%[^,],$%s", oper, rs, rt) == 3)
      {
        //printf("parsed line: op:%s rs:%s rt:%s\n", oper[count], rs[count], rt[count]);  
        inArray[count].u.rFormat.oper = 0;
        inArray[count].u.rFormat.rd = 0;
        inArray[count].u.rFormat.shift = 0;
        for(int i = 0; i < 32; ++i)
        {        
          if (strcmp(rs,regIndex[i]) == 0) //swap these
            inArray[count].u.rFormat.rt = i;
          if (strcmp(rt,regIndex[i]) == 0)
            inArray[count].u.rFormat.rs = i;  
        }
        if(strcmp(oper, "div") == 0)
          inArray[count].u.rFormat.func = 26;       
        if(strcmp(oper, "mult") == 0)
          inArray[count].u.rFormat.func = 24;           
        ++count;
      }
      // 1 address R format
      else if (sscanf(line, "%s $%s", oper, rd) == 2)
      {
        //printf("parsed line: op:%s rd:%s\n", oper[count], rd[count]);  
        inArray[count].u.rFormat.oper = 0; 
        inArray[count].u.rFormat.rs = 0;
        inArray[count].u.rFormat.rt = 0;      
        for(int i = 0; i < 32; ++i)
        {
          if (strcmp(rd,regIndex[i]) == 0)
            inArray[count].u.rFormat.rd = i;
        }
        if (strcmp(oper, "mfhi") == 0)
          inArray[count].u.rFormat.func = 16;
        if (strcmp(oper, "mflo") == 0)
          inArray[count].u.rFormat.func = 18;        
        ++count;
      }    
      // j format 
      else if (sscanf(line, "%s %s", oper, target) == 2)
      {
        //printf("parsed line: op:%s rd:%s\n", oper[count], rd[count]);      
        if (strcmp(oper, "j") == 0)
        {
          inArray[count].u.jFormat.oper = 2;
          for (int i = 0; i < sizeof(textLabel); ++i)
          {
            if(strcmp(target, textLabel[i]) == 0)
              inArray[count].u.jFormat.target = i-1;
          }
        }      
        ++count;
      }
      // single input string (syscall)
      else if (sscanf(line, "%s", oper) == 1)
      {
        if(strcmp(oper,"syscall") == 0)
        {
          inArray[count].u.rFormat.oper = 0;
          inArray[count].u.rFormat.rs = 0;
          inArray[count].u.rFormat.rd = 0;
          inArray[count].u.rFormat.rt = 0;
          inArray[count].u.rFormat.shift = 0;
          inArray[count].u.rFormat.func = 12; 
          ++count;   
        } 
          
      }
      else     
      {
        printf("Invalid input line: %s\n", line);
        
      }       
     
    ++lCount;
  } // end while
  // output area
  printf("%d %d\n", count, dataCount);
  for (int i = 0; i < count; ++i)  
    printf("%08x\n", inArray[i].u.x);
  
  for (int i = 0; i < dataCount; ++i)
    std::cout <<std::setw(8) << std::setfill('0') << std::hex << data[i] << '\n';  
  /*
  for (int i = 0; i < count; ++i)
    std::cout << i <<  textLabel[i] << '\n';
   
  */
  return 0;
} // end main
