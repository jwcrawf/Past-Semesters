/*
  fprime+.cpp
  10/13/17
  Chris Lacher

  test Prime API
*/

#include <prime+.h>
#include <fstream>

void DisplayMenu (size_t ub, std::ostream& os = std::cout);
void CopyTest    (Prime p);
void AssignTest  (const Prime& p);

int main (int argc, char* argv[])
{

  if (argc < 2)
  {
    std::cout << " ** command line arguments:\n"
	      << "    1: upper bound (unsigned int) [required]\n"
              << "    2: timer (bool, default = 0)  [optional - to invoke timer]\n"
	      << "    3: batch (bool, default = 0)  [optional - for processing a file of commands]\n";
    return EXIT_FAILURE;
  }
  size_t n = atol(argv[1]);
  bool timed = 0;
  if (argc > 2)
  {
    timed = atoi(argv[2]);
  }
  Prime p(n,timed);

  std::ifstream ifs;
  std::istream* isptr = &std::cin;
  bool BATCH = 0;  
  if (argc > 3)
  {
    ifs.open(argv[3]);
    if (ifs.fail())
    {
      std::cout << " ** unable to open file \"" << argv[3] << "\"\n"
                << "    try again\n";
      return EXIT_FAILURE;
    }
    isptr = &ifs;
    BATCH = 1;
  }

  char selection;
  std::cout << "Welcome to fprime\n";
  DisplayMenu(p.UpperBound());
  do
  {
    std::cout << " Enter selection ('Q' to quit): ";
    *isptr >> selection;
    switch(selection)
    {
      case '=':
        if (BATCH)  std::cout << selection << '\n'; // echo input
        CopyTest(p);
        AssignTest(p);
        break;

      case 'l': case 'L':
        *isptr >> n;
        if (BATCH) std::cout << n << '\n';
        std::cout << "  p.Largest(" << n << ") = " << p.Largest(n) << '\n';
        break;
      case 'a':
        *isptr >> n;
        if (BATCH) std::cout << n << '\n';
        std::cout << "  p.All(" << n << "): ";
        p.All(n,std::cout);
        std::cout << '\n';
        break;
      case 'A':
        if (BATCH) std::cout << '\n';
        std::cout << "  p.All(): ";
        p.All(std::cout);
        std::cout << '\n';
        break;
      case 'u': case 'U':
        if (BATCH) std::cout << '\n';
        std::cout << "  p.UpperBound() = " << p.UpperBound() << '\n';
        break;
      case 'r': case 'R':
        *isptr >> n;
        if (BATCH) std::cout << n << '\n';
        std::cout << "  p.ResetUpperBound(" << n << ")\n";
        p.ResetUpperBound(n);
        break;
      case 'd': case 'D':
        if (BATCH) std::cout << '\n';
        std::cout << "  p.Dump():\n";
        p.Dump();
        break;
      case 'x': case 'X':
        if (BATCH)
        {
          std::cout << selection << '\n'; // echo input
          isptr = &std::cin;
          ifs.close();
          BATCH = 0;
          std::cout << " ** switched to interactive mode\n";
        }
        else
        {
          std::cout << " ** already in interactive mode\n";
        }
        break;
      case 'm': case 'M':
        if (BATCH) std::cout << '\n';
        DisplayMenu(p.UpperBound());
        break;
      case 'q': case 'Q': 
        if (BATCH)  std::cout << selection << '\n'; // echo input
        selection = 'Q';
        if (BATCH)
          ifs.close();
        break;
      default:
        if (BATCH)  std::cout << selection << '\n'; // echo input
        std::cout << "  command not found\n";
    }
  }
  while (selection != 'Q');
  std::cout << "Thank you for testing class Prime\n";
  return EXIT_SUCCESS;
}

void DisplayMenu(size_t ub, std::ostream& os)
{
  os << "     Prime p(" << ub << ");\n"
     << "     operation                                  entry\n"
     << "     ---------                                  -----\n"
     << "     Largest (n) ...............................  l n\n"
     << "     All (n) ...................................  a n\n"
     << "     All (UpperBound()) ........................  A\n"
     << "     UpperBound ()  ............................  u\n"
     << "     ResetUpperBound (n) .......................  r n\n"
     << "     Dump () ...................................  d\n"
     << "     copy, assign tests  .......................  =\n"
     << "     display this Menu  ........................  m\n"
     << "     switch to interactive mode  ...............  x\n"
     << "     Quit program  .............................  q\n"
     << '\n';
}

void CopyTest(Prime p)
{
  std::cout << " CopyTest:\n";
  std::cout << "  Copied object   All: "; 
  p.All(p.UpperBound());
}

void AssignTest(const Prime& p)
{
  Prime p1(0);
  p1 = p;
  std::cout << " AssignTest:\n";
  std::cout << "  Original object All: "; 
  p.All(p.UpperBound());
  std::cout << "  Assignee object All: "; 
  p1.All(p1.UpperBound());
}
