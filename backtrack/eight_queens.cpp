#include <iostream>
#include <vector>

using namespace std;

size_t m = 0;
const int n = 8;
void backtrack(vector<int>& X, int k = 0)
{
  if (k == n)
  {
    for (const auto& c : X)
      cout << c << ' ';
    cout << endl;
    ++m;
  }
  else
    for (int i = 0; i < n; ++i)
    {
      bool safe = true;
      for (int j = 0; j < k; ++j)
        if (X[j] == i || X[j] - i == j - k || X[j] - i == k - j)
          safe = false;
      if (safe)
      {
        X[k] = i;
        backtrack(X, k + 1);
      }
    }
}

int main()
{
  vector<int> Q(n);
  backtrack(Q);
  cout << "解法共有" << m << "种"<< endl;
  return 0;
}
