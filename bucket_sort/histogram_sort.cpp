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
  size_t E = 10;  // 每个桶中期望元素个数.
  std::vector<size_t> C(V.size() / E + 1, 0);     // 使用计数方法.
  std::vector<double> B(V.size());                // 另一种形式的桶.
  // 对每个桶的元素进行计数.
  for (const auto& x : V)
    ++C[x * (V.size() / E) + 1];
  // 指示每个桶的起始位置.
  for (size_t i = 1; i < C.size(); ++i)
    C[i] += C[i - 1];
  // 将V中元素分配到不同的桶中.
  for (const auto& x : V)
    B[C[x * (V.size() / E)]++] = x;
  // 对不同的桶进行排序, 区间为[left, right).
  auto left = B.begin();
  for (size_t i = 1; i < C.size(); ++i)
  {
    auto right = B.begin() + C[i - 1];
    std::sort(left, right);
    left = right;
  }
  // 利用交换将数据放回原向量中.
  V.swap(B);
  // 排序计时结束并输出时间.
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60)
            << " minutes" << std::endl;

  return 0;
}
