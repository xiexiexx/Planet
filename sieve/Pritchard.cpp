#include <iostream>
#include <vector>

using namespace std;

int main()
{
  const size_t n = 1000000000;
  // C代表合数判定.
  vector<bool> C(n + 1, false);
  C[0] = C[1] = true;
  // 对于int范围以内的素数, size_t全部换用int会快很多, 因为有乘法和取模运算.
  vector<size_t> P(n / 2);
  size_t m = 0;

  for (size_t i = 2; i <= n / 2; ++i)
  {
    // 这种否定的写法有利于分支预测.
    if (!C[i])
      P[m++] = i;
    /*
    循环判断直接使用P[j] * i <= n有溢出的可能性,
    但是和循环体的中的P[j] * i一致有利于编译器优化,
    改为P[j] <= n / i速度会略慢, 不过会更安全.
    */
    for (size_t j = 0; j < m && P[j] * i <= n; ++j)
    {
      C[P[j] * i] = true;
      if (i % P[j] == 0)
        break;
    }
  }

  for (size_t i = n / 2 + 1; i <= n; ++i)
    if (!C[i])
      ++m;
  cout << m << endl;
  return 0;
}
