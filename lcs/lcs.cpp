#include <iostream>
#include <vector>
#include <string>

using namespace std;

size_t LCS(const string& X, const string& Y)
{
  if (X.size() == 0 || Y.size() == 0)
    return 0;
  vector<vector<size_t>> l;
  l.resize(X.size() + 1);
  for (size_t i = 0; i < l.size(); ++i)
    l[i].resize(Y.size() + 1, 0);
  // 动态规划求解.
  for (size_t i = 1; i <= X.size(); ++i)
    for (size_t j = 1; j <= Y.size(); ++j)
      if (X[i - 1] == Y[j - 1])
        l[i][j] = l[i - 1][j - 1] + 1;
      else if (l[i][j - 1] < l[i - 1][j])
        l[i][j] = l[i - 1][j];
      else
        l[i][j] = l[i][j - 1];
  size_t i = X.size() + 1;
  size_t j = Y.size() + 1;
  string Z;
  while (i > 0 && j > 0)
    if (X[i - 1] == Y[j - 1])
    {
      Z.push_back(X[i - 1]);
      --i;
      --j;
    }
    else if (l[i][j - 1] < l[i - 1][j])
      --i;
    else
      --j;
  // 逆向打印Z.
  for (auto iter = Z.crbegin(); iter != Z.crend(); ++iter)
    cout << *iter;
  cout << endl;
  return l.back().back();
}

int main()
{
  cout << LCS("Algorithm", "AlphaGo") << endl;
  cout << LCS("BDCABA", "ABCBDAB") << endl;
  return 0;
}
