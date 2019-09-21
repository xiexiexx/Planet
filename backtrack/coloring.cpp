#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using graph = vector<vector<size_t>>;

size_t k;

bool solved;

void coloring(const graph& G, vector<size_t>& C, const vector<size_t>& P,
              size_t v = 0)
{
  if (v == G.size())
  {
    solved = true;
    for (size_t i = 0; i < C.size(); ++i)
      cout << "顶点" << i << "着色为" << C[i] << endl;
    return;
  }
  vector<bool> R(k, true);
  for (const auto& x : G[P[v]])
    if (C[x] != k)
      R[C[x]] = false;
  for (size_t i = 0; i < R.size(); ++i)
    if (R[i])
    {
      C[P[v]] = i;
      coloring(G, C, P, v + 1);
      if (solved)
        return;
    }
}

bool two_colorable(const graph& G, vector<size_t>& C)
{
  if (G.size() == 0)
    return true;
  enum color : size_t {red, blue, blank};
  for (auto& x : C)
    x = blank;
  queue<size_t> Q;
  Q.push(0);
  C[0] = red;
  while (!Q.empty())
  {
    size_t u = Q.front();
    Q.pop();
    for (const auto v : G[u])
      if (C[v] == blank)
      {
        C[v] = (C[u] == red) ? blue : red;
        Q.push(v);
      }
      else if (C[u] == C[v])
        return false;
  }
  return true;
}

int main()
{
  graph G = {{1, 3, 4, 5},
             {0, 2, 3},
             {1, 3, 4},
             {0, 1, 2, 4},
             {0, 2, 3, 5},
             {0, 4}};
  cin >> k;
  vector<size_t> C(G.size(), k);
  vector<size_t> P(G.size());
  for (size_t i = 0; i < G.size(); ++i)
    P[i] = i;
  sort(P.begin(), P.end(), [G](size_t a, size_t b)
      { return G[a].size() > G[b].size(); });
  solved = false;
  coloring(G, C, P);
  if (!solved)
    cout << "不能以" << k << "种颜色对该图着色!" << endl;
  if (!two_colorable(G, C))
    cout << "不能以两种颜色对该图着色!" << endl;
  return 0;
}
