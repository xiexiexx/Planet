#include <iostream>
#include <vector>

using namespace std;

const double POSITIVE_INFINITY = numeric_limits<double>::infinity();

struct vertex_information {
  size_t vertex;
  double weight;
};

void sink(vector<vertex_information>& H, size_t i, vector<size_t>& vertex_index)
{
  // 暂存H[i]数据, 注意后续操作是和H[0]比较.
  H[0] = H[i];
  // 结点的右孩子编号.
  size_t rChildNo = 2 * i + 1;
  // 右孩子存在(即左右孩子均存在)时的下沉.
  while (rChildNo < H.size())
  {
    // MIN为较小结点的编号, 注意其初值为0.
    size_t MIN = 0;
    // 右孩子较小则MIN换为右孩子编号.
    if (H[rChildNo].weight < H[MIN].weight)
      MIN = rChildNo;
    // 左孩子较小则MIN换为左孩子编号.
    if (H[rChildNo - 1].weight < H[MIN].weight)
      MIN = rChildNo - 1;
    // 断言: 不需要交换则下沉结束.
    if (MIN == 0)
      break;
    // 需要交换时先将较小的孩子存于i位置.
    H[i] = H[MIN];
    vertex_index[H[i].vertex] = i;
    // 继续向下判断.
    i = MIN;
    rChildNo = 2 * i + 1;
  }
  // 处理特殊情况: 最后仅存在左孩子且需要继续下沉.
  if (rChildNo == H.size() && H[rChildNo - 1].weight < H[0].weight)
  {
    // 需要交换时先将左孩子存于i位置.
    H[i] = H[rChildNo - 1];
    vertex_index[H[i].vertex] = i;
    // 获得最终停留位置.
    i = rChildNo - 1;
  }
  // 将初始结点处的数据存于下沉操作最终停留的位置.
  H[i] = H[0];
  vertex_index[H[i].vertex] = i;
}

/*
其实路径长度不仅在path中存放, 堆里也存放里一份副本.
但是堆最终状态比较杂乱, 所以这种冗余还是有必要的.
*/

void swim(vector<vertex_information>& H, size_t i, vector<size_t>& vertex_index)
{
  // 在H[0]处设置哨兵以终止循环, 并保存初始结点i处的数据.
  H[0] = H[i];
  // 如果H[0]小于i位置的父亲结点值H[i / 2]则不断让i位置上浮,
  // 但初始结点处的数据暂不处理, 其值仍存于H[0].
  while (H[0].weight < H[i / 2].weight)
  {
    H[i] = H[i / 2];
    vertex_index[H[i].vertex] = i;
    i = i / 2;
  }
  // 将初始结点处的数据存于上浮操作最终停留的位置.
  H[i] = H[0];
  vertex_index[H[i].vertex] = i;
}

void Dijkstra(vector<vector<vertex_information>> & WG, size_t s,
              vector<vertex_information>& path)
{
  size_t V = WG.size();
  path.resize(V);
  for (auto& x : path)
    x = {s, POSITIVE_INFINITY};
  path[s].weight = 0;
  // 堆H用于寻找最小权重的顶点, 注意首位置用于哨兵, 长度是V + 1.
  vector<vertex_information> H(V + 1);
  vector<size_t> vertex_index(V);
  for (size_t i = 1; i < H.size(); ++i)
  {
    H[i] = {i - 1, path[i - 1].weight};
    vertex_index[i - 1] = i;
  }
  swim(H, vertex_index[s], vertex_index);
  for (size_t i = 0; i < V; ++i)
  {
    size_t u = H[1].vertex;
    H[1] = H.back();
    sink(H, 1, vertex_index);
    H.pop_back();
    for (const auto& neighbor : WG[u])
      if (path[u].weight + neighbor.weight < path[neighbor.vertex].weight)
      {
        size_t v = neighbor.vertex;
        path[v] = {u, path[u].weight + neighbor.weight};
        H[vertex_index[v]].weight = path[v].weight;
        swim(H, vertex_index[v], vertex_index);
      }
  }
}

int main()
{
  vector<vector<vertex_information>> WG = {
    {{1, 10}, {3, 5}},
    {{2, 1}, {3, 2}},
    {{4, 4}},
    {{1, 3}, {2, 9}, {4, 2}},
    {{0, 7}, {2, 4}},
    {}
  };
  size_t s = 0;
  // 更精简的写法, 将路径中的上一顶点和路径长度存在一起.
  vector<vertex_information> path(WG.size());
  Dijkstra(WG, s, path);
  vector<size_t> real_path;
  real_path.reserve(WG.size());
  for (size_t i = 0; i < path.size(); ++i)
  {
    cout << s << " to " << i << ", ";
    if (path[i].weight == POSITIVE_INFINITY)
    {
      cout << "Unreachable => Length: POSITIVE_INFINITY." << endl;
      continue;
    }
    real_path.resize(0);
    size_t x = i;
    while (x != s)
    {
      real_path.push_back(x);
      x = path[x].vertex;
    }
    if (real_path.size() != 0)
    {
      cout << "Path: " << s << ' ';
      for (auto riter = real_path.rbegin(); riter != real_path.rend(); ++riter)
        cout << *riter << ' ';
    }
    else
      cout << "Empty path ";
    cout << "=> Length: " << path[i].weight << '.';
    cout << endl;
  }
  return 0;
}
