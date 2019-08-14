#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

int main()
{
  double start_t, end_t;  // 计时器.

  const size_t n = 1000000000;
  std::vector<size_t> V(n);

  // 数据取值范围为[0, n * f), f越小计数排序效果越好, 若内存不够可将f改小一点.
  const double f = 2;
  const size_t m = n * f;

  // 利用随机数生成器生成[0, m)之间的自然数.
  std::default_random_engine generator(time(NULL));
  std::uniform_int_distribution<size_t> distribution(0, m - 1);
  for (size_t i = 0; i < V.size(); ++i)
    V[i] = distribution(generator);

  std::vector<size_t> W(V.begin(), V.end());

  // 常规sort函数排序.
  start_t = clock();
  std::sort(V.begin(), V.end());
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60)
            << " minutes" << std::endl;

  // 计数排序.
  start_t = clock();
  std::vector<size_t> C(m, 0);
  for (const auto& z : W)
    ++C[z];
  size_t x = 0;
  for (size_t i = 0; i < C.size(); ++i)
    while (C[i]-- > 0)
      W[x++] = i;
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60)
            << " minutes" << std::endl;

  return 0;
}
