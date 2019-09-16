#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

using graph = vector<vector<size_t>>;

size_t find_longest(const graph& G, size_t s)
{
  vector<size_t> A(G.size(), (size_t) -1);
  A[s] = 0;
  size_t level = 0;
  queue<size_t> Q;
  Q.push(s);
  while (!Q.empty())
  {
    size_t u = Q.front();
    for (const auto& v : G[u])
      if (A[v] == (size_t) -1)
      {
        A[v] = A[u] + 1;
        level = A[v];
        Q.push(v);
      }
    Q.pop();
  }
  return level;
}

int main()
{
  graph G = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
  size_t diameter = 0;
  for (size_t s = 0; s < G.size(); ++s)
  {
    size_t level = find_longest(G, s);
    if (level > diameter)
      diameter = level;
  }
  cout << diameter << endl;
  return 0;
}
