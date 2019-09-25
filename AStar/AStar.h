#pragma once
#include <list>
#include <map>
#include <string>
using std::list;
using std::map;
using std::string;

namespace AI_assignment {
class AStar {
 public:
  struct Node {
    string name;
    list<string> neighbour;
    map<string, int> distance;
    map<string, int> heuristics;
  };
  struct Cost {
    string from;
    string node;
    int cost;
    bool operator<(const Cost& other) const { return cost > other.cost; }
  };
  AStar();
  void AddNode(string name);
  void AddEdge(string from, string to, int distance);
  void AddHeuristics(string from, string to, int distance);
  int GetShortestDistance(string from, string to, list<string>& path);

 private:
  map<string, Node> nodes;
};
}  // namespace AI_assignment