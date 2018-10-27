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

std::unordered_map<int, std::unordered_set<int>> build_graph(
    const std::vector<std::pair<int, int>>& edges) {
  std::unordered_map<int, std::unordered_set<int>> graph;
  for (const auto& p : edges) {
    graph[p.first].insert(p.second);
    graph[p.second].insert(p.first);
  }
  return graph;
}

struct Node {
  int number;
  int depth;
};

void generate_depth_list(
    const std::unordered_map<int, std::unordered_set<int>>& graph,
    std::vector<Node>& node_list, int current_node, int prior_node, int depth) {
  const auto neighbors = graph.at(current_node);
  for (const auto node : neighbors) {
    if (node == prior_node) continue;
    node_list.push_back(Node{node, depth});
    generate_depth_list(graph, node_list, node, current_node, depth + 1);
  }
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
  std::vector<Node> depth_list;
  generate_depth_list(graph, depth_list, 1, -1, 0);
  std::sort(depth_list.begin(), depth_list.end(),
            [](const Node& x, const Node& y) { return x.depth > y.depth; });
  std::unordered_set<int> node_set;
  for (const auto p : graph) {
    node_set.insert(p.first);
  }

  int connections = 0;
  for (const auto node : depth_list) {
    if (node.depth <= 2) break;

    // Get connected node
    assert(graph[node.number].size() == 1);
    int parent;
    for (const auto x : graph.at(node.number)) {
      parent = x;
    }
  }

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
