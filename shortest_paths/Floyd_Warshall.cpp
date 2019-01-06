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
  size_t V = WG.size();
  // 初始化path矩阵数据.
  path.resize(V);
  for (size_t u = 0; u < V; u++)
  {
    path[u].resize(V);
    for (size_t v = 0; v < V; v++)
      path[u][v] = {u, WG[u][v]};
  }
  // 依次计算k-最短路径, 每次计算更新path矩阵,
  // 也就是根据需要将从u到v的路径后半段变为从k到v的路径.
  for (size_t k = 0; k < V; k++)
    for (size_t u = 0; u < V; u++)
      for (size_t v = 0; v < V; v++)
        if (path[u][k].weight + path[k][v].weight < path[u][v].weight)
          path[u][v] = {path[k][v].vertex,
                        path[u][k].weight + path[k][v].weight};
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
  return 0;
}
