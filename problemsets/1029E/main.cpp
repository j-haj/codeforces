#include <iostream>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define UNUSED(x) \
  do {            \
    (void)x;      \
  } while (false);

/**
 * Grab input edges and return them as a vector of pairs.
 *
 * @return a vector of int pairs representing edges.
 */
std::vector<std::pair<int, int>> get_input() {
  int n_lines;
  std::cin >> n_lines;
  std::vector<std::pair<int, int>> edges(n_lines - 1);
  for (int i = 0; i < n_lines - 1; ++i) {
    int x, y;
    std::cin >> x >> y;
    edges[i] = std::make_pair(x, y);
  }
  return edges;
}

std::unordered_map<int, std::unordered_set<int>> build_graph(const std::vector<std::pair<int, int>>& edges) {
  std::unordered_map<int, std::unordered_set<int>> graph;
  for (const auto& p : edges) {
    graph[p.first].insert(p.second);
  }
  return graph;
}

/**
 * Finds the minimum number of edges needed such that every vertex is at most 2
 * edges from vertex 1.
 *
 * @param edges a vector of edges
 * @return the min number of edges required to be added
 */
int find_min_edges(const std::vector<std::pair<int, int>>& edges) {
  auto graph = build_graph(edges);
  struct Node {
    int depth;
    int value;
  };

  std::stack<Node> node_tracker;
  int edge_count = 0;
  int depth = 0;
  node_tracker.push(Node{0, 1});
  while (!node_tracker.empty()) {
    auto node = node_tracker.top();
    node_tracker.pop();
    bool has_children = (graph.find(node.value) == graph.end()) ? false : true;
    if (has_children) {
      for (const auto e : graph[node]) {
        node_tracker.push(e);      
      }
      ++depth;
      continue;
    }
    if (depth > 2) edge_count += depth - 2;
    --depth;
  }
  return edge_count;
}

int main(int argc, char** argv) {
  UNUSED(argc);
  UNUSED(argv);
  auto edges = get_input();
  for (const auto& p : edges) {
    std::cout << "(" << p.first << ", " << p.second << ")\n";
  }
  return 0;
}
