#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const double POSITIVE_INFINITY = numeric_limits<double>::infinity();

struct vertex_information {
  size_t vertex;
  double weight;
};

bool Bellman_Ford_Moore(const vector<vector<vertex_information>>& WG, size_t s,
                        vector<vertex_information>& path)
{
  size_t V = WG.size();
  path.resize(V);
  for (auto& x : path)
    x = {s, POSITIVE_INFINITY};
  path[s].weight = 0;
  vector<size_t> L(V, 0);
  queue<size_t> Q;
  // 初始存入顶点s, 其迭代层次为1.
  Q.push(s);
  L[s] = 1;
  // 逐步迭代求最短路径长度, 至多V - 1次.
  while (!Q.empty())
  {
    // 队首元素对应顶点为u.
    size_t u = Q.front();
    // 迭代层次超过V, 必然存在负环.
    if (L[u] > V)
      return false;
    Q.pop();
    // 必须提前保留这个层次的边界值, 因为有可能存在自边. 减1的目的是为了区别于当前队列的层次.
    size_t bound = L[u]--;
    for (const auto& x : WG[u])
      if (path[u].weight + x.weight < path[x.vertex].weight)
      {
        // 为方便表述, 将当前所处理顶点简记为v.
        size_t v = x.vertex;
        path[v] = {u, path[u].weight + x.weight};
        // 若v不在队列中则入队, 注意迭代层次是bound的下一层次.
        if (L[v] < bound)
        {
          Q.push(v);
          L[v] = bound + 1;
        }
      }
  }
  return true;
}

int main()
{
  vector<vector<vertex_information>> WG = {
    {{1, 6}, {3, 7}},
    {{2, 5}, {3, 8}, {4, -4}},
    {{1, -2}},
    {{2, -3}, {4, 9}},
    {{0, 2}, {2, 7}}
  };
  size_t s = 0;
  vector<vertex_information> path(WG.size());
  bool has_shortest_path = Bellman_Ford_Moore(WG, s, path);
  if (has_shortest_path)
  {
    for (const auto& x : path)
      cout << x.weight << ' ';
    cout << endl;
  }
  return 0;
}
