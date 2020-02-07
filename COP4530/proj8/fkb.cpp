/*
    fkb.cpp
    05/02/17
*/


#include <moviematch.h>
#include <xstring.h>
#include <timer.h>

// in lieu of makefile
#include <xstring.cpp>
#include <bitvect.cpp>
#include <primes.cpp>
#include <hashfunctions.cpp>
#include <timer.cpp>
// */

// bool BATCH = 1;
bool BATCH = 0;

// set up buffer system for read loop
static size_t buffSize = 100;
static char* buffer = new char [buffSize + 1];

fsu::String GetName (std::istream& is)
// reads to end of line, including blanks
{
  size_t currSize = 0;
  char x;
  std::cin >> x;
  while ((x != '\n') && (!is.eof()))
  {
    if (currSize == buffSize)  // need more buffer 
    {
      buffSize += 100;
      char* newbuffer = new char [buffSize + 1];
      for (size_t i = 0; i < currSize; ++i)
      {
        newbuffer[i] = buffer[i];
      }
      delete [] buffer;
      buffer = newbuffer;
    }
    buffer[currSize++] = x;
    x = is.get();
  }
  buffer[currSize] = '\0';
  return buffer;
} // end read block

void DisplayMenu(std::ostream& os)
{
  os << '\n'
     << "      function              command\n"
     << "      --------              -------\n"
     << "      mm.MovieDistance (name) ... K\n"
     << "      mm.Hint (name) ............ H\n"
     << "      mm.ShowStar (name) ........ S\n"
     << "      mm.ShowPath (name) ........ P\n"
     << "      mm.Shuffle() .............. $\n"
     << "      mm.GetVrtx (name) ......... V\n"
     << "      mm.GetName (vrtx) ......... N\n"
     << "      mm.Dump ()  ............... U\n"
     << "      mm.DegreeSequence (max) ... D\n"
     << "      mm.Analysis() ............. A\n"
     << "      mm.SaveAbstractGraph() .... G\n"
     << "      DisplayMenu() ............. m\n"
     << "      Return to Game ............ x\n"
     << "      Quit ...................... x0\n"
     << '\n';
}

int main(int argc, char* argv[])
{

  fsu::String database = "movies.txt", baseactor = "Bacon, Kevin";

  if (argc < 2)
  {
    std::cout << "\n ** no database specified, using default \'" << database << "\'\n"; 
  }
  else
  {
    database = argv[1];
  }
  if (argc < 3)
  {
    std::cout << "\n ** no base actor specified, using default \'" << baseactor << "\'\n"; 
  }
  else
  {
    baseactor = argv[2];
  }

  MovieMatch mm;

  // set up timer for Load call
  fsu::Timer timer;
  fsu::Instant time;
  timer.EventReset();
  // bool success = mm.Load(argv[1]);
  bool success = mm.Load(database.Cstr());
  time = timer.EventTime();
  if (!success)
  {
    // std::cout << " ** KB: Failure to Load " << argv[1] << '\n';
    std::cout << " ** KB: Failure to Load " << database << '\n';
    return EXIT_FAILURE;
  }
  else
  {
    std::cout << " Load time: ";
    time.Write_seconds(std::cout,2);
    std::cout << " sec\n";
  }
  timer.EventReset();
  // success = mm.Init(argv[2]);
  success = mm.Init(baseactor.Cstr());
  time = timer.EventTime();
  if (!success)
  {
    // std::cout << " ** failure to Init " << argv[2] << '\n';
    std::cout << " ** failure to Init " << baseactor << '\n';
    std::cout << "    try: \" kb.x movies.txt \'Bacon, Kevin\' \"\n";
    return EXIT_FAILURE;
  }
  else
  {
    std::cout << " Init time: ";
    time.Write_seconds(std::cout,2);
    std::cout << " sec\n";
  }
  // std::cout << "\nWelcome to MovieMatch ( " << argv[2] << " )\n";
  std::cout << "\nWelcome to MovieMatch ( " << baseactor << " )\n";
  fsu::String name  = "1";
  fsu::String answer = "yes";
  long kbn = 0;

  while (1)
  {
    std::cout << "Enter actor name ('0' to quit, '$' to shuffle, '!' for API menu): ";
    name = GetName(std::cin);
    if (BATCH) std::cout << name << '\n';
    if (name.Size() == 1)
    {
      if (name[0] == '0') break;
      if (name[0] == '$')
      {
        mm.Shuffle();
        continue;
      }
      if (name[0] == '!')
      {
        DisplayMenu(std::cout);
        char ch;
        size_t max, threshold;
        char* buffer;
        do
        {
          std::cout << "  Enter command ('m' for API menu, 'x' to return to game): ";
          std::cin >> ch;
          if (BATCH) std::cout << ch << '\n';
          switch(ch)
          {
            case '$':  // Shuffle()
              mm.Shuffle();
              break;
            case 'k': case 'K':
              std::cout << "    Enter name: ";
              name = GetName(std::cin);
              if (BATCH) std::cout << name << '\n';
              std::cout << "      KB Number of " << name << " = " << mm.MovieDistance(name.Cstr()) << '\n';
              break;
            case 'h': case 'H':
              std::cout << "    Enter name: ";
              name = GetName(std::cin);
              if (BATCH) std::cout << name << '\n';
              std::cout << "      Hint(" << name << "):\n";
              mm.Hint(name,std::cout);
              break;
            case 's': case 'S':
              std::cout << "    Enter name: ";
              name = GetName(std::cin);
              if (BATCH) std::cout << name << '\n';
              std::cout << "      ShowStar(" << name << "):\n";
              mm.ShowStar(name,std::cout);
              break;
            case 'p': case 'P':
              std::cout << "      current path:\n";
              mm.ShowPath(std::cout);
              break;
            case 'u': case 'U':  // Dump
              mm.Dump(std::cout);
              break;
            case 'v': case 'V':
              std::cout << "    Enter name: ";
              name = GetName(std::cin);
              if (BATCH) std::cout << name << '\n';
              std::cout << "      vrtx[" << name << "] = " << mm.GetVrtx(name) << '\n';
              break;
            case 'n': case 'N':
              std::cout << "    Enter vrtx: ";
              std::cin >> max;
              if (BATCH) std::cout << max << '\n';
              std::cout << "      name[" << max << "] = " << mm.GetName(max) << '\n';
              break;
            // Begin cases not required
            case 'd': case 'D':
              std::cout << "      max to display (0 for no limit): ";
              std::cin >> max;
              if (BATCH) std::cout << max << '\n';
              mm.DegreeSequence(max);
              break;
            case 'a': case 'A':  // Save abstract graph
              std::cout << "    Enter threshold: ";
              std::cin >> threshold;
              if (BATCH) std::cout << threshold << '\n';
              max  = strlen(mm.DBName());
              buffer = new char [max + 5];
              strcpy (buffer,mm.DBName());
              buffer[max] = '.';
              buffer[max+1] = 'l';
              buffer[max+2] = 'o';
              buffer[max+3] = 'g';
              buffer[max+4] = '\0';
              mm.Analysis(mm.BaseActor(),threshold,buffer);
              delete [] buffer;
              break;
            case 'g': case 'G':  // Save abstract graph
              mm.SaveAbstractGraph();
              break;
            // End cases not required */
            case 'm': case 'M': case '!': // display command menu
              DisplayMenu(std::cout);
              break;
            case 'x': case 'X':  // exit command loop
              ch = 'x';
              break;
            default:
              std::cout << "      command not found\n";
              break;
          } // switch
        } // do
        while (ch != 'x');
        continue;
      }
    }
    kbn = mm.MovieDistance(name.Cstr()); 
    if (kbn == -3)
    {
      std::cout << " Name \"" << name << "\" not in DB \'" << database << "\'\n"
                << " Here are some similar name possibilities:\n";
      mm.Hint(name,std::cout);
    }
    else if (kbn == -2)
    {
      std::cout << " Name \'" << name << "\' unreachable from base actor \'" << baseactor << "\'\n"
                << " Here are the names adjacent to \'" << name << "\' in the DB:\n";
      mm.ShowStar(name, std::cout);
    }
    else if (kbn == -1)
    {
      std::cout << " name \'" << name << "\' is a movie, not an actor\n";
      std::cout << "  Do you want details? ";
      std::cin >> answer;
      if (BATCH) std::cout << answer << '\n';
      if (answer.Element(0) == 'y' || answer.Element(0) == 'Y')
      {
        std::cout << "   The movie is:\n";
        mm.ShowStar(name, std::cout);
      }
    }
    else
    {
      std::cout << " The KB Number of \'" << name << "\' is: "
                << kbn
                << '\n';
      std::cout << "  Do you want proof? ";
      std::cin >> answer;
      if (BATCH) std::cout << answer << '\n';
      if (answer.Element(0) == 'y' || answer.Element(0) == 'Y')
      {
        std::cout << "   A connecting path is:\n";
        mm.ShowPath(std::cout);
        std::cout << "   The path is minimal because it was found with BFS [ref graph theory].\n";
      }
    }
  } // end while
  delete [] buffer;
  std::cout << "Thank you for playing Kevin Bacon\n";
  return EXIT_SUCCESS;
}
