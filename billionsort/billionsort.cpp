#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

int main()
{
  // 计时开始.
  double start_t = clock();

  std::vector<double> V(1000000000);  // 10亿个数, 需要7.5GB内存.
  // 利用随机数生成器生成0.0到1.0之间的实数.
  std::default_random_engine generator(time(NULL));
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  for (size_t i = 0; i < V.size(); ++i)
    V[i] = distribution(generator);
  // 对10亿个随机数排序.
  sort(V.begin(), V.end());

  // 计时结束并输出时间.
  double end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60) << " minutes" << std::endl;

  return 0;
}

