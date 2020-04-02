#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

void simple_count(vector<int>& V)
{
  sort(V.begin(), V.end());
  for (size_t left = 0, right; left < V.size(); left = right)
  {
    for (right = left + 1; right < V.size(); ++right)
      if (V[right] != V[left])
        break;
    cout << V[left] << ": " << right - left << endl;
  }
}

void count(vector<int>& V)
{
  sort(V.begin(), V.end());
  size_t left, right;
  for (left = 0, right = 1; right < V.size(); ++right)
    if (V[right] != V[left])
    {
      cout << V[left] << ": " << right - left << endl;
      left = right;
    }
  if (V.size() > 0)
    cout << V[left] << ": " << right - left << endl;
}

void unique(vector<int>& V)
{
  // 因为必须判断V是否为空, 所以提前做可以节约时间.
  if (V.size() == 0)
    return;
  sort(V.begin(), V.end());
  size_t left = 0;
  for (size_t right = left + 1; right < V.size(); ++right)
    if (V[right] != V[left])
      V[++left] = V[right];
  // 注意空向量情况不加判断直接执行下面这句会出错.
  V.resize(++left);
}

template <typename T, typename U>
void unique_with_set(vector<T>& V, U& S)
{
  S.clear();
  for (const auto& x : V)
    S.insert(x);
  V.resize(S.size());
  copy(S.begin(), S.end(), V.begin());
  S.clear();
}

template <typename T>
void print_all(const T& S)
{
  for (const auto& x : S)
    cout << x << ' ';
  cout << endl;
}

int main()
{
  cout << "Example A: " << endl;
  vector<int> A = {7, 2, 3, 2, 5, 1, 1};
  count(A);
  unique(A);
  print_all(A);
  cout << "Example B: " << endl;
  vector<int> B = {-9};
  count(B);
  unique(B);
  print_all(B);
  cout << "Example C: " << endl;
  vector<int> C;
  count(C);
  unique(C);
  print_all(C);
  cout << "Example D: " << endl;
  vector<int> D = {1, 2, 1, 2, 1, 1, 1};
  vector<int> E = D;
  set<int> F;
  unordered_set<int> G;
  unique_with_set(D, F);
  print_all(D);
  cout << "Example E: " << endl;
  unique_with_set(E, G);
  print_all(E);
  return 0;
}
