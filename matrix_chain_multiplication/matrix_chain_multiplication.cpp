#include <iostream>
#include <vector>

using namespace std;

void print_optimal_solution(const vector<vector<size_t>>& s, size_t i, size_t j)
{
  if (i == j)
    cout << "A" << i;
  else
  {
    cout << "(";
    print_optimal_solution(s, i, s[i][j]);
    print_optimal_solution(s, s[i][j] + 1, j);
    cout << ")";
  }
}

int main()
{
  // 矩阵尺寸数组.
  vector<int> p = {30, 35, 15, 5, 10, 20, 25};
  if (p.size() <= 1)
    return 0;

  // 共有n个矩阵.
  size_t n = p.size() - 1;
  // 二维向量, 但是下标0位置不用.
  vector<vector<int>> m(n + 1);     // 矩阵最优乘法次数.
  vector<vector<size_t>> s(n + 1);  // 最优划分位置.
  // 二维向量每维的尺寸指定为n + 1并赋初值.
  for (size_t i = 1; i <= n; ++i)
  {
    m[i].resize(n + 1, 0);
    s[i].resize(n + 1, i);
  }

  //动态规划求解.
  for (size_t d = 1; d < n; ++d)
    for (size_t i = 1; i + d <= n; ++i)
    {
      m[i][i + d] = m[i][i] + m[i + 1][i + d] + p[i - 1] * p[i] * p[i + d];
      // s[i][i + d]已经赋过初值i.
      for (size_t k = i + 1; k < i + d; ++k)
      {
        int cost = m[i][k] + m[k + 1][i + d] + p[i - 1] * p[k] * p[i + d];
        if (cost < m[i][i + d])
        {
          m[i][i + d] = cost;
          s[i][i + d] = k;
        }
      }
    }
  cout << "最少乘法次数: " << m[1][n] << endl;
  print_optimal_solution(s, 1, n);
  cout << endl;
  return 0;
}
