#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

using graph = vector<vector<size_t>>;

enum color { white, gray, black };

struct vertex {
  color status;
  pair<size_t, size_t> time;
  size_t parent;
};

void depth_first_search(const graph& G, vector<vertex>& A,
                        size_t u, size_t& counter)
{
  A[u].time.first = counter++;
  A[u].status = gray;
  for (auto& v : G[u])
    if (A[v].status == white)
    {
      A[v].parent = u;
      depth_first_search(G, A, v, counter);
    }
  A[u].time.second = counter++;
  A[u].status = black;
}

void DFS(const graph& G, vector<vertex>& A)
{
  size_t counter = 0;
  for (size_t i = 0; i < A.size(); ++i)
    A[i] = {white, {}, i};
  for (size_t u = 0; u < G.size(); ++u)
    if (A[u].status == white)
      depth_first_search(G, A, u, counter);
}

int main()
{
  graph G = {{1, 3}, {2}, {3}, {1}, {2, 5}, {5}};
  vector<vertex> A(G.size());
  DFS(G, A);
  for (const auto& x : A)
    cout << x.time.first << ' ' << x.time.second << endl;
  return 0;
}
