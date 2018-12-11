#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const double POSITIVE_INFINITY = numeric_limits<double>::max();

// 按照直观习惯, 次序是先写顶点后写权重. 当然直接用pair也可以, 但不够清晰.
struct neighbor_information {
  size_t vertex;
  double weight;
};

// 必须定义比较准则才能使用neighbor_information集合.
struct cmp_neighbor_weight_greater {
	bool operator()(const neighbor_information& a,
                  const neighbor_information& b) const
	{
    // 利用pair的字典序, 这样会少写很多判断, 这里以weight为主, 注意pair定义略有不同.
    using P = pair<double, size_t>;
    // 难点在于先要对weight分大于、小于和等于三种情况，等于情况下还得继续处理vertex.
    return P(a.weight, a.vertex) > P(b.weight, b.vertex);
    // 实际上由于这里可以使用==判断, 而vertex又是唯一的, 所以也可以这样写:
    /*
    return (a.weight == b.weight ? a.vertex > b.vertex : a.weight > b.weight);
    */
    // 上述写法类似于字符串比较大小, 先找到不相等的位置.
    // 但是一般情况下如果只有<关系, 还是得分三种情况讨论.
	}
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
  // 尚未寻找到的顶点放到优先级队列里.
  priority_queue<neighbor_information, vector<neighbor_information>,
                 cmp_neighbor_weight_greater> PQ;
  // 初始化优先级队列.
  PQ.push({s, length[s]});
  for (size_t i = 0; i < V; i++)
  {
    // 去除已处理过的顶点.
    while (length[PQ.top().vertex] < PQ.top().weight)
        PQ.pop();
    // 每次在未找到的顶点集合中, 寻找以s为起点的路径长度最短的顶点.
    // 设本次所找到的顶点为u, 对应路径长度为min.
    double min = PQ.top().weight;
    size_t u = PQ.top().vertex;
    PQ.pop();
    // 以u的邻接表为依据更新相关数据.
    for (const auto& neighbor : WG[u])
      if (length[u] + neighbor.weight < length[neighbor.vertex])
      {
        // 为方便表述, 将当前所处理顶点为neighbor.vertex简记为v.
        size_t v = neighbor.vertex;
        // 若lenght[u] + w(u, v) < length[v],
        // 则更新path[v]和length[v].
        path[v] = u;
        length[v] = length[u] + neighbor.weight;
        // 放入优先级队列中.
        PQ.push({v, length[v]});
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
