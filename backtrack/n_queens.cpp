#include <iostream>

using namespace std;

size_t m;
const int n = 16;
size_t P[n];
bool C[n];
bool S[2 * n + 1];
bool D[2 * n + 1];

void backtrack(int x)
{
  if (x == n)
    ++m;
  else
    for (int y = 0; y < n; ++y)
    {
      if (C[y] || S[x + y] || D[x - y + n])
        continue;
      C[y] = true;
      S[x + y] = true;
      D[x - y + n] = true;
      backtrack(x + 1);
      C[y] = false;
      S[x + y] = false;
      D[x - y + n] = false;
    }
}

int main()
{
  for (int i = 0; i < n; ++i)
    C[i] = false;
  for (int i = 0; i < 2 * n + 1; ++i)
    S[i] = D[i] = false;
  for (int y = 0; y < (n % 2 == 0 ? n / 2 : n / 2 + 1); ++y)
  {
    m = 0;
    C[y] = true;
    S[0 + y] = true;
    D[0 - y + n] = true;
    backtrack(1);
    C[y] = false;
    S[0 + y] = false;
    D[0 - y + n] = false;
    P[y] = m;
  }
  for (int i = 0; i < n / 2; ++i)
    P[n - 1 - i] = P[i];
  m = 0;
  for (int i = 0; i < n; ++i)
    m += P[i];
  cout << n << "皇后问题的解法共有" << m << "种"<< endl;
  return 0;
}
