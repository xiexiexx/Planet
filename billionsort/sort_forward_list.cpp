#include <iostream>
#include <forward_list>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>

int main()
{
  double start_t, end_t;  // 计时器.

  // 内存分配计时开始.
  start_t = clock();
  // 1亿个数, 需要3GB内存, 注意链表本身没有用到这么大空间. 另外, 换成list差别不大.
  std::forward_list<float> L(100000000);
  // 内存分配计时结束并输出时间.
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60) << " minutes" << std::endl;

  // 数据赋值计时开始.
  start_t = clock();
  // 利用随机数生成器生成0.0到1.0之间的实数.
  std::default_random_engine generator(time(NULL));
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  for (auto iter = L.begin(); iter != L.end(); ++iter)
    *iter = distribution(generator);
  // 数据赋值计时结束并输出时间.
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60) << " minutes" << std::endl;

  // 排序计时开始.
  start_t = clock();
  // 对10亿个随机数排序, 如果用数组时间也没什么太大差别.
  //L.sort();
  // 排序计时结束并输出时间.
  end_t = clock();
  std::cout << (end_t - start_t) / (CLOCKS_PER_SEC * 60) << " minutes" << std::endl;

  return 0;
}
