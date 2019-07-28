#include <iostream>

void Virgo()
{
  while (true)
    std::cout << "作" << std::endl;
}

void Libra()
{
  const int N = 42;
  double A[N] = {0};
  for (int R = 0; R < N; R = (R + 1) % N)
    std::cout << "似乎A[" << R << "]不如其他元素～" << std::endl;
}

void Capricorn()
{
  int black = 99;
  while (black)
    black++;
}

int main()
{
  // 请谨慎调用某些函数!
  return 0;
}
