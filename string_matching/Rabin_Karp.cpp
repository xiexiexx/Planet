#include <iostream>
#include <string>
#include <vector>

using namespace std;

const uint64_t L = 104729;
const uint16_t A = 256;

uint64_t Horner(const string& s, size_t m)
{
  uint64_t value = 0;
  for (size_t i = 0; i < m; ++i)
    value = (value * A + (uint8_t)s[i]) % L;
  return value;
}

double initialize(const string& p, const string& t, size_t m,
                  uint64_t& hp, uint64_t& ht)
{
  vector<uint64_t> power(m);
  auto iter = power.rbegin();
  uint64_t value = 1;
  for (auto riter = power.rbegin(); riter != power.rend(); ++riter)
  {
    *riter = value;
    value = (value * A) % L;
  }
  hp = ht = 0;
  for (size_t i = 0; i < m; ++i)
  {
    hp = (hp + power[i] * (uint8_t)p[i]) % L;
    ht = (ht + power[i] * (uint8_t)t[i]) % L;
  }
  return power.front();
}

size_t RK(const string& p, const string& t)
{
  size_t m = p.size();
  size_t n = t.size();
  if (n < m || m == 0)
    return n;
  uint64_t c = 1;
  for (size_t i = 1; i < m; ++i)
    c = (c * A) % L;
  uint64_t hp = Horner(p, m);
  uint64_t ht = Horner(t, m);
/*
  下列语句也可使用, 但性能略差.
  c = initialize(p, t, m, hp, ht);
*/
  for (size_t i = 0; i <= n - m; ++i)
  {
    if (hp == ht && t.compare(i, i + m, p, 0, m) == 0)
      return i;
    ht = (ht - (c * (uint8_t)t[i]) % L + L) % L;
    ht = (ht * A + (uint8_t)t[i + m]) % L;
  }
  return n;
}

int main()
{
  cout << RK("Algorithm_", "Data Structures and Algorithms") << endl;
  cout << RK("Algorithms", "Data Structures and Algorithms") << endl;
  cout << RK("Data", "Data Structures and Algorithms") << endl;
  return 0;
}
