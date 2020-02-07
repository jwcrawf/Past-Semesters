#ifndef _WGRAPH_UTIL_H
#define _WGRAPH_UTIL_H

#include <graph_util.h>

// ****************************************************************************************
// prototypes
// ****************************************************************************************

template < class G >
bool WLoad (const char* inFile, G& g);

template < class G >
bool WLoad (std::istream& inStream, G& g);

template < class G >
bool Save_UWG (const char* filenameBase, const G& g);

template < class G >
bool Save_DWG (const char* filenameBase, const G& g);

void WFileSpec(std::ostream& os = std::cout);

// ****************************************************************************************
// implementations
// ****************************************************************************************



template < class G >
bool WLoad (std::istream& inStream, G& g)
{ 
  typename G::Vertex x, y; // general purpose vertex variables
  char ch;  // general purpose file read variable
  double w;                 
  // skip documentation -- '#' in column 1
  ch = inStream.peek();
  while (ch == '#')
  {
    ch = inStream.get();
    while ((ch != '\n') && (!inStream.eof()))
      ch = inStream.get();
    ch = inStream.peek();
  }
  // read graph data and build graph
  inStream >> x;
  if (inStream.fail())
  {
    std::cerr << " ** Load error: vertex size not readable\n";
    return 0;
  }
  g.SetVrtxSize(x);
  while (inStream >> x >> y >> w)
  {
    g.AddEdge(x, y, w);
    //std::cout << " adding edge [" << x << ',' << y << ',' << w << "]\n";
  }
  return 1;
}

template < class G >
bool WLoad (const char* inFile, G& g)
{
  std::ifstream inStream;
  inStream.open(inFile);
  if (inStream.fail())
  {
    return 0;;
  }
  bool status = WLoad(inStream,g);
  inStream.clear();
  inStream.close();
  return status;
}

template < class G >
bool Save_UWG (const char* filenameBase, const G& g)
{
  // saves each undirected edge only one time
  size_t size = strlen(filenameBase);
  char filename [size+5];
  strcpy(filename,filenameBase);
  filename[size] = '.';
  filename[size+1] = 'u';
  filename[size+2] = 'w';
  filename[size+3] = 'g';
  filename[size+4] = '\0';
  std::ofstream outStream;
  outStream.open(filename);
  if (outStream.fail())
  {
    return 0;;
  }
  typename G::Vertex v;
  typename G::AdjIterator i;
   
  outStream << g.VrtxSize() << '\n';
  for (v = 0; v < g.VrtxSize(); ++v)
  {
    for (i = g.Begin(v); i != g.End(v); ++i)
    {
      if (v < *i) outStream << v << '\t' << *i << '\t' << GetWeight(v,*i) << '\n';
    }
  }
  outStream.close();
  std::cout << " wungraph saved as " << filename << '\n';
  return 1;
}

template < class G >
bool Save_DWG (const char* filenameBase, const G& g)
{
  // saves each directed edge
  size_t size = strlen(filenameBase);
  char filename [size+5];
  strcpy(filename,filenameBase);
  filename[size] = '.';
  filename[size+1] = 'd';
  filename[size+2] = 'w';
  filename[size+3] = 'g';
  filename[size+4] = '\0';
  std::ofstream outStream;
  outStream.open(filename);
  if (outStream.fail())
  {
    return 0;;
  }
  typename G::Vertex v;
  typename G::AdjIterator i;  
  outStream << g.VrtxSize() << '\n';
  for (v = 0; v < g.VrtxSize(); ++v)
  {
    for (i = g.Begin(v); i != g.End(v); ++i)
    {
      outStream << v << '\t' << *i << '\t' << GetWeight(v,*i) << '\n';
    }
  }
  outStream.close();
  std::cout << " wdigraph saved as " << filename << '\n';
  return 1;
}

void WFileSpec(std::ostream& os)
{
  os << " -----------------------------------------------------------------------\n"
     << " Graph File Specs                                                       \n"
     << " ----------------                                                       \n"
     << " 1 File documentation at beginning of file, lines begin with '#'        \n"
     << " 2 Remainder of file consists of unsigned integers in decimal notation  \n"
     << " 2.1 First number is vertex size                                        \n"
     << " 2.2 Remaining numbers occur in pairs                                   \n"
     << " 2.3 Pair represents an edge \"from\" \"to\"                            \n"
     << " 2.4 Edge vertices must be in range determined by 2.1                   \n"
     << " -----------------------------------------------------------------------\n";
}

#endif