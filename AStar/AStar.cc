#include "AStar.h"
#include <queue>
#include <set>
using std::pair;
using std::priority_queue;
using std::set;

namespace AI_assignment {

AStar::AStar() {}

void AStar::AddNode(string name) {
  nodes.insert(pair<string, Node>(name, Node({name})));
}

void AStar::AddEdge(string from, string to, int distance) {
  nodes[from].distance.insert(pair<string, int>(to, distance));
  nodes[from].neighbour.push_back(to);
  nodes[to].distance.insert(pair<string, int>(from, distance));
  nodes[to].neighbour.push_back(from);
}

void AStar::AddHeuristics(string from, string to, int distance) {
  nodes[from].heuristics.insert(pair<string, int>(to, distance));
}

int AStar::GetShortestDistance(string from, string to, list<string>& path) {
  if (from == to) return 0;
  
  Node &start = nodes[from], &end = nodes[to];

  for (auto it = nodes.begin(); it != nodes.end(); ++it) {
    if (it->first == from) continue;
    it->second.heuristics[to] =
        start.heuristics[to] - start.heuristics[it->first];
  }

  priority_queue<Cost> pq;
  list<Cost> result;
  set<string> used({from});
  int distance = 0;

  for (auto it = start.neighbour.begin(); it != start.neighbour.end(); ++it) {
    Node& node = nodes[*it];
    pq.push(Cost({from, *it, node.distance[from] + node.heuristics[to]}));
  }

  while (!pq.empty()) {
    Cost top = pq.top();
    result.push_back(top);
    pq.pop();

    Node& node = nodes[top.node];
    for (auto it = node.neighbour.begin(); it != node.neighbour.end(); ++it) {
      if (used.find(*it) != used.end()) continue;
      used.insert(*it);
      Node& neighbour = nodes[*it];
      if (*it == to) {
        int tmp = node.distance[from] + node.distance[*it];
        distance = distance > 0 ? std ::min(tmp, distance) : tmp;
        break;
      }
      neighbour.distance[from] = node.distance[from] + node.distance[*it];
      pq.push(Cost(
          {node.name, *it, neighbour.distance[from] + start.heuristics[*it]}));
    }
    if (distance > 0) break;
  }

  path.clear();
  string index = result.back().node;
  path.push_front(index);
  index = result.back().from;
  path.push_front(index);
  while (index != from) {
    for (auto each : result) {
      if (each.node == index) {
        index = each.from;
        path.push_front(index);
        break;
      }
    }
  }
  return distance;
}
}  // namespace AI_assignment