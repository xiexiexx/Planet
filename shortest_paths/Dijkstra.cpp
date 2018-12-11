#include <iostream>
#include <vector>
#include <set>

using namespace std;

const double POSITIVE_INFINITY = numeric_limits<double>::max();

struct neighbor_information {
  size_t v;
  double weight;
};

void Dijkstra(vector<vector<neighbor_information>>& WG, size_t s,
              vector<size_t>& path, vector<double>& length)
{
  size_t V = WG.size();
  // 顶点数为V, 我们需要保证path和length都是长为V的向量.
  if (path.size() != V || length.size() != V)
    return;
  // 初始化path向量, 其中所有元素初值均为s.
  for (auto& x : path)
    x = s;
  // 初始化length向量.
  // 暂时设所有length向量中的元素为正无穷大.
  for (auto& x : length)
    x = POSITIVE_INFINITY;
  // s位置路径长度初值为0, 这样还可让s最先被找到.
  length[s] = 0;
  // 尚未寻找到的顶点集合为NS.
  set<pair<double, size_t>> NS;
  // 顶点在集合NS中的位置存于vertex_iter中.
  vector<set<pair<double, size_t>>::iterator> vertex_position(V);
  for (size_t u = 0; u < V; u++)
    vertex_position[u] = NS.insert({length[u], u}).first;
  for (size_t i = 0; i < V; i++)
  {
    // 每次在未找到的顶点集合中, 寻找以s为起点的路径长度最短的顶点.
    // 设本次所找到的顶点为u, 对应路径长度为min.
    double min = NS.begin()->first;
    size_t u = NS.begin()->second;
    // u已找到, 将其从NS中删除.
    NS.erase(NS.begin());
    // 以u的邻接表为依据更新相关数据.
    for (const auto& neighbor : WG[u])
      if (length[u] + neighbor.weight < length[neighbor.v])
      {
        // 为方便表述, 将当前所处理顶点为neighbor.v简记为v.
        size_t v = neighbor.v;
        // 若lenght[u] + w(u, v) < length[v],
        // 则更新path[v]和length[v].
        path[v] = u;
        length[v] = length[u] + neighbor.weight;
        // 通过删除和重新插入改变NS中的相应取值并保存位置.
        NS.erase(vertex_position[v]);
        vertex_position[v] = NS.insert({length[v], v}).first;
      }
    }
}

int main()
{
  vector<vector<neighbor_information>> WG = {
    {{1, 10}, {3, 5}},
    {{2, 1}, {3, 2}},
    {{4, 4}},
    {{1, 3}, {2, 9}, {4, 2}},
    {{0, 7}, {2, 4}}
  };
  size_t s = 0;
  vector<size_t> path(WG.size());
  vector<double> length(WG.size());
  Dijkstra(WG, s, path, length);
  for (const auto& x : length)
    cout << x << ' ';
  cout << endl;
  return 0;
}
