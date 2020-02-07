/*
  moviematch.h

  Jon Crawford

  4/16/2018

  header file with implementations for proj8 Kevin Bacon
*/

#ifndef _MOVIEMATCH_H
#define _MOVIEMATCH_H

#include <cstdlib>
#include <iostream>
#include <vector.h>
#include <graph.h>
#include <bfsurvey.h>
#include <dfsurvey.h>
#include <hashtbl.h>
#include <genalg.h>
#include <xstring.h>
#include <graph_util.h>
#include <survey_util.h>
#include <fstream>
#include <hashclasses.h>
#include <deque.h>
#include <list.h>
#include <cctype>
#include <gheap.h>
#include <gbsearch.h>

typedef uint32_t                           Vertex;
typedef fsu::String                        Name;
typedef fsu::ALUGraph <Vertex>             Graph;
typedef fsu::BFSurvey <Graph>              BFS;
typedef hashclass::KISS<Name>              Hash;
typedef fsu::HashTable<Name,Vertex,Hash>   AA; 
typedef fsu::Vector<Name>                  Vector;
typedef fsu::List<Vertex>                  List;
typedef fsu::Vector<size_t>                Hint;

class MovieMatch
{
public:
  MovieMatch         ();
  bool Load          (const char* filename);
  bool Init          (const char* actor);
  void Shuffle       ();
  long MovieDistance (const char* actor);
  void ShowPath      (std::ostream& os) const;
  void ShowStar      (Name name, std::ostream& os) const;
  void Hint          (Name name, std::ostream& os) const;
  void Dump          (std::ostream& os) const;
  
private:

  static void  Line  (std::istream& is, Vector& movie);
 
  Vector             movie_;
  Graph              g_;
  Vector             name_;
  AA                 vrtx_;
  Name               baseActor_;
  BFS                bfs_;
  List               path_;
  Vector             hint_;
  
};

class LessThanLower
{
public:
  bool operator () (const Name& s1, const Name& s2)
  {
    size_t i = 0;
    while (i < s1.Size() && i < s2.Size())
    {
      if (tolower(s1[i]) < tolower(s2[i])) return true;
      else if (tolower(s1[i]) > tolower(s2[i])) return false;
      ++i;
    }
    return (s1.Size() < s2.Size());
  }
};

class Levenshtein
{
public:
  size_t LevenshteinDist(const Name& s1, const Name& s2)
  {
    size_t len1 = s1.Size(), len2 = s2.Size();
    Hint col(len2 + 1), prev(len2 + 1);
    for (size_t i = 0; i < prev.Size(); ++i)
      prev[i] = i;
    for (size_t i = 0; i < len1; ++i)
    {
      col[0] = i + 1;
      for (size_t j = 0; j < len2; ++j)
      {
        size_t  w, x, y, z;
        x = prev[1 + j] + 1, y = col[j] + 1, z = prev[j] + (tolower(s1[i]) == tolower(s2[j]) ? 0:1);
        w = std::min(x, y);
        col[j + 1] = std::min(w, z);
      }
      col.Swap(prev);
    }
    return prev[len2];
  }
};


MovieMatch::MovieMatch (): g_(), name_(), vrtx_(), baseActor_(), bfs_(g_), hint_()
{}

bool MovieMatch::Load (const char* filename)
{
  std::cout << "\n Loading database " << filename << " (first read) ...";
  Vertex count = 0, v = 0;
  size_t actor(0), numBuckets(10);
  Vector inData;
  std::ifstream inFile;
  inFile.open(filename);
  if (!inFile) return false;
  while (!(inFile.eof()))
  {
    MovieMatch::Line(inFile, inData);
    for ( size_t i = 0; i < inData.Size(); ++i)
    {
      if (!(vrtx_.Retrieve(inData[i], v)))
      {
        if (i == 0) movie_.PushBack(inData[i]);
        vrtx_[inData[i]] = count;
        ++count;
        name_.PushBack(inData[i]);
        ++actor;
        hint_.PushBack(inData[i]);
      }
    }
    if (actor > 3 * numBuckets)
    {
      numBuckets *= 2;
      vrtx_.Rehash(numBuckets);
    }
  }
  vrtx_.Rehash(actor);
  std::cout << "(second read) ... ";
  inFile.clear();
  inFile.seekg(0);
  g_.SetVrtxSize(vrtx_.Size());
  while (!(inFile.eof()))
  {
    MovieMatch::Line(inFile, inData);
    for (size_t i = 1; i < inData.Size(); ++i)
      g_.AddEdge(vrtx_[inData[0]], vrtx_[inData[i]]);
  }
  inFile.close();
  std::cout << "done. " 
            << "\n " << movie_.Size() << " movies and " 
            << actor - movie_.Size() << " actors read from " 
            << filename << "\n";
  return true;
} // end Load(filename)

bool MovieMatch::Init (const char* actor)
{
  Vertex v;
  if (!(vrtx_.Retrieve(actor, v)))
  {
    std::cerr << " ** Init: " << actor << " is not in the database\n";
    return false;
  }
  LessThanLower cmp;
  Name movie(name_[v]);
  g_heap_sort(movie_.Begin(), movie_.End());
  if (g_binary_search(movie_.Begin(), movie_.End(), movie, cmp))
  {
    std::cerr << " ** Init: " << actor << " is a movie\n";
    return false;
  }
  g_heap_sort(hint_.Begin(),hint_.End(), cmp);
  baseActor_ = actor;
  bfs_.Reset();
  bfs_.Search(v);
  return true;
} //end Init(actor)

void MovieMatch::Shuffle ()
{
  g_.Shuffle();
  bfs_.Reset();
  bfs_.Search(vrtx_[baseActor_]);
}

long MovieMatch::MovieDistance (const char* actor)
{
  Vertex v;
  LessThanLower cmp;
  if (!(vrtx_.Retrieve(actor, v)))
    return -3;
  if (bfs_.Color()[v] != 'b')     
    return -2;   
  Name movie(name_[v]);
  if (g_binary_search(movie_.Begin(), movie_.End(), movie, cmp))
    return -1;
  long baconNumber = bfs_.Distance()[v] / 2;
  path_.Clear();
  path_.PushBack(v);
  while (bfs_.Parent()[v] != bfs_.NullVertex())
  {
    path_.PushBack(bfs_.Parent()[v]);
    v = bfs_.Parent()[v];
  }
  return baconNumber;
}

void MovieMatch::ShowPath (std::ostream& os) const
{
  size_t count(0);
  List::ConstIterator i;
  os << "\n";
  for (i = path_.Begin(); i != path_.End(); ++i)
  {
    if (count % 2 == 0)
      os << " " << name_[*i] << "\n";
    else
      os << "   | " << name_[*i] << "\n";
    ++count;
  }
  os << "\n";
}

void MovieMatch::ShowStar (Name name, std::ostream& os) const
{
  Graph::AdjIterator i;
  Vector::ConstIterator j;
  Vertex v = vrtx_[name];
  Vector star;
  for (i = g_.Begin(v); i != g_.End(v); ++i)
    star.PushBack(name_[*i]);
  g_selection_sort(star.Begin(), star.End());
  os << "\n " << name << "\n";
  for (j = star.Begin(); j != star.End(); ++j)
    os << "   | " << *j << "\n";
  os << "\n";
}

void MovieMatch::Hint (Name name, std::ostream& os) const
{
  size_t bound(5), nameLength = name.Size();
  if (nameLength < bound)
    bound = nameLength;
  char cName[bound + 1];
  for (size_t i = 0; i < bound; ++i)
    cName[i] = name.Element(i);
  cName[bound] = '\0';
  Name lowName(cName);
  Name highName(lowName);
  highName.SetSize(bound + 3);
  highName[bound] = 'z';
  highName[bound + 1] = 'z'; 
  highName[bound + 2] = '\0';
  
  LessThanLower cmp;
  Vector::ConstIterator low, high, lo, hi;
  low = hint_.Begin(), high = hint_.End();
  lo = g_lower_bound(low, high, lowName, cmp);
  hi = g_upper_bound(low, high, highName, cmp);
  for (size_t i = 0; i < 2; ++i)
  {
    if (lo != low) -- lo;
    if (hi != high) ++ hi;
  }
  //for (; lo < hi; ++lo) 
  // os << *lo << "\n";
  Levenshtein lev;
  size_t levBnd(4);
  if (nameLength <= levBnd)
    levBnd = 3;     
  for (; low < high; ++low)
  {
    if(lev.LevenshteinDist(name,*low) < levBnd)
      os << *low << "\n";
  }
} // end Hint(name)

void MovieMatch::Line (std::istream& is, Vector& movie)
{
  movie.Clear();
  fsu::String line;
  char delim = '/';
  line.GetLine(is);
  char* name_buffer = new char [1+line.Size()];
  size_t pos = 0, next = 0;
  while (pos < line.Size())
  {
    next = line.Position(delim,pos);
    for (size_t i = pos; i < next; ++i)
    {
      name_buffer[i - pos]= line[i];
    }
    name_buffer[next-pos] = '\0';
    movie.PushBack(name_buffer);
    pos = ++next;
  }
  delete [] name_buffer;
}

void MovieMatch::Dump(std::ostream& os) const
{
  ShowAL(g_,os);
  WriteData(bfs_,os);
  vrtx_.Dump(os);
  for (size_t i = 0; i < name_.Size(); ++i)
  {
    os << "name_[" << i << "] = " << name_[i] << '\t';
    os << "vrtx_[" << name_[i] << "] = " << vrtx_[name_[i]] << '\n';
  }
  vrtx_.Analysis(std::cout);
}

#endif
