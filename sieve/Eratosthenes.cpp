#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
  const size_t n = 1000000000;
  // 统一赋值更快, 不要一开始区分奇偶分开赋值.
  vector<bool> P(n + 1, true);
  P[0] = P[1] = false;
  // P[0]和P[1]后续不作处理, 也可以不赋值. 另外, P[2]为true是筛法起点.

  /*
  这种涉及到取模运算(编译器已有位运算优化)分开赋值效果不好.
  for (size_t i = 3; i <= n; ++i)
    P[i] = i % 2 == 0 ? false : true;
  */

  size_t s = sqrt(n);
  for (size_t i = 2; i <= s; ++i)
    if (P[i])
      for (size_t j = i * i; j <= n; j += i)
        P[j] = false;
  // 有的解法根据P[j]从true到false的判断减去合数个数, 速度并不快.

  int m = 0;
  for (size_t i = 2; i <= n; ++i)
    if (P[i])
      ++m;
  cout << m << endl;

  return 0;
}
