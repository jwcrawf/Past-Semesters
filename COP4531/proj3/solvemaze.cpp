/*
  solvemaze.cpp

  Jon Crawford

  COP4531 Summer 2019 proj3 - Mazes on the Web

*/

#include <graph.h>
#include <graph_util.h>
#include <bfsurvey.h>
#include <dfsurvey.h>
#include <survey_util.h>
#include <vector.h>
#include <maze_util.h>
#include <fstream>
#include <iostream>
#include <list.h>

int main (int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cout << "** command line arguments required:\n"
              << "   1: mazefile\n"
              << "** try again" << std::endl;
    return 0;
  }
  size_t n = strlen(argv[1]);
  char file[n + 5];
  strcpy(file, argv[1]);
  file[n] = '.';
  file[n + 1] = 'd';
  file[n + 2] = 'f';
  file[n + 3] = 's';
  file[n + 4] = '\0'; 
  char* maze = argv[1];
  fsu::ALDGraph<size_t> graph;
  size_t start, goal; 
  fsu::List<size_t> path;
  LoadMaze(maze, graph, start, goal);
  CheckSymmetry(graph);  
  Path_DFS(graph, start, goal, path);
  
  std::ifstream in;
  std::ofstream of;
  in.open(argv[1], std::ios::in | std::ios::binary);
  of.open(file, std::ios::out | std::ios::binary);
  of << in.rdbuf(); 
  in.close(); 
  std::cout << "Solution found has " << path.Size() << " cells\n";
  fsu::List<size_t>::Iterator i;
  of << '\n';
  for(i = path.Begin(); i != path.End(); ++i)
    of << ' ' << *i;
  of << '\n';
  of.close();
  of.clear();
  std::cout << "Maze and solution written to file \"" << file << "\"\n";
  return 0;
}