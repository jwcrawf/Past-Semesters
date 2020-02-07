/*
  ED.cpp

  Jon Crawford

  COP4531 Summer 2019 - String Matching
*/

#include <genalg.h>
#include <matrix.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ansicodes.h>
#include <vector.h>

size_t editDist(const char* str1, const char* str2, fsu::Matrix<size_t>& D, fsu::Matrix<char>& P,
                  size_t m, size_t n, size_t cost);

int main(int argc , char* argv[])
{
  if(argc < 2)
  {
    std::cout << "\n  ED uses dynamic programming to find the edit distance (ED) between two sequences s and t.\n"
              << "    Input is at the command line and consists of:\n"
              << "      1,2: ascii strings             (required)\n"
              << "        3: value for substition cost (optional - default = 2 = Levenshtein)\n"
              << "        4: matrix dump code          (optional - default = 0): 0 = none, 1 = distance, 2 = parent, 3 = both\n"
              << "    Output shows:\n"
              << "      the edit distance\n"
              << "      the string s\n"
              << "      edit transcript for s -> t\n"
              << "      edit transcript for t -> s\n"
              << "      the string t\n"
              << "      optimal alignment of the two strings\n"
              << "  The two REQUIRED strings two OPTIONAL inputs must be entered as command line arguments\n";  
    std::cout << ANSI_BOLD_RED
    << "  Please report errors or suggestions to lacher@cs.fsu.edu" << ANSI_RESET_ALL << std::endl;
    std::cout << std::endl;
    exit (EXIT_FAILURE);
  }
  const char* s = argv[1];
  const char* t = argv[2];  
  size_t m = strlen(s), n = strlen(t), cost(2), d(0); 
  if(argc == 4)  
    cost = atoi(argv[3]);  
  if(argc == 5)
  {
    cost = atoi(argv[3]);
    d = atoi(argv[4]);    
  } 
  fsu::Matrix<size_t> D(1 + m, 1 + n, 0);
  fsu::Matrix<char> P(1 + m, 1 + n, '-');
  size_t ed = editDist(s, t, D, P, m, n, cost);  
  size_t x(n), y(m);
  fsu::Vector<char> script;
  char xy = P[y][x];
  while((x + y) != 0)
  {    
    script.PushBack(xy);
    if(xy == 'D')
    {     
      --x; 
      --y;       
    }
    else if(xy == 'L')
    {      
      --x;       
    }
    else //if (xy == 'U')
    {      
      --y;
    }
    xy = P[y][x];
  } 
  //script.Dump(std::cout); //debug
  if(d == 1)
  {
    std::cout << "Distance Matrix:" << std::endl;
    D.Dump(std::cout, 2);
  }
  if(d == 2)
  {
    std::cout << "Parent Matrix:" << std::endl;
    P.Dump(std::cout, 2);
  }
  if(d == 3)
  {
    std::cout << "Distance Matrix:" << std::endl;
    if(m >= 10 || n >= 10)
      D.Dump(std::cout, 3);
    else
      D.Dump(std::cout, 2);
    std::cout << "Parent Matrix:" << std::endl;
    P.Dump(std::cout, 2);
  }
  std::cout << "\n      Edit Distance: " << ed;
  if(cost == 2)         
    std::cout <<  " // Levenshtein - substitution cost = " << cost;
  else
    std::cout <<  " // substitution cost = " << cost;
  std::cout << "\n                  s: " << s
            << "\n   s > t transcript: ";
  size_t ch1(0), ch2(0);
  for(fsu::Vector<char>::ConstIterator i = script.End() - 1; i != script.Begin() - 1; --i)
  {    
    if(*i == 'D')
    { 
      if(s[ch1] == t[ch2])
        std::cout << 'M';
      else
        std::cout << 'S'; 
      ++ch1; ++ch2;
    }  
    else if(*i == 'L')
    {
      std::cout << 'I';
      ++ch2;
    }    
    else //if(*i == 'U')
    {
      std::cout << 'D';
      ++ch1;
    }
  }
  std::cout << "\n   t > s transcript: ";
  ch1 = 0, ch2 = 0;
  for(fsu::Vector<char>::ConstIterator i = script.End() - 1; i != script.Begin() - 1; --i)
  {    
    if(*i == 'D')
    { 
      if(s[ch1] == t[ch2])
        std::cout << 'M';
      else
        std::cout << 'S'; 
      ++ch1; ++ch2;
    }  
    else if(*i == 'L')
    {
      std::cout << 'D';
      ++ch2;
    }    
    else //if(*i == 'U')
    {
      std::cout << 'I';
      ++ch1;
    }
  }
  std::cout << "\n                  t: " << t
            << "\n  optimal alignment:"                       
            << "\n   s = ";
  ch1 = 0, ch2 = 0;
  for(fsu::Vector<char>::ConstIterator i = script.End() - 1; i != script.Begin() - 1; --i)
  {    
    if(*i == 'D')
    { 
      if(s[ch1] == t[ch2])
      {
        std::cout << s[ch1];       
        ++ch1; ++ch2;
      }
      else
      {
        std::cout << s[ch1];       
        ++ch1;
      }
    }  
    else if(*i == 'L')
    {
      std::cout << '-';
      ++ch2;
    }    
    else //if(*i == 'U')
    {
      std::cout << s[ch1];
      ++ch1;
    }
  }
  std::cout << "\n       ";
  ch1 = 0, ch2 = 0;
  for(fsu::Vector<char>::ConstIterator i = script.End() - 1; i != script.Begin() - 1; --i)
  {    
    if(*i == 'D')
    { 
      if(s[ch1] == t[ch2])
      {
        std::cout << '|';       
        ++ch1; ++ch2;
      }
      else
      {
        std::cout << ' ';       
        ++ch1; ++ch2;
      }
    }  
    else if(*i == 'L')
    {
      std::cout << ' ';
      ++ch2;
    }    
    else //if(*i == 'U')
    {
      std::cout << ' ';
      ++ch1;
    }
  }
  std::cout << "\n   t = ";
  ch1 = 0, ch2 = 0;
  for(fsu::Vector<char>::ConstIterator i = script.End() - 1; i != script.Begin() - 1; --i)
  {    
    if(*i == 'D')
    { 
      if(s[ch1] == t[ch2])
      {
        std::cout << t[ch2];       
        ++ch1; ++ch2;
      }
      else
      {
        std::cout << t[ch2];       
        ++ch2;
      }
    }  
    else if(*i == 'L')
    {      
      std::cout << t[ch2];
      ++ch2;
    }    
    else //if(*i == 'U')
    {
      std::cout << '-';
      ++ch1;
    }
  }
  std::cout << "\n";
  return 0;
}

size_t editDist(const char* str1, const char* str2, fsu::Matrix<size_t>& D, fsu::Matrix<char>& P,
                  size_t m, size_t n, size_t cost) 
{ 
  for (size_t i = 1; i <= m; ++i) 
  {
    D[i][0] = i;
    P[i][0] = 'U';
    for (size_t j = 1; j <= n; ++j) 
    {  
      D[0][j] = j; 
      P[0][j] = 'L';    
      if (str1[i - 1] == str2[j - 1])
      { 
        D[i][j] = D[i - 1][j - 1]; 
        P[i][j] = 'D';
      }      
      else
      {  
        size_t A(0), B(0), C(0), x(0);
        A = D[i][j - 1] + 1, B = D[i - 1][j] + 1, C = D[i - 1][j - 1] + cost;        
        D[i][j] = (C <= (x = (A <= B ? A : B)) ? C : x);    
        if(D[i][j] == A) P[i][j] = 'L'; 
        if(D[i][j] == B) P[i][j] = 'U'; 
        if(D[i][j] == C) P[i][j] = 'D';
      }
    } 
  }
  return D[m][n]; 
} 