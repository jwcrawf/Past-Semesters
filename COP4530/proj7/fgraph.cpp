/*
    fgraph.cpp
    07/18/17

    Tests input of graphs 
    Includes topological sort driver and OutDegreeFrequencyDistribution

    File format:

      Lines at the top of the file begining with '#' are file documentation.
      Once those lines are passed, the remainder of the file is data.

      The data in the file consists of unsigned integers. 
      The first number (after documentation) is the vertex count.
      Then there are numbers in pairs representing "from to" edges.
      The number of edges is limited only by the graph structures possible.
      The numbers (which represent vertices) must be in the range [0..VertexCount).

      For example:
        # 
        # yada dada
        # 
        3 
        1 2 1 0 
        2 0
        0 1 0 2
      represents a graph with 3 vertices (enumerated 0, 1, 2) and edges
      [1 2] [1 0] [2 0] [0 1] [0 2].

      The format of the file is irrelevant, but may be more readable of all
      edges from a given vertex are placed on a single line.

    Copyright 2017, R.C. Lacher
*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ansicodes.h>
#include <graph.h>
#include <graph_util.h> // ShowAL, FileSpec, OutDegreeFrequencyDistribution
#include <topsort.h>
#include <queue.h>

// choose the adjacency list representations
typedef size_t Vertex;
typedef fsu::ALUGraph<Vertex>  Ungraph;
typedef fsu::ALDGraph<Vertex>  Digraph;
// */

/* // choose the adjacency matrix representations
typedef size_t Vertex;
typedef fsu::IAMUGraph        Ungraph;
typedef fsu::IAMDGraph        Digraph;
// */

int main( int argc , char* argv[] )
{
  // std::cout << ANSI_BOLD_BLUE;
  std::cout << "\n  Welcome to fgraph - a graph functionality test\n";
  // std::cout << ANSI_RESET_ALL;
  char* inFile(0);
  bool verbose = 0;

  if (argc < 2)
  {
    std::cout << ANSI_BOLD_RED
              << "  Arguments expected:\n"
              << "                      1: input filename (required)\n"
              << "                      2: verbose mode   (optional)\n";
    FileSpec(std::cout);
    std::cout << ANSI_RESET_ALL;
    exit (EXIT_FAILURE);
  }
  else if (argc == 2)
  {
    std::cout << "  Input file: " << argv[1] << '\n'
	      << "  Verbose output disabled\n";
    inFile = argv[1];
  }
  else
  {
    std::cout << "  Input file: " << argv[1] << '\n'
	      << "  Verbose output enabled\n";
    inFile = argv[1];
    verbose = 1;
  }

  Ungraph unGraph;
  Digraph diGraph;

  std::ifstream inStream;
  std::ofstream logStream;
  Vertex v, w; // general purpose vertex variables
  char ch;     // general purpose file read variable

  inStream.open(inFile);
  if (inStream.fail())
  {
    std::cout << "Cannot open file " << inFile << ". Please try again.\n";
    FileSpec(std::cout);
    exit (EXIT_FAILURE);
  }
 
  // skip documentation -- '#' in column 1
  ch = inStream.peek();
  while (ch == '#')
  {
    ch = inStream.get();
    while ((ch != '\n') && (!inStream.eof()))
      ch = inStream.get();
    ch = inStream.peek();
  }

  std::cout << "Loading from file " << inFile << "..." << std::flush;
  inStream >> v;
  unGraph.SetVrtxSize(v);
  diGraph.SetVrtxSize(v);
  while (inStream >> v >> w)
  {
    // if (verbose) std::cout << " adding undirected edge [" << v << ',' << w << "]\n";
    unGraph.AddEdge(v,w);
    // if (verbose) std::cout << " adding   directed edge (" << (size_t)v << ',' << (size_t)w << ")\n";
    diGraph.AddEdge(v,w);
  }
  inStream.close();
  std::cout << "\nLoad complete.\n" << std::flush;

  std::cout << "unGraph.VrtxSize(): " << unGraph.VrtxSize() << '\n';
  std::cout << "unGraph.EdgeSize(): " << unGraph.EdgeSize() << '\n';

  // ungraph checks
  if (verbose) 
  {
    std::cout << "unGraph.Dump():\n";
    unGraph.Dump(std::cout);
    for (size_t i = 0; i < unGraph.VrtxSize(); ++i)
    {
      std::cout << "unGraph.InDegree(" << i << ")  == " << unGraph.InDegree(i) << '\n'
                << "unGraph.OutDegree(" << i << ") == " << unGraph.OutDegree(i) << '\n';
    }
  }
  std::cout << "OutDegreeFrequencyDistribution(unGraph):\n";
  OutDegreeFrequencyDistribution(unGraph);

  // digraph checks
  if (verbose) 
  {  
    std::cout << "diGraph.Dump():\n";
    diGraph.Dump(std::cout);
    for (size_t i = 0; i < diGraph.VrtxSize(); ++i)
    {
      std::cout << "diGraph.InDegree(" << i << ")  == " << diGraph.InDegree(i) << '\n'
                << "diGraph.OutDegree(" << i << ") == " << diGraph.OutDegree(i) << '\n';
    }
  }
  std::cout << "OutDegreeFrequencyDistribution(diGraph):\n";
  OutDegreeFrequencyDistribution(diGraph);

  // reverse digraph checks
  Digraph reverse;
  diGraph.Reverse(reverse);
  if (verbose) 
  {  
    std::cout << "reverse.Dump():\n";
    reverse.Dump(std::cout);
    for (size_t i = 0; i < reverse.VrtxSize(); ++i)
    {
      std::cout << "reverse.InDegree(" << i << ")  == " << reverse.InDegree(i) << '\n'
                << "reverse.OutDegree(" << i << ") == " << reverse.OutDegree(i) << '\n';
    }
  }
  std::cout << "OutDegreeFrequencyDistribution(reverse):\n";
  OutDegreeFrequencyDistribution(reverse);

  // top sorts
  std::cout << "\nTopological sort tests:\n";
  fsu::Queue<int> result;
  bool success =  fsu::TopSort(diGraph, result);
  if (success)
  {
    std::cout << " Top Sort (diGraph): " ;
  }
  else
  {
    std::cout << " No Top Sort: diGraph has cycle\n";
    std::cout << " Partial Top Sort: " ;
  }
  result.Display(std::cout, ' ');
  std::cout << '\n';
  result.Clear();
  success =  fsu::TopSort(reverse, result);
  if (success)
  {
    std::cout << " Top Sort (reverse): " ;
  }
  else
  {
    std::cout << " No Top Sort: reverse has cycle\n";
    std::cout << " Partial Top Sort: " ;
  }
  result.Display(std::cout, ' ');
  std::cout << '\n';
 
  return EXIT_SUCCESS;
}
