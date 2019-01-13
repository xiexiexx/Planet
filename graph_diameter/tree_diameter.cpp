#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

using graph = vector<vector<size_t>>;

void find_last(const graph& G, size_t s, size_t& last, size_t& level)
{
  if (s > G.size())
    return;
  vector<size_t> A(G.size(), (size_t) -1);
  A[s] = 0;
  queue<size_t> Q;
  Q.push(s);
  while (!Q.empty())
  {
    last = Q.front();
    for (const auto& v : G[last])
      if (A[v] == (size_t) -1)
      {
        A[v] = A[last] + 1;
        Q.push(v);
      }
    Q.pop();
  }
  level = A[last];
}

int main()
{
  graph G = {{1, 2, 3, 4}, {0}, {0}, {0}, {0}};
  size_t s = 0;
  size_t t;
  size_t level;
  find_last(G, s, t, level);
  find_last(G, t, s, level);
  cout << level << endl;
  return 0;
}
