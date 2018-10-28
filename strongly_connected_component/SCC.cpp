#include <iostream>
#include <vector>
using namespace std;

using graph = vector<vector<size_t>>;

enum color { white, gray, black };

struct vertex {
  color status;
  pair<size_t, size_t> time;
  size_t parent;
};

void depth_first_search(const graph& G, vector<vertex>& A, vector<size_t>& F,
                        size_t u, size_t& counter)
{
  A[u].time.first = counter++;
  A[u].status = gray;
  for (auto& v : G[u])
    if (A[v].status == white)
    {
      A[v].parent = u;
      depth_first_search(G, A, F, v, counter);
    }
  A[u].time.second = counter++;
  A[u].status = black;
  F.push_back(u);
}

int main()
{
  graph G = {{1}, {2, 3}, {0}, {5}, {3}, {4}};
  vector<vertex> A(G.size());
  for (size_t i = 0; i < A.size(); ++i)
    A[i] = {white, {}, i};
  vector<size_t> R;
  R.reserve(G.size());
  size_t counter = 0;
  for (size_t u = 0; u < G.size(); ++u)
    if (A[u].status == white)
      depth_first_search(G, A, R, u, counter);
  graph GT(G.size());
  for (size_t u = 0; u < G.size(); ++u)
    for (const auto& v : G[u])
      GT[v].push_back(u);
  for (size_t i = 0; i < A.size(); ++i)
    A[i] = {white, {}, i};
  vector<size_t> W;
  W.reserve(G.size());
  counter = 0;
  for (auto iter = R.rbegin(); iter != R.rend(); ++iter)
    if (A[*iter].status == white)
      depth_first_search(GT, A, W, *iter, counter);
  for (auto& x : A)
    x.status = white;
  for (const auto& x : W)
    if (A[x].status == white)
    {
      size_t v = x;
      while (A[v].parent != v)
      {
        cout << v << ' ';
        A[v].status = black;
        v = A[v].parent;
      }
      cout << v << endl;
      A[v].status = black;
    }
  return 0;
}
