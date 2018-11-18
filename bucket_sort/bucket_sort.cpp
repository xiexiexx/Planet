#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

int main()
{
  double start_t, end_t;  // 计时器.

  // 内存分配计时开始.
  start_t = clock();
  std::vector<double> V(1000000000);  // 10亿个数.
  // 内存分配计时结束并输出时间.
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60)
            << " minutes" << std::endl;

  // 数据赋值计时开始.
  start_t = clock();
  // 利用随机数生成器生成0.0到1.0之间的实数.
  std::default_random_engine generator(time(NULL));
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  for (size_t i = 0; i < V.size(); ++i)
    V[i] = distribution(generator);
  // 数据赋值计时结束并输出时间.
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60)
            << " minutes" << std::endl;

  // 排序计时开始.
  start_t = clock();
  size_t E = 20;  // 每个桶中期望元素个数.
  std::vector<std::vector<double>> B(V.size() / E); // 桶.
  for (auto& b : B)
    b.reserve(E);
  // 将V中元素分配到不同的桶中.
  for (const auto& x : V)
    B[x * B.size()].push_back(x);
  for (auto& b : B)
    std::sort(b.begin(), b.end());
  size_t i = 0;
  for (const auto& b : B)
    for (const auto& x : b)
      V[i++] = x;
  // 排序计时结束并输出时间.
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60)
            << " minutes" << std::endl;

  return 0;
}
