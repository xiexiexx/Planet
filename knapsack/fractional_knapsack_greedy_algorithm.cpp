#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct gold {
  int id;
  double value;
  double weight;
};

int main()
{
  vector<gold> G = {{3, 120, 30}, {1, 60, 10}, {2, 100, 20}};
  // 按照价值/重量从大到小排序.
  sort(G.begin(), G.end(), [](const gold& x, const gold& y)
      { return x.value / x.weight > y.value / y.weight; });
  // 背包重量上限W.
  double W = 50;
  size_t m;
  double total = 0;
  for (m = 0; m < G.size() && total < W; ++m)
    total += G[m].weight;
  vector<gold> knapsack;
  if (m > 0)
  {
    knapsack.resize(m);
    for (size_t i = 0; i < m; ++i)
      knapsack[i] = G[i];
    // 末尾修正比例.
    double f = 1 - (total - W) / knapsack.back().weight;
    knapsack.back().weight *= f;
    knapsack.back().value *= f;
  }
  for (const auto& x : knapsack)
    cout << x.id << " " << x.value << " " << x.weight << endl;
  return 0;
}
