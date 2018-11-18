#include <iostream>
#include <vector>

using namespace std;

int recursive_cr(const vector<int>& p, size_t n)
{
  int opt = p[0];
  for (size_t i = 1; i <= n; ++i)
  {
    int value = p[i] + recursive_cr(p, n - i);
    if (value > opt)
      opt = value;
  }
  return opt;
}

int memoized_cr_aux(const vector<int>& p, vector<int>& r, size_t k)
{
  if (r[k] >= 0)
    return r[k];
  int opt = 0;
  for (size_t i = 1; i <= k; ++i)
  {
    int value = p[i] + memoized_cr_aux(p, r, k - i);
    if (value > opt)
      opt = value;
  }
  r[k] = opt;
  return opt;
}

int memoized_cr(const vector<int>& p, vector<int>& r, size_t n)
{
  for (size_t i = 0; i < r.size(); ++i)
    r[i] = -1;
  return memoized_cr_aux(p, r, n);
}

void bottom_up_cr(const vector<int>& p, vector<int>& r)
{
  r[0] = 0;
  for (size_t j = 1; j < r.size(); ++j)
  {
    int opt = p[j];
    for (size_t i = 1; i < j; ++i)
      if (p[i] + r[j - i] > opt)
        opt = p[i] + r[j - i];
    r[j] = opt;
  }
}

void extended_bottom_up_cr(const vector<int>& p, vector<int>& r,
                           vector<int>& s)
{
  for (size_t i = 0; i < s.size(); ++i)
    s[i] = i;
  r[0] = 0;
  for (size_t j = 1; j < r.size(); ++j)
  {
    int opt = p[j];
    for (size_t i = 1; i < j; ++i)
      if (p[i] + r[j - i] > opt)
      {
        opt = p[i] + r[j - i];
        s[j] = i;
      }
    r[j] = opt;
  }
}

int main()
{
  // 价格向量, 注意首项为0, 所有元素必须非负.
  vector<int> p = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  // 收入向量.
  vector<int> r(p.size());
  // 解向量.
  vector<int> s(p.size());

  // 递归方法计算结果并打印.
  cout << recursive_cr(p, p.size() - 1) << endl;
  // 备忘录方法计算结果和完整的收入向量并打印.
  cout << memoized_cr(p, r, p.size() - 1) << endl;
  for (size_t i = 0; i < r.size(); ++i)
    cout << r[i] << ' ';
  cout << endl;

  // 自底向上方法计算完整的收入向量并打印.
  bottom_up_cr(p, r);
  for (size_t i = 0; i < r.size(); ++i)
    cout << r[i] << ' ';
  cout << endl;

  // 自底向上方法计算完整的解向量并打印.
  extended_bottom_up_cr(p, r, s);
  for (size_t i = 0; i < s.size(); ++i)
  {
    size_t j = i;
    while (j > 0)
    {
      cout << s[j] << ' ';
      j -= static_cast<size_t>(s[j]);
    }
    cout << endl;
  }

  return 0;
}
