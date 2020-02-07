/*
    fmap.cpp
    03/02/18
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

// <String, size_t>
#include <xstring.h>
#include <xstring.cpp>  // in lieu of makefile
typedef fsu::String KeyType;
typedef size_t      DataType;
const char fill = '-';
// */

/* // <String, int>
#include <xstring.h>
#include <xstring.cpp>  // in lieu of makefile
typedef fsu::String KeyType;
typedef int         DataType;
const char fill = '-';
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

// these are helper functions determining column widths in displaying table

template < typename T >
int CorrectDataWidth(const T& t, int dw)
{
  int digits = 1+(size_t)log10(t);
  if (dw < digits)
    dw = digits;
  return dw;
}
template <>
int CorrectDataWidth(const fsu::String& t, int dw)
{
  int digits = (int)t.Size();
  if (dw < digits)
    dw = digits;
  return dw;
}

void DisplayMenu(std::ostream& os = std::cout);

// copy test
template < class C >
void CopyTest ( const C& x1,  C x2 )
{
  size_t size1, size2,
    height1, height2;
  bool ok = 1;
  // std::cout << " ** CopyTest limited by lack of operator== and lack of Iterators\n";
  if (x1 != x2)
  {
    std::cout << " ** CopyTest: original and copy not equal\n";
    ok = 0;
  }
  // this needs implementing for Map
  if (!x2.CheckStructure(0))
  {
    std::cout << " ** CopyTest: copy.CheckStructure() failed\n";
    ok = 0;
  } // */
  size1   = x1.Size();
  height1 = x1.Height();
  size2   = x2.Size();
  height2 = x2.Height();
  if (size1  != size2)
  {
    std::cout << " ** CopyTest: original and copy have different size\n";
    ok = 0;
  }
  if (height1 != height2)
  {
    std::cout << " ** CopyTest: original and copy have different height\n";
    ok = 0;
  }
  if (ok) std::cout << " CopyTest OK\n";
} // CopyTest */

// assign test
template < class C >
void AssignTest ( const C& x1 )
{
  C x2;
  size_t size1, size2,
    height1, height2;
  bool ok = 1;
  size2 = x2.Size();
  x2 = x1;
  // std::cout << " ** AssignTest limited by lack of operator== and lack of Iterators\n";
  if (x1 != x2)
  {
    std::cout << " ** AssignTest: original and copy not equal\n";
    ok = 0;
  }
  // this needs implementing for Map
  if (!x2.CheckStructure(0))
  {
    std::cout << " ** AssignTest: assignee.CheckStructure() failed\n";
    ok = 0;
  } // */
  size1   = x1.Size();
  height1 = x1.Height();
  size2   = x2.Size();
  height2 = x2.Height();
  if (size1  != size2)
  {
    std::cout << " ** AssignTest: original and copy have different size\n";
    ok = 0;
  }
  if (height1  != height2)
  {
    std::cout << " ** AssignTest: original and copy have different height\n";
    ok = 0;
  }
  if (ok) std::cout << " AssignTest OK\n";
} // AssignTest

int main(int argc, char* argv[])
{
  MapType map;
  Iterator mapi, itr1, itr2;
  ConstIterator mapci;
  bool initited = 0;
  KeyType     key;
  DataType    data;
  char        command;
  size_t      size, numnodes, nsize, digits, ndigits;
  int dw1 = 1, dw2 = 1;
  std::ifstream com;
  std::ifstream ifs;
  std::istream * inptr = &std::cin;
  bool BATCH = 0;
  if (argc > 1)
  {
    BATCH = 1;
    com.open(argv[1]);
    if (com.fail()) return 0;
    inptr = &com;
  }
  if (!BATCH) DisplayMenu();
  std::cout << " default data value: " << DataType() << '\n';
  do
  {
    std::cout << "command ('M' for menu, 'Q' to quit): ";
    *inptr >> command;
    if (BATCH) std::cout << command;
    switch(command)
    {
      case 'l': case 'L':
        *inptr >> key;
        if (BATCH) std::cout << ' ' << key << '\n';
        ifs.open(key.Cstr());
        if (ifs.fail())
        {
          std::cout << "  ** Unable to open file " << key << '\n';
          ifs.clear();
          break;
        }
        size = 0;
        digits = 0;
        while (ifs >> key >> data)
        {
          map[key] = data;
          // map[key] += data;
          nsize = key.Size();
          ndigits = 1 + (size_t)log10(data);
          if (size < nsize) size = nsize;
          if (digits < ndigits) digits = ndigits;
        }
        if (dw1 < (int)size)   dw1 = size;
        if (dw2 < (int)digits) dw2 = digits;
        ifs.clear();
        ifs.close();
        std::cout << "  ** table data read and stored\n";
        initited = 0;
        break;

      case 'k': case 'K':
        *inptr >> key;
        if (BATCH) std::cout << ' ' << key << '\n';
        ifs.open(key.Cstr());
        if (ifs.fail())
        {
          std::cout << "  ** Unable to open file " << key << '\n';
          ifs.clear();
          break;
        }
        size = 0;
        while (ifs >> key)
        {
          map[key];
          // ++map[key];
          nsize = key.Size();
          if (size < nsize) size = nsize;
        }
        if (dw1 < (int)size)   dw1 = size;
        ifs.clear();
        ifs.close();
        std::cout << "  ** keys read and stored\n";
        initited = 0;
        break;

      case '[':
        *inptr >> key;
        if (BATCH) std::cout << key;
        *inptr >> command;
        if (BATCH) std::cout << command;
        if (command != ']')
        {
          std::cout << " ** close bracket expected - re-enter command\n";
          inptr->clear();
          while (command != '\n') command = (char)inptr->get();
          inptr->clear();
          break;
        }
        command = (char)inptr->peek();
        if (command == '\n')
        {
          if (BATCH) std::cout << '\n';
          std::cout << "  " << map[key]
                    << " = map[" << key << "]\n";
          dw1 = CorrectDataWidth(key,dw1);
          break;
        }
        *inptr >> command >> data; // assume '='
        if (BATCH) std::cout << command << data << '\n';
        if (command == '+')
        {
          std::cout << "map[" << key << "] += " << data << '\n';
          map[key] += data;
        }
        else // assume '='
        {
          std::cout << "map[" << key << "] = " << data << '\n';
          map[key] = data;
        }
        dw1 = CorrectDataWidth(key,dw1);
        dw2 = CorrectDataWidth(data,dw2);
        initited = 0;
        break;

      case '1': case 'p': case 'P':
        *inptr >> key >> data;
        if (inptr->fail())
        {
          std::cout << " ** bad key or data encountered - re-enter command\n";
          inptr->clear();
          while (command != '\n') command = (char)inptr->get();
          inptr->clear();
          break;
        }
        if (BATCH) std::cout << ' ' << key << ' ' << data << '\n';
        std::cout << "map.Put(" << key << ',' << data << ")\n";
        map.Put(key,data);
        dw1 = CorrectDataWidth(key,dw1);
        dw2 = CorrectDataWidth(data,dw2);
        initited = 0;
        break;

      case '2': case 'g': case 'G':
        *inptr >> key;
        if (inptr->fail())
        {
          std::cout << " ** bad key encountered - re-enter command\n";
          inptr->clear();
          while (command != '\n') command = (char)inptr->get();
          inptr->clear();
          break;
        }
        if (BATCH) std::cout << ' ' << key << '\n';
        std::cout << "  " << map.Get(key)
                  << " = map.Get(" << key << ")\n";
        dw1 = CorrectDataWidth(key,dw1);
        initited = 0;
        break;

      case 'r': case 'R':
        *inptr >> key;
        if (inptr->fail())
        {
          std::cout << " ** bad key encountered - re-enter command\n";
          inptr->clear();
          while (command != '\n') command = (char)inptr->get();
          inptr->clear();
          break;
        }
        if (BATCH) std::cout << ' ' << key << '\n';
        if (map.Retrieve(key,data))
        {
          std::cout << "  map.Retrieve(" << key << ",d) successful with d = " << data << '\n';
        }
        else
        {
          std::cout << "  map.Retrieve(" << key << ",d) unsuccessful\n";
        }
        dw1 = CorrectDataWidth(key,dw1);
        break;

      case 'e': case 'E':
        *inptr >> key;
        if (inptr->fail())
        {
          std::cout << " ** bad key encountered - re-enter command\n";
          inptr->clear();
          while (command != '\n') command = (char)inptr->get();
          inptr->clear();
          break;
        }
        if (BATCH) std::cout << ' ' << key << '\n';
        std::cout << "  map.Erase(" << key << ")\n";
        map.Erase(key);
        initited = 0;
        break;

      case 'd': case 'D':
        *inptr >> command;
        if (BATCH) std::cout << command << '\n';
        switch (command)
        {
          case '0': map.DumpBW(std::cout); break;
          case '1': map.Dump(std::cout); break;
          case '2': map.Dump(std::cout,dw1); break;
          case '3': map.Dump(std::cout,dw1,fill); break;
          default: std::cout << " ** undefined command (level 2)\n";
        }
        break;

      case 't':  case 'T':
        *inptr >> command;
        if (BATCH) std::cout << command << '\n';
        switch (command)
        {
          case 'f': case 'F': // forward
            std::cout << "Forward Traversal\n"
                      << "-----------------\n";
            std::cout << std::setw (3+dw1) << "key" << std::setw(5+dw2) << "data" << '\n';
            std::cout << std::setw (3+dw1) << "---" << std::setw(5+dw2) << "----" << '\n';
            for( Iterator i = map.Begin() ; i != map.End() ; ++i )
            {
              data = (*i).data_;     // testing constness read
              (*i).data_ = 0 + data; // testing non-constness read/write
              std::cout << std::setw (3+dw1) << (*i).key_ << std::setw(5+dw2) << (*i).data_ << '\n';
            }
            std::cout << '\n';
            break;
          case 'r': case 'R': // reverse
            std::cout << "Reverse Traversal\n"
                      << "-----------------\n";
            std::cout << std::setw (3+dw1) << "key" << std::setw(5+dw2) << "data" << '\n';
            std::cout << std::setw (3+dw1) << "---" << std::setw(5+dw2) << "----" << '\n';
            for( ConstIterator i = map.rBegin() ; i != map.rEnd() ; --i )
            {
              data = (*i).data_;     // testing constness read
              // (*i).data_ = 0 + data; // testing non-constness read/write
              std::cout << std::setw (3+dw1) << (*i).key_ << std::setw(5+dw2) << (*i).data_ << '\n';
            }
            std::cout << '\n';
            break;
          case 'l': case 'L': // level
            std::cout << "Levelorder Traversal\n"
                      << "--------------------\n";
            std::cout << std::setw (3+dw1) << "key" << std::setw(5+dw2) << "data" << '\n';
            std::cout << std::setw (3+dw1) << "---" << std::setw(5+dw2) << "----" << '\n';
            for( LevelorderIterator i = map.BeginLevelorder() ; i != map.EndLevelorder() ; ++i )
            {
              std::cout << std::setw (3+dw1) << (*i).key_ << std::setw(5+dw2) << (*i).data_ << '\n';
            }
            std::cout << '\n';
            break;
          case '!':
            {
              size_t loc = 0;
              Iterator j,k;
              bool ok = 1;
              for( Iterator i = map.Begin() ; i != map.End() ; ++i )
              {
                k = i;
                j = ++(--k);
                // if (k != map.End()) std::cout << *k << '\n';
                if (j != k)
                {
                  std::cout << " ** ++(--) iterator reciprocity failure at location " << loc << " with entry " << *i << '\n';
                  ok = 0;
                }
                k = i;
                j = --(++k);
                // if (k != map.End()) std::cout << *k << '\n';
                if (j != k)
                {
                  std::cout << " ** --(++) iterator reciprocity failure at location " << loc << " with entry " << *i << '\n';
                  ok = 0;
                }
                ++loc;
              }
              if (ok) std::cout << "  passed iterator reciprocity test\n";
            }
            break;

          default: std::cout << " ** undefined command (level 2)\n";
        } // switch
        break;

      case 's': case 'S':
        if (BATCH) std::cout << '\n';
        size = map.Size();
        numnodes = map.NumNodes();
        std::cout << "  map.Size()          = " << size << '\n'
                  << "  map.NumNodes()      = " << numnodes << '\n'
                  << "  map.Height()        = " << map.Height() << '\n';
        if (size > 0)
          std::cout << "  optimal ht (size)   = " << (size_t)(floor(log2(size))) << '\n';
        if (numnodes > 0)
          std::cout << "  optimal ht (nodes)  = " << (size_t)(floor(log2(numnodes))) << '\n';
        break;

      case 'c': case 'C':
        if (BATCH) std::cout << '\n';
        map.Clear();
        initited = 0;
        break;

      case 'x': case 'X':
        if (BATCH)
        {
          std::cout << '\n';
          inptr = &std::cin;
          com.close();
          std::cout << "   ** switched to keyboard input **\n";
          BATCH = 0;
          DisplayMenu();
        }
        else
        {
          std::cout << "  ** already using keyboard input\n";
        }
        break;

      case '=':
        if (BATCH) std::cout << '\n';
        CopyTest(map, map);
        AssignTest(map);
        break;

      case 'H': case 'h':
        if (BATCH) std::cout << '\n';
        map.Rehash();
        initited = 0;
        break;

      case 'i':
        *inptr >> key;
        if (BATCH) std::cout << key << '\n';
        mapi = map.Includes(key);
        if (mapi != map.End())
        {
          std::cout << " iterator at entry <" << (*mapi).key_ << ',' << (*mapi).data_ << ">\n"; 
          initited = 1;
        }
        else
        {
          std::cout << " key not found\n";
          initited = 0;
        }
        break;

      case 'I':
        *inptr >> key;
        if (BATCH) std::cout << key << '\n';
        mapi = map.Includes(key);
        if (mapi != map.End())
        {
          itr1 = itr2 = mapi;
          --itr1;
          ++itr2;
          if (itr1 != map.rEnd())
          {
            std::cout << " *(--i) = <" << (*itr1).key_ << ',' << (*itr1).data_ << ">\n";
          }
          std::cout << " *i     = <" << (*mapi).key_ << ',' << (*mapi).data_ << ">\n";
          if (itr2 != map.End())
          {
            std::cout << " *(++i) = <" << (*itr2).key_ << ',' << (*itr2).data_ << ">\n";
          }
        }
        else
          std::cout << "key \"" << key << "\" not found\n";
        break;

      case '*':
        *inptr >> data;
        if (BATCH) std::cout << data << '\n';
        if (initited && mapi != map.End())
        {
          (*mapi).data_ = data;
          mapci = mapi;
          std::cout << " iterator at entry <" << (*mapci).key_ << ',' << (*mapci).data_ << ">\n"; 
          // (*mapci).data_ = data; // uncomment this and see compile error message
          // (*mapi).key_ = key;    // uncomment this and see compile error message
          dw2 = CorrectDataWidth(data,dw2);
        }
        else if (!initited)
        {
          std::cout << " iterator not initialized\n";
        }
        else
        {
          std::cout << " iterator at End()\n";
        }
        break;
      case 'b': case 'B':
        if (BATCH) std::cout << '\n';
        mapi = map.Begin();
        if (mapi != map.End())
        {
          std::cout << " iterator at entry <" << (*mapi).key_ << ',' << (*mapi).data_ << ">\n"; 
          initited = 1;
        }
        else
          std::cout << " iterator at End()\n";
        break;
      case '+':
        if (BATCH) std::cout << '\n';
        ++mapi;
        if (mapi != map.End())
          std::cout << " iterator at entry <" << (*mapi).key_ << ',' << (*mapi).data_ << ">\n"; 
        else
          std::cout << " iterator at End()\n";
        break;
      case '-':
        if (BATCH) std::cout << '\n';
        --mapi;
        if (mapi != map.rEnd())
          std::cout << " iterator at entry <" << (*mapi).key_ << ',' << (*mapi).data_ << ">\n"; 
        else
          std::cout << " iterator at End()\n";
        break;
      case '!':
        *inptr >> command;
        if (BATCH) std::cout << command << '\n';
        switch (command)
        { 
          case '0': map.CheckStructure(0); break;
          case '1': map.CheckStructure(1); break;
          case '2': map.CheckStructure(2); break;
          // case '0': map.CheckBST(0); break;
          // case '1': map.CheckBST(1); break;
          // case '2': map.CheckBST(2); break;
          default: std::cout << " ** undefined command (level 2)\n";
        }
        break;
      case 'a': case 'A':
        if (BATCH) std::cout << '\n';
        fsu::Analysis(map, std::cout, 15);
        break;
      case 'm': case 'M':
        if (BATCH) std::cout << '\n';
        DisplayMenu();
        break;
      case 'q': case 'Q':
        if (BATCH)
        {
          std::cout << '\n';
          com.close();
        }
        command = 'q';
        break;
      default:
        if (BATCH) std::cout << '\n';
        std::cout << " ** undefined command (level 1)\n";
        // while (command != '\n')
        //   command = *inptr.get(); 
    }
  }
  while (command != 'q');
}

void DisplayMenu(std::ostream& os)
{
  os << "   OPERATION                       ENTRY\n"
     << "   ---------                       -----\n"
     << "   Load data from file  ............. L filename\n"
     << "   x.Put(key,data)  ................. P key data\n"
     << "   x.Get(key) ....................... G key\n"
     << "   x.Retrieve(key,&d) ............... R key\n"
     << "   x.Erase(key) ..................... E key\n"
     << "   map[key] = data  ................. [ key ] = data\n"
     << "   map[key] += data  ................ [ key ] + data\n"
     << "   data = map[key] .................. [ key ]\n"
     << "   i = x.Includes(key)  ............. i key\n"
     << "   i = x.Includes(key), --i, ++i  ... I key\n"
     << "   *i = newdata ..................... * data\n"
     << "   i = Begin() ...................... B\n"
     << "   ++i / --i  ....................... +/-\n"
     << "   x.Clear() ........................ C\n"
     << "   Rehash  .......................... H\n"
     << "   x.DumpBW(cout) ................... D0\n"
     << "   x.Dump(cout) ..................... D1\n"
     << "   x.Dump(cout,ofc) ................. D2\n"
     << "   x.Dump(cout,ofc,fill) ............ D3\n"
     << "   Size test  ....................... S\n"
     << "   shape Analysis  .................. A\n"
     << "   structural test  ................. ! 0|1|2   [structural check level 0, 1, 2]\n"
     << "   Traversal  ....................... T F|R|L|! [Forward, Reverse, Level, check]\n"
     << "   copy/assign test ................. =\n"
     << "   switch from batch mode ........... X\n"
     << "   quit program ..................... Q\n";
}
