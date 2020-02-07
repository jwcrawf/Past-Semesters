/*
    ranstring.cpp
    02/23/14
    Chris Lacher

    creates random string data for test data

    Copyright 2014, R.C. Lacher
*/

#include <fstream>

#include <xstring.cpp>
#include <xran.cpp>
#include <xranxstr.cpp>

int main(int argc, char* argv[])
{
  if (argc < 5)
  {
    std::cout << " ** program requires 4 arguments\n"
	      << "    1 = number of generated entries\n"
	      << "    2 = min length of string\n"
	      << "    3 = max length of string\n"
	      << "    4 = output filename\n"
	      << "    5 = upper & lower case mixed? (optional 1|0 - default = 0)\n"
	      << " ** try again\n";
    exit(0);
  }

  bool mixedCase = 0;
  if (argc > 5 && argv[5][0] != '0') mixedCase = 1;
  std::cout << "Program generating file string entries, one per line.\n"
            << " strings have length in [" << argv[2] << ',' << argv[3] << "]\n";
  if (mixedCase) 
  {
    std::cout << " and consist of mixed upper/lower case letters\n";
  }
  else
  {
    std::cout << " and consist of lower case letters only\n";
  }
  std::cout << " ...\n";

  std::ofstream out1;
  out1.open(argv[4]);
  if (out1.fail())
  {
    std::cout << " ** Unable to open file " << argv[4] << '\n'
	      << " ** program closing\n";
    exit(0);
  }

  fsu::Random_String ranString;
  fsu::Random_mixedcase_String ranmixedString;
  fsu::Random_int ranint;
  size_t num = atoi(argv[1]), min = atoi(argv[2]), max = atoi(argv[3]) + 1, len;
  if (mixedCase)
  {
    for (size_t i = 0; i < num; ++i)
    {
      len = ranint(min, max);
      out1 << ranmixedString(len) << '\n';
    }
  }
  else
  {
    for (size_t i = 0; i < num; ++i)
    {
      len = ranint(min, max);
      out1 << ranString(len) << '\n';
    }
  }

  // close outfile
  out1.close();

  // terminate program
  std::cout << "File of strings constructed:\n"
	    << " filename:        " << argv[4] << '\n'
	    << " number of strings: " << num << '\n'
	    << " string lengths:  [" << min << ',' << max - 1 << "]\n";

  return 0;
}
