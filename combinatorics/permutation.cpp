#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
void check(const vector<T>& S)
{
  // 可以加入最终解的测试, 这里为了方便仅输出整个向量.
  for (const auto& x : S)
    cout << x << ' ';
  cout << endl;
}

template <typename T>
void permute(vector<T>& S, size_t k = 0)
{
  if (k == S.size())
  {
    check(S);
    return;
  }
  for (size_t i = k; i < S.size(); ++i)
  {
    swap(S[k], S[i]);
    permute(S, k + 1);
    swap(S[i], S[k]);
  }
}

int main()
{
  vector<string> V = {"do", "care", "book", "apple"};

  cout << "递归生成所有排列:" << endl;
  permute(V);

  cout << "从逆字典序开始生成所有排列:" << endl;
  do {
    check(V);
  } while ( prev_permutation(V.begin(), V.end()) );
  next_permutation(V.begin(), V.end());
  cout << "从字典序开始生成所有排列:" << endl;
  do {
    check(V);
  } while ( next_permutation(V.begin(), V.end()) );

  return 0;
}
