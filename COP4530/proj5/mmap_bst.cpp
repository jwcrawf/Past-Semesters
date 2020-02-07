/*
    mmap.cpp
    01/12/18
    Chris Lacher


    Dynamic Random Test of Map<String, int>

    Driver program testing Map_ADT<T> for pointer errors and memory
    leaks by fully exercising all Map_ADT<T> functions randomly in an unending loop.

    IMPORTANT INSTRUCTIONS FOR USE: 
    ==============================

    Running this program using a faulty implementation of Map can take over a
    machine and virtually shut it down, preventing all other processes from
    running, including those of other users. It is therefore REQUIRED that this
    program be executed ONLY using the following procedures:

    1. Create a login to one of the programming machines (program or linprog)
    2. Compile using your command line compile script
    3. Limit your memory use by entering
       "limit vmemoryuse 50000"
    4. Check that your limits have been set by entering
       "limit"
    5. Run by entering the executable name
    6. Execution should terminate when memory is used up
    7. After a run, remove your vmememoryuse restriction by entering
       "limit vmemoryuse unlimited"

    With vmemoryuse limited to 4000, you don't have enough space to run emacs
    or a compiler. 

    NOTE: Students not following this procedure and resulting in bogging down a
    machine will be responsible for the consequences, including possible
    suspension of your CS account, which could affect your performance in this
    and other courses. 

    Copyright 2018, R.C. Lacher
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <xran.h>
#include <xran.cpp>

// <String, int>
#include <xstring.h>
#include <xstring.cpp>  // in lieu of makefile
#include <xranxstr.h>
#include <xranxstr.cpp> // in lieu of makefile
typedef fsu::String KeyType;
typedef int         DataType;
// */

/* // RBLLT with ADT iterators
#include <map_rbllt_adt.h>
typedef fsu::Map_RBLLT<KeyType, DataType> MapType;
typedef fsu::Map_RBLLT<KeyType, DataType>::Iterator Iterator;
typedef fsu::Map_RBLLT<KeyType, DataType>::ConstIterator ConstIterator;
typedef fsu::Map_RBLLT<KeyType, DataType>::LevelorderIterator LevelorderIterator;
// */

// BST with threaded iterators
#include <map_bst_threaded.h>
typedef fsu::Map_BST<KeyType, DataType> MapType;
typedef fsu::Map_BST<KeyType, DataType>::Iterator Iterator;
typedef fsu::Map_BST<KeyType, DataType>::ConstIterator ConstIterator;
typedef fsu::Map_BST<KeyType, DataType>::LevelorderIterator LevelorderIterator;
// */

typedef fsu::Random_String Random_class;
const char* vT = "String , int";
const long unsigned int maxSize        =     4000;
// const long unsigned int maxNodes       =     5000;
// const      size_t       stringLength   =        5;
const long unsigned int reportInterval =    10000;
const      unsigned int getPercent  =       50;    // to control
const      unsigned int putPercent  =       50;    // growth rate
const      unsigned int assignPercent  =    30;    // and volatility
// */

// constants for number of containers and operations
const unsigned int numObj = 3;  // containers x0, x1, x2
const unsigned int numOps = 6; //  operations 0..5

// template < typename T , class P >
void WriteReport(MapType x, char n, unsigned long numreports);

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << " ** Argument required:  number of reports (enter 0 for unlimited)\n"
              << "    Try again\n";
    return 0;
  }
  size_t maxrpts = atoi(argv[1]);

  // objects
  MapType        x0, x1, x2;
  Iterator       i0, i1, i2, j, k;
  Random_class   ranobj;
  DataType       data;
  KeyType        key;
  size_t         loc = 0;
  bool           ok = 1;

  // controls
  fsu::Random_int ranint;
  unsigned long numtrials(0);
  unsigned long numrpts(0); 
  unsigned int option;
  size_t size;

  std::cout << "\nStarting dynamic random test of Map < " << vT << " >"
            << "\n\n" << std::flush;
  while(1)
  {
    option = ranint(0,numObj);
    switch(option)
    {
      case 0:
        option = ranint(0,numOps); 
        switch (option)
        {
          case 0:   // Put (k,d)
            option = ranint(0,100);
            if (option < putPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x0.Put(key,data);
            }
            break;
        
          case 1:   // void Get (k)
            option = ranint(0,100);
            if (option < getPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x0.Get(key);
            }
            break;
        
          case 2:   // void Size()
            size = x0.Size();
            if (size >= maxSize)
            {
              x0.Clear();
              std::cout << " ** x0 cleared at size = " << size << std::endl;
            }
            break;

          case  3:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                x0 = x0;
                break;
              case 1:
                x0 = x1;
                break;
              case 2:
                x0 = x2;
                break;
              }
            }
            break;

          case 4: // Includes
            i0 = x0.Includes(key);
            if (i0 != x0.End())
            {
              data = ranint(1,11);
              (*i0).data_ = data;
            }
            break;

          case 5: // traversal
            {
              loc = 0;
              ok = 1;
              for( i0 = x0.Begin() ; i0 != x0.End() ; ++i0 )
              {
                k = i0;
                j = ++(--k);
                if (j != k)
                {
                  std::cout << " ** ++(--) iterator reciprocity failure at location " << loc << " with entry " << *i0 << '\n';
                  ok = 0;
                }
                k = i0;
                j = --(++k);
                if (j != k)
                {
                  std::cout << " ** --(++) iterator reciprocity failure at location " << loc << " with entry " << *i0 << '\n';
                  ok = 0;
                }
                ++loc;
              }
              // if (ok) std::cout << "  passed iterator reciprocity test\n";
            }
            break;

          default: std::cout << " ** bad operation number\n";


        }   // end switch() x0 operations

      case 1:
        option = ranint(0,numOps); 
        switch (option)
        {
          case 0:   // Put (k,d)
            option = ranint(0,100);
            if (option < putPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x1.Put(key,data);
            }
            break;
        
          case 1:   // void Get (k)
            option = ranint(0,100);
            if (option < getPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x1.Get(key);
            }
            break;
        
          case 2:   // void Size()
            size = x1.Size();
            if (size >= maxSize)
            {
              x1.Clear();
              std::cout << " ** x1 cleared at size = " << size << std::endl;
            }
            break;

          case  3:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                x1 = x0;
                break;
              case 1:
                x1 = x1;
                break;
              case 2:
                x1 = x2;
                break;
              }
            }
            break;

          case 4: // Includes
            i1 = x1.Includes(key);
            if (i1 != x1.End())
            {
              data = ranint(1,11);
              (*i1).data_ = data;
            }
            break;

          case 5: // traversal
            {
              loc = 0;
              ok = 1;
              for( i1 = x1.Begin() ; i1 != x1.End() ; ++i1 )
              {
                k = i1;
                j = ++(--k);
                if (j != k)
                {
                  std::cout << " ** ++(--) iterator reciprocity failure at location " << loc << " with entry " << *i1 << '\n';
                  ok = 0;
                }
                k = i1;
                j = --(++k);
                if (j != k)
                {
                  std::cout << " ** --(++) iterator reciprocity failure at location " << loc << " with entry " << *i1 << '\n';
                  ok = 0;
                }
                ++loc;
              }
              // if (ok) std::cout << "  passed iterator reciprocity test\n";
            }
            break;

          default: std::cout << " ** bad operation number\n";

        }   // end switch() x1 operations

      case 2:
        option = ranint(0,numOps); 
        switch (option)
        {
          case 0:   // Put (k,d)
            option = ranint(0,100);
            if (option < putPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x2.Put(key,data);
            }
            break;
        
          case 1:   // void Get (k)
            option = ranint(0,100);
            if (option < getPercent)
            {
              data = ranint(1,11);
              key = ranobj(data);
              x2.Get(key);
            }
            break;
        
          case 2:   // void Size()
            size = x2.Size();
            if (size >= maxSize)
            {
              x2.Clear();
              std::cout << " ** x2 cleared at size = " << size << std::endl;
            }
            break;

          case  3:  // assignment
            option = ranint(0,100);
            if (option < assignPercent)
            {
              option = ranint(0,numObj);
              switch(option)
              {
              case 0:
                x2 = x0;
                break;
              case 1:
                x2 = x1;
                break;
              case 2:
                x2 = x2;
                break;
              }
            }
            break;

          case 4: // Includes
            i2 = x2.Includes(key);
            if (i2 != x2.End())
            {
              data = ranint(1,11);
              (*i2).data_ = data;
            }
            break;

          case 5: // traversal
            {
              loc = 0;
              ok = 1;
              for( i2 = x2.Begin() ; i2 != x2.End() ; ++i2 )
              {
                k = i2;
                j = ++(--k);
                if (j != k)
                {
                  std::cout << " ** ++(--) iterator reciprocity failure at location " << loc << " with entry " << *i2 << '\n';
                  ok = 0;
                }
                k = i2;
                j = --(++k);
                if (j != k)
                {
                  std::cout << " ** --(++) iterator reciprocity failure at location " << loc << " with entry " << *i2 << '\n';
                  ok = 0;
                }
                ++loc;
              }
              // if (ok) std::cout << "  passed iterator reciprocity test\n";
            }
            break;

          default: std::cout << " ** bad operation number\n";

        }   // end switch() x2 operations

    } // end switch() case x2

    ++numtrials;
    if (numtrials == reportInterval)
    {
      ++numrpts;
      numtrials = 0;
      option = ranint(0,3);
      switch(option)
      {
        case 0: WriteReport(x0,'0',numrpts); break;
        case 1: WriteReport(x1,'1',numrpts); break;
        case 2: WriteReport(x2,'2',numrpts); break;
      }
      if (numrpts == maxrpts)
      {
        std::cout << "\nTest Complete\n";
        break;
      }
    }
  }  // end while()
  return EXIT_SUCCESS;
}  // end main()

// template < typename T , class P >
void WriteReport(MapType x, char n, unsigned long numrpts)
{
  size_t size = x.Size();
  std::cout << std::showpoint << std::fixed << std::setprecision(2);
  std::cout << "\nTesting Map < " << vT << " >"
            << " at trial " << numrpts << " x " << reportInterval << ":\n";
  x.DepthDistribution(std::cout,7);
  std::cout << "  Depth distrubution shown with compression divisor 7\n"
            << "   x" << n << ".Size()              ==  " << size << '\n' 
            << "   x" << n << ".Height()            ==  " << x.Height() << '\n'
            << "   optimal ht (size)      ==  " << (size_t)(floor(log2(size))) << '\n';
  std::cout << std::flush;
}
