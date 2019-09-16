#include <iostream>
#include <vector>

using namespace std;

int look_up(vector<vector<int>>& m, const vector<int>& p, size_t i, size_t j)
{
  // 要求i <= j的前提条件.
  if (m[i][j] != -1)
    return m[i][j];
  if (i == j)
    return 0;
  else
  {
    // 此处必然有i < j, 先赋m[i][j]的初值.
    m[i][j] = look_up(m, p, i, i) + look_up(m, p, i + 1, j)
            + p[i - 1] * p[i] * p[j];
    for (size_t k = i + 1; k < j; ++k)
    {
      int cost = look_up(m, p, i, k) + look_up(m, p, k + 1, j)
               + p[i - 1] * p[k] * p[j];
      if (cost < m[i][j])
        m[i][j] = cost;
    }
  }
  return m[i][j];
}

int memoized_matrix_chain(const vector<int>& p)
{
  if (p.size() <= 1)
    return 0;
  size_t n = p.size() - 1;
  vector<vector<int>> m(n + 1);
  for (size_t i = 1; i < m.size(); ++i)
    m[i].resize(n + 1, -1);
  return look_up(m, p, 1, n);
}

int main()
{
  // 矩阵尺寸数组.
  vector<int> p = {30, 35, 15, 5, 10, 20, 25};
  cout << "最少乘法次数: " << memoized_matrix_chain(p) << endl;
  return 0;
}
