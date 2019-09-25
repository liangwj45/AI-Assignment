#include <iostream>
#include "AStar.h"
using namespace AI_assignment;

void DataImport(AStar& obj);

int main() {
  AStar test;
  list<string> path;
  DataImport(test);
  string from = "Bucharest";
  string to = "Arad";
  int distance = test.GetShortestDistance(from, to, path);
  printf("Cost:\t%d\nPath:\t", distance);
  for (auto each : path) {
    printf("%s -> ", each.c_str());
  }
  printf("%s\n", to.c_str());
}

void DataImport(AStar& obj) {
  obj.AddNode("Oradea");
  obj.AddNode("Zerind");
  obj.AddNode("Arad");
  obj.AddNode("Timisoara");
  obj.AddNode("Lugoj");
  obj.AddNode("Mehadia");
  obj.AddNode("Dobreta");
  obj.AddNode("Sibiu");
  obj.AddNode("Rimnicu Vilcea");
  obj.AddNode("Craiova");
  obj.AddNode("Fagaras");
  obj.AddNode("Pitesti");
  obj.AddNode("Bucharest");
  obj.AddNode("Giurgiu");
  obj.AddNode("Urziceni");
  obj.AddNode("Vaslui");
  obj.AddNode("Iasi");
  obj.AddNode("Neamt");
  obj.AddNode("Hirsova");
  obj.AddNode("Eforie");

  obj.AddEdge("Oradea", "Zerind", 71);
  obj.AddEdge("Oradea", "Sibiu", 151);
  obj.AddEdge("Zerind", "Arad", 75);
  obj.AddEdge("Arad", "Timisoara", 118);
  obj.AddEdge("Arad", "Sibiu", 140);
  obj.AddEdge("Timisoara", "Lugoj", 111);
  obj.AddEdge("Lugoj", "Mehadia", 70);
  obj.AddEdge("Mehadia", "Dobreta", 75);
  obj.AddEdge("Dobreta", "Craiova", 120);
  obj.AddEdge("Sibiu", "Rimnicu Vilcea", 80);
  obj.AddEdge("Sibiu", "Fagaras", 99);
  obj.AddEdge("Rimnicu Vilcea", "Craiova", 146);
  obj.AddEdge("Rimnicu Vilcea", "Pitesti", 97);
  obj.AddEdge("Craiova", "Pitesti", 138);
  obj.AddEdge("Fagaras", "Bucharest", 211);
  obj.AddEdge("Pitesti", "Bucharest", 101);
  obj.AddEdge("Bucharest", "Giurgiu", 90);
  obj.AddEdge("Bucharest", "Urziceni", 85);
  obj.AddEdge("Urziceni", "Vaslui", 142);
  obj.AddEdge("Urziceni", "Hirsova", 98);
  obj.AddEdge("Vaslui", "Iasi", 92);
  obj.AddEdge("Iasi", "Neamt", 87);
  obj.AddEdge("Hirsova", "Eforie", 86);

  obj.AddHeuristics("Bucharest", "Oradea", 380);
  obj.AddHeuristics("Bucharest", "Zerind", 374);
  obj.AddHeuristics("Bucharest", "Arad", 366);
  obj.AddHeuristics("Bucharest", "Timisoara", 329);
  obj.AddHeuristics("Bucharest", "Lugoj", 244);
  obj.AddHeuristics("Bucharest", "Mehadia", 241);
  obj.AddHeuristics("Bucharest", "Dobreta", 242);
  obj.AddHeuristics("Bucharest", "Sibiu", 253);
  obj.AddHeuristics("Bucharest", "Rimnicu Vilcea", 193);
  obj.AddHeuristics("Bucharest", "Craiova", 160);
  obj.AddHeuristics("Bucharest", "Fagaras", 178);
  obj.AddHeuristics("Bucharest", "Pitesti", 98);
  obj.AddHeuristics("Bucharest", "Giurgiu", 77);
  obj.AddHeuristics("Bucharest", "Urziceni", 80);
  obj.AddHeuristics("Bucharest", "Vaslui", 199);
  obj.AddHeuristics("Bucharest", "Iasi", 226);
  obj.AddHeuristics("Bucharest", "Neamt", 234);
  obj.AddHeuristics("Bucharest", "Hirsova", 151);
  obj.AddHeuristics("Bucharest", "Eforie", 161);
}