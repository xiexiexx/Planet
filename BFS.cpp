#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

using graph = vector<vector<size_t>>;

struct vertex {
  bool discovered;
  size_t level;
  size_t parent;
};

void BFS(const graph& G, size_t s)
{
  if (s > G.size())
    return;
  vector<vertex> A(G.size());
  for (size_t i = 0; i < A.size(); ++i)
    A[i] = {false, (size_t) -1, i};
  A[s].discovered = true;
  A[s].level = 0;
  queue<size_t> Q;
  stack<size_t> R;
  Q.push(s);
  while (!Q.empty())
  {
    size_t u = Q.front();
    cout << u << ' ';
    R.push(u);
    for (const auto& v : G[u])
      if (!A[v].discovered)
      {
        A[v] = {true, A[u].level + 1, u};
        Q.push(v);
      }
    Q.pop();
  }
  cout << endl;
  for (auto& x : A)
    x.discovered = false;
  while (!R.empty())
  {
    size_t v = R.top();
    R.pop();
    if (!A[v].discovered)
    {
      while (A[v].parent != v)
      {
        cout << v << ' ';
        A[v].discovered = true;
        v = A[v].parent;
      }
      cout << v << endl;
      A[v].discovered = true;
    }
  }
}

int main()
{
  graph G = {{}, {0, 2}, {0, 4}, {2}, {2, 3}};
  BFS(G, 1);
  return 0;
}
