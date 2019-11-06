#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  // 向量W之中的元素取自[l, r)区间, 且r - l不是很大.
  vector<int> W = {-4, 5, 6, 6, 6, 1};
  auto p = minmax_element(W.begin(), W.end());
  int l = *p.first;
  int r = *p.second + 1;
  size_t m = r - l;
  // 用于统计W中各种元素出现次数的向量C.
  vector<size_t> C(m, 0);
  // 基于偏移和下标快速统计W中每个元素x的出现次数, 并存于C[z - l]中.
  for (const auto& z : W)
    ++C[z - l];
  // 根据元素i出现的次数C[i]将其逐个放回W中.
  // 注意i从小到大增长, 可保证W有序.
  size_t x = 0;
  for (size_t i = 0; i < C.size(); ++i)
    while (C[i]-- > 0)
      W[x++] = i + l;
  for (const auto& z : W)
    cout << z << ' ';
  cout << endl;
  return 0;
}
