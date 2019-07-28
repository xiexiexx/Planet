#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void check(const vector<T>& S, const vector<bool>& AUX)
{
  // 可以加入最终解的测试, 这里为了方便仅按照取值情况输出向量的当前子集.
  for (size_t i = 0; i < AUX.size(); ++i)
    if (AUX[i])
      cout << S[i] << ' ';
  cout << endl;
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
  return 0;
}
