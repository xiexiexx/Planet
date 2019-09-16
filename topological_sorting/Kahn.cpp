#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using graph = vector<vector<size_t>>;

void Kahn(const graph& G)
{
  vector<size_t> in_degree(G.size(), 0);
  for (size_t u = 0; u < G.size(); ++u)
    for (const auto& v : G[u])
      ++in_degree[v];
  queue<size_t> Q;
  for (size_t v = 0; v < in_degree.size(); ++v)
    if (in_degree[v] == 0)
      Q.push(v);
  while (!Q.empty())
  {
    size_t u = Q.front();
    Q.pop();
    cout << u << ' ';
    for (const auto& v : G[u])
      if (--in_degree[v] == 0)
        Q.push(v);
  }
}

int main()
{
  graph G = {{1, 2}, {}, {4}, {2}, {}, {1}};
  Kahn(G);
  return 0;
}
