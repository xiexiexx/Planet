#include <iostream>
#include <vector>

using namespace std;

const double POSITIVE_INFINITY = numeric_limits<double>::infinity();

struct vertex_information {
  size_t vertex;
  double weight;
};

void print_all(const vector<vector<vertex_information>>& path)
{
  for (const auto& x : path)
  {
    for (const auto& y : x)
      cout << y.vertex << ' ';
    cout << endl;
  }
  for (const auto& x : path)
  {
    for (const auto& y : x)
      cout << y.weight << ' ';
    cout << endl;
  }
}

void Floyd_Warshall(const vector<vector<double>>& WG,
                    vector<vector<vertex_information>>& path)
{
  size_t n = WG.size();
  // 初始化path矩阵数据.
  path.resize(n);
  for (size_t u = 0; u < n; ++u)
  {
    path[u].resize(n);
    // 条件表达式无法使用{}初始化列表.
    for (size_t v = 0; v < n; ++v)
      if (WG[u][v] < POSITIVE_INFINITY && u != v)
        path[u][v] = {u, WG[u][v]};
      else
        path[u][v] = {n, WG[u][v]};
  }
  // 依次计算k-最短路径, 每次计算更新path矩阵,
  // 也就是根据需要将从u到v的路径后半段变为从k到v的路径.
  for (size_t k = 0; k < n; ++k)
    for (size_t u = 0; u < n; ++u)
      for (size_t v = 0; v < n; ++v)
        if (path[u][k].weight + path[k][v].weight < path[u][v].weight)
          path[u][v] = {path[k][v].vertex,
                        path[u][k].weight + path[k][v].weight};
}

void print_path(const vector<vector<vertex_information>>& path,
                size_t u, size_t v, vector<size_t>& P)
{
  if (path[u][v].vertex == path.size())
    return;
  P.resize(0);
  while (v != u)
  {
    P.push_back(v);
    v = path[u][v].vertex;
  }
  P.push_back(v);
  for (auto riter = P.rbegin(); riter != P.rend(); ++riter)
    cout << *riter << ' ';
  cout << endl;
}

int main()
{
  vector<vector<double>> WG = {
    {0, 3, 8, POSITIVE_INFINITY, -4},
    {POSITIVE_INFINITY, 0, POSITIVE_INFINITY, 1, 7},
    {POSITIVE_INFINITY, 4, 0, POSITIVE_INFINITY, POSITIVE_INFINITY},
    {2, POSITIVE_INFINITY, -5, 0, POSITIVE_INFINITY},
    {POSITIVE_INFINITY, POSITIVE_INFINITY, POSITIVE_INFINITY, 6, 0}
  };
  vector<vector<vertex_information>> path(WG.size());
  Floyd_Warshall(WG, path);
  print_all(path);
  // 查询路径辅助向量P.
  vector<size_t> P;
  P.reserve(WG.size());
  print_path(path, 4, 2, P);
  return 0;
}
