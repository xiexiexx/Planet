#include <iostream>
#include <vector>
#include <parallel/algorithm>
#include <random>
#include <ctime>
#include <chrono>

// 需要gcc 9以上版本并安装OpenMP.
// 编译指令: g++-9 -std=c++17 -fopenmp -O3

int main()
{
  double start_t, end_t;  // 计时器.

  // 内存分配计时开始.
  start_t = clock();
  std::vector<double> V(1000000000);  // 10亿个数, 至少需要7.5GB内存.
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

  // 排序计时开始, 多核并行计算如果用clock()会累计每个核的计算时间, 所以改用chrono.
  const auto p_start = std::chrono::system_clock::now();
  // 对10亿个随机数以并行算法排序.
  __gnu_parallel::sort(V.begin(), V.end());
  // 排序计时结束并输出时间.
  const auto p_end = std::chrono::system_clock::now();
  std::cout << (std::chrono::duration<double>(p_end - p_start).count() / 60)
            << " minutes" << std::endl;

  return 0;
}
