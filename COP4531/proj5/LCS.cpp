/*
  LCS.cpp

  Jon Crawford

  COP4531 Summer 2019 - String Matching
*/

#include <genalg.h>
#include <matrix.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ansicodes.h>
#include <bitvect.h>
#include <bitvect.cpp>

size_t LCS(const char* s, size_t m, const char* t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt);

void LCS(const char* s, size_t m, const char* t, size_t n, fsu::Matrix<size_t>& L); 

int main(int argc , char* argv[])
{
  if(argc < 2)
  {
    std::cout << "\n  LCS uses dynamic programming to find the longest common subsequence (LCS) of two sequences s and t.\n"
              << "    Input is at the command line and consists of two ascii strings.\n"
              << "    Output shows:\n"
              << "      Length of the LCS\n"
              << "      subscripts of the LCS in s\n"
              << "       bitcode of the LCS in s\n"
              << "       LCS highlighted in s\n"
              << "      subscripts of the LCS in t\n"
              << "       bitcode of the LCS in t\n"
              << "       LCS highlighted in t\n"
              << "      alignment of the two strings with LCS highlighted\n"
              << "  The two strings must be entered as command-line arguments\n";
    std::cout << ANSI_BOLD_RED
    << "  Please report errors or suggestions to lacher@cs.fsu.edu" << ANSI_RESET_ALL << std::endl;
    std::cout << std::endl;
    exit (EXIT_FAILURE);
  }
  const char* s = argv[1];
  const char* t = argv[2];
  size_t m = strlen(s), n = strlen(t); 
  fsu::BitVector bvs(m), bvt(n);
  std::cout << "\n  Length of LCS:  " <<  LCS(s, m, t, n, bvs, bvt)
            << "\n  LCS in s: { ";
  for(size_t i = 0; i < m; ++i)
    if(bvs[i]) std::cout << i << " ";
  std::cout << "}"
             << "\n   bitcode: ";
  for(size_t i = 0; i < m; ++i)
    std::cout << (size_t)bvs[i];           
  std::cout << "\n        s = " << s 
            << "\n  LCS in t: { "; 
  for(size_t i = 0; i < n; ++i)
    if(bvt[i]) std::cout << i << " ";
  std::cout << "}"
            << "\n   bitcode: ";
  for(size_t i = 0; i < n; ++i)
    std::cout << (size_t)bvt[i];  
  std::cout << "\n        t = " << t   
            << "\n  optimal alignment:"                        
            << "\n   s = ";
  size_t bound(0), ch1(0), ch2(0);
  if(m > n)   
    bound = m;
  else   
    bound = n;
  while(ch1 < bound && ch2 < bound)
  {
    if(ch2 >= m) 
    {
      std::cout << '-';
      ch1++;
    }
    else if (ch1 >= n)
    {
      std::cout << s[ch2];
      ++ch2;
    }
    else if(!bvt[ch1] && !bvs[ch2])
    {
      std::cout << s[ch2];
      ++ch1; ++ch2;
    }
    else if(!bvt[ch1]) 
    {
      std::cout << '-';
      ++ch1;
    } 
    else if(!bvs[ch2])
    {
      std::cout << s[ch2];
      ++ch2; 
    }       
    else //if(bvt[ch1] == bvs[ch2])
    {
      std::cout << s[ch2];
      ++ch1; ++ch2;
    }
  }
  std::cout << "\n       "; 
  ch1 = 0; ch2 = 0;
  while(ch1 < bound && ch2 < bound)
  {
    if(!bvt[ch1] && !bvs[ch2])
    {
      std::cout << ' ';
      ++ch1; ++ch2;
    }
    else if(!bvt[ch1]) 
    {
      std::cout << ' ';
      ++ch1;
    }
    else if(!bvs[ch2])
    {
      std::cout << ' ';
      ++ch2;
    }
    else //if(bvt[ch1] == bvs[ch2])
    {
      std::cout << '|';
      ++ch1; ++ch2;
    }
  }
  std::cout << "\n   t = ";  
  ch1 = 0, ch2 = 0;
  while(ch1 < bound && ch2 < bound)
  {
    if(ch1 >= n)
    {
      std::cout << '-';
      ch2++;
    }
    else if (ch2 >= m)
    {
      std::cout << t[ch1];
      ++ch1;
    }
    else if(!bvt[ch1] && !bvs[ch2])
    {
      std::cout << t[ch1];
      ++ch1; ++ch2;
    }
    else if(!bvt[ch1]) 
    {
      std::cout << t[ch1];
      ++ch1;
    } 
    else if(!bvs[ch2])
    {
      std::cout << '-';
      ++ch2; 
    }       
    else //if(bvt[ch1] == bvs[ch2])
    {
      std::cout << t[ch1];
      ++ch1; ++ch2;
    }
  }
  std::cout << "\n\n";
  return 0;  
}

size_t LCS(const char* s, size_t m, const char* t, size_t n, fsu::BitVector& bvs, fsu::BitVector& bvt)
{
  fsu::Matrix<size_t> L(1 + m, 1 + n, 0);
  LCS(s, m, t, n, L);  
  bvs.Unset(); bvt.Unset();
  size_t i = m, j = n;
  while(i > 0 &&  j > 0)  
  {
    if (s[i - 1] == t[j - 1])
    {
      bvs.Set(i - 1); bvt.Set(j - 1);
      --i; --j;
    }
    else if (L[i][j] == L[i - 1][j])    
      --i;    
    else // L[i,j] == L[i,j-1]    
      --j;        
  }
  //L.Dump(std::cout, 1);
  return L[m][n];  
}

void LCS(const char* s, size_t m, const char* t, size_t n, fsu::Matrix<size_t>& L)
{     
  for (size_t i = 1; i <= m; ++i) 
  {
    for (size_t j = 1; j <= n; ++j)
    {
      if (s[i - 1] == t[j - 1])
        L[i][j] = 1 + (L[i - 1] [j - 1]);
      else
        L[i][j] = fsu::Max(L[i - 1][j] , L[i][j - 1]);
    }
  }
}
