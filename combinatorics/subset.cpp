#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

template <typename T>
void check(const vector<T>& S, const vector<bool>& AUX)
{
  // 可以加入最终解的测试, 这里为了方便仅按照取值情况输出向量的当前子集.
  cout << "{ ";
  for (size_t i = 0; i < AUX.size(); ++i)
    if (AUX[i])
      cout << S[i] << ' ';
  cout << "}" << endl;
}

// 假设向量S中无重复元素.
template <typename T>
void subset(vector<T>& S, vector<bool>& AUX, size_t k = 0)
{
  if (k == S.size())
  {
    check(S, AUX);
    return;
  }
  AUX[k] = false;
  subset(S, AUX, k + 1);
  AUX[k] = true;
  subset(S, AUX, k + 1);
}

int main()
{
  vector<string> V = {"do", "care", "book", "apple"};
  vector<bool> AUX(V.size());
  cout << "递归生成所有子集:" << endl;
  subset(V, AUX);
  cout << "迭代生成所有子集:" << endl;
  size_t m = pow(2, V.size());
  vector<vector<size_t>> P(m);
  for (size_t i = 0; i < V.size(); ++i)
  {
    size_t half = m / 2;
    for (size_t j = 0; j < P.size(); ++j)
      if (j % m >= half)
        P[j].push_back(i);
    m = half;
  }
  for (const auto& S : P)
  {
    cout << "{ ";
    for (const auto& x : S)
      cout << V[x] << ' ';
    cout << " }" << endl;
  }
  cout << "以二进制生成所有子集:" << endl;
  m = pow(2, V.size());
  for (size_t i = 0; i < AUX.size(); ++i)
    AUX[i] = false;
  for (size_t i = 0; i < m; ++i)
  {
    check(V, AUX);
    for (size_t j = 0; j < AUX.size(); ++j)
    {
      if (!AUX[j])
      {
        AUX[j] = true;
        break;
      }
      AUX[j] = false;
    }
  }
  return 0;
}
