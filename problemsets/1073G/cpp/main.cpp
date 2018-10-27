#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct Query {
  Query(std::size_t k, std::size_t l) : k(k), l(l) {}
  std::size_t k;
  std::size_t l;
  std::vector<int> a;
  std::vector<int> b;
}; // struct Query

struct ProblemInfo {
  ProblemInfo(std::size_t n, std::size_t q, std::string_view s) : n(n), q(q), s(s) {}
  std::size_t n;
  std::size_t q;
  std::string s;
  std::vector<Query> queries;
}; // struct ProblemInfo

ProblemInfo createProblemInfo() {
  std::size_t n, q;
  std::string s;
  std::cin >> n >> q >> s;
  ProblemInfo pi(n, q, s);
  for (std::size_t i  = 0; i  < pi.q; ++i) {
    std::size_t k, l;
    std::cin >> k >> l;
    Query q(k, l);
    for (std::size_t j = 0; j < k; ++j) {
      int a;
      std::cin >> a;
      q.a.push_back(a);
    }

    for (std::size_t j = 0; j < l; ++j) {
      int b;
      std::cin >> b;
      q.b.push_back(b);
    }

    pi.queries.push_back(q);
  }
  return pi;
}

int main() {
  createProblemInfo();
  return 0;
}
